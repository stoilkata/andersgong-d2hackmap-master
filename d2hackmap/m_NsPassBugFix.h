#ifdef FUNCTION_DECLARE
	#define MODULE_NSPASSBUGFIX
	void NsPassingActBugFixPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FAF5564, 0x6FAEE7EB),    (DWORD)NsPassingActBugFixPatch_ASM,       9 ,   &fDefault},//-ns bugfix for d2loader  

#endif

#ifdef CONFIG_LOAD


#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
