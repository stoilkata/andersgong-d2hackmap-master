#ifdef FUNCTION_DECLARE
	#define MODULE_TRANSGOLDHELP
	void SetGoldPatch_ASM();
	void SetDefaultGoldPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 
#endif

#ifdef PATH_INSTALL

{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB6FDF6, 0x6FAC97F6),      (DWORD)SetGoldPatch_ASM,		6 , &fDefault},//����ת�ƵĽ��ֵ
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB734DB, 0x6FACCEDB),      (DWORD)SetDefaultGoldPatch_ASM, 5 , &fDefault},//����Ĭ��ֵ
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
