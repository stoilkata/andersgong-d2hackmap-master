#include "stdafx.h"

void GameLoopPatch()
{
	static wchar_t *wszProgTitle = L"<Hackmap>: Sting's Hackmap For Diablo II fixed by Anders (v1.13c&d.1.6) installed.";	
	if ( fInGame==FALSE ) {
		fInGame = TRUE;
		D2ShowGameMessage( wszProgTitle, 0);
		
		ShowWarningMessage();
		
		if(fEnterGameSound){
			MessageBeep(MB_ICONEXCLAMATION);
		}

		#define RUN_ONCE
			#include "Module.h"
		#undef RUN_ONCE

		if ( wszCFGVersion[dwGameLng][0] ) {
			D2ShowGameMessage( wszCFGVersion[dwGameLng], 9);
		}
		
	}
	dwCurrentAct = PLAYER->dwAct;
	dwCurrentLevel = PLAYER->pMonPath->pRoom1->pRoom2->pDrlgLevel->dwLevelNo;
	fPlayerInTown = (LEVELNO==actlvls[ACTNO]);

	#define RUN_LOOP
		#include "Module.h"
	#undef RUN_LOOP

}

void GameEndPatch()
{
	if ( fInGame ){
	
		fInGame = FALSE;
		fPlayerInTown = TRUE;

		#define RUN_ENDGAME
			#include "Module.h"
		#undef RUN_ENDGAME

	}
}

void __declspec(naked) GameLoopPatch_ASM()
{
	__asm {
		pop eax
		sub esp, 0x20
		mov [esp+0x0c], ecx
		push eax
		jmp GameLoopPatch
	}
}

void __declspec(naked) GameEndPatch_ASM()
{
	__asm {
		call GameEndPatch
		mov ecx,0xb4
		ret
	}
}

