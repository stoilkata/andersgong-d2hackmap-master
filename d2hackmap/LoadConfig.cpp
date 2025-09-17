#include "stdafx.h"
#include "JsonConfig.h"

#define CONFIG_LOAD
#include "Module.h"
#undef CONFIG_LOAD

void AddMinimapConfig( DWORD dwLevelNo , WORD wPointNo ,BYTE fFlag , BYTE nColour );
MinimapConfig aMinimapConfigs[140];//�������趨�Ĵ�ָ������

ToggleVar *tKeyEvent[100] = {{0}};
int nKeyCount = 0 ;

static char WarningMsg[200][100];
static int nMsgCount = 0 ;
static TreeNode *pTreeRoot = 0;

void InitValues(){

	memset( tKeyEvent ,       -1 ,      sizeof(tKeyEvent) );
	nKeyCount = 0 ;

	memset( WarningMsg ,        '\0' ,      sizeof(WarningMsg) );
	nMsgCount = 0 ;
	
	memset( aMinimapConfigs ,			0	,		sizeof(aMinimapConfigs) );
	#define INIT_VALUE
		#include "Module.h"
	#undef INIT_VALUE

}

void FixValues(){

	#define FIX_VALUE
		#include "Module.h"
	#undef FIX_VALUE

	//ǿ�����������Ĺ�Ĺ������ָ��
	AddMinimapConfig(46 ,300 ,1 ,(BYTE)-1);
	for (DWORD i=66 ; i<=72 ; i++ ){
		AddMinimapConfig(i ,300 ,1 ,(BYTE)-1);
	}

}


void InitKeyEvent(){
	for ( int i = 0; i < _ARRAYSIZE(aConfigVars); i++ ) {
		if( aConfigVars[i].type==1 ){
			ToggleVar *tgKey = (ToggleVar *)aConfigVars[i].pVar;

			if(tgKey->value==0 || tgKey->isOn>1 ){
				tgKey->value = tgKey->isOn?tgKey->isOn:1;
			}
			if( tgKey->isOn>1 ) tgKey->isOn = 1;

			if(tgKey->key != 0 && (tgKey->key != (BYTE)-1) ){

				tKeyEvent[nKeyCount] = tgKey;
				nKeyCount++;

			}
		}
	}

}

void AddMinimapConfig( DWORD dwLevelNo , WORD wPointNo ,BYTE fFlag , BYTE nColour ){
	
	MinimapConfig *pConfig = &aMinimapConfigs[dwLevelNo];
	if ( pConfig->nPoints>=30 ) return;
	int idx = pConfig->nPoints ;
	for ( int i=0;i<pConfig->nPoints ;i++){
		if ( wPointNo==pConfig->aPoint[i].wPointNo ) {
			idx = i ;
			break;
		}
	}
	pConfig->aPoint[idx].fFlag = fFlag ;
	pConfig->aPoint[idx].nColour = nColour ;
	pConfig->aPoint[idx].wPointNo = wPointNo ;
	if ( idx==pConfig->nPoints )pConfig->nPoints++;

}

void AddWarningMessage(char *msg , int flag=0){

	for( int i=0 ; i<nMsgCount ; i++){
		if( _stricmp( WarningMsg[i] , msg ) ==0 ){
			return;
		}
	}

	if (nMsgCount>=199) return ; 
	if (flag==0){
		sprintf(WarningMsg[nMsgCount], " Command -- %s -- unused , Check it ", msg);
	}else{
		strncpy( WarningMsg[nMsgCount] , msg , 99);
	}
	nMsgCount++;

}

void ShowWarningMessage(){

	if( fShowCheckInfo && nMsgCount > 0 ){
		for( int i=0 ; i<nMsgCount ; i++){
			ShowGameMessage(WarningMsg[i]);
		}
		memset( WarningMsg,			'\0',		sizeof(WarningMsg) );
		nMsgCount = 0 ;
	}

}

