///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#include "Features.h"
#include "stdio.h"
// �������������
//     Ŀǰ������������������
static MalSoftware malsoftware[] = {
	{ "RootKit1", "Only fot test1", 1, { { 100, 2, {0x1A,0xB}},{},{},{},{}} },
	{ "RootKit2", "Only fot test2", 1, { { 37, 23,{ 0xf, 0x1f, 0x44, 0x0, 0x0,
		       0x48, 0x83, 0x3d, 0xdb, 0x21, 0x0, 0x0, 0x0, 0x55, 0x48, 0x89,
		       0xe5,0x53, 0x75, 0x26, 0x48, 0xc7, 0xc1, 0x54 } },{},{},{} } },
	{ "RootKit3", "Only fot test2", 1, { { 37, 23,{ 0xf, 0x1f, 0x44, 0x0, 0x0,
		       0x48, 0x83, 0x3d, 0xfb, 0x21, 0x0, 0x0, 0x0, 0x55, 0x48, 0x89, 
		       0xe5, 0x53, 0x75, 0x26, 0x48, 0xc7, 0xc1, 0x51 }  },{},{},{} } },
	{ "RootKit4", "Only fot test2", 1, { { 37, 23,{ 0xf, 0x1f, 0x44, 0x0, 0x0,
		       0x48, 0x83, 0x3d, 0xa3, 0x30, 0x0, 0x0, 0x0, 0x55, 0x48, 0x89,
		       0xe5, 0x53, 0x75, 0x34, 0x48, 0x83, 0x3d, 0x84 }  },{},{},{} } }
};

//0xf, 0x1f, 0x44, 0x0, 0x0, 0x48, 0x83, 0x3d, 0xa3, 0x30, 0x0, 0x0, 0x0, 0x55, 0x48, 0x89, 0xe5, 0x53, 0x75, 0x34, 0x48, 0x83, 0x3d, 0x84
//0xf, 0x1f, 0x44, 0x0, 0x0, 0x48, 0x83, 0x3d, 0xfb, 0x21, 0x0, 0x0, 0x0, 0x55, 0x48, 0x89, 0xe5, 0x53, 0x75, 0x26, 0x48, 0xc7, 0xc1, 0x51
//55 48 8b 3d d5 55 0 0 48 89 e5 e8 d 47 d c1 48 c7 c7 0 d0 23 c0 e8 b1 b4 f7 ff 48 8b 3d c2 55 0 0 e8 85 24 e6 c0 e8 b0 ff ff ff e8 2 0 0 0 5d c3 55 48 c7 c6 b9 b8 23 c0 48 c7 c7 c0 63 cf 81 48 89 e5 e8 2 a7 f7 ff 48 8b 3d ab 55 0 0 e8 c6 46 d c1 bf 3 0 0 0 e8 4c a8 f7 ff 48 c7 c7
// ���ڵ����Ķ����������ƥ��
//     Ŀǰ�Ǽ�ʵ�֣��Ժ�����Ҫ���ÿ���������дһ���ض�������ƥ�亯��
bool CheckMalsoftware(unsigned char *pText, int len, MalSoftware &mal )
{//printf("CheckMalsoftware in\n");
//printf("len %d\n",len);
	for (int i = 0; i < mal.len; i++) {
		MalSoftwareFeature &feat = mal.feats[i];
		//ƥ��
		unsigned char *pTextNow = pText;
		unsigned char *pPattern = feat.f;
		for (int j = 0; j < feat.len; j++){
			if (pTextNow[j] != pPattern[j])
				return false;
			printf("0x%lx, ",pTextNow[j]);
		}
			
	}//printf("``````````````````````find\n");
	return true;
}

// �����������Ƿ�����������������(���԰�������������������)
// ���룺ָ������(len)�Ĵ�������(pText),���ֽ����б�ʾ
// �������ƥ��Ϊ0������Ϊ����ƥ��ɹ��Ķ��������������Ϣ��MalSoftware�ṹָ�룩
//       
MalSoftware *CheckMalsoftware_(unsigned char *pText, int len) 
{//printf("CheckMalsoftware_ in");
	for (int i = 0; i < sizeof(malsoftware) / sizeof(malsoftware[0]); i++)
		if ( CheckMalsoftware(pText, len, malsoftware[i]) )
			return malsoftware + i;
	return 0;
}

