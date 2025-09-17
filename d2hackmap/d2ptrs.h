#ifndef D2_PTR_H
typedef enum D2Version {
    D2_VER_113C,
    D2_VER_113D,

    UNKNOWN = -1,
  }eGameVersion;

  enum DllBase { //Ϊ���ҷ���෽��, ��ȫ��ַ��ʽ���庯����ַ��������Ҫע��˴���ֵ�뷴����ļ��ж�Ӧ
    DLLBASE_D2CLIENT = 0x6FAB0000,
    DLLBASE_D2COMMON = 0x6FD50000,
    DLLBASE_D2GFX = 0x6FA80000,
    DLLBASE_D2WIN = 0x6F8E0000,
    DLLBASE_D2LANG = 0x6FC00000,
    DLLBASE_D2CMP = 0x6FE10000,
    DLLBASE_D2MULTI = 0x6F9D0000,
    DLLBASE_BNCLIENT = 0x6FF20000,
    DLLBASE_D2NET = 0x6FBF0000, 
    DLLBASE_STORM = 0x6FFB0000,//6FBF0000  , ��D2NET��ͻ���޸�ֵ
    DLLBASE_FOG = 0x6FF50000,
    DLLBASE_D2GAME = 0x6FC20000,
    DLLBASE_D2LAUNCH = 0x6FA40000,
	DLLBASE_D2MCPCLIENT = 0x6FA20000
  };

  enum DllNo {DLLNO_D2CLIENT, DLLNO_D2COMMON, DLLNO_D2GFX, DLLNO_D2WIN, DLLNO_D2LANG, DLLNO_D2CMP, DLLNO_D2MULTI, DLLNO_BNCLIENT, DLLNO_D2NET, DLLNO_STORM, DLLNO_FOG, DLLNO_D2GAME , DLLNO_D2LAUNCH,DLLNO_D2MCPCLIENT};
  //#define DLLOFFSET(a1,b1) ((DLLNO_##a1)|(( ((b1)<0)?(b1):((b1)-DLLBASE_##a1) )<<8))
  extern DWORD CalcFuncOffset_X(DWORD dwNo, DWORD dwBase, int iValue);
  extern DWORD Map_D2Version();
  #define DLLOFFSET(a1,b1) CalcFuncOffset_X(DLLNO_##a1, DLLBASE_##a1, b1)
  #define DLLOFFSET2(a1,b1,b2) ((D2_VER_113D == Map_D2Version()) ? (CalcFuncOffset_X(DLLNO_##a1, DLLBASE_##a1, b2)) : (CalcFuncOffset_X(DLLNO_##a1, DLLBASE_##a1, b1)))

  #define D2FUNCPTR(d1,o1,v1,t1,t2) typedef t1 D2##v1##_t t2; extern D2##v1##_t *D2##v1;
  #define D2FUNCPTR2(d1,o1,o2,v1,t1,t2) typedef t1 D2##v1##_t t2; extern D2##v1##_t *D2##v1;
  #define D2VARPTR(d1,o1,v1,t1)     typedef t1 p_D2##v1##_t;    extern p_D2##v1##_t *p_D2##v1;
  #define D2VARPTR2(d1,o1,o2,v1,t1)     typedef t1 p_D2##v1##_t;    extern p_D2##v1##_t *p_D2##v1;
  #define D2ASMPTR(d1,o1,v1)        extern volatile DWORD vD2##v1;
  #define D2ASMPTR2(d1,o1,o2,v1)        extern DWORD vD2##v1;

  #define D2_PTR_H

