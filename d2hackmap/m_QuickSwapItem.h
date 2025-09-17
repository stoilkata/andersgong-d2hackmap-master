
#ifdef FUNCTION_DECLARE
	#define MODULE_QUICKSWAPITEM

	void RButtonUpHandlerPatch_ASM();
	void RButtonInTradePatch_ASM();

	void CtrlClickHandlerPatch_ASM();
	void LButtonUpHandlerPatch_ASM();
	
	void DealCtrlClick();
#endif

#ifdef VARIABLE_DEFINE

    GVAR2(ToggleVar,	tRightClickSwap,    1,	1,	(BYTE)-1,	1 ,	"Right Click Swap")
	GVAR2(ToggleVar,	tCtrlClickSwap,     1,	0,	(BYTE)-1,	1 ,	"Ctrl Click Swap")
	GVAR2(ToggleVar,	tQuickDropToggle,	1,	0,	(BYTE)-1,	1 , "Quick Drop")

#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FAF4630, 0x6FAF5680),    (DWORD)RButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, 
  {PatchJMP,    DLLOFFSET2(D2CLIENT, 0x6FB3B976, 0x6FB3FC36),    (DWORD)RButtonInTradePatch_ASM,         5 ,   &fDefault}, 
	
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB46CCE, 0x6FB4B21E),    (DWORD)CtrlClickHandlerPatch_ASM,       6 ,   &fDefault}, 
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB4B7F9, 0x6FB4FBC9),    (DWORD)LButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, //家里箱子和身上箱子之间
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB4B2D4, 0x6FB4F6A4),    (DWORD)LButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, //cube和身上箱子之间
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB4C81F, 0x6FB50BEF),    (DWORD)LButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, //左边空地和身上箱子之间
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB4BC16, 0x6FB4FFE6),    (DWORD)LButtonUpHandlerPatch_ASM,       5 ,   &fDefault}, //交易界面和身上箱子之间

#endif

#ifdef CONFIG_LOAD
  {1, "RightClickSwapToggle",  &tRightClickSwap   },
  {1, "CtrlClickSwapToggle",   &tCtrlClickSwap    },
  {1, "QuickDropToggle",       &tQuickDropToggle  },
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP

DealCtrlClick();
#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
