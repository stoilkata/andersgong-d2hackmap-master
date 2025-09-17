#ifdef FUNCTION_DECLARE
	#define MODULE_ITEMDEFINE
	void SwitchItemMode();
	BYTE GetItemColour(UnitAny *pItem,DWORD arridx);
	int GetItemIndex(int pos);
#endif

#ifdef VARIABLE_DEFINE
GVAR (DWORD,		dwGoldGoodNum,					   0)


GVAR (char,			anGoldGoodCol[4],		  {(char)-1})
GVAR (char,			anGoldPoorCol[4],		  {(char)-1})
GVAR2(char,			anRuneColours[100][4]	,		 {0})
GVAR2(char,			anItemColours[3000][8][2][7][4]	,{0})
GVAR2(char,			anItemHideLevel[3000][8]		,{0})

GVAR2(ToggleVar,	tSwitchItemMode,		2,	0,	(BYTE)-1,		1,	0,	&SwitchItemMode)
GVAR (DWORD,	    nItemShowMode,				   1)


#endif

#ifdef PATH_INSTALL


#endif

#ifdef CONFIG_LOAD

  {5, "ItemColours",       &anItemColours,       4, {3000 , 8 , 2 , 7}},
  {5, "WeaponColours",     &anItemColours,       4, {1000 , 8 , 2 , 7}},
  {5, "ArmorColours",      &anItemColours[1000], 4, {1000 , 8 , 2 , 7}},
  {5, "MiscItemColours",   &anItemColours[2000], 4, {1000 , 8 , 2 , 7}},
  {5, "RuneColours",       &anRuneColours,       4, {100} },

  {5, "CharmColours",      &anItemColours[2095], 4, {3, 8, 2, 7} },
  {5, "RejuvPotColours",   &anItemColours[2007], 4, {2, 8, 2, 7} },
  {5, "HealingPotColours", &anItemColours[2079], 4, {5, 8, 2, 7} },
  {5, "ManaPotColours",    &anItemColours[2084], 4, {5, 8, 2, 7} },
  {5, "AmethystColours",   &anItemColours[2049], 4, {5, 8, 2, 7} },
  {5, "TopazColours",      &anItemColours[2054], 4, {5, 8, 2, 7} },
  {5, "SapphireColours",   &anItemColours[2059], 4, {5, 8, 2, 7} },
  {5, "EmeraldColours",    &anItemColours[2064], 4, {5, 8, 2, 7} },
  {5, "RubyColours",       &anItemColours[2069], 4, {5, 8, 2, 7} },
  {5, "DiamondColours",    &anItemColours[2074], 4, {5, 8, 2, 7} },
  {5, "SkullColours",      &anItemColours[2089], 4, {5, 8, 2, 7} },
  {5, "ItemHideLvl",       &anItemHideLevel,     1, {3000 , 8} },
                                 
  {5, "GoodGoldColour",      &anGoldGoodCol,     4,{1}},
  {5, "PoorGoldColour",      &anGoldPoorCol,     4,{1}},
  {2, "GoodGoldNumber",      &dwGoldGoodNum,     4 },
  {2, "DefaultItemShowMode", &nItemShowMode,     4 },
  {1, "SwitchItemShowMode",  &tSwitchItemMode    },
	


#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE
  memset(anGoldGoodCol,     -1,       sizeof(anGoldGoodCol));
  memset(anGoldPoorCol,     -1,       sizeof(anGoldPoorCol));
  memset(anItemColours,     -1,       sizeof(anItemColours));
  memset(anRuneColours,     -1,       sizeof(anRuneColours));
  memset(anItemHideLevel,   -1,       sizeof(anItemHideLevel));

#endif

#ifdef FIX_VALUE
 if ( nItemShowMode>3 )nItemShowMode = 3;

#endif
