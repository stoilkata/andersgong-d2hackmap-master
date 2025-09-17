#include "stdafx.h"

#ifdef MODULE_ITEMINGROUND

BOOL  CheckItemVisible(UnitAny *pItem){
	// false 不显示 true 显示
	if( tHiddenItems.isOn ) return TRUE;

	//已辨识物品隐藏判定
	if( tShowIdentifiedItem.isOn && fPlayerInTown && pItem->pItemData->dwQuality>=3){
		if( D2CheckItemFlag(pItem, ITEMFLAG_IDENTIFIED, 0, "?") ) return TRUE;
	}

	//神符之语不隐藏
	if ( D2CheckItemFlag(pItem, ITEMFLAG_RUNEWORD, 0, "?") ) return TRUE;

	BYTE nColour = GetItemColour( pItem , nItemShowMode );
	if ( nColour == 0xFE ) return FALSE;
	return TRUE;

}

#define D2TXTCODE(x) ( ((x)&0xff)<<24 | ((x)>>8&0xff)<<16 | ((x)>>16&0xff)<<8 | ((x)>>24&0xff) )
BYTE GetItemPicks(UnitAny* pItem, DWORD arridx)
{
	ItemTxt* pItemTxt = D2GetItemTxt(pItem->dwTxtFileNo);

    if (!pItemTxt) return 0;

	int index = GetItemIndex(pItem->dwTxtFileNo);
	if (index > MAX_ITEM_HTN - 1) index = MAX_ITEM_HTN - 1;

	DWORD dwQuality = (pItem->pItemData->dwQuality - 1) & 7;

	int socknum = D2GetUnitStat(pItem, STAT_NUMSOCKETS, 0);

	char color = anItemPicks[index][dwQuality][!!D2CheckItemFlag(pItem, ITEMFLAG_ETHEREAL, 0, "?")][socknum][arridx];
	return (BYTE)color;
}

WORD GetUnitPositionX(UnitAny* pUnit)
{
	//return D2GetUnitPosX(pItem->pMonPath);
	DWORD dwUnitType = pUnit->dwUnitType;
	if (dwUnitType == UNITNO_PLAYER
		|| dwUnitType == UNITNO_MONSTER
		|| dwUnitType == UNITNO_MISSILE)
		return (WORD)D2GetUnitPosX(pUnit->pMonPath);
	else
		return (WORD)pUnit->pItemPath->dwPosX;
}

WORD GetUnitPositionY(UnitAny* pUnit)
{
	//return D2GetUnitPosY(pItem->pMonPath);
	DWORD dwUnitType = pUnit->dwUnitType;
	if (dwUnitType == UNITNO_PLAYER
		|| dwUnitType == UNITNO_MONSTER
		|| dwUnitType == UNITNO_MISSILE)
		return (WORD)D2GetUnitPosY(pUnit->pMonPath);
	else
		return (WORD)pUnit->pItemPath->dwPosY;
}

DWORD GetDistance(LONG x1, LONG y1, LONG x2, LONG y2)
{
	return (DWORD)::sqrt((double)(((int)x1 - (int)x2) * ((int)x1 - (int)x2) + ((int)y1 - (int)y2) * ((int)y1 - (int)y2)));
}

DWORD GetItemMapDistanceFrom(UnitAny* pItem) // Player's distance from a position
{
	return GetDistance(PLAYER->pMonPath->wPosX, PLAYER->pMonPath->wPosY, pItem->pItemPath->dwPosX, pItem->pItemPath->dwPosY);
}

UnitAny* EnumStorageDirectBag(DWORD itemqulity, DWORD TxtNoNeedImport, BYTE* itloc)//在1-8
{
	if (!PLAYER || itemqulity != 2)return NULL;

	UnitAny* pItem = D2GetFirstItemInInv(PLAYER->pInventory);
	if (!pItem)
		return NULL;

	return NULL;
}

static UnitAny* FindClosestItemGround(DWORD range)
{
	DrlgRoom1* pRoom1 = PLAYER->pMonPath->pRoom1;
	if (!pRoom1 || !pRoom1->pRoom2)
		return FALSE; // not

	DWORD DD2BR1stitemgrounddistance = MAXDWORD;
	UnitAny* ret = NULL;

	for (DWORD i = 0; i < pRoom1->dwRoomsNear; i++)
	{
		for (UnitAny* pUnit = pRoom1->paRoomsNear[i]->pUnitFirst; pUnit; pUnit = pUnit->pListNext)
		{
			if (pUnit && pUnit->dwUnitType == UNITNO_ITEM)
			{
				DWORD dis = GetItemMapDistanceFrom(pUnit);
				if (dis < range &&
					(
						GetItemPicks(pUnit, 0) == 1
						|| GetItemPicks(pUnit, 0) == 2
						||
						(EnumStorageDirectBag(pUnit->pItemData->dwQuality, pUnit->dwTxtFileNo, NULL)
							&& GetItemPicks(pUnit, 0) != 3)
						)
					)
				{
					if (dis < DD2BR1stitemgrounddistance)
					{
						DD2BR1stitemgrounddistance = dis;
						ret = pUnit;
					}
				}
			}
		}
	}
	return ret;
}

