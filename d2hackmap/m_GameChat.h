
#ifdef FUNCTION_DECLARE
	#define MODULE_GAMECHAT
	void WisperPatch_ASM();
	void InputLinePatch1_ASM();
	void InputLinePatch2_ASM();
	void CheckD2WinEditBox();
	void SelectTextPatch1_ASM();
	void SelectTextPatch2_ASM();
#endif

#ifdef VARIABLE_DEFINE

 GVAR2(ToggleVar,	tWisperNotice,				1,	0,	(BYTE)-1,	1, "Wisper Notice")
 GVAR2(ToggleVar,	tInputLine,					1,	1,	(BYTE)-1,	1, "Input line Patch")
 GVAR2(ToggleVar,	tUseCustomFont,				1,	0,	(BYTE)-1,	1, "Use Custom Font")
 GVAR (D2EditBox*,	pD2WinEditBox,				0)
#endif

#ifdef PATH_INSTALL
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB1FEC7, 0x6FB61187),    (DWORD)WisperPatch_ASM,                 5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB20C6C, 0x6FB6254C),    (DWORD)InputLinePatch1_ASM,             5 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB2037B, 0x6FB6186B),    (DWORD)InputLinePatch2_ASM,             5 ,   &fDefault},
  {PatchVALUE,  DLLOFFSET2(D2CLIENT, 0x6FB54745, 0x6FAC6505),     0x2EB58,                               3 ,   &fDefault}, 
  {PatchVALUE,  DLLOFFSET2(D2CLIENT, 0x6FB546C5, 0x6FAC6485),     0x2EB58,                               3 ,   &fDefault},
  {PatchCALL,   DLLOFFSET2(D2WIN ,   0x6F8F5F61, 0x6F8F17C1),     (DWORD)SelectTextPatch1_ASM,			8 ,   &fDefault}, //聊天框选中中文文字
  {PatchCALL,   DLLOFFSET2(D2WIN ,   0x6F8F5F02, 0x6F8F1762),     (DWORD)SelectTextPatch2_ASM,			8 ,   &fDefault}, //聊天框选中中文文字
#endif

#ifdef CONFIG_LOAD
	{1, "WisperNoticeToggle",     &tWisperNotice      },
	{1, "InputLineToggle",        &tInputLine         },
	{1, "UseCustomFontToggle",    &tUseCustomFont     },
#endif


#ifdef RUN_ONCE


#endif

#ifdef RUN_LOOP

CheckD2WinEditBox();
#endif


#ifdef RUN_ENDGAME

		if (pD2WinEditBox) {
			*(DWORD*)p_D2LastChatMessage = 0;
			wchar_t *p = wcscpy(p_D2LastChatMessage, D2GetEditBoxText(pD2WinEditBox));
			*p_D2ChatTextLength = wcslen(p);
			D2DestroyEditBox(pD2WinEditBox);
			pD2WinEditBox = NULL;
			FOCUSECONTROL = NULL;
		}

#endif

#ifdef INIT_VALUE


#endif

#ifdef FIX_VALUE


#endif