#else

  #define D2FUNCPTR(d1,o1,v1,t1,t2) D2##v1##_t *D2##v1 = (D2##v1##_t *)DLLOFFSET(d1,o1);
  #define D2FUNCPTR2(d1,o1,o2,v1,t1,t2) D2##v1##_t *D2##v1 = (D2##v1##_t *)DLLOFFSET2(d1,o1,o2);
  #define D2VARPTR(d1,o1,v1,t1)     p_D2##v1##_t *p_D2##v1 = (p_D2##v1##_t *)DLLOFFSET(d1,o1);
  #define D2VARPTR2(d1,o1,o2,v1,t1)     p_D2##v1##_t *p_D2##v1 = (p_D2##v1##_t *)DLLOFFSET2(d1,o1,o2);
  #define D2ASMPTR(d1,o1,v1)        volatile DWORD vD2##v1 = DLLOFFSET(d1,o1);
  #define D2ASMPTR2(d1,o1,o2,v1)        DWORD vD2##v1 = DLLOFFSET2(d1,o1,o2);
	
#endif

//���ļ���Ҫ������cpp���ظ�����һ��

D2ASMPTR(D2CLIENT,  0xEEEEEE00, ERR)
D2ASMPTR(D2CLIENT,  0xEEEEEE00, StartOfPtr)

D2FUNCPTR2(D2CLIENT, 0x6FB2D850, 0x75EB0+DLLBASE_D2CLIENT, ShowGameMessage,    void __stdcall, (wchar_t* text, int nColor) )
D2FUNCPTR2(D2CLIENT, 0x6FB2D610, 0x75C70+DLLBASE_D2CLIENT, ShowPartyMessage,   void __stdcall, (wchar_t* text, int nColor))

D2FUNCPTR2(D2CLIENT, 0x6FAEB8B0, 0x6FAED660, ShowMap,            void __fastcall, ())
D2FUNCPTR2(D2CLIENT, 0x6FB12580, 0x73160+DLLBASE_D2CLIENT, RevealAutomapRoom,  void __stdcall, (DrlgRoom1 *room1, DWORD clipflag, AutomapLayer *layer))
D2FUNCPTR2(D2CLIENT, 0x6FB5C440, 0x6FB328C0, RecvCommand07,      void __fastcall, (BYTE *cmdbuf))
D2FUNCPTR2(D2CLIENT, 0x6FB5C3D0, 0x6FB32850, RecvCommand08,      void __fastcall, (BYTE *cmdbuf))
D2FUNCPTR2(D2CLIENT, 0x6FB0F6B0, 0x703C0+DLLBASE_D2CLIENT, NewAutomapCell,     AutomapCell * __fastcall, ())
D2FUNCPTR2(D2CLIENT, 0x6FB11320, 0x71EA0+DLLBASE_D2CLIENT, AddAutomapCell,     void __fastcall, (AutomapCell *cell, AutomapCell **node))

D2FUNCPTR2(D2CLIENT, 0x6FAEF6C0, 0x5BC20+DLLBASE_D2CLIENT, GetPlayerXOffset,   long __stdcall, ())
D2FUNCPTR2(D2CLIENT, 0x6FAEF6D0, 0x5BC30+DLLBASE_D2CLIENT, GetPlayerYOffset,   long __stdcall, ())

D2FUNCPTR2(D2CLIENT, 0x6FB72790, 0x1C190+DLLBASE_D2CLIENT, SetUiStatus,        DWORD __fastcall, (DWORD dwUiNo, DWORD howset, DWORD unknown1))


D2FUNCPTR2(D2CLIENT, 0x6FB3AFD0, 0x6FB65EE0, CalcShake,          void __stdcall, (DWORD *pPosX, DWORD *pPosY))
D2FUNCPTR2(D2CLIENT, 0x6FAD16A0, 0x8E3D0+DLLBASE_D2CLIENT, GetMonsterOwner,    DWORD __fastcall, (DWORD dwUnitId))
D2FUNCPTR2(D2CLIENT, 0x6FB55B40, 0x620D0+DLLBASE_D2CLIENT, GetUnitFromId,      UnitAny * __fastcall, (DWORD dwUnitId, DWORD dwUnitType)) //���ݱ�ź����ͻ�ȡ����,monster and palyer
D2FUNCPTR2(D2CLIENT, 0x6FB01A80, 0x17280+DLLBASE_D2CLIENT, GetSelectedUnit,    UnitAny * __stdcall, ())


