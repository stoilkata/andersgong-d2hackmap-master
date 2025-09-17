#ifdef FUNCTION_DECLARE
	#define MODULE_AUTOMAPBLOB
	void ForceDrawBlob_ASM();
	void DrawBlobPath_ASM();
	void MixedBlobColPatch_ASM();
	void DrawPartyPlayerBlobPatch_ASM();
	void HostilePlayerColor_ASM();
	void DrawPlayerTextPatch_ASM();
	void ResetMonsterColours();
	void MonsterBlobDescPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

GVAR2(ToggleVar,	tAutomapCorpse,		  1,  0, (BYTE)-1, 1, 0)
GVAR2(ToggleVar,    tAutomapMonsters,     1,  0, (BYTE)-1, 1, 0)
GVAR2(ToggleVar,    tAutomapChests,       1,  0, (BYTE)-1, 1, 0)
GVAR2(ToggleVar,    tAutomapMissiles,     1,  0, (BYTE)-1, 1, 0)
GVAR2(ToggleVar,    tAutomapItems,        1,  0, (BYTE)-1, 1, "Show automap items")

GVAR (BYTE,			nHostileMissileColor,		 0x62)
GVAR (BYTE,			nGuidedMissileColor,		 0x5B)
GVAR (BYTE,			nTracerMissileColor,		 0xFF)
GVAR (BYTE,			nOtherMissileColor,			 0xFF)
GVAR (BYTE,			nClosedChestColor,				9)
GVAR (BYTE,			nLockedChestColor,				9)
GVAR (BYTE,			nNormalCorpseColor,				8)
GVAR (BYTE,			nBossCorpseColor,					8)
GVAR (BYTE,			nMinionCorpseColor,				8)
GVAR (BYTE,			nChampionCorpseColor,			8)
GVAR (BYTE,			nMonsterNormalColor,		 0x62)
GVAR (BYTE,			nMonsterBossColor,			 0x5b)
GVAR (BYTE,			nMonsterMinionColor,		 0x5b)
GVAR (BYTE,			nMonsterChampColor,			 0x5b)
GVAR (BYTE,			nSuperUniqueColor,		 (BYTE)-1)
GVAR (BYTE,			nNeutralPlayerColor,		 0x62)
GVAR (BYTE,			nHostilePlayerColor,		 0x5b)
GVAR (BYTE,			nFriendMinionColor,			 0x7f)
GVAR (BYTE,			nPlayerMinionColor,			 0xcb)
GVAR (BYTE,			nPartyTextColour,				2)
GVAR (BYTE,			nNeutralTextColour,				9)
GVAR (BYTE,			nHostileTextColour,				1)
GVAR (BYTE,			nMonsterTextCol,				1)
GVAR2(wchar_t,		awszEnchantDescs[50][20]	,	{L'\0'})
GVAR2(wchar_t,		awszAuraDescs[7][20]	,		{L'\0'})
GVAR2(wchar_t,		awszImmuneDescs[6][20]	,		{L'\0'})
GVAR2(BYTE,			anMonsterCorpseColors[1000]	,   {0})
GVAR2(BYTE,			anMissileColours[1000]	,	    {0})
GVAR2(ToggleVar,	tBossNameToggle,			1,	0,	(BYTE)-1,	1 , 0)
GVAR2(BYTE,			anMonsterColours[1000]	,   {0})
GVAR (BYTE,			nSuperUniqueDescFont,			0)
#endif

#ifdef PATH_INSTALL

	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB11AC4, 0x6FB22F24),    (DWORD)ForceDrawBlob_ASM,           6 ,   &fDefault},
	{PatchJMP,    DLLOFFSET2(D2CLIENT, 0x6FB0F1C0, 0x6FB1FED0),    (DWORD)DrawBlobPath_ASM,            6 ,   &fDefault},
	{PatchJMP,    DLLOFFSET2(D2CLIENT, 0x6FB11688, 0x6FB22638),    (DWORD)MixedBlobColPatch_ASM,       6 ,   &fDefault},    
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB10BD8, 0x6FB21758),    (DWORD)DrawPartyPlayerBlobPatch_ASM,5 ,   &fDefault},
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB1175D, 0x6FB2270D),    (DWORD)HostilePlayerColor_ASM,      6 ,   &fDefault},
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB11CD3, 0x6FB23133),    (DWORD)DrawPlayerTextPatch_ASM,     11,   &fDefault},
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB11B67, 0x6FB22FC7),    (DWORD)MonsterBlobDescPatch_ASM,    5,    &fDefault},
#endif

#ifdef CONFIG_LOAD

	{2, "AutomapPartyDefault",      &fAutomapPartyDefault , 1 },
    {2, "AutomapNamesDefault",      &fAutomapNamesDefault , 1 },

	{1, "BossNameToggle",			&tBossNameToggle    },
	

	{3, "UnitBlobFiles",            &aszUnitBlobFiles ,   5,  {50}},
    {3, "PlayerBlobFile",           &aszUnitBlobFiles[0], 1,  {50}},
    {3, "MonsterBlobFile",          &aszUnitBlobFiles[1], 1,  {50}},
    {3, "ObjectBlobFile",           &aszUnitBlobFiles[2], 1,  {50}},
    {3, "MissileBlobFile",          &aszUnitBlobFiles[3], 1,  {50}},
    {3, "ItemBlobFile",             &aszUnitBlobFiles[4], 1,  {50}},
    {3, "BossBlobFile",             &aszUnitBlobFiles[6], 1,  {50}},
    {3, "NpcBlobFile",              &aszUnitBlobFiles[7], 1,  {50}},
    {3, "MyBlobFile",               &aszUnitBlobFiles[8], 1,  {50}},
    {3, "CorpseBlobFile",           &aszUnitBlobFiles[9], 1,  {50}},

	
  {1, "AutomapCorpsesToggle",    &tAutomapCorpse     },
  {1, "AutomapMonstersToggle",   &tAutomapMonsters   },
  {1, "AutomapChestsToggle",     &tAutomapChests     },
  {1, "AutomapMissilesToggle",   &tAutomapMissiles     },
  {1, "AutomapItemsToggle",      &tAutomapItems      },
                                 
  {5, "MonsterColours",          &anMonsterColours,    1,{1000}},
  {5, "MonsterCorpseColours",    &anMonsterCorpseColors, 1,{1000}},
  {5, "MissileColours",          &anMissileColours,    1,{1000}},
  
                                 
  {2, "HostileMissileColour",    &nHostileMissileColor,  1 },
  {2, "GuidedMissileColour",     &nGuidedMissileColor, 1 },
  {2, "TracerMissileColour",     &nTracerMissileColor, 1 },
  {2, "OtherMissileColour",      &nOtherMissileColor,  1 },
                                 
  {2, "ClosedChestColour",       &nClosedChestColor,   1 },
  {2, "LockedChestColour",       &nLockedChestColor,   1 },
  {2, "NormalCorpseColour",      &nNormalCorpseColor,  1 },
  {2, "BossCorpseColour",        &nBossCorpseColor , 1 },
  {2, "MinionCorpseColour",      &nMinionCorpseColor,  1 },
  {2, "ChampionCorpseColour",    &nChampionCorpseColor,  1 },
  {2, "NormalMonsterColour",     &nMonsterNormalColor, 1 },
  {2, "BossMonsterColour",       &nMonsterBossColor  , 1 },
  {2, "MinionMonsterColour",     &nMonsterMinionColor, 1 },
  {2, "ChampionMonsterColour",   &nMonsterChampColor,  1 },
  {2, "SuperUniqueColour",       &nSuperUniqueColor  , 1 },
  {2, "Act5BarbarianColour",     &anMonsterColours[522], 1 },
  {2, "NeutralPlayerColour",     &nNeutralPlayerColor, 1 },
  {2, "HostilePlayerColour",     &nHostilePlayerColor, 1 },
  {2, "FriendMinionColour",      &nFriendMinionColor,  1 },
  {2, "PlayerMinionColour",      &nPlayerMinionColor,  1 },
  {2, "PartyPlayerTextColour",   &nPartyTextColour,    1 },
  {2, "NeutralPlayerTextColour", &nNeutralTextColour,  1 },
  {2, "HostilePlayerTextColour", &nHostileTextColour,  1 },
  {2, "SuperUniqueDescFont",	 &nSuperUniqueDescFont,1 },

  {2, "MonsterDescColour",        &nMonsterTextCol  , 1 },
  {4, "EnchantmentDescs",         &awszEnchantDescs,    50, {20 }},
  {4, "AuraDescs",                &awszAuraDescs,     7,  {20 }},
  {4, "ImmunityDescs",            &awszImmuneDescs,   6,  {20 }},
                                  
  {4, "ExtraStrongDesc",          &awszEnchantDescs[5], 1,  {20 }},
  {4, "ExtraFastDesc",            &awszEnchantDescs[6], 1,  {20 }},
  {4, "CursedDesc",               &awszEnchantDescs[7], 1,  {20 }},
  {4, "MagicResistantDesc",       &awszEnchantDescs[8], 1,  {20 }},
  {4, "FireEnchantedDesc",        &awszEnchantDescs[9], 1,  {20 }},
  {4, "ChampionDesc",             &awszEnchantDescs[16],  1,  {20 }},
  {4, "LightningEnchantedDesc",   &awszEnchantDescs[17],  1,  {20 }},
  {4, "ColdEnchantedDesc",        &awszEnchantDescs[18],  1,  {20 }},
  {4, "ThiefDesc",                &awszEnchantDescs[24],  1,  {20 }},
  {4, "ManaBurnDesc",             &awszEnchantDescs[25],  1,  {20 }},
  {4, "TeleportationDesc",        &awszEnchantDescs[26],  1,  {20 }},
  {4, "SpectralHitDesc",          &awszEnchantDescs[27],  1,  {20 }},
                                  
  {4, "StoneSkinDesc",            &awszEnchantDescs[28],  1,  {20 }},
  {4, "MultipleShotsDesc",        &awszEnchantDescs[29],  1,  {20 }},
  {4, "GhostlyDesc",              &awszEnchantDescs[36],  1,  {20 }},
  {4, "FanaticDesc",              &awszEnchantDescs[37],  1,  {20 }},
  {4, "PossessedDesc",            &awszEnchantDescs[38],  1,  {20 }},
  {4, "BerserkerDesc",            &awszEnchantDescs[39],  1,  {20 }},
                                  
  {4, "MightAuraDesc",            &awszAuraDescs[0],    1,  {20 }},
  {4, "HolyFireAuraDesc",         &awszAuraDescs[1],    1,  {20 }},
  {4, "BlessedAimAuraDesc",       &awszAuraDescs[2],    1,  {20 }},
  {4, "HolyFreezeAuraDesc",       &awszAuraDescs[3],    1,  {20 }},
  {4, "HolyShockAuraDesc",        &awszAuraDescs[4],    1,  {20 }},
  {4, "ConvictionAuraDesc",       &awszAuraDescs[5],    1,  {20 }},
  {4, "FanaticismAuraDesc",       &awszAuraDescs[6],    1,  {20 }},
                                  
  {4, "PhysicalImmunityDesc",     &awszImmuneDescs[0],  1,  {20 }},
  {4, "MagicImmunityDesc",        &awszImmuneDescs[1],  1,  {20 }},
  {4, "FireImmunityDesc",         &awszImmuneDescs[2],  1,  {20 }},
  {4, "LightningImmunityDesc",    &awszImmuneDescs[3],  1,  {20 }},
  {4, "ColdImmunityDesc",         &awszImmuneDescs[4],  1,  {20 }},
  {4, "PoisonImmunityDesc",       &awszImmuneDescs[5],  1,  {20 }},
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef INIT_VALUE
	memset( aszUnitBlobFiles ,    '\0' ,      sizeof(aszUnitBlobFiles) );
	memset(anMonsterCorpseColors, -1,       sizeof(anMonsterCorpseColors));
	memset(anMissileColours,    -1,       sizeof(anMissileColours));
	memset( awszAuraDescs ,            0 ,      sizeof(awszAuraDescs) );
	memset( awszEnchantDescs ,         0 ,      sizeof(awszEnchantDescs) );
	memset( awszImmuneDescs ,          0 ,      sizeof(awszImmuneDescs) );
	ResetMonsterColours();
#endif

#ifdef FIX_VALUE
	if ( !aszUnitBlobFiles[6][0] ){
		strcpy(aszUnitBlobFiles[6],aszUnitBlobFiles[1]);
	}
	if ( !aszUnitBlobFiles[7][0] ){
		strcpy(aszUnitBlobFiles[7],aszUnitBlobFiles[1]);
	}
	if ( !aszUnitBlobFiles[8][0] ){
		strcpy(aszUnitBlobFiles[8],aszUnitBlobFiles[0]);
	}
	if ( !aszUnitBlobFiles[9][0] ){
		strcpy(aszUnitBlobFiles[9],aszUnitBlobFiles[1]);
	}
	if ( nMonsterTextCol>12 ) nMonsterTextCol= 0 ;

	if ( nSuperUniqueDescFont>12 ) nSuperUniqueDescFont = 0;

#endif
