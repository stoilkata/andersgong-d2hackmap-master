
#ifdef FUNCTION_DECLARE
	#define MODULE_QUESTPROTECT
	void DrawQuestPagePatch_ASM();
	void ReSetTimer();
	void InitBugInfo();
	void SetBugQuestStatus();
	void ShowBugInfo() ;
	void RecvCommand_5D_Patch_ASM();
	void RecvCommand_89_Patch_ASM();
	void CheckUnitKM();
#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tBugKM,				1,	0,	(BYTE)-1,	1, "Bug KM Protect" , &ReSetTimer)
GVAR2(ToggleVar,	tBugKD,				1,	0,	(BYTE)-1,	1, "Bug KD Protect" , &ReSetTimer)
GVAR2(ToggleVar,	tBugKB,				1,	0,	(BYTE)-1,	1, "Bug KB Protect" , &ReSetTimer)
GVAR2(ToggleVar,	tBugAutoQuit,	    1,	1,	(BYTE)-1,	1, "Bug Auto Quit Toggle"	,&ReSetTimer)
GVAR (DWORD,		dwBugAlertTimes,			10)
GVAR2(ToggleVar,	tAlertNoBug,		1,	1,	(BYTE)-1,	1, 0)
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FACF7C9, 0x6FB3E0C9),    (DWORD)DrawQuestPagePatch_ASM,          6 ,   &fDefault},

{PatchCALL,   DLLOFFSET2(D2CLIENT , 0x6FB5F8F0, 0x6FB35E00),   (DWORD)RecvCommand_5D_Patch_ASM,        5 ,   &fDefault},
{PatchCALL,   DLLOFFSET2(D2CLIENT , 0x6FB023B0, 0x6FB191A0),   (DWORD)RecvCommand_89_Patch_ASM,        5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
  {1, "BugKMToggle",          &tBugKM         },
  {1, "BugKDToggle",          &tBugKD         },
  {1, "BugKBToggle",          &tBugKB         },
  {1, "BugAutoQuitToggle",    &tBugAutoQuit   },
  {2, "BugAlertTimes",        &dwBugAlertTimes ,4 },
  {1, "AlertNoBug",           &tAlertNoBug    },
#endif


#ifdef RUN_ONCE

SetBugQuestStatus();
#endif

#ifdef RUN_LOOP
CheckUnitKM();
ShowBugInfo();

#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE
InitBugInfo();

#endif
