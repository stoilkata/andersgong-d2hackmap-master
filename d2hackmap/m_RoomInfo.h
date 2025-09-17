#ifdef FUNCTION_DECLARE
	#define MODULE_ROOMINFO
	void SetTickCount();
	void __fastcall DrawGameInfoPatch(DWORD dwFont) ;
	void DrawGameVersionPatch_ASM() ;
#endif

#ifdef VARIABLE_DEFINE

	GVAR2(ToggleVar,	tServerIp,			    1,	1,	(BYTE)-1,		1,	"Server Ip" )
	GVAR2(ToggleVar,	tGameTime,				1,	1,	(BYTE)-1,		1,	"Game Time" )
	GVAR2(ToggleVar,	tClock,					1,	1,	(BYTE)-1,		1,	"Clock" )
	GVAR2(ToggleVar,	tLayerLevelNo,			1,	0,	(BYTE)-1,		1,	"Layer LevelNo" )
	GVAR2(ToggleVar,	tAreaLevel,				1,	0,	(BYTE)-1,		1,	"Area Level" )
	GVAR2(ToggleVar,	tMousePosition,				1, 0, (BYTE)-1, 1, "Mouse Positon")
 
#endif

#ifdef PATH_INSTALL

	{PatchJMP,    DLLOFFSET2(D2CLIENT, 0x6FB126FE, 0x6FB2349E),    (DWORD)DrawGameInfoPatch,               5 ,   &fDefault},//游戏右上角信息显示
    {PatchCALL,    DLLOFFSET2(D2CLIENT, 0x6FB0FF18, 0x6FB20988),    (DWORD)DrawGameVersionPatch_ASM,            5 ,   &fDefault},//游戏右上角信息显示
#endif

#ifdef CONFIG_LOAD
  {1, "ServerIpToggle",			&tServerIp        },
  {1, "GameTimeToggle",         &tGameTime        },
  {1, "ClockToggle",            &tClock           },
  {1, "LayerLevelNoToggle",     &tLayerLevelNo    },
  {1, "AreaLevelToggle",        &tAreaLevel       },
  {1, "MousePositionToggle",        &tMousePosition       },

#endif


#ifdef RUN_ONCE
	SetTickCount();

#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
