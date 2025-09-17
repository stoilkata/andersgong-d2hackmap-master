
#ifdef FUNCTION_DECLARE
	#define MODULE_SKIPNPCMESSAGE
	void NPCQuestMessageStartPatch_ASM();
	void NPCQuestMessageEndPatch1_ASM();
	void NPCQuestMessageEndPatch2_ASM();
	void NPCMessageLoopPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

	GVAR (DWORD,		mSkipQuestMessage,			0)

#endif

#ifdef PATH_INSTALL

  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FAFBB07, 0x6FB2EB87),    (DWORD)NPCQuestMessageStartPatch_ASM,           6 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FAF8BD6, 0x6FB2B4C6),    (DWORD)NPCQuestMessageEndPatch1_ASM,            8 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FAF819F, 0x6FB2A9CF),    (DWORD)NPCQuestMessageEndPatch2_ASM,            5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB2E9B7, 0x6FB27737),    (DWORD)NPCMessageLoopPatch_ASM,					6 ,   &fDefault},
#endif

#ifdef CONFIG_LOAD
	{2, "SkipQuestMessage",   &mSkipQuestMessage,   4},

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
