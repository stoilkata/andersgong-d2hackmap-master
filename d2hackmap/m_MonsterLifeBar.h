
#ifdef FUNCTION_DECLARE
	#define MODULE_MONSTERLIFEBAR
	void MonsterDescCommaPatch1_ASM();
	void MonsterDescCommaPatch2_ASM();
	void MonsterDescCommaPatch3_ASM();
	void MonsterNamePatch_ASM();
	void InitTCList();
	MonTC *GetTcLevel(WORD tcno , DWORD mlvl);
	void LifeBarPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tMonsterLevel,				1,	0,	(BYTE)-1,	1	,"Monster Level")
GVAR2(ToggleVar,	tMonsterTC,					1,	0,	(BYTE)-1,	1	,0)
GVAR2(ToggleVar,	tMonsterRuneTC,				1,	0,	(BYTE)-1,	1	,0)
GVAR2(ToggleVar,	tMonsterResists,			1,	0,	(BYTE)-1,	1	,0)
GVAR2(ToggleVar,	tMonsterHPPercent,		    1,	0,	(BYTE)-1,	1	,0)
GVAR2(ToggleVar,	tMonsterDistance,			1,	0,	(BYTE)-1,	1	,0)
GVAR2(ToggleVar,	tMonsterID,					1,	0,	(BYTE)-1,	1	,0)
GVAR (BYTE,			nLifeBarTrans,				(BYTE)-1)
GVAR (BYTE,			nLifeBarColour,				(BYTE)-1)
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET2(D2WIN,    0x6F8F34D3, 0x6F8F4063),    (DWORD)LifeBarPatch_ASM,                6 ,   &fDefault},
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FACFE3B, 0x6FAD3CFB),    (DWORD)MonsterDescCommaPatch1_ASM,      5 ,   &fDefault},//给怪物的增强属性增加分隔符
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FACFF25, 0x6FAD3DE5),    (DWORD)MonsterDescCommaPatch2_ASM,      5 ,   &fDefault},//给怪物的增强属性增加分隔符
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB70C01, 0x6FACA651),    (DWORD)MonsterDescCommaPatch3_ASM,      6 ,   &fDefault},//给怪物的增强属性增加分隔符
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB70B5F, 0x6FACA5AF),    (DWORD)MonsterNamePatch_ASM,			  5 ,   &fDefault},

#endif

#ifdef CONFIG_LOAD
  {1, "MonsterTCToggle",         &tMonsterTC         },
  {1, "MonsterRuneTCToggle",     &tMonsterRuneTC     },
  {1, "MonsterLevelToggle",      &tMonsterLevel      },
  {1, "MonsterResistsToggle",    &tMonsterResists    },                                       
  {1, "MonsterHPPercentToggle",  &tMonsterHPPercent  },
  {1, "MonsterDistanceToggle",   &tMonsterDistance   },
  {1, "MonsterIDToggle",		 &tMonsterID		 },
  {2, "LifeBarTransparency",     &nLifeBarTrans  ,   1 },
  {2, "LifeBarColour",           &nLifeBarColour ,   1 },

#endif


#ifdef RUN_ONCE
InitTCList();

#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
