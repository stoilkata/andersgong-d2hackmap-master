#ifdef FUNCTION_DECLARE
	#define MODULE_ULCPATH
	void ULCPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tULCMask,				1,	0,	(BYTE)-1,		1	,"ULC Mask Toggle" )
 
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB5F134, 0x6FB35634),    (DWORD)ULCPatch_ASM,                    6 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
{1, "ULCMaskToggle",	 &tULCMask       },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
