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
// 恶意软件特征库
//     目前仅包含代码序列特征
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
// 对于单个的恶意软件特征匹配
//     目前是简单实现，以后大概需要针对每个恶意软件写一个特定的特征匹配函数
bool CheckMalsoftware(unsigned char *pText, int len, MalSoftware &mal )
{//printf("CheckMalsoftware in\n");
//printf("len %d\n",len);
	for (int i = 0; i < mal.len; i++) {
		MalSoftwareFeature &feat = mal.feats[i];
		//匹配
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

// 检查代码序列是否包含恶意软件的特征(可以包含几条代码特征序列)
// 输入：指定长度(len)的代码序列(pText),以字节序列表示
// 输出：不匹配为0，否则为特征匹配成功的恶意软件的描述信息（MalSoftware结构指针）
//       
MalSoftware *CheckMalsoftware_(unsigned char *pText, int len) 
{//printf("CheckMalsoftware_ in");
	for (int i = 0; i < sizeof(malsoftware) / sizeof(malsoftware[0]); i++)
		if ( CheckMalsoftware(pText, len, malsoftware[i]) )
			return malsoftware + i;
	return 0;
}