D2FUNCPTR2(D2CLIENT, 0x6FB12710, 0x733D0+DLLBASE_D2CLIENT, InitAutomapLayerStub,   AutomapLayer* __fastcall, (DWORD nLayerNo)) //nLayerNo==>eax ���õ�ǰLayerָ��,�����ӦnLayerNoδ����,�����һ�������ڿͻ���
D2FUNCPTR2(D2CLIENT, 0x6FB6E400, 0x17C50+DLLBASE_D2CLIENT, CheckUiStatusStub,      DWORD __fastcall, (DWORD dwUiNo) )//dwUiNo ==> eax
D2FUNCPTR2(D2CLIENT, 0x6FB0F8D0, 0x6FB205E0, SetAutomapPartyStub	,   void __fastcall, (DWORD flag) )    //parm = flag  ==> esi 
D2FUNCPTR2(D2CLIENT, 0x6FB0F8A0, 0x6FB205B0, SetAutomapNamesStub ,   void __fastcall, (DWORD flag) )    //parm = flag  ==> esi 
D2FUNCPTR2(D2CLIENT, 0x6FB20C45, 0x6FB62525, ChatInputStub ,         void __stdcall, (D2MSG *pmsg) )  //�����ƫ����5������,ʹ���Զ����eax



D2FUNCPTR2(D2CLIENT, 0x6FAD3200, 0x6FB5E300, ItemProtect,		void __stdcall, (UnitAny *pUnit, DWORD dwType))
D2FUNCPTR2(D2CLIENT, 0x6FAD9250, 0x6FB1F300, DrawClient,         void __fastcall, ())   //******
D2FUNCPTR2(D2CLIENT, 0x6FABBE84, 0x6FABBD8C, Storm511,           void __stdcall, (D2MSG *pMsg) )



D2VARPTR2(D2CLIENT,  0x6FBCC1C0, 0x6FBCCF24, AutomapLayerList,   AutomapLayer *) //����AutomapLayer�б�
D2VARPTR2(D2CLIENT,  0x6FBCC1C4, 0x11CF28+DLLBASE_D2CLIENT, AutomapLayer,       AutomapLayer *) //��ǰ���ڵ�AutomapLayer

D2VARPTR2(D2CLIENT,  0x6FBCBBFC, 0x11D050+DLLBASE_D2CLIENT, PlayerUnit,         UnitAny *)
D2VARPTR2(D2CLIENT,  0x6FBCBC14, 0x11CB04+DLLBASE_D2CLIENT, RosterUnitList,     RosterUnit *) //����б�
D2VARPTR2(D2CLIENT,  0x6FBCC4D4, 0x6FBCCE30, PetUnitList,        PetUnit * ) //����ٻ����б�

D2VARPTR2(D2CLIENT,  0x6FBCC3B8, 0x6FBCD200, DrlgAct,            DrlgAct *)
D2VARPTR2(D2CLIENT,  0x6FBC9854, 0x1087B4+DLLBASE_D2CLIENT, Expansion,          DWORD ) // 1����Ƭ 0 ������Ƭ
D2VARPTR2(D2CLIENT,  0x6FBCC390, 0x6FBCD1D8, Difficulty,         BYTE) //��ǰ�Ѷ� 0 1 2
D2VARPTR2(D2CLIENT,  0x6FBCB980, 0x109738+DLLBASE_D2CLIENT, GameInfo,           GameStructInfo *)
D2VARPTR2(D2CLIENT,  0x6FBCC2AC, 0x11CE10+DLLBASE_D2CLIENT, Fps,                DWORD )
D2VARPTR2(D2CLIENT,  0x6FBC9804, 0x108764+DLLBASE_D2CLIENT, Ping,               DWORD )
D2VARPTR2(D2CLIENT,  0x6FBA8C9C, 0x6FBA79E0, ExitAppFlag,        DWORD)
D2VARPTR2(D2CLIENT,  0x6FBCC3A0, 0x6FBCD1E8, InGame,             BOOL ) //�Ƿ�����Ϸ��

