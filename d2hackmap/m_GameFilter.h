#ifdef FUNCTION_DECLARE
	#define MODULE_GAMEFILTER
	void D2MCPPacketHandler_05_Patch_ASM();
	void CreateGameBoxPatch_ASM();
	void __stdcall DestroyGamelistPatch( D2EditBox* pListBox );
	void GameListRefreshTimePatch_ASM();
	void DrawGameListPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

  GVAR (BOOL,			fGameFilter,		FALSE)
#endif

#ifdef PATH_INSTALL

	{PatchCALL,   DLLOFFSET2(D2WIN ,		 0x6F8F8911, 0x6F8EEC61),   (DWORD)DrawGameListPatch_ASM,           5,   &fGameFilter},

#endif

#ifdef PATH_INSTALL2
	
    {PatchCALL,   DLLOFFSET2(D2MCPCLIENT, 0x6FA263E0, 0x6FA27450),   (DWORD)D2MCPPacketHandler_05_Patch_ASM,     5 ,   &fGameFilter},
	{PatchCALL,   DLLOFFSET2(D2MULTI,	 0x6F9E49EF, 0x6F9DAD8F),   (DWORD)CreateGameBoxPatch_ASM,				5 ,   &fGameFilter},
	{PatchCALL,   DLLOFFSET2(D2MULTI,	 0x6F9E1DC3, 0x6F9D8413),   (DWORD)DestroyGamelistPatch,				5 ,   &fGameFilter},
	{PatchCALL,   DLLOFFSET2(D2MULTI,	 0x6F9DDF4E, 0x6F9E21EE),   (DWORD)GameListRefreshTimePatch_ASM,		7 ,   &fGameFilter},
	
#endif

#ifdef CONFIG_LOAD

{2, "GameFilterSupport",     &fGameFilter,  4},

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
