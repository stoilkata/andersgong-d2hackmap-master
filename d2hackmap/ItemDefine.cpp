#include "stdafx.h"

#ifdef MODULE_ITEMDEFINE

//物品定义相关

int GetItemIndex(int pos)
{
    /*
    weapon.txt 一共308行，去掉表头和Expansion两行，剩下是306
    armor.txt 一共204行，去掉表头和Expansion两行，剩下是202
    上面两个加起来是508，而gold在misc.txt里的序号是15(从0开始)，所以txtno=306+202+15=523，index就是15+2000=2015
    */
	return (pos < *p_D2WeaponsTxts) ? pos :((pos -= *p_D2WeaponsTxts) < *p_D2ArmorTxts) ? pos+1000 : pos - *p_D2ArmorTxts + 2000;
}

BYTE GetItemColour(UnitAny *pItem,DWORD arridx) {
	ItemTxt *pItemTxt = D2GetItemTxt( pItem->dwTxtFileNo );

	if ( pItemTxt->nType==4 ) {//gold
		return (D2GetUnitStat(pItem, STAT_GOLD, 0) >= (int)dwGoldGoodNum) ? anGoldGoodCol[arridx] : anGoldPoorCol[arridx];
	}

	if ( pItemTxt->nType == 74) {//rune
		DWORD dwRuneNo = (pItemTxt->szCode[1]-'0')*10+(pItemTxt->szCode[2]-'0')-1;
		if ( dwRuneNo < 100 ) return anRuneColours[dwRuneNo][arridx];
	}

	int index = GetItemIndex(pItem->dwTxtFileNo);
	if ( index >2999 ) index= 2999;

	DWORD dwQuality = (pItem->pItemData->dwQuality-1)&7;
	if ( arridx>0 ){
		BYTE nHiddenLevel = anItemHideLevel[index][dwQuality];//小于隐藏等级的隐藏
		if (nHiddenLevel!=(BYTE)-1 && ( pItem->pItemData->dwItemLevel < (DWORD)(nHiddenLevel>99?0:nHiddenLevel) )  ) return (BYTE)-2;
	}
	int socknum = D2GetUnitStat(pItem, STAT_NUMSOCKETS, 0);
	if( socknum > 6) socknum = 6;
	char color = anItemColours[index][dwQuality][!!D2CheckItemFlag(pItem, ITEMFLAG_ETHEREAL, 0, "?")][socknum][arridx];
	return (BYTE)color;
}


void SwitchItemMode(){
	DWORD lastmode = nItemShowMode;
	nItemShowMode = (++nItemShowMode)%4 ;
	if(nItemShowMode==0)nItemShowMode=1;
	wchar_t temp[512];
	wsprintfW(temp, L"<Hackmap>: Switch to Item Show Mode  %d to %d",lastmode, nItemShowMode);
	D2ShowPartyMessage(temp, 0);
}



#endif