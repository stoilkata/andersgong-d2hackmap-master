#ifdef FUNCTION_DECLARE
	#define MODULE_SHOWORBS
	void ShowLifePatch_ASM();
	void ShowManaPatch_ASM();
	void SetLifeManaShow();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tPermShowOrb,		1,	1,	(BYTE)-1,	 1,  "Perm Show Life/Mana" , &SetLifeManaShow)

#endif

#ifdef PATH_INSTALL

	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FAD76B5, 0x6FB1D765),    (DWORD)ShowLifePatch_ASM,           5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FAD7767, 0x6FB1D817),    (DWORD)ShowManaPatch_ASM,           5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
{1, "PermShowOrbsToggle",    &tPermShowOrb       },

#endif


#ifdef RUN_ONCE
	SetLifeManaShow();

#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
