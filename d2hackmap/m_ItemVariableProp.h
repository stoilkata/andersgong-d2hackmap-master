#ifdef FUNCTION_DECLARE
	#define MODULE_ITEMVARIABLEPROP
	void GetItemPropStringPatch_ASM();
	void StrcatItemPropStringPatch_ASM();
	void StrcatSocketStringPatch_ASM();
	void StrcatDefenseStringPatch_ASM();
	void StrcatDamageStringPatch_ASM1();
	void StrcatDamageStringPatch_ASM2();
#endif

#ifdef VARIABLE_DEFINE
GVAR2(ToggleVar,	tShowItemVariableProp,	  1,	0,	(BYTE)-1,	1 , "Item Variable Prop")
 
#endif

#ifdef PATH_INSTALL

    {PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB05DAA, 0x6FADE07A),    (DWORD)GetItemPropStringPatch_ASM,      5 ,   &fDefault},//��ͨ����
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB04658, 0x6FADC928),    (DWORD)StrcatItemPropStringPatch_ASM,   6 ,   &fDefault},//��ǿ�˺�����������
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB3E2C5, 0x6FB42F45),    (DWORD)StrcatSocketStringPatch_ASM,     6 ,   &fDefault},//ƴ������ETH�ȵײ��ַ�������������Ϊ����
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB3FDAD, 0x6FB422FD),    (DWORD)StrcatDefenseStringPatch_ASM,    6 ,   &fDefault},//ƴ����ֵ�ַ���
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB44367, 0x6FB48737),    (DWORD)StrcatDamageStringPatch_ASM1,    6 ,   &fDefault},//ƴ�����ַ���,һ������
	{PatchCALL,   DLLOFFSET2(D2CLIENT, 0x6FB42EE4, 0x6FB472B4),    (DWORD)StrcatDamageStringPatch_ASM2,    9 ,   &fDefault},//ƴ�����ַ���,��ɫ����
	
#endif

#ifdef CONFIG_LOAD
{1, "ShowItemVariablePropToggle",					&tShowItemVariableProp         },

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
