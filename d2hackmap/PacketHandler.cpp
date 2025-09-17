#include "stdafx.h"
//÷ª≤‚ ‘”√
//6FB8BC30 + 12*n 
#ifdef MODULE_PACKETHANDLER


void __fastcall GamePacketReceivedIntercept(BYTE* aPacket, DWORD aLength)
{
	if( tPacketHandler.isOn ){
		if ( 1 /* && aPacket[0] == 0x53*/){
		wchar_t wszTemp[512];
		wcscpy(wszTemp,L" [");
		for ( int i=0 ; i<12 ; i++){
			wsprintfW(wszTemp+wcslen(wszTemp),L" %X" , aPacket[i]);
		}
		wcscat(wszTemp,L" ]");
		D2ShowGameMessage (wszTemp,0);
		}
		
	}
	return;
}
//////////////////////////////////////////////////////////////////////
// GamePacketReceivedSTUB()
// -------------------------------------------------------------------

// before call orignal code
// bl = packet number
// esi = length
// edi = pointer to packet
// free register before pushad: eax
//////////////////////////////////////////////////////////////////////
void __declspec(naked) GamePacketReceivedInterceptPatch_ASM()
{
	__asm {
		mov eax, esi; // save length

		// original code
		movzx esi, bl;
		mov ebp, esi
		shl ebp, 1
		add ebp, esi
		pushad;
		// Call our clean c function
		mov edx, eax;
		mov ecx, edi;
		call GamePacketReceivedIntercept;
		// Return to game
		popad;
		add dword ptr[esp], 1; 
		ret;
	}
}



#endif