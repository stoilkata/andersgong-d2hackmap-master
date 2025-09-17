#ifdef FUNCTION_DECLARE
	#define MODULE_ITEMSOCKETPROTECT
	void SocketProtectPatch1_ASM();
	void SocketProtectPatch2_ASM();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tSocketProtect,				1,	0,	(BYTE)-1,	1 , "Socket protect")
 
#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB49174, 0x6FB4D544),    (DWORD)SocketProtectPatch1_ASM,         6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB46FAB, 0x6FB4B4FB),    (DWORD)SocketProtectPatch2_ASM,         6 ,   &fDefault},
#endif

#ifdef CONFIG_LOAD

{1, "SocketProtectToggle",   &tSocketProtect   },
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
