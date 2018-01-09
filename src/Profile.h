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
	wxString vm_os;                 // 监控对象（虚拟机OS内核） 
	time_t t_monitoring;            // 监控启动的时间点
	struct tm tm_monitoring;        // details of t_monitoring
	MonitorRepeatType repeat;       // 监控的重复周期
	bool os_ds_process;             // 监控OS内核数据结构：进程 
	bool os_ds_module;              // 监控OS内核数据结构：模块 
	bool os_ds_file;                // 监控OS内核数据结构：文件
	wxString path;                  // 文件监控的路径
	time_t t_gap;                   // 周期
	time_t t_next;                  // 下次启动时间
} SettingsMoni;

typedef struct _MonitorProfile {
	wxString filename;
	vector< SettingsMoni > settings;
} MonitorProfile ;

// interfaces
bool LoadProfile(MonitorProfile &profile, const wxString &filename = wxEmptyString);
bool SaveProfile(MonitorProfile &profile, const wxString &filename = wxEmptyString);

#endif
