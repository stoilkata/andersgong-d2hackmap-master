#ifdef FUNCTION_DECLARE
	#define MODULE_ENVIRONMENT
	void WeatherPatch_ASM();
	void LightingPatch_ASM();
	void InfravisionPatch_ASM();
	void __stdcall ShakeScreenPatch(DWORD *pPosX, DWORD *pPosY);
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tFullVisuals,			1,	0, (BYTE)-1,		1,	0)
GVAR2(ToggleVar,	tWeather,				1,	0, (BYTE)-1,		1,	0)
GVAR2(ToggleVar,	tLightRadiu,			1,	0, (BYTE)-1,		1,	0)
GVAR2(ToggleVar,	tInfravision,			1,	1, (BYTE)-1,		1,	0)
GVAR2(ToggleVar,	tScreenshake,			1,	0, (BYTE)-1,		1,	0)
GVAR2(BYTE,			afMonsterCorpses[1000]	,	    {0})
GVAR2(BYTE,			afMissileCorpses[1000]	,	    {0})
GVAR2(ToggleVar,    tHiddenCorpse,        1,  0, (BYTE)-1,  1,	0)

#endif

#ifdef PATH_INSTALL

  {PatchFILL,   DLLOFFSET2(D2CLIENT, 0x6FB125C4, 0x6FB231A4),    INST_NOP,                               2 ,   &fDefault}, //floors inside
  {PatchFILL,   DLLOFFSET2(D2CLIENT, 0x6FB1260A, 0x6FB231EA),    INST_NOP,                               2 ,   &fDefault}, //walls inside

  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB59A37, 0x6FAD33A7),    (DWORD)LightingPatch_ASM,               6 ,   &fDefault},
  {PatchJMP,    DLLOFFSET2(D2COMMON, 0x6FDBCCB6, 0x6FD80C96),    (DWORD)WeatherPatch_ASM,                5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FAF42A2, 0x6FAF52F2),    (DWORD)ShakeScreenPatch,                5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB16625, 0x6FB64A25),    (DWORD)InfravisionPatch_ASM,            5 ,   &fDefault}, 
#endif

#ifdef CONFIG_LOAD
  {1, "FullVisualsToggle",		&tFullVisuals   },
  {1, "WeatherToggle",			&tWeather		},
  {1, "LightRadiusToggle",		&tLightRadiu    },
  {1, "InfravisionToggle",		&tInfravision   },
  {1, "ScreenShakeToggle",		&tScreenshake   },

  {5, "MissileCorpses",         &afMissileCorpses,    1,{1000}},
  {5, "MonsterCorpses",         &afMonsterCorpses,    1,{1000}},
  {1, "HiddenCorpsesToggle",    &tHiddenCorpse      },


#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE
  
  memset(afMonsterCorpses,    1,        sizeof(afMonsterCorpses));
  memset(afMissileCorpses,    1,        sizeof(afMissileCorpses));

#endif

#ifdef FIX_VALUE
	
  if ( tWeather.isLoad==FALSE ){

	  tWeather.isOn = tFullVisuals.isOn;
	  tWeather.key = tFullVisuals.key;

  }

  if ( tLightRadiu.isLoad==FALSE ){

	  tLightRadiu.isOn = tFullVisuals.isOn;
	  tLightRadiu.key = tFullVisuals.key;

  }

  if ( tInfravision.isLoad==FALSE ){

	  tInfravision.isOn = tFullVisuals.isOn;
	  tInfravision.key = tFullVisuals.key;

  }

  if ( tScreenshake.isLoad==FALSE ){

	  tScreenshake.isOn = tFullVisuals.isOn;
	  tScreenshake.key = tFullVisuals.key;

  }
  

#endif
