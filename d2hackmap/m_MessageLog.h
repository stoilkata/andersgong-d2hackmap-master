
#ifdef FUNCTION_DECLARE
	#define MODULE_MESSAGELOG
	void MessageLogPatch1_ASM();
	void MessageLogPatch2_ASM();
	void LogExitMessage();
#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tLogMessage,		1,	0,	(BYTE)-1,	1,0)
 GVAR (DWORD,		dwMessageFileSize,		1048576)
#endif

#ifdef PATH_INSTALL
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB2D8AD, 0x6FB25F10),    (DWORD)MessageLogPatch1_ASM,            6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB2D673, 0x6FB25CD3),    (DWORD)MessageLogPatch2_ASM,            5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD

  {1, "MessageLogToggle",    &tLogMessage},
  {2, "MessageLogFileSize",  &dwMessageFileSize,4},
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME
	LogExitMessage();

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