D2VARPTR2(D2CLIENT,  0x6FBAADA8, 0x11C8B8+DLLBASE_D2CLIENT, AutomapOn,          DWORD) //С��ͼ�Ƿ��
D2VARPTR2(D2CLIENT,  0x6FBA16B0, 0xF34F8+DLLBASE_D2CLIENT, Divisor,            long)
D2VARPTR2(D2CLIENT,  0x6FBCC1F8, 0x11CF5C+DLLBASE_D2CLIENT, Offset,             D2_POINT)
D2VARPTR2(D2CLIENT,  0x6FBCC1E8, 0x6FBCCF4C, AutomapPos,         D2_POINT)
D2VARPTR2(D2CLIENT,  0x6FBCC230, 0x6FBCCF94, AutoMapSize,        D2_POINT) //��ͼ��С
D2VARPTR2(D2CLIENT,  0x6FBCC1B0, 0x6FBCCF14, MinmapType,         DWORD) // 1С��ͼ 0 ���ͼ
D2VARPTR2(D2CLIENT,  0x6FBCC228, 0x6FBCCF8C, MinimapOffset,      D2_POINT) //С��ͼ��Ե��ַ �����ͼΪ -16*-16

D2VARPTR2(D2CLIENT,  0x6FBCBEFC, 0x6FBCCA68, IsMapShakeOn,       BOOL)
D2VARPTR2(D2CLIENT,  0x6FBBB9DC, 0xFC3DC+DLLBASE_D2CLIENT, MapShakeY,          long)
D2VARPTR2(D2CLIENT,  0x6FBCBF00, 0x11CA6C+DLLBASE_D2CLIENT, MapShakeX,          long)

D2VARPTR2(D2CLIENT,  0x6FB8BC48, 0xF7034+DLLBASE_D2CLIENT, ScreenSizeX,        int ) //��Ļ���X 800*600   640*480
D2VARPTR2(D2CLIENT,  0x6FB8BC4C, 0xF7038+DLLBASE_D2CLIENT, ScreenSizeY,        int ) //��Ļ���Y 800*600   640*480
D2VARPTR2(D2CLIENT,  0x6FB8BC48, 0xF7034+DLLBASE_D2CLIENT, ScreenSize,         D2_POINT)  //��Ļ���X 800*600   640*480
D2VARPTR2(D2CLIENT,  0x6FBCB9A0, 0x11D354+DLLBASE_D2CLIENT, DrawOffset,         D2_POINT )//��ʾ��ƫ����
D2VARPTR2(D2CLIENT,  0x6FBA9E14, 0x6FBD3D64, InfoPositionX,      int) //��Ϸ��Ϣ��ʾX����
D2VARPTR2(D2CLIENT,  0x6FBCC21C, 0x6FBCCF80, InfoPositionY,      int) //��Ϸ��Ϣ��ʾY����

D2VARPTR2(D2CLIENT,  0x6FBC973B, 0x1018B3+DLLBASE_D2CLIENT, QuestData,          void *) //���������Ϣ��
D2VARPTR2(D2CLIENT,  0x6FBC973F, 0x6FBB18B7, GameQuestData,      void *) //����������Ϣ��
D2VARPTR2(D2CLIENT,  0x6FBD3395, 0x6FBD1865, QuestPage,          int)

D2VARPTR2(D2CLIENT,  0x6FBCC3A0, 0x6FBCD1E8, MButton,            BOOL )
D2VARPTR2(D2CLIENT,  0x6FBCEC80, 0x11D650+DLLBASE_D2CLIENT, LastChatMessage,    wchar_t)  
D2VARPTR2(D2CLIENT,  0x6FBCC028, 0x6FBCCAA4, ChatTextLength,         int)

