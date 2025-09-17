#ifdef FUNCTION_DECLARE
	#define MODULE_GAMEMONITOR
	void DrawMonitorInfo();
	void RecvCommand_A8_Patch_ASM();
	void RecvCommand_A9_Patch_ASM();
	void RecvCommand_A7_Patch_ASM();
	void ResetMonitor();
#endif

#ifdef VARIABLE_DEFINE
	GVAR2(StatMonitor,		sMonitorStr[200]	,		 { {L'\0'}})
	GVAR (int,				nMonitors,			0)
	GVAR2(ToggleVar,		tStateMonitorToggle,	1,	0,	(BYTE)-1,	1,	"State Monitor")	
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET2(D2CLIENT , 0x6FB5DEB1, 0x6FB34391),   (DWORD)RecvCommand_A7_Patch_ASM,        9 ,   &fDefault},//…Ë÷√◊¥Ã¨1
{PatchCALL,   DLLOFFSET2(D2CLIENT , 0x6FB5DD74, 0x6FB34254),   (DWORD)RecvCommand_A8_Patch_ASM,        9 ,   &fDefault},//…Ë÷√◊¥Ã¨2
{PatchCALL,   DLLOFFSET2(D2CLIENT , 0x6FB5DD31, 0x6FB34211),   (DWORD)RecvCommand_A9_Patch_ASM,        9 ,   &fDefault},//Ω· ¯◊¥Ã¨

#endif

#ifdef CONFIG_LOAD

	{7, "StateMonitor",          0			},
	{1, "StateMonitorToggle",		&tStateMonitorToggle     },
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME
ResetMonitor();

#endif

#ifdef INIT_VALUE

memset( sMonitorStr ,  0 , sizeof(sMonitorStr));
nMonitors = 0;

#endif

#ifdef FIX_VALUE


#endif