HANDLE OpenFileReadHelper(char *postfix)
{
	char filename[MAX_PATH];
	sprintf(filename,"%sd2hackmap.%s",szPluginPath,postfix);
	HANDLE hFile = OpenFileRead(filename);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		const char *szDefaultFileName[] = {"d2maphack", "maphack" , "hackmap"};
		for (int i = 0; i < ARRAYSIZE(szDefaultFileName); i++) {
			sprintf(filename,"%s%s.%s",szPluginPath,szDefaultFileName[i],postfix);
			hFile = OpenFileRead(filename);
			if ( hFile != INVALID_HANDLE_VALUE ) {
				break;
			}
		}
	}
	return hFile;
}


void DeleteTree(TreeNode *&node)
{
	if (!node) return;
	delete node->key;
	delete node->str;
	DeleteTree(node->left);
	DeleteTree(node->right);
	node->left = 0;
	node->right = 0;
	delete node;
}
TreeNode *&SearchTree(TreeNode *&node, char *key)
{
	if (!node) return node;
	int res = _stricmp(key, node->key);
	if (res < 0) return SearchTree(node->left, key);
	if (res > 0) return SearchTree(node->right, key);
	return node;
}
char isquote(char c)
{
	return ((c) == '"' || (c) == '`') ? c : 0;
}

void FilterSpace(char *line,char *temp){
	char *p = line;
	char *desc = temp;
	BOOL skipflag = true;
	while(*p){
		if(!isspace(*p) || !skipflag ){
			if( *p=='/' && *(p+1)=='/' ){
				*desc = '\0';	
				return;
			}else{
				if(isquote(*p)){
					skipflag = !skipflag;
				}
				*desc = *p;
				desc++;
			}
		}
		p++;
	}
	*desc = '\0';
}
void SplitLine(char *line , char *left , char *right){
	char temp[1024];
	FilterSpace( line,temp );//ȥ����Ч�ַ�
	strcpy( line ,temp );
	*left = '\0';
	*right = '\0';
	char *pt = strtok( temp, ":");
	if(pt){
		strcpy( left , pt );
		pt = strtok( NULL, ":");
		if(pt){
			strcpy( right , pt );
		}else{
			//û��:�ŷָ������]�����ָ�
			char *p=NULL;
			char *p2=temp;
			while(*p2){
				if(*p2==']') p=p2;
				p2++;
			}
			if(p){
				//����]
				p++;
				strcpy( right , p );
				*p = '\0';
				strcpy( left , temp );
			}

		}
	}
}
void ReplaceByVcb(char *dest){
	//����vcb�����滻�ַ���
	char temp[1024],word[1024];
	TreeNode **node;

	char *p = dest;
	char *pt = temp;
	char *pw = word;

	while( *p && !isalnum(*p) ){
		*pt++ = *p++;
	}

	while(1){
		if( *p && ( isalnum(*p) || isspace(*p) || *p=='_' || *p=='\'' || isquote(*p) ) ){
			*pw++ = *p;
		}else{
			*pw = '\0';
			pw = word;
			if(*pw){
				char *ptr = *(node = &SearchTree(pTreeRoot, word))? (*node)->str : word;
				pt = strcpy(pt, ptr) + strlen(ptr);
			}
			*pt++ = *p;
		}
		if(!*p){
			break;
		}
		p++;

	}
	strcpy( dest,temp );

}


void ConvertToD2String( wchar_t *dst , char  *src , int size)
{
  char ch = 0, col = 0, next;
  char hascolor = 0;
  wchar_t *pOld = dst;
  int sizecount = 0 ;
  ch = *src++;
  sizecount++;
  while(ch){
    if( ch=='%' ){
      next = *src;
      if(!next)break;
	  hascolor = 1;
      if ( isalpha(next) ){
        col = toupper(next)-'A'+10;
        src++;
      }else{
        col = (char)strtol(src,&src,10);
      }
      *dst++ = 0xff;
      *dst++ = 'c';
      *dst++ = '0'+col;
      ch = *src++;
      sizecount += 3;
    }else{
      *dst++ = ch;
      ch = *src++;
      sizecount++;
    }

  }
  if(hascolor==1){
	*dst++ = 0xff;
  }
  *dst = 0 ;
  if(sizecount>=size){
    *(pOld+size) = L'\0';
  }

}




int strtol2(int &num, char *&str, int base)
{
	char *p = str;
	num = strtol(str, &str, base);
	return (p != str);
}


