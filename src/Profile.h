///////////////////////////////////////////////////////////////////////////////
// Name:        Profile.h
// Purpose:     Head file of Profile.cpp.
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-09-16
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#ifndef __PROFILE_H__
#define __PROFILE_H__

#include "vector"
using namespace std;
#include <wx/string.h>
#include "time.h"

typedef enum { 
	MONITOR_ONCE = 1 ,
	MONITOR_EACH_HOUR,
	MONITOR_HALFDAY,
	MONITOR_EACH_DAY,
	MONITOR_WORKDAY_WEEK,
	MONITOR_EACH_WEEK,
	MONITOR_EACH_BIWEEK,
	MONITOR_EACH_MONTH
} MonitorRepeatType ;

typedef struct _SettingsMoni {
	wxString vm_os;                 // ��ض��������OS�ںˣ� 
	time_t t_monitoring;            // ���������ʱ���
	struct tm tm_monitoring;        // details of t_monitoring
	MonitorRepeatType repeat;       // ��ص��ظ�����
	bool os_ds_process;             // ���OS�ں����ݽṹ������ 
	bool os_ds_module;              // ���OS�ں����ݽṹ��ģ�� 
	bool os_ds_file;                // ���OS�ں����ݽṹ���ļ�
	wxString path;                  // �ļ���ص�·��
	time_t t_gap;                   // ����
	time_t t_next;                  // �´�����ʱ��
} SettingsMoni;

typedef struct _MonitorProfile {
	wxString filename;
	vector< SettingsMoni > settings;
} MonitorProfile ;

// interfaces
bool LoadProfile(MonitorProfile &profile, const wxString &filename = wxEmptyString);
bool SaveProfile(MonitorProfile &profile, const wxString &filename = wxEmptyString);

#endif