BOOL GoToEntity(UnitAny* pUnit, BOOL bShowClientMove)
{
	BYTE aPacket[16] = { 0 };
	aPacket[0] = 0x04;
	::memcpy(aPacket + 1, &pUnit->dwUnitType, 4);
	::memcpy(aPacket + 5, &pUnit->dwUnitId, 4);

	D2SendPacket(9, 0, aPacket);
	return TRUE;
}

BOOL PickGroundItem(UnitAny* pItem, BOOL bToCursor)
{
	if (!pItem || !pItem->dwUnitId)
		return FALSE;

	if (GetItemMapDistanceFrom(pItem) > 5)
	{
		GoToEntity(pItem, TRUE);
		return TRUE;
	}

	BYTE aPacket[13] = { 0 };
	aPacket[0] = 0x16;
	aPacket[1] = 0x04;
	::memcpy(aPacket + 5, &pItem->dwUnitId, 4);
	if (bToCursor)aPacket[12] = 1;
	D2SendPacket(13, 0, aPacket);
	return TRUE;
}

void PickLoop()
{
	if (tAutoPickItems.isOn == FALSE)return;

	UnitAny* pItem = FindClosestItemGround(5);

	if (pItem)
	{
		BOOL ToCursor = FALSE;
		if (GetItemPicks(pItem, 0) == 2
			||
			(EnumStorageDirectBag(pItem->pItemData->dwQuality, pItem->dwTxtFileNo, NULL)
				&& GetItemPicks(pItem, 0) != 3)
			)ToCursor = TRUE;

		PickGroundItem(pItem, ToCursor);
	}
}

void __fastcall Deal9C(UnitAny* pItem)
{
	if (tAutoPickItems.isOn && pItem && PLAYER && PLAYER->pInventory)
	{
		if (GetItemPicks(pItem, 0) == 2)
		{
			for (UnitAny* ptItem = D2GetFirstItemInInv(PLAYER->pInventory); ptItem; ptItem = D2GetNextItemInInv(ptItem))
			{
				ItemTxt* txt = D2GetItemTxt(ptItem->dwTxtFileNo);
				if (txt && txt->dwCode[0] == D2TXTCODE('box '))
				{
					BYTE aPacket[9] = { 0x2A,0 };
					::memcpy(aPacket + 1, &pItem->dwUnitId, 4);//物品ID
					::memcpy(aPacket + 5, &ptItem->dwUnitId, 4);//cubeid
					D2SendPacket(9, 0, aPacket);
					ItemTxt* txt = D2GetItemTxt(pItem->dwTxtFileNo);
					if (txt)
					{
						wchar_t* TTT = D2GetLocaleText(txt->wLocaleTxtNo);
						D2ShowGameMessage(TTT, 0);
					}
					return; //点进赫拉迪克方块
				}
			}
		}
		else
		{
			UnitAny* pBag = EnumStorageDirectBag(pItem->pItemData->dwQuality, pItem->dwTxtFileNo, NULL);
			if (pBag && GetItemPicks(pItem, 0) != 3)
			{
				BYTE aPacket[17] = { 0x1f,0 };
				::memcpy(aPacket + 1, &pItem->dwUnitId, 4);
				::memcpy(aPacket + 5, &pBag->dwUnitId, 4);
				//return D2Net::D2NetSendPacketToServer(0, aPacket, 17);
				D2SendPacket(17, 0, aPacket);

				ItemTxt* txt = D2GetItemTxt(pItem->dwTxtFileNo);
				if (txt)
				{
					wchar_t* TTT = D2GetLocaleText(txt->wLocaleTxtNo);
					D2ShowGameMessage(TTT, 0);
				}
				return;
			}
		}
	}
}

__declspec(naked) void RecvCommand_PickUp_Patch_ASM()
{
	__asm
	{
		pushad
		mov ecx, esi
		call Deal9C
		popad
		pop esi
		add esp, 0x18
		retn
	}
}
#endif
