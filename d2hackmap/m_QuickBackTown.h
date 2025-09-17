#ifdef FUNCTION_DECLARE
	#define MODULE_QUICKBACKTOWN
	void RecvCommand_60_Patch_ASM();
	void BackToTown();
#endif

#ifdef VARIABLE_DEFINE

 GVAR (BOOL,			fBackToTown,				FALSE)
 GVAR2(ToggleVar,		tBackToTown,		2,	0, (BYTE)-1,		1,	0,		&BackToTown)
 GVAR (DWORD,			nTownportalAlertNums,			(DWORD)-1)
#endif

#ifdef PATH_INSTALL

{PatchCALL,   DLLOFFSET2(D2CLIENT , 0x6FB5D2F0, 0x6FB33630),   (DWORD)RecvCommand_60_Patch_ASM,        5 ,   &fDefault},



#endif

#ifdef CONFIG_LOAD
	{1, "QuickBackToTownKey",   &tBackToTown		    	},
	{2, "TownportalNumsAlert",  &nTownportalAlertNums, 4    },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP

	if( fPlayerInTown )fBackToTown = FALSE;

#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
