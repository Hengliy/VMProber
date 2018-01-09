///////////////////////////////////////////////////////////////////////////////
// Name:        Features.h
// Purpose:     Head file for Features.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#ifndef __FEATURES_H__
#define __FEATURES_H__
#include <iostream>
//#include "definition.h"
// ���������������
typedef struct _MalSoftwareFeature {
	int offset;         // ƫ����
	int len;            // ����
	unsigned char f[100];// ע�������ַ����飬�����ַ������м���ܺ�0
} MalSoftwareFeature ;

// �������
typedef struct _MalSoftware {
	char *name;
	char *description;    
	int len;            // ʵ��������
	MalSoftwareFeature feats[5];//���5����
} MalSoftware;

// �����������Ƿ�����������������(���԰�������������������)
// ���룺ָ������(len)�Ĵ�������(pText),���ֽ����б�ʾ
// �������ƥ��Ϊ0������Ϊ����ƥ��ɹ��Ķ��������������Ϣ��MalSoftware�ṹָ�룩
//       
MalSoftware *CheckMalsoftware_(unsigned char *pText, int len);


#endif