BOOL StoreArrayConfig(ConfigVar *config ,int index ,int arrays, char *left , char *right){
	
	if ( config->anArrayMax[arrays] >0 ){
		char temp[1024];
		char *p = left ;
		char *pt = temp;
		int num1, num2;
		char errflag = 0;
		*pt = '\0';

		while (*p &&  *p != '['){
			p++;
		}

		if( *p=='[' ){
			errflag = 1 ;
			while ( *p && *p!=']'){
				*pt++ = *p++;
			}
			*pt = '\0';
			if (*p==']'){
				errflag = 0 ;
			}
		}
		if ( errflag ){
			return FALSE;
		}

		pt = temp ;
		while( *pt && !isdigit(*pt) ){
			pt++ ;
		}

		if(*pt){
			while( strtol2(num1, pt, 0) ) {
				num2 = num1;
				if ( (*pt == '-') || (*pt == '+') || (*pt == '.') ) {
					do pt++; while (*pt == '.');
					if (!strtol2(num2, pt, 0)) num2 = config->anArrayMax[arrays];
				}
				if ( num1 > num2 ) SwapInt(num1, num2);
				if ( num1 < 1 ) num1 = 1;
				if ( num2>config->anArrayMax[arrays] ) num2 = config->anArrayMax[arrays];
				if ( num1 > num2 ) num1=num2;
				for (int j = num1; j <= num2; j++) {
					if (!StoreArrayConfig(config, index*(config->anArrayMax[arrays])+j-1, arrays+1, p , right)){
						return FALSE;
					};
				}
				if(*pt)pt++;
			}
		}else{
			for (int j = 1; j <= config->anArrayMax[arrays]; j++) {
				if (!StoreArrayConfig(config, index*(config->anArrayMax[arrays])+j-1, arrays+1, p , right)){
						return FALSE;
				};
			}
		}
	}else{
		int num = 0  , lastnum = 0 ;
		for ( int i = 0 ; i < config->size ; i++ ){
			lastnum = num ;
			if (strtol2(num, right, 0)){
				memcpy( (char *)config->pVar+index*config->size+i, &num, 1);
			}else{
				if ( lastnum!= num ){
					memcpy( (char *)config->pVar+index*config->size+i, &lastnum, 1);
				}
			}
			if(*right)right++;
		}

	}

	return TRUE;

}


