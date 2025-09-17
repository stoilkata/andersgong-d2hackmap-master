#ifdef FUNCTION_DECLARE
	#define MODULE_PACKETHANDLER
	void GamePacketReceivedInterceptPatch_ASM();
#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tPacketHandler,				1,	0,	(BYTE)-1,	1,  0 )
#endif

#ifdef PATH_INSTALL
{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB6DFCF, 0x6FAC79CF),      (DWORD)GamePacketReceivedInterceptPatch_ASM, 6 , &fDefault},

#endif

#ifdef CONFIG_LOAD
{1, "PacketHandlerToggle",          &tPacketHandler         },

#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP


#endif


#ifdef RUN_ENDGAME


#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
