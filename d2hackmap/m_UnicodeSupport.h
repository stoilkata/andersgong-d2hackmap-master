
#ifdef FUNCTION_DECLARE
	#define MODULE_UNICODESUPPORT
	LPCSTR __fastcall D2Lang_Unicode2WinPatch(LPSTR lpWinStr, LPWSTR lpUnicodeStr, DWORD dwBufSize);
	LPWSTR __fastcall D2Lang_Win2UnicodePatch(LPWSTR lpUnicodeStr, LPCSTR lpWinStr, DWORD dwBufSize);
	DWORD __fastcall ChannelEnterCharPatch(D2EditBox *hWnd, BYTE bKeyCode);
	void	MultiByteFixPatch_ASM();
	void	IsPritableCharacterPatch_ASM();
	
#endif

#ifdef VARIABLE_DEFINE
 
 
#endif

#ifdef PATH_INSTALL

  {PatchJMP,    DLLOFFSET2(D2LANG, 0x6FC082F0, 0x6FC082B0),      (DWORD)D2Lang_Unicode2WinPatch,          5 ,   &fLocalizationSupport},
  {PatchJMP,    DLLOFFSET2(D2LANG, 0x6FC08320, 0x6FC082E0),      (DWORD)D2Lang_Win2UnicodePatch,          5 ,   &fLocalizationSupport},
  {PatchCALL,   DLLOFFSET2(D2WIN,  0x6F8F83A0, 0x6F8EE850),      (DWORD)ChannelEnterCharPatch,            5 ,   &fLocalizationSupport}, //ע��InputLinePatch1_ASM�������������Ȼ�����𲿷ֶ�ջ����(��Ȼ��Ӱ��ʹ��)
  {PatchCALL,   DLLOFFSET2(BNCLIENT,0x6FF2FF5C, 0x6FF3513C),     (DWORD)MultiByteFixPatch_ASM,            6 ,   &fLocalizationSupport}, // for /w *acc msg text
  {PatchCALL,   DLLOFFSET2(D2WIN , 0x6F8F1880, 0x6F8F2410),      (DWORD)IsPritableCharacterPatch_ASM,     8 ,   &fLocalizationSupport}, //����

  {PatchFILL,   DLLOFFSET2(D2WIN,  0x6F8F30E9, 0x6F8F3C79),		INST_NOP,							     2,	   &fLocalizationSupport},//ǿ��tbl������ʽ
  {PatchFILL,   DLLOFFSET2(D2WIN,  0x6F8F30F8, 0x6F8F3C88),		INST_JMPR,							     1,	   &fLocalizationSupport},//ǿ��tbl������ʽ

#endif

#ifdef CONFIG_LOAD


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
