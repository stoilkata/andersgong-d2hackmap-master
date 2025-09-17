#ifndef MAX_ITEM_HTN
#define MAX_ITEM_HTN 6000
#endif

#ifdef FUNCTION_DECLARE
	#define MODULE_ITEMINGROUND
	BOOL  CheckItemVisible(UnitAny *pItem);
    void RecvCommand_PickUp_Patch_ASM();
    void PickLoop();
#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tShowIdentifiedItem,  1,	0,	(BYTE)-1,		1,	"Show Identified items")
GVAR2(ToggleVar,    tHiddenItems,         1,	1,	VK_ADD,	1,	"Show hidden items")
 
GVAR2(char, anItemPicks[MAX_ITEM_HTN][8][2][7][4], { 0 })
GVAR2(ToggleVar,    tAutoPickItems,         1,  0, (BYTE)-1,      1, "Auto Pick Item")
#endif

#ifdef PATH_INSTALL

{
  PatchJMP, DLLOFFSET2(D2CLIENT, 0x6FB34BA4, 0x6FB6C284), (DWORD)RecvCommand_PickUp_Patch_ASM,5, & fDefault
},
#endif

#ifdef CONFIG_LOAD
  {1, "ShowIdentifiedItem",    &tShowIdentifiedItem	 },
  {1, "HiddenItemsToggle",     &tHiddenItems         },
  {5, "ImportItem",       &anItemPicks,       4, {MAX_ITEM_HTN , 8 , 2 , 7} },
  {1, "AutoPickItemToggle",     &tAutoPickItems },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP
    PickLoop();
#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE
memset(anItemPicks, -1, sizeof(anItemPicks));
#endif

#ifdef FIX_VALUE


#endif