void StoreConfig(ConfigVar *config , char *left , char *right){
	if (!*right){
		AddWarningMessage(left);
		return;
	}
	switch(config->type){
		case 5:
			{
				if ( !StoreArrayConfig(config , 0 , 0 , left , right) ){
					AddWarningMessage(left);
				}
			}
			break;

		#ifdef MODULE_MINIMAPPOINT
		case 6:
			{
				DWORD dwLevelNo = 0 ;
				WORD wPointNo =0 ;
				BYTE fFlag =0 ;
				BYTE nColour=0;
				char *p=left;
				while (*p &&  *p != '['){
					p++;
				}
				p++;
				if (*p){
					dwLevelNo = strtoul(p,&p,0);
				}
				while (*p &&  *p != '['){
					p++;
				}
				p++;
				if (*p){
					wPointNo = (WORD)strtoul(p,&p,0);
				}
				char *endptr;
				fFlag = (BYTE)strtoul(right,&endptr,0);
				while(*endptr && !isdigit(*endptr)){
						endptr++;
				}
				if(*endptr){
					nColour = (BYTE)strtoul(endptr,&endptr,0); 
				}else{
					nColour = (BYTE)-1;
				}

				if ( dwLevelNo && wPointNo){
					AddMinimapConfig( dwLevelNo,wPointNo,fFlag,nColour);
				}

			}
			break;
		#endif
		case 1:
			{
				ToggleVar *tgKey = (ToggleVar *)config->pVar;
				tgKey->isLoad = TRUE;
				if( tgKey->type == 1){
					//��������
					char *endptr;
					tgKey->isOn = (BYTE)strtoul(right,&endptr,0);//��һ�� 0 �� ��0 �� 
					if(*endptr)endptr++;
					if(*endptr){
						tgKey->key = (BYTE)strtoul(endptr,&endptr,0); //��ݼ�
					}else{
						tgKey->key = (BYTE)-1;
					}
					if(*endptr)endptr++;
					if(*endptr){
						tgKey->value = (BYTE)strtoul(endptr,NULL,0); //Ĭ��ֵ
					}

				}else{
					//���������¼�
					char *endptr;
					tgKey->key = (BYTE)strtoul(right,&endptr,0);	//��ݼ�
					if(*endptr)endptr++;
					if(*endptr){
						tgKey->param = (BYTE)strtoul(endptr,NULL,0); //����
					}
				}
			}
			break;
		case 2:
			{
				//��ֵ
				if( config->size == 1 ){
					*((BYTE *)config->pVar) = (BYTE)strtoul(right,NULL,0);
				}else if( config->size == 2 ){
					*((WORD *)config->pVar) = (WORD)strtoul(right,NULL,0);
				}else if( config->size == 4 ){
					*((DWORD *)config->pVar) = (DWORD)strtoul(right,NULL,0);
				}

			}
			break;
		case 3:
			{
				char *p =right++;//ȥ����β����
				while(*p){
					p++;
				}
				if ( p != right ){
					*(--p)='\0';
				}
				//�ַ��������ֽ�
				if ( config->size >1 ){
					for( int i=0 ; i <config->size ; i ++ ){
						strncpy( (char *)config->pVar + config->anArrayMax[0]*i, right , config->anArrayMax[0]-1);
					}

				}else{
					strncpy( (char *)config->pVar , right , config->anArrayMax[0]-1 );
				}
			}
			break;
		case 4:
			{
				char *p =right++;//ȥ����β����
				while(*p){
					p++;
				}
				if ( p != right ){
					*(--p)='\0';
				}
				//�ַ�����˫�ֽ�
				if ( config->size >1 ){
					for( int i=0 ; i <config->size ; i ++ ){
						ConvertToD2String( (wchar_t *)config->pVar + config->anArrayMax[0]*i, right ,config->anArrayMax[0]-1);
					}

				}else{
					ConvertToD2String( (wchar_t *)config->pVar , right, config->anArrayMax[0]-1 );
				}
			}
			break;

		#ifdef MODULE_GAMEMONITOR
		case 7:
			{
				DWORD dwStatNo = 0 ;
				DWORD dwColor = 0;
				char *p=left;
				while (*p &&  *p != '['){
					p++;
				}
				p++;
				if (*p){
					dwStatNo = strtoul(p,&p,0);
				}
				sMonitorStr[nMonitors].dwStatNo = dwStatNo;
				dwColor = strtoul(right,&right,0);
				right++ ;
				sMonitorStr[nMonitors].dwColor = dwColor;

				p = right++;
				while(*p && *p !=','){
					p++;
				}
				if ( p != right ){
					*(p-1)='\0';
				}
				ConvertToD2String( sMonitorStr[nMonitors].wszDesc[0] , right, 29 );
				if(*p)p++;// , ��
				if(*p)p++;// " ��
				char *endptr = p;
				while (*p){
					p++;
				}
				if ( p != endptr ){
					*(p-1)='\0';
				}
				if ( *endptr ){
					char ptemp[30];
					ConvertToColorString((BYTE*)ptemp,endptr,30);
					if( fLocalizationSupport>1 ) GB2GBK(ptemp);
					MyMultiByteToWideChar(CP_ACP, 0, ptemp, -1, sMonitorStr[nMonitors].wszDesc[1]  , 30);
				}else{
					wcscpy( sMonitorStr[nMonitors].wszDesc[1] , sMonitorStr[nMonitors].wszDesc[0]);
				}
				nMonitors++;
			}
			break;
		#endif
		default:
			break;
	}
}

