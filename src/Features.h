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
// 恶意软件代码特征
typedef struct _MalSoftwareFeature {
	int offset;         // 偏移量
	int len;            // 长度
	unsigned char f[100];// 注意这是字符数组，不是字符串，中间可能含0
} MalSoftwareFeature ;

// 恶意软件
typedef struct _MalSoftware {
	char *name;
	char *description;    
	int len;            // 实际特征数
	MalSoftwareFeature feats[5];//最多5特征
} MalSoftware;

// 检查代码序列是否包含恶意软件的特征(可以包含几条代码特征序列)
// 输入：指定长度(len)的代码序列(pText),以字节序列表示
// 输出：不匹配为0，否则为特征匹配成功的恶意软件的描述信息（MalSoftware结构指针）
//       
MalSoftware *CheckMalsoftware_(unsigned char *pText, int len);


#endif
