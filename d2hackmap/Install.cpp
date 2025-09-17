#include "stdafx.h"

#include "d2ptrs.h"

#define PATH_INSTALL
#include "Module.h"
#undef PATH_INSTALL

#define PATH_INSTALL2
#include "Module.h"
#undef PATH_INSTALL2

#pragma comment(lib, "Version.Lib")

BOOL RelocD2Ptrs()
{
	DWORD *pPtrsStart = (DWORD *)&vD2StartOfPtr;
	DWORD *pPtrsEnd = (DWORD *)&vD2EndOfPtr;
	DWORD *p = pPtrsStart, ret = TRUE;
	while (++p < pPtrsEnd){
		if (!(*p = GetDllOffset(*p))) ret = FALSE;
	};
	return ret;
}


BOOL InstallD2Patchs(Patch_t* pPatchStart, Patch_t* pPatchEnd)
{
  Patch_t* p = pPatchStart;
  while( p<pPatchEnd ){
    if ( !p->fInit){
      p->addr = GetDllOffset(p->addr);
      p->fInit = 1 ;
    }
    if (p->func && *(p->fEnable)){
      p->oldcode = new BYTE[p->len];
      ReadLocalBYTES(p->addr, p->oldcode, p->len);
      p->func(p->addr, p->param, p->len);
    }
    p++;
  }
  return TRUE;
}

void RemoveD2Patchs(Patch_t* pPatchStart, Patch_t* pPatchEnd)
{
  Patch_t* p = pPatchStart;
  while( p<pPatchEnd) {
    if (p->oldcode && *(p->fEnable) ){
      WriteLocalBYTES(p->addr, p->oldcode, p->len);
      delete p->oldcode;
    }
    p++;
  }
}

//D2loader 存在bug，部分dll需要迟后加装

BOOL fInstallPatch2 = 0;
BOOL RelocD2Ptrs2()
{
	DWORD *pPtrsStart = (DWORD *)&vD2StartOfPtr2;
	DWORD *pPtrsEnd = (DWORD *)&vD2EndOfPtr2;
	DWORD *p = pPtrsStart, ret = TRUE;
	while (++p < pPtrsEnd){
		if (!(*p = GetDllOffset(*p))) ret = FALSE;
	};
	return ret;
}
void InstallPatchAfterLoad(){
	if ( !fInstallPatch2 ){
		RelocD2Ptrs2();
		InstallD2Patchs(aD2Patch2s, aD2Patch2s+_ARRAYSIZE(aD2Patch2s));
		fInstallPatch2 = 1;
	}
}
void __declspec(naked) InstallPatchAfterLoad_ASM()
{
	__asm{
		cmp [fInstallPatch2],1
		je org
		push edi
		call InstallPatchAfterLoad
		pop edi
org:
		pop ecx
		lea eax, dword ptr [esp+0x4]
		push eax
		jmp ecx
	}
}

BOOL InstallPatchs(){
  if(!InstallD2Patchs(aD2Patchs, aD2Patchs+_ARRAYSIZE(aD2Patchs))){
    return FALSE;
  };

  #ifdef MODULE_GAMEWINDOW
	KeepWindowPatch();
  #endif

  return TRUE;
}

void RemovePatchs(){
	RemoveD2Patchs(aD2Patchs, aD2Patchs+_ARRAYSIZE(aD2Patchs));
	if ( fInstallPatch2 ){
		RemoveD2Patchs(aD2Patch2s, aD2Patch2s+_ARRAYSIZE(aD2Patch2s));
		fInstallPatch2 = 0;
	}
	#ifdef MODULE_GAMEWINDOW
		RemoveKeepWindowPatch();
	#endif

}

void InitCellFiles()
{
	char filename[MAX_PATH];
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUMOF_SHRINES; j++) {
			sprintf(filename,"%s%s%.2d.BMP",szPluginPath,"MINISHRINE"+(i?0:4) ,j);
			apMyShrineCells[i][j] = InitCellFile(LoadBmpCellFile(filename));
		}
	}
	sprintf(filename,"%s%s",szPluginPath,"WAYPOINT.BMP");
	pWaypointCell = InitCellFile(LoadBmpCellFile(filename));
	sprintf(filename,"%s%s",szPluginPath,"BLOBCELL.BMP");
	pMinimapObjectCell = InitCellFile(LoadBmpCellFile(filename));
	if(!pMinimapObjectCell) {
		sprintf(filename,"%s%s",szPluginPath,"BLOBDOT.BMP");
		pMinimapObjectCell = InitCellFile(LoadBmpCellFile(filename));
	}

	for (int i = 0; i < _ARRAYSIZE(pUnitBlobCells); i++) {
		if (aszUnitBlobFiles[i]) {
			sprintf(filename,"%s%s.BMP",szPluginPath, aszUnitBlobFiles[i]);
			pUnitBlobCells[i] = InitCellFile(LoadBmpCellFile(filename));
		}
	}

}