// JSON Configuration loading functions
BOOL LoadJsonConfigValue(const JsonValue& value, ConfigVar* config) {
	if (!config) return FALSE;

	switch(config->type) {
		case 1: // ToggleVar
		{
			ToggleVar *tgKey = (ToggleVar *)config->pVar;
			tgKey->isLoad = TRUE;

			if (value.isObject()) {
				// Handle object format like {"enabled": true, "key": "F9"}
				if (value.contains("enabled")) {
					tgKey->isOn = value["enabled"].asBool() ? 1 : 0;
				}
				if (value.contains("key")) {
					std::string keyStr = value["key"].asString();
					tgKey->key = ConvertKeyFromJson(keyStr);
				}
				if (value.contains("value")) {
					tgKey->value = (BYTE)value["value"].asInt();
				}
			} else if (value.isBool()) {
				// Handle simple boolean format
				tgKey->isOn = value.asBool() ? 1 : 0;
				tgKey->key = (BYTE)-1;
			}
			break;
		}
		case 2: // Numeric value
		{
			if (value.isNumber()) {
				if (config->size == 1) {
					*((BYTE *)config->pVar) = (BYTE)value.asInt();
				} else if (config->size == 2) {
					*((WORD *)config->pVar) = (WORD)value.asInt();
				} else if (config->size == 4) {
					*((DWORD *)config->pVar) = (DWORD)value.asInt();
				}
			} else if (value.isString()) {
				// Handle special string values
				std::string strVal = value.asString();
				DWORD numVal = 0;

				if (strVal == "disabled" || strVal == "false") numVal = 0;
				else if (strVal == "enabled" || strVal == "true") numVal = 1;
				else if (strVal == "exit_game") numVal = 1;
				else if (strVal == "town_portal") numVal = 2;
				else if (strVal == "dual_display") numVal = 2;
				else if (strVal == "auto_convert_to_chinese") numVal = 2;
				else if (strVal == "switch_position") numVal = 2;
				else if (strVal == "auto_position") numVal = 3;
				else numVal = atoi(strVal.c_str());

				if (config->size == 1) {
					*((BYTE *)config->pVar) = (BYTE)numVal;
				} else if (config->size == 2) {
					*((WORD *)config->pVar) = (WORD)numVal;
				} else if (config->size == 4) {
					*((DWORD *)config->pVar) = (DWORD)numVal;
				}
			}
			break;
		}
		case 3: // String (single byte)
		{
			if (value.isString()) {
				std::string strVal = value.asString();
				if (config->size > 1) {
					for(int i = 0; i < config->size; i++) {
						strncpy((char *)config->pVar + config->anArrayMax[0]*i, strVal.c_str(), config->anArrayMax[0]-1);
					}
				} else {
					strncpy((char *)config->pVar, strVal.c_str(), config->anArrayMax[0]-1);
				}
			}
			break;
		}
		case 4: // String (wide char with color support)
		{
			if (value.isString()) {
				std::string strVal = value.asString();
				if (config->size > 1) {
					for(int i = 0; i < config->size; i++) {
						ConvertToD2String((wchar_t *)config->pVar + config->anArrayMax[0]*i, (char*)strVal.c_str(), config->anArrayMax[0]-1);
					}
				} else {
					ConvertToD2String((wchar_t *)config->pVar, (char*)strVal.c_str(), config->anArrayMax[0]-1);
				}
			}
			break;
		}
	}
	return TRUE;
}

