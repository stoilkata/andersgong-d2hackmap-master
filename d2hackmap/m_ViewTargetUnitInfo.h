
#ifdef FUNCTION_DECLARE
	#define MODULE_VIEWTARGETUNITINFO
	void GetViewingStatsPlayerPatch1_ASM();
	void GetViewingStatsPlayerPatch2_ASM();
	UnitAny* GetViewStatUnit();
	UnitAny*  GetViewEquUnit();
	void SetViewUnit();
	void ViewUnit(int nType);

	void GetUnitDrawEquipItemPatch_ASM();
	void GetUnitDrawItemDescPath_ASM();
	void GetUnitTestHasItem_ASM();
	void GetUnitDrawInvItemPatch_ASM();
	void GetUnitProtectClickEquipPatch_ASM();
	void GetUnitProtectClickInvPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tViewEquipmentKey,	    3,	0,	(BYTE)-1,  1,	0, &ViewUnit ,UIVAR_INVENTORY)
 GVAR2(ToggleVar,	tViewPlayerStatsKey,    3,	0,	(BYTE)-1,	 1, 0, &ViewUnit ,UIVAR_STATS)
#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB6CEA6, 0x6FB6F646),    (DWORD)GetViewStatUnit,                 5 ,   &fDefault}, //draw stat
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB6D743, 0x6FB6FEE3),    (DWORD)GetViewStatUnit,                 5 ,   &fDefault}, //draw stat
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB6CBA3, 0x6FB6F343),    (DWORD)GetViewStatUnit,                 5 ,   &fDefault}, //draw stat
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FADFE63, 0x6FAE4E43),    (DWORD)GetViewingStatsPlayerPatch1_ASM, 6 ,   &fDefault}, //drawstat
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB6C524, 0x6FB6ECC4),    (DWORD)GetViewingStatsPlayerPatch2_ASM, 6 ,   &fDefault}, //draw stat

  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB453E2, 0x6FB497B2),    (DWORD)GetUnitDrawEquipItemPatch_ASM,   6 ,   &fDefault}, //draw equip items
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB44AB4, 0x6FB48E84),    (DWORD)GetUnitDrawItemDescPath_ASM,     6 ,   &fDefault}, //desc item
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB43A6F, 0x6FB47E3F),    (DWORD)GetUnitTestHasItem_ASM,          5 ,   &fDefault}, //test has item for desc item
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB4A695, 0x6FB4EA65),    (DWORD)GetUnitDrawInvItemPatch_ASM,     5 ,   &fDefault}, //draw inv items

  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB49120, 0x6FB4D4F0),    (DWORD)GetUnitProtectClickEquipPatch_ASM, 5 ,   &fDefault}, //protect click equip
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB4908B, 0x6FB4D45B),    (DWORD)GetUnitProtectClickInvPatch_ASM, 7 ,   &fDefault}, //protect click inv
  

#endif

#ifdef CONFIG_LOAD

  {1, "ViewEquipmentKey",      &tViewEquipmentKey    },
  {1, "ViewPlayerStatsKey",    &tViewPlayerStatsKey  },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP
SetViewUnit();

#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