void DeleteCellFiles()
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < NUMOF_SHRINES; j++) {
			DeleteCellFile(apMyShrineCells[i][j]);
		}
	}
	DeleteCellFile(pWaypointCell);
	DeleteCellFile(pMinimapObjectCell);

	memset( apMyShrineCells ,			0 ,			sizeof(apMyShrineCells) );
	pWaypointCell = NULL;
	pMinimapObjectCell = NULL;

	for (int i = 0; i < _ARRAYSIZE(pUnitBlobCells); i++) {
		DeleteCellFile(pUnitBlobCells[i]);
	}
	memset( pUnitBlobCells ,			0 ,			sizeof(pUnitBlobCells) );
}



BOOL Install(){

	//重定位函数
	if(!RelocD2Ptrs()){
		return FALSE;
	}

	//加载配置文件
	if(!LoadConfig()){
		return FALSE;
	}

	//加载旁路点
	if(!InstallPatchs()){
		return FALSE;
	}
	
	//InitCellFiles();

	if (fAutomapPartyDefault != (BYTE)-1) D2SetAutomapParty(fAutomapPartyDefault==0?0:1);
	if (fAutomapNamesDefault != (BYTE)-1) D2SetAutomapNames(fAutomapNamesDefault==0?0:1);
	
	return TRUE;

}


void Uninstall(){
	
	#ifdef MODULE_AUTOMAPCELL
		RemoveMyAutomapCells();
	#endif
	
	DeleteCellFiles();
	RemovePatchs();

}

void ReloadConfig(){
	DeleteCellFiles();
	if (LoadConfig()){
		InitCellFiles();
		#ifdef MODULE_MINIMAPPOINT
		BuildMiniMapPoint(5);
		#endif

		ShowGameMessage("Config Reload Successful");
		ShowWarningMessage();
	}
}

DWORD CalcFuncOffset_X(DWORD dwNo, DWORD dwBase, int iValue)
{
    if ( 0 > iValue )
    {
        return (dwNo | (iValue <<8));
    }

    return (dwNo | ((iValue - dwBase) <<8));
}

#if 0
DWORD GetD2Version(LPCVOID pVersionResource)
{
	if (!pVersionResource) return D2_VER_113C;

	UINT uLen;
	VS_FIXEDFILEINFO* ptFixedFileInfo;
	if (!VerQueryValue(pVersionResource, "\\", (LPVOID*)&ptFixedFileInfo, &uLen))
		return D2_VER_113C;

	if (uLen == 0)
		return D2_VER_113C;

	WORD major = HIWORD(ptFixedFileInfo->dwFileVersionMS);
	WORD minor = LOWORD(ptFixedFileInfo->dwFileVersionMS);
	WORD revision = HIWORD(ptFixedFileInfo->dwFileVersionLS);
	WORD subrevision = LOWORD(ptFixedFileInfo->dwFileVersionLS);

	if (major != 1)
		return D2_VER_113C;
	if (minor == 0 && revision == 13 && subrevision == 64) return D2_VER_113D;
	return D2_VER_113C;
}

DWORD GetD2Version(char* gameExe)
{
    static DWORD version = 0xFFFFFFFF;

    if ( 0xFFFFFFFF != version )
    {
        return version;
    }

	DWORD len = GetFileVersionInfoSize(gameExe, NULL);
	if (len == 0)
	{
	    version = D2_VER_113C;
		return version;
	}

	BYTE* pVersionResource = new BYTE[len];
	GetFileVersionInfo(gameExe, NULL, len, pVersionResource);
	version = GetD2Version(pVersionResource);
	delete pVersionResource;

	return version;
}