BOOL LoadJsonConfig() {
	char filename[MAX_PATH];
	sprintf(filename, "%sd2hackmap.json", szPluginPath);

	HANDLE hFile = OpenFileRead(filename);
	if (hFile == INVALID_HANDLE_VALUE) {
		return FALSE; // JSON file doesn't exist, fallback to CFG
	}

	// Read entire JSON file
	DWORD fileSize = GetFileSize(hFile, NULL);
	if (fileSize == INVALID_FILE_SIZE || fileSize > 1024*1024) { // Limit to 1MB
		CloseHandle(hFile);
		return FALSE;
	}

	std::string jsonContent;
	jsonContent.resize(fileSize);
	DWORD bytesRead;
	if (!ReadFile(hFile, &jsonContent[0], fileSize, &bytesRead, NULL) || bytesRead != fileSize) {
		CloseHandle(hFile);
		return FALSE;
	}
	CloseHandle(hFile);

	// Parse JSON
	JsonParser parser;
	JsonValue root = parser.parse(jsonContent);

	if (!root.isObject()) {
		AddWarningMessage("Invalid JSON format", 1);
		return FALSE;
	}

	// Map JSON paths to config variables
	struct JsonConfigMapping {
		const char* jsonPath;
		const char* configName;
	};

	static JsonConfigMapping mappings[] = {
		{"general.showCfgCheckInfo", "Show CFGCheck Info"},
		{"general.enableLanguageCheck", "Enable Language Check"},
		{"general.gameFilterSupport", "GameFilterSupport"},
		{"general.localizationSupport", "Localization Support"},
		{"hotkeys.reloadConfig", "Reload Config Key"},
		{"hotkeys.quickBackToTown", "Quick Back To Town Key"},
		{"hotkeys.permShowItemsToggle", "Perm Show Items Toggle"},
		{"hotkeys.hiddenItemsToggle", "Hidden Items Toggle"},
		{"hotkeys.socketProtectToggle", "Socket Protect Toggle"},
		{"hotkeys.quickExitGame", "Quick Exit Game Key"},
		{"hotkeys.quickNextGame", "Quick Next Game Key"},
		{"hotkeys.viewEquipment", "View Equipment Key"},
		{"hotkeys.viewPlayerStats", "View Player Stats Key"},
		{"hotkeys.autoInviteToggle", "Auto Invite Toggle"},
		{"hotkeys.autoPartyToggle", "Auto Party Toggle"},
		{"display.useCustomFont", "Use Custom Font Toggle"},
		{"display.autoLootPermit", "Auto Loot Permit"},
		{"display.monsterResists", "Monster Resists Toggle"},
		{"display.itemValue", "Item Value Toggle"},
		{"display.itemLevels", "Item Levels Toggle"},
		{"display.showItemVariableProp", "Show Item Variable Prop Toggle"},
		{"display.showPing", "Show Ping Toggle"},
		{"display.outTownSelect", "Out Town Select Toggle"},
		{"display.showBaseED", "Show Base ED Toggle"},
		{"display.showPartyLevel", "Show Party Level Toggle"},
		{"display.gameTime", "Game Time Toggle"},
		{"display.clock", "Clock Toggle"},
		{"display.serverIp", "Server Ip Toggle"},
		{"display.areaLevel", "Area Level Toggle"},
		{"display.mousePosition", "Mouse Position Toggle"},
		{"automap.autoRevealAct", "Auto Reveal Act"},
		{"automap.autoMapToggle", "AutoMap Toggle"},
		{"automap.autoMapLevelNames", "Automap Level Names Toggle"},
		{"automap.minimapToggle", "Minimap Toggle"},
		{"automap.minimapSize", "Minimap Size"},
		{"automap.scrollMapToggle", "Scroll Map Toggle"},
		{"automap.diagonalScroll", "Diagonal Scroll Toggle"},
		{"automap.scrollMode", "Scroll Mode"},
		{"automap.miniShrines", "Mini Shrines Toggle"},
		{"visuals.fullVisuals", "Full Visuals Toggle"},
		{"visuals.weather", "Weather Toggle"},
		{"visuals.infravision", "Infravision Toggle"},
		{"visuals.lightRadius", "Light Radius Toggle"},
		{"visuals.screenShake", "Screen Shake Toggle"},
		{"visuals.lifeBarTransparency", "Life Bar Transparency"},
		{"visuals.permShowOrbs", "Perm Show Orbs Toggle"},
		{"chicken.chickenLifeAction", "Chicken Life Action"},
		{"items.automapItems", "Automap Items Toggle"},
		{"items.runeNumbers", "Rune Numbers Toggle"},
		{"items.socketNumbers", "Socket Numbers Toggle"},
		{"items.itemLifePerLevel", "Item Life Per Level Toggle"},
		{"items.goodGoldNumber", "Good Gold Number"},
		{"monsters.monsterLevel", "Monster Level Toggle"},
		{"monsters.monsterTC", "Monster TC Toggle"},
		{"monsters.monsterRuneTC", "Monster Rune TC Toggle"},
		{"monsters.monsterHPPercent", "Monster HPPercent Toggle"},
		{"monsters.monsterDistance", "Monster Distance Toggle"},
		{"monsters.playerLevel", "Player Level Toggle"},
		{"monsters.playerDistance", "Player Distance Toggle"},
		{"monsters.playerHPPercent", "Player HPPercent Toggle"},
		{"monsters.bossName", "Boss Name Toggle"},
		{"monsters.automapMonsters", "Automap Monsters Toggle"},
		{"chests.automapChests", "Automap Chests Toggle"},
		{"missiles.automapMissiles", "Automap Missiles Toggle"},
		{"advanced.autoNextGameName", "Auto Next Game Name"},
		{"advanced.autoNextGamePassword", "Auto Next Game Password"},
		{"advanced.inputLine", "Input Line Toggle"},
		{"advanced.rightClickSwap", "Right Click Swap Toggle"},
		{"advanced.ctrlClickSwap", "Ctrl Click Swap Toggle"},
		{"advanced.quickDrop", "Quick Drop Toggle"}
	};

	// Process mappings
	for (int i = 0; i < sizeof(mappings)/sizeof(mappings[0]); i++) {
		// Navigate JSON path
		JsonValue currentValue = root;
		std::string path = mappings[i].jsonPath;
		size_t pos = 0;

		while (pos < path.length()) {
			size_t dotPos = path.find('.', pos);
			if (dotPos == std::string::npos) dotPos = path.length();

			std::string segment = path.substr(pos, dotPos - pos);
			if (currentValue.contains(segment)) {
				currentValue = currentValue[segment];
			} else {
				currentValue = JsonValue(); // null value
				break;
			}

			pos = dotPos + 1;
		}

		if (!currentValue.isNull()) {
			// Find corresponding config variable
			for (int j = 0; j < _ARRAYSIZE(aConfigVars); j++) {
				if (_stricmp(aConfigVars[j].szCmdName, mappings[i].configName) == 0) {
					LoadJsonConfigValue(currentValue, &aConfigVars[j]);
					break;
				}
			}
		}
	}

	return TRUE;
}