D2VARPTR2(D2CLIENT,  0x6FBCB824, 0x11C94C+DLLBASE_D2CLIENT, MousePos,           D2_POINT_REV )//���λ��
D2VARPTR2(D2CLIENT,  0x6FB8BC54, 0x6FBA7F98, LastMousePos,		D2_POINT_REV )//�������λ��
D2VARPTR2(D2CLIENT,  0x6FB90EB8, 0xEE4AC+DLLBASE_D2CLIENT, CursorInvGridX,     DWORD)//������Ʒ��λ��
D2VARPTR2(D2CLIENT,  0x6FB90EBC, 0xEE4B0+DLLBASE_D2CLIENT, CursorInvGridY,     DWORD)//������Ʒ��λ��
D2VARPTR2(D2CLIENT,  0x6FBCBC38, 0x11CB28+DLLBASE_D2CLIENT, CurrentViewItem,    UnitAny*) //ѡ����ʾ����Ʒ

D2VARPTR2(D2CLIENT,  0x6FBCBBB0, 0x11D568+DLLBASE_D2CLIENT, GoldInTranBox,         int)
D2VARPTR2(D2CLIENT,  0x6FBCC4B0, 0x6FBCD008, ShowLifeStr,         BOOL)
D2VARPTR2(D2CLIENT,  0x6FBCC4B4, 0x6FBCD00C, ShowManaStr,         BOOL)

D2ASMPTR2(D2CLIENT,  0x6FBC3880, 0x6FBB8658, AutomapCellListBaseAddr)
D2ASMPTR2(D2CLIENT,  0x6FADB420, 0xA9480+DLLBASE_D2CLIENT, LoadUiImageFunc)

D2FUNCPTR2(D2COMMON, 0x6FD8E980, 0x1ADC0+DLLBASE_D2COMMON,   GetObjectTxt,         ObjectTxt * __stdcall, (DWORD objno))
D2FUNCPTR2(D2COMMON, 0x6FDBCB20, 0x6FD80B00,  GetLevelDefTxt,       LevelDefTxt* __fastcall, (DWORD levelno))
D2FUNCPTR2(D2COMMON, 0x6FDBCCC0, 0x6FD80CA0,   GetLevelTxt,          LevelTxt * __stdcall, (DWORD levelno))
D2FUNCPTR2(D2COMMON, 0x6FDC19A0, 0x6FDB2C70,   GetItemTxt,           ItemTxt * __stdcall, (DWORD itemno))
D2FUNCPTR2(D2COMMON, 0x6FDA3420, 0x6FDCB7E0,  GetTreasureClasses,   TreasureClass * __stdcall, (WORD tcno, DWORD lvlno))
D2FUNCPTR2(D2COMMON, 0x6FDA3370, 0x6FDCB630,  GetSuperUniqueTxt,    SuperUniqueTxt * __stdcall, (DWORD dwUniqueNo))

D2FUNCPTR2(D2COMMON, 0x6FD72640, 0x6FD90F00,  GetItemFileIndex,     DWORD __stdcall, (UnitAny *pItem) ) //pItem->pItemData->dwFileIndex


D2FUNCPTR2(D2COMMON, 0x6FD88710, 0x6FDA8080,  GetStatFromStatList,  BOOL __stdcall, (StatList *pStatList, DWORD dwStatNo, StatEx *pStatVal ,DWORD dwMask ) ) //�Ƿ��������,����õ�����ֵ
D2FUNCPTR2(D2COMMON, 0x6FD87EC0, 0x6FDA7830,   GetStatListWithFlag,  StatList *  __stdcall, (UnitAny *pUnit, DWORD dwStatNo, DWORD dwListFlag) )//
D2FUNCPTR2(D2COMMON, 0x6FD88B70, 0x6FDA84E0,   GetUnitStat,          int __stdcall, (UnitAny *pUnit, DWORD dwStatNo, WORD dwLayerNo))
D2FUNCPTR2(D2COMMON, 0x6FD88C20, 0x6FDA8590,   GetUnitBaseStat,      int __stdcall, (UnitAny *pUnit, DWORD dwStatNo, WORD dwLayerNo))//ֻ���ѯ��һ��statlist,����Ҵ󲿷������ܲ鵽
D2FUNCPTR2(D2COMMON, 0x6FD82330, 0x6FD68A20,  GetMonsterHpPercent,  int __stdcall, (UnitAny *pUnit) )//�������Ч


