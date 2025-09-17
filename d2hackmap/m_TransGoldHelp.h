#ifdef FUNCTION_DECLARE
	#define MODULE_TRANSGOLDHELP
	void SetGoldPatch_ASM();
	void SetDefaultGoldPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 
#endif

#ifdef PATH_INSTALL

{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB6FDF6, 0x6FAC97F6),      (DWORD)SetGoldPatch_ASM,		6 , &fDefault},//设置转移的金额值
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB734DB, 0x6FACCEDB),      (DWORD)SetDefaultGoldPatch_ASM, 5 , &fDefault},//设置默认值
#endif

#ifdef CONFIG_LOAD


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
