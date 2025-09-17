#ifdef FUNCTION_DECLARE
	#define MODULE_PERMSHOWITEM
	void	PermShowItemsPatch1_ASM();
	void	PermShowItemsPatch2_ASM();
	void	PermShowItemsPatch3_ASM();
	void	PermShowItemsPatch4_ASM();	

#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tPermShowItems,				1,	0,	(BYTE)-1,	1,	"Perm show items")
 GVAR2(ToggleVar,	tLockAltToggle,				1,	0,	(BYTE)-1,	1,	"Lock Alt")

#endif

#ifdef PATH_INSTALL
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB73D4E, 0x6FACD74E),    (DWORD)PermShowItemsPatch1_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB70E9A, 0x6FACA89A),    (DWORD)PermShowItemsPatch1_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB09483, 0x6FAFEA13),    (DWORD)PermShowItemsPatch2_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB0908A, 0x6FAFE61A),    (DWORD)PermShowItemsPatch3_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB56BA3, 0x6FB13443),    (DWORD)PermShowItemsPatch4_ASM,         6 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
	{1, "PermShowItemsToggle",		&tPermShowItems     },
	{1, "LockAltToggle",			&tLockAltToggle     },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