BOOL LoadConfig(){
	//����vcb
	InitValues();
	

	HANDLE hFile;
	char line[1024], left[1024], right[1024];
	hFile = OpenFileReadHelper("VCB");
	while ( ReadFileLine(line, sizeof(line), hFile) ) {
		__try {
			SplitLine( line, left, right );
			if( *left && *right ){
				ReplaceByVcb(right);
				char *pleft = strtok( left, ",");
				while(pleft){
					TreeNode **pLeaf;
					pLeaf = &SearchTree( pTreeRoot, pleft );
					*pLeaf = new TreeNode;
					(*pLeaf)->key = AllocStrN(pleft, strlen(pleft));
					(*pLeaf)->str = AllocStrN(right, strlen(right));
					(*pLeaf)->left = (*pLeaf)->right = 0;

					pleft = strtok( NULL, ",");
				}
			}
		} __except(EXCEPTION_EXECUTE_HANDLER) {
			AddWarningMessage("Load VCB Error!" , 1 );
		}
	}
	CloseHandle(hFile);

	// Try to load JSON config first, fallback to CFG if not found
	BOOL jsonLoaded = LoadJsonConfig();

	//����cfg (only if JSON wasn't loaded)
	if (!jsonLoaded) {
		hFile = OpenFileReadHelper("CFG");
	while ( ReadFileLine(line, sizeof(line), hFile) ) {
		__try {
			SplitLine( line, left, right );
			if( *left && *right ){
				ReplaceByVcb(left);
				//�����һ���ַ���" �����滻
				ReplaceByVcb(right);
				BOOL hascmd = false;
				char *p=line;
				char *p1 = left;
				while(*p1 && ( isalnum(*p1) || isspace(*p1) || *p1=='_'  ) ){
					*p++ = *p1++;
				}
				*p='\0';

				if ( *line ){
					int num = _ARRAYSIZE(aConfigVars);
					for( int i=0 ; i<num ; i++ ){
						if ( _stricmp(aConfigVars[i].szCmdName, line)==0 ){
							StoreConfig(&aConfigVars[i],left,right);
							hascmd = true;
							break;
						}
					}
				}
				if ( hascmd == false ){
					AddWarningMessage(line);
				}
			}else{
				if ( *line ){
					AddWarningMessage(line);
				}
			}
		} __except(EXCEPTION_EXECUTE_HANDLER) {
			AddWarningMessage("Load CFG Error!" , 1 );
		}
	}
	CloseHandle(hFile);
	} // End of CFG loading block

	__try {
		FixValues();
		InitKeyEvent();
	} __except(EXCEPTION_EXECUTE_HANDLER) {
		AddWarningMessage("Init Key Event Errors!" , 1 );
	}
	DeleteTree(pTreeRoot);
	pTreeRoot=0;
	return TRUE;
}
