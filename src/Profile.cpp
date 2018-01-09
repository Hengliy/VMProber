///////////////////////////////////////////////////////////////////////////////
// Name:        Profile.cpp
// Purpose:     Profile of monitoring part of the application. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-09-16
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "wx/app.h"
#include "wx/config.h"
#include "wx/fileconf.h"
#include "Profile.h"

// 读取单个虚拟机的监控配置
bool ReadSettings(SettingsMoni &vm, wxFileConfig *config )
{
	wxString str_time;
	if (!config->Read("Start", &str_time))
		return false;
	string s = std::string(str_time);
	tm tm_start;
	// 格式：//2017.08.22 02:08:09
	sscanf(s.c_str(), "%d.%d.%d %d:%d:%d",
		&tm_start.tm_year, &tm_start.tm_mon, &tm_start.tm_mday,
		&tm_start.tm_hour, &tm_start.tm_min, &tm_start.tm_sec);
	tm_start.tm_year -= 1900; // from 1900
	tm_start.tm_mon --; // to 0-11
	tm_start.tm_isdst = 0;
	// ok
	time_t t= time(NULL);
	vm.t_monitoring = mktime(&tm_start);
	vm.tm_monitoring = *localtime(&vm.t_monitoring );  // 本地时间

	wxString str_repeat;
	if (!config->Read(wxT("RepeatType"), &str_repeat)) 
		return false;
	if (str_repeat == wxT("MONITOR_EACH_HOUR"))
		vm.repeat = MONITOR_EACH_HOUR;
	else if (str_repeat == wxT("MONITOR_EACH_DAY"))
		vm.repeat = MONITOR_EACH_DAY;
	else if (str_repeat == wxT("MONITOR_WORKDAY_WEEK"))
		vm.repeat = MONITOR_WORKDAY_WEEK;
	else if (str_repeat == wxT("MONITOR_EACH_WEEK"))
		vm.repeat = MONITOR_EACH_WEEK;
	else if (str_repeat == wxT("MONITOR_EACH_BIWEEK"))
		vm.repeat = MONITOR_EACH_BIWEEK;
	else if (str_repeat == wxT("MONITOR_EACH_MONTH"))
		vm.repeat = MONITOR_EACH_MONTH;
	else
		vm.repeat = MONITOR_ONCE;  // undefined

	wxString str_process, str_module, str_file;
	if (!config->Read(wxT("Process"), &str_process) ) 
		return false;
	vm.os_ds_process = (str_process == wxT("ON"));
	if (!config->Read(wxT("Module"), &str_module))
		return false;
	vm.os_ds_module = (str_module == wxT("ON"));
	if (!config->Read(wxT("File"), &str_file))
		return false;
	vm.os_ds_file = (str_file == wxT("ON"));

	wxString str_path ;
	if (!config->Read(wxT("FilePath"), &str_path))
		return true;  // 可能没有
	vm.path = str_path;

	return true;
}
// 保存单个虚拟机的监控配置
bool SaveSettings(SettingsMoni &vm, wxFileConfig *config)
{
	wxString str_time;
	str_time = str_time.Format("%04d.%02d.%02d %02d:%02d:%02d", 
		vm.tm_monitoring.tm_year+1990, vm.tm_monitoring.tm_mon+1, vm.tm_monitoring.tm_mday,
		vm.tm_monitoring.tm_hour, vm.tm_monitoring.tm_min, vm.tm_monitoring.tm_sec);
	config->Write(wxT("Start"), str_time);

	wxString str_repeat;
	if (vm.repeat == MONITOR_EACH_HOUR )
		config->Write(wxT("RepeatType"), wxT("MONITOR_EACH_HOUR"));
	else if (vm.repeat == MONITOR_EACH_DAY)
		config->Write(wxT("RepeatType"), wxT("MONITOR_EACH_DAY"));
	else if (vm.repeat == MONITOR_WORKDAY_WEEK)
		config->Write(wxT("RepeatType"), wxT("MONITOR_WORKDAY_WEEK"));
	else if (vm.repeat == MONITOR_EACH_WEEK)
		config->Write(wxT("RepeatType"), wxT("MONITOR_EACH_WEEK"));
	else if (vm.repeat == MONITOR_EACH_BIWEEK)
		config->Write(wxT("RepeatType"), wxT("MONITOR_EACH_BIWEEK"));
	else if (vm.repeat == MONITOR_EACH_MONTH)
		config->Write(wxT("RepeatType"), wxT("MONITOR_EACH_MONTH"));
	else 
		config->Write(wxT("RepeatType"), wxT("MONITOR_ONCE"));

	config->Write(wxT("Process"), ( vm.os_ds_process ? wxT("ON") : wxT("OFF") ) );
	config->Write(wxT("Module"), (vm.os_ds_module ? wxT("ON") : wxT("OFF")));
	config->Write(wxT("File"), (vm.os_ds_file ? wxT("ON") : wxT("OFF")));
	//config->Write("LastPrompt", "AAAAAA");
	//config->Write("/LastRun/CalculatedValues/MaxValue", value);
	//config->SetPath("/LastRun");
	//config->Write("MaxValue2", value);

	config->Write(wxT("FilePath"), vm.path );

	return true;
}

bool LoadProfile(MonitorProfile &profile, const wxString &filename /*= wxEmptyString*/)
{
	profile.settings.empty();  // 删除现有的
	if (filename != wxEmptyString )
		profile.filename = filename ;
	wxFileConfig *config = new wxFileConfig(wxEmptyString, wxEmptyString, profile.filename);

	// save current group 
	wxString oldpath = config->GetPath();

	// read settings of all VMs
	long index;
	wxString vmos_group;
	bool ret = config->GetFirstGroup(vmos_group, index);
	while (ret) {
		// read monitoring-settings of a virtual machine
		SettingsMoni vm;
		config->SetPath(vmos_group);    // goto group 
		if (ReadSettings(vm, config)) {
			vm.vm_os = vmos_group;
			profile.settings.push_back(vm);
		}
		config->SetPath(oldpath);		// restore group

		// next
		ret = config->GetNextGroup(vmos_group, index);
	}

	delete config;

	return true;
}

bool SaveProfile(MonitorProfile &profile, const wxString &filename /*= wxEmptyString*/ )
{
	wxString fname = filename;
	if (fname == wxEmptyString)
		fname = profile.filename;
	wxFileConfig *config = new wxFileConfig(wxEmptyString, wxEmptyString, fname);
	config->DeleteAll();  // empty the profile

	// save current group 
	wxString oldpath = config->GetPath();

	// save settings of all VMs
	for (size_t i = 0; i < profile.settings.size(); i++ ) {
		SettingsMoni &vm = profile.settings[i] ;
		config->SetPath(vm.vm_os);    // goto group 
		SaveSettings(vm, config);
		config->Write(wxT(""), wxT(""));
		config->SetPath(oldpath);		// restore group
	}

	delete config;

	return true;

}