D2FUNCPTR2(D2COMMON, 0x6FD83CD0, 0x6FD7F310,   CheckUnitState,       BOOL __stdcall, (UnitAny *pUnit, DWORD dwStateNo))
D2FUNCPTR2(D2COMMON, 0x6FD7D0F0, 0x6FD7D7A0,   CheckQuestFlag,       BOOL __stdcall, ( void *pQuestData, DWORD dwQuestNo, DWORD dwCheckFlag ))
D2FUNCPTR2(D2COMMON, 0x6FD73940, 0x6FD92200,  CheckItemFlag,        BOOL __stdcall, (UnitAny *pItem, DWORD dwFlagMask, DWORD dwLineno, char *filename) )

D2FUNCPTR2(D2COMMON, 0x6FDA0150, 0x6FDC38F0,  CheckCorpseCanUse,    BOOL __stdcall, (UnitAny *pMon,DWORD flag))


D2FUNCPTR2(D2COMMON, 0x6FD79D60, 0x6FD98620,   GetItemValue,         int __stdcall, (UnitAny * pPlayer, UnitAny * pItem, DWORD dwDifficulty, void* questinfo, int value, DWORD dwFlag))
D2FUNCPTR2(D2COMMON, 0x6FD6DFB0, 0x6FD87820,  GetCursorItem,        UnitAny * __stdcall, (UnitInventory * ptInventory))//pUnit->pInventory->pCursorItem
D2FUNCPTR2(D2COMMON, 0x6FD6E190, 0x6FD87A00,   GetFirstItemInInv,    UnitAny * __stdcall, (UnitInventory* ptInventory)) // pUnit->pInventory->pFirstItem
D2FUNCPTR2(D2COMMON, 0x6FD6E8F0, 0x6FD88160,   GetNextItemInInv,     UnitAny * __stdcall, (UnitAny *pItem))
D2FUNCPTR2(D2COMMON, 0x6FD7FB60, 0x6FD66280,  GetBoxType,           DWORD __stdcall, (UnitAny * pUnit, BYTE invType, DWORD dwExpansion));//��������
D2FUNCPTR2(D2COMMON, 0x6FD6F1F0, 0x6FD88A60,  CheckInvLocation,     int __stdcall, (UnitInventory* pInventory, UnitAny *pItem, DWORD dwCursorGridX, DWORD dwCursorGridY, DWORD dwBoxType, int* GridCount, int* ItemCount, BYTE invType))

D2FUNCPTR2(D2COMMON, 0x6FD7D9B0, 0x6FDBD440,   GetDrlgLevel,         DrlgLevel * __fastcall, (DrlgMisc *drlgmisc, DWORD levelno))//����һ���µ�DrlgLevel�ṹ,���ڷ����
D2FUNCPTR2(D2COMMON, 0x6FD7E360, 0x6FDBDDF0,  InitDrlgLevel,        void __stdcall, (DrlgLevel *drlglevel))
D2FUNCPTR2(D2COMMON, 0x6FD8C000, 0x6FD73B80,  GetLevelIdFromRoom,   DWORD __stdcall, (DrlgRoom1 *pDrlgRoom1))


D2FUNCPTR2(D2COMMON, 0x6FD84B80, 0x6FDC7670,  GetUnitPosX,          DWORD __stdcall, (DynamicPath *pPath) ) //(Players, Monsters, Missiles) 
D2FUNCPTR2(D2COMMON, 0x6FD84BB0, 0x6FDC76A0,  GetUnitPosY,          DWORD __stdcall, (DynamicPath *pPath) ) //(Players, Monsters, Missiles) 

D2FUNCPTR2(D2COMMON, 0x6FDAE810, 0x6FD5CA80,  GetMinExpToLevel,     int __stdcall, (DWORD dwCharClass, DWORD dwLevel))