DWORD Map_D2Version()
{
    char szBuffer[MAX_PATH] = {0};
    char *pcTemp = NULL;
    static DWORD version = 0xFFFFFFFF;

    if ( 0xFFFFFFFF != version )
    {
        return version;
    }

    GetModuleFileName(GetModuleHandle("PlugY.dll"), szBuffer, sizeof(szBuffer) / sizeof(szBuffer[0]) - 1);
    if ( 0 == szBuffer[0] || NULL == (pcTemp = strstr(szBuffer, ".dll")) )
	{
	    version = D2_VER_113C;
		return version;
	}

    pcTemp -= strlen("PlugY");
    strcpy(pcTemp, "game.exe");
    return (version = GetD2Version(szBuffer));
}
#else
eGameVersion GetD2Version(LPCVOID pVersionResource)
{
	if (!pVersionResource) return UNKNOWN;

	UINT uLen;
	VS_FIXEDFILEINFO* ptFixedFileInfo;
	if (!VerQueryValue(pVersionResource, "\\", (LPVOID*)&ptFixedFileInfo, &uLen))
		return UNKNOWN;

	if (uLen == 0)
		return UNKNOWN;

	WORD major = HIWORD(ptFixedFileInfo->dwFileVersionMS);
	WORD minor = LOWORD(ptFixedFileInfo->dwFileVersionMS);
	WORD revision = HIWORD(ptFixedFileInfo->dwFileVersionLS);
	WORD subrevision = LOWORD(ptFixedFileInfo->dwFileVersionLS);

	if (major != 1)
		return UNKNOWN;
	if (minor == 0 && revision == 7 && subrevision == 0) return UNKNOWN;//V107;
	if (minor == 0 && revision == 8 && subrevision == 28) return UNKNOWN;//V108;
	if (minor == 0 && revision == 9 && subrevision == 19) return UNKNOWN;//V109;
	if (minor == 0 && revision == 9 && subrevision == 20) return UNKNOWN;//V109b;
	if (minor == 0 && revision == 9 && subrevision == 22) return UNKNOWN;//V109d;
	if (minor == 0 && revision == 10 && subrevision == 39) return UNKNOWN;//V110;
	if (minor == 0 && revision == 11 && subrevision == 45) return UNKNOWN;//V111;
	if (minor == 0 && revision == 11 && subrevision == 46) return UNKNOWN;//V111b;
	if (minor == 0 && revision == 12 && subrevision == 49) return UNKNOWN;//V112;
	if (minor == 0 && revision == 13 && subrevision == 60) return D2_VER_113C;
	if (minor == 0 && revision == 13 && subrevision == 64) return D2_VER_113D;
	if (minor == 14 && revision == 0 && subrevision == 64) return UNKNOWN;//V114a;
	if (minor == 14 && revision == 1 && subrevision == 68) return UNKNOWN;//V114b;
	if (minor == 14 && revision == 2 && subrevision == 70) return UNKNOWN;//V114c;
	if (minor == 14 && revision == 3 && subrevision == 71) return UNKNOWN;//V114d;
	return UNKNOWN;
}

eGameVersion GetD2Version(char* gameExe)
{
    static eGameVersion version = UNKNOWN;

    if ( UNKNOWN != version )
    {
        return version;
    }

	DWORD len = GetFileVersionInfoSize(gameExe, NULL);
	if (len == 0)
		return UNKNOWN;

	BYTE* pVersionResource = new BYTE[len];
	GetFileVersionInfo(gameExe, NULL, len, pVersionResource);
	version = GetD2Version(pVersionResource);
	delete pVersionResource;

	return version;
}

eGameVersion GetD2Version(HMODULE hModule)
{
    static eGameVersion version = UNKNOWN;

    if ( UNKNOWN != version )
    {
        return version;
    }

	HRSRC hResInfo = FindResource(hModule, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	if (!hResInfo) return UNKNOWN;
	HGLOBAL hResData = LoadResource(hModule, hResInfo);
	if (!hResData) return UNKNOWN;
	LPVOID pVersionResource = LockResource(hResData);
	version = GetD2Version(pVersionResource);
	FreeResource(hResData);
	return version;
}

DWORD Map_D2Version()
{
    char szBuffer[MAX_PATH] = {0};
    char *pcTemp = NULL;
    static eGameVersion version = UNKNOWN;

    if ( UNKNOWN != version )
    {
        return version;
    }

    version = GetD2Version((HMODULE)GetModuleHandle(NULL));

    return version;
}
#endif