D2VARPTR2(D2COMMON,  0x6FDEFBA0, 0x6FDF4CBC, WeaponsTxts,         int)
D2VARPTR2(D2COMMON,  0x6FDEFBA8, 0xA4CC4+DLLBASE_D2COMMON, ArmorTxts,           int)
D2VARPTR2(D2COMMON,  0x6FDE9E1C, 0xA33F0+DLLBASE_D2COMMON, DataTables,        DWORD)
D2VARPTR2(D2COMMON,  0x6FDEFBD4, 0x6FDF4CF0, RuneWords,         DWORD)
D2VARPTR2(D2COMMON,  0x6FDEFBD8, 0x6FDF4CF4, RuneWordTxt,	   DWORD)

D2FUNCPTR2(D2GFX,  0x6FA87FB0, 0x6FA8B0C0,   GetHwnd,                HWND __stdcall, ())
D2FUNCPTR2(D2GFX,  0x6FA8BA30, 0x6FA88210,   DrawRectangle,          void __stdcall, (long dwXstart, long dwYstart, long dwXend, long dwYend, DWORD dwPal, DWORD dwTransLvl))
D2FUNCPTR2(D2GFX,  0x6FA8B9C0, 0x6FA881A0,   DrawLine,               void __stdcall, (long x1, long y1, long x2, long y2, DWORD dwColor, DWORD dwTransLvl))
D2FUNCPTR2(D2GFX,  0x6FA8B080, 0x6FA87E60,   DrawCellFile,           void __stdcall, (CellContext *context, DWORD xPos, DWORD yPos, DWORD dw1, DWORD dwTransLvl, BYTE *coltab))
D2FUNCPTR2(D2GFX,  0x6FA8AFF0, 0x6FA87DD0,   DrawAutomapCell,        void __stdcall, (CellContext *context, DWORD xpos, DWORD ypos, RECT *cliprect, DWORD dwTransLvl))
D2FUNCPTR2(D2GFX,  0x6FA87FC0, 0x6FA8B0D0,  MinimizeWindows,        void __stdcall, (DWORD dwFlag))

D2VARPTR2(D2GFX,  0x6FA9D66C, 0x6FA9D640, WinState,			DWORD)

D2FUNCPTR2(D2WIN,  0x6F8F2FA0, 0x6F8F3B30,   DrawText,               void __fastcall, (wchar_t *wStr, long xPos, long yPos, DWORD dwColor, DWORD dwAlign))
D2FUNCPTR2(D2WIN,  0x6F8F18F0, 0x6F8F2480,  DrawHoverText,          void __fastcall, (wchar_t *wStr, long xPos, long yPos, DWORD dwTran, DWORD dwColor))
D2FUNCPTR2(D2WIN,  0x6F8F2730, 0x6F8F32C0,  DrawUnitLifeBar,        DWORD __fastcall, (wchar_t *wStr ,long xPos, long yPos, DWORD dwColor, DWORD dwUnk1 ,DWORD dwUnk2) )
D2FUNCPTR2(D2WIN,  0x6F8F33A0, 0x6F8F3F30,  DrawHover,              void __fastcall, ()) //������ʾ�ַ���ĵط�������3��ֻ�������˱���,��ʾ���ȼ��ǳ���

D2FUNCPTR2(D2WIN,  0x6F8F2700, 0x6F8F3290,   GetTextAreaSize,        DWORD __fastcall, (wchar_t *wStr, DWORD* pWidth, DWORD* pHeight)) 
D2FUNCPTR2(D2WIN,  0x6F8F2FE0, 0x6F8F3B70,   SetTextFont,            DWORD __fastcall, (DWORD dwFont))
D2FUNCPTR2(D2WIN,  0x6F8F2B20, 0x6F8F36B0,  GetTextPixelLen,        DWORD __fastcall, (wchar_t *wStr) )//����������ֱܷ���ɫ���룬ֻ��������ɫ�ַ���

D2FUNCPTR2(D2WIN,  0x6F8F36A0, 0x6F8EEF00,  GetEditBoxText,         wchar_t* __fastcall, (D2EditBox* box))
D2FUNCPTR2(D2WIN,  0x6F8F3720, 0xEF80+DLLBASE_D2WIN,   SelectEditBoxText,      void __fastcall,  (D2EditBox* box))
D2FUNCPTR2(D2WIN,  0x6F8F5450, 0x6F8F0CE0,  AddEditBoxChar,         DWORD __fastcall, (D2EditBox* box, BYTE keycode))
D2FUNCPTR2(D2WIN,  0x6F8F59E0, 0xF320+DLLBASE_D2WIN,   DestroyEditBox,         DWORD __fastcall, (D2EditBox* box))
D2FUNCPTR2(D2WIN,  0x6F8F8490, 0x6F8EE5F0,  DestroyListBox,         void __stdcall,   (D2EditBox* box))

D2FUNCPTR2(D2WIN,  0x6F8F61B0, 0x11A10+DLLBASE_D2WIN,   CreateEditBox,          D2EditBox* __fastcall, (DWORD dwPosX, DWORD dwPosY, DWORD dwSizeX, DWORD dwSizeY, DWORD dwOffsetX, DWORD dwOffsetY, CellFile *pCellFile, DWORD dwReturnHandler, DWORD arg9, DWORD dwIsCloaked, void* buf))
D2FUNCPTR2(D2WIN,  0x6F8F4DF0, 0x6F8F0680,  SetEditBoxText,         void* __fastcall, (D2EditBox* box, wchar_t* wcszTxt))
D2FUNCPTR2(D2WIN,  0x6F8F3970, 0xF1D0+DLLBASE_D2WIN,   SetEditBoxProc,         void __fastcall, (D2EditBox* box, BOOL (__stdcall *FunCallBack)(D2EditBox*,DWORD,char*)))

D2ASMPTR2(D2WIN,  0x6F8E7720, 0x6F8E7710, ToggleSound)

D2VARPTR2(D2WIN,   0x6F9014B0, 0x8DB44+DLLBASE_D2WIN, FocusedControl,        D2EditBox*)

D2FUNCPTR2(D2CMP,  0x6FE21520, 0x6FE235B0,   DeleteCellFile,         void __stdcall, (CellFile *cellfile))
D2FUNCPTR2(D2CMP,  0x6FE21AC0, 0x6FE23B50,   InitCellFile,           void __stdcall, (void *cellfile, CellFile **outptr, char *srcfile, DWORD lineno, DWORD filever, char *filename))

D2FUNCPTR2(D2LANG, 0x9450+DLLBASE_D2LANG, 0x98A0+DLLBASE_D2LANG,   GetLocaleText,          wchar_t* __fastcall, (DWORD dwLocaleTxtNo))

D2VARPTR2(D2NET,  0x6FBFB244, 0x6FBFB244, UnkNetFlag,	   DWORD)
D2FUNCPTR2(D2NET,  0x7650+DLLBASE_D2NET, 0x6F20+DLLBASE_D2NET,   SendPacket,             void __stdcall, (size_t len, DWORD arg1, BYTE* buf))

D2VARPTR2(BNCLIENT,  0x6FF3F64C, 0x6FF3F618, BnChatMessage,     LPDWORD )

D2ASMPTR(D2CLIENT,  0xEEEEEEEE, EndOfPtr)

D2ASMPTR(D2CLIENT,  0xEEEEEE00, StartOfPtr2)

D2VARPTR2(D2MULTI,  0x6FA09CC0, 0x39FF0+DLLBASE_D2MULTI, GameListControl,       D2EditBox *)
D2VARPTR2(D2MULTI,  0x6F9E9C60, 0x19C60+DLLBASE_D2MULTI, EditboxPreferences,    void *)  //6F9E9C5C+4

D2ASMPTR(D2CLIENT,  0xEEEEEEEE, EndOfPtr2)

#undef D2FUNCPTR
#undef D2FUNCPTR2
#undef D2VARPTR
#undef D2VARPTR2
#undef D2ASMPTR
#undef D2ASMPTR2



