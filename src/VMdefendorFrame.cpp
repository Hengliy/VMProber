
///////////////////////////////////////////////////////////////////////////////
// Name:        VMdefendorFrame.cpp
// Purpose:     Main frame of the application. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include <iostream>
using namespace std;

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include "definition.h"
#include "wx/app.h"
#include "wx/grid.h"
#include "wx/treectrl.h"
#include "wx/spinctrl.h"
#include "wx/artprov.h"
#include "wx/clipbrd.h"
#include "wx/image.h"
#include "wx/colordlg.h"
#include "wx/wxhtml.h"
#include "wx/imaglist.h"
#include "wx/dataobj.h"
#include "wx/dcclient.h"
#include "wx/bmpbuttn.h"
#include "wx/menu.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
#include "wx/msgdlg.h"
#include "wx/textdlg.h"
#include "wx/filedlg.h"
#include "module.h"

#include "wx/aui/aui.h"
#include "../rc/VMdefendor.xpm"

#include "VMdefendor.h"

#include "VMdefendorFrame.h"

#include "Profile.h"
#include "SizeReportCtrl.h"
#include "SettingsPanel.h"
#include "PanelWelcome.h"
#include "PanelVM.h"
#include "PanelProcess.h"
#include "PanelModule.h"
#include "PanelFile.h"
#include "ProcessTree.h"
#include "ModuleList.h"
#include "VMList.h"
#include "CustomArtProv.h"
#include "WorkerProcess.h"
#include "VMStatusBar.h"
#include "ProfileMain.h"
#include "SettingMain.h"
#include "FileTree.h"

#include "process_list.h"
#ifdef ____LIBVMI____

#include <libvmi/libvmi.h>
#include "process.h"

#include <stdio.h>
#endif // ____LIBVMI____

wxBEGIN_EVENT_TABLE(VMdefendorFrame, wxFrame)
	// File
	EVT_MENU(ID_PROFILE_SWITCH, VMdefendorFrame::OnProfileSwitch)
	EVT_MENU(ID_PROFILE_SAVE, VMdefendorFrame::OnProfileSave)
	EVT_MENU(wxID_EXIT, VMdefendorFrame::OnExit)
	// View
    EVT_MENU(ID_AllowFloating, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_TransparentHint, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_VenetianBlindsHint, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_RectangleHint, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_NoHint, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_HintFade, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_NoVenetianFade, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_TransparentDrag, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_LiveUpdate, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_AllowActivePane, VMdefendorFrame::OnManagerFlag)
    EVT_MENU(ID_NotebookTabFixedWidth, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookNoCloseButton, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookCloseButton, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookCloseButtonAll, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookCloseButtonActive, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookAllowTabMove, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookAllowTabExternalMove, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookAllowTabSplit, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookScrollButtons, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookWindowList, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookArtGloss, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookArtSimple, VMdefendorFrame::OnNotebookFlag)
    EVT_MENU(ID_NotebookAlignTop,     VMdefendorFrame::OnTabAlignment)
    EVT_MENU(ID_NotebookAlignBottom,  VMdefendorFrame::OnTabAlignment)
    EVT_MENU(ID_NoGradient, VMdefendorFrame::OnGradient)
    EVT_MENU(ID_VerticalGradient, VMdefendorFrame::OnGradient)
    EVT_MENU(ID_HorizontalGradient, VMdefendorFrame::OnGradient)
    EVT_MENU(ID_AllowToolbarResizing, VMdefendorFrame::OnToolbarResizing)
	// Monitor & toolbar
	EVT_MENU(ID_VM_ENUMERATE, VMdefendorFrame::OnVMEnumerate)
	EVT_MENU(ID_VM_FIND, VMdefendorFrame::OnVMFind)
	EVT_MENU(ID_VM_MONITOR_START, VMdefendorFrame::OnVMStart)
	EVT_MENU(ID_OS_SCAN, VMdefendorFrame::OnOSScan)
	EVT_MENU(ID_OS_SNAP, VMdefendorFrame::OnOSSnap)
	EVT_MENU(ID_OS_MONITORLIST, VMdefendorFrame::OnOSMonitorlist)
	EVT_MENU(ID_OS_MONITORLIST_ADD, VMdefendorFrame::OnOSMonitorlistAdd)
	EVT_MENU(ID_OS_MONITORLIST_REMOVE, VMdefendorFrame::OnOSMonitorlistRemove)
	EVT_MENU(ID_OS_MONITOR_START, VMdefendorFrame::OnOSMonitorStart)
	EVT_MENU(ID_PROCESS_KILL, VMdefendorFrame::OnProcessKill)
	EVT_MENU(ID_PROCESS_SUSPEND, VMdefendorFrame::OnProcessSuspend)
	EVT_MENU(ID_PROCESS_INFO, VMdefendorFrame::OnProcessInfo)
	// Toolkit
	EVT_MENU(ID_TOOLKIT_SCAN_PROCESS, VMdefendorFrame::OnToolkitScanProcess)
	EVT_MENU(ID_TOOLKIT_SCAN_PROCESS_IOVIEW, VMdefendorFrame::OnToolkitScanProcessIOView)
	EVT_MENU(ID_TOOLKIT_SCAN_MODULE, VMdefendorFrame::OnToolkitScanModule)
	EVT_MENU(ID_TOOLKIT_SCAN_FILE, VMdefendorFrame::OnToolkitScanFile)
	EVT_MENU(ID_SETTINGS, VMdefendorFrame::OnSettings)
	EVT_MENU(ID_SETTINGS_VM, VMdefendorFrame::OnSettingsVM)
	// Windows
	EVT_MENU(ID_WIN_PROCESS, VMdefendorFrame::OnWinProcess)
	EVT_MENU(ID_WIN_PROCESS_LIST, VMdefendorFrame::OnWinProcessList)
	EVT_MENU(ID_WIN_VMS, VMdefendorFrame::OnWinVMs)
	EVT_MENU(ID_WIN_NTBOOK, VMdefendorFrame::OnWinNTbook)
	EVT_MENU(ID_WIN_FILE, VMdefendorFrame::OnWinFile)
	EVT_MENU(ID_WIN_MODULE, VMdefendorFrame::OnWinModule)
	EVT_MENU(ID_WIN_MSG, VMdefendorFrame::OnWinMsg)
	EVT_MENU_RANGE(ID_FirstPerspective, ID_FirstPerspective + 1000, VMdefendorFrame::OnRestorePerspective)
	// Help
	EVT_MENU(wxID_ABOUT, VMdefendorFrame::OnAbout)

	//
	EVT_THREAD(WORKER_EVENT, VMdefendorFrame::OnWorkerEvent)
	EVT_THREAD(WORKER_EVENT_START, VMdefendorFrame::OnWorkerEventStart)
	EVT_THREAD(WORKER_EVENT_END, VMdefendorFrame::OnWorkerEventEnd)
	EVT_THREAD(WORKER_EVENT_PROCESS_TREE, VMdefendorFrame::OnWorkerEventProcessTree)
	EVT_THREAD(WORKER_EVENT_PROCESS, VMdefendorFrame::OnWorkerEventProcess)
	EVT_THREAD(WORKER_EVENT_MODULE, VMdefendorFrame::OnWorkerEventModule)

	EVT_ERASE_BACKGROUND(VMdefendorFrame::OnEraseBackground)
	EVT_SIZE(VMdefendorFrame::OnSize)

	EVT_TIMER(ID_TIMER_1_SEC, VMdefendorFrame::OnTimer)
	EVT_TIMER(ID_TIMER_MONITOR, VMdefendorFrame::OnTimerMonitor)

	EVT_TREE_ITEM_RIGHT_CLICK(wxID_ANY, VMdefendorFrame::OnShowPanelProcess)
	EVT_LISTBOX_DCLICK(wxID_ANY, VMdefendorFrame::OnWinMsgDclik)

    EVT_UPDATE_UI(ID_NotebookTabFixedWidth, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookNoCloseButton, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookCloseButton, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookCloseButtonAll, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookCloseButtonActive, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookAllowTabMove, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookAllowTabExternalMove, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookAllowTabSplit, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookScrollButtons, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NotebookWindowList, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_AllowFloating, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_TransparentHint, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_VenetianBlindsHint, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_RectangleHint, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoHint, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_HintFade, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoVenetianFade, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_TransparentDrag, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_LiveUpdate, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_NoGradient, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_VerticalGradient, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_HorizontalGradient, VMdefendorFrame::OnUpdateUI)
    EVT_UPDATE_UI(ID_AllowToolbarResizing, VMdefendorFrame::OnUpdateUI)
    EVT_AUITOOLBAR_TOOL_DROPDOWN(ID_DropDownToolbarItem, VMdefendorFrame::OnDropDownToolbarItem)
    EVT_AUI_PANE_CLOSE(VMdefendorFrame::OnPaneClose)
    EVT_AUINOTEBOOK_ALLOW_DND(wxID_ANY, VMdefendorFrame::OnAllowNotebookDnD)
    EVT_AUINOTEBOOK_PAGE_CLOSE(wxID_ANY, VMdefendorFrame::OnNotebookPageClose)
    EVT_AUINOTEBOOK_PAGE_CLOSED(wxID_ANY, VMdefendorFrame::OnNotebookPageClosed)

	EVT_MENU(ID_CreateTree, VMdefendorFrame::OnCreateTree)
	EVT_MENU(ID_CreateGrid, VMdefendorFrame::OnCreateGrid)
	EVT_MENU(ID_CreateText, VMdefendorFrame::OnCreateText)
	EVT_MENU(ID_CreateSizeReport, VMdefendorFrame::OnCreateSizeReport)
	EVT_MENU(ID_CreateNotebook, VMdefendorFrame::OnCreateNotebook)
	EVT_MENU(ID_CreatePerspective, VMdefendorFrame::OnCreatePerspective)
	EVT_MENU(ID_CopyPerspectiveCode, VMdefendorFrame::OnCopyPerspectiveCode)
	EVT_MENU(ID_CustomizeToolbar, VMdefendorFrame::OnCustomizeToolbar)
	EVT_MENU(ID_GridContent, VMdefendorFrame::OnChangeContentPane)
	EVT_MENU(ID_TreeContent, VMdefendorFrame::OnChangeContentPane)
	EVT_MENU(ID_TextContent, VMdefendorFrame::OnChangeContentPane)
	EVT_MENU(ID_SizeReportContent, VMdefendorFrame::OnChangeContentPane)
	EVT_MENU(ID_HTMLContent, VMdefendorFrame::OnChangeContentPane)
	EVT_MENU(ID_NotebookContent, VMdefendorFrame::OnChangeContentPane)

wxEND_EVENT_TABLE()


VMdefendorFrame::VMdefendorFrame(wxWindow* parent,
                 wxWindowID id,
                 const wxString& title,
                 const wxPoint& pos,
                 const wxSize& size,
                 long style)
        : wxFrame(parent, id, title, pos, size, style)
{
    //tell wxAuiManager to manage this frame
    m_mgr.SetManagedWindow(this);

    // set frame icon
    SetIcon(wxIcon(WMdefendor_xpm));
	// min size for the frame itself isn't completely done.
	SetMinSize(wxSize(400, 300));
printf("1\n");
	// Profile, 目前主要用于监控，以后会丰富其余的系统配置
	LoadProfile(config, wxT("/MyAppName.conf"));
printf("2\n");
	// create menu, toolbar and statusbar
	InitMenu();printf("3\n");
	InitStatusBar();printf("4\n");
	InitToolBar();  // managed by m_mgr
	printf("5\n");
	// other panes except toolbars initialized in InitToolBar() 
	InitPanels();   // managed by m_mgr
printf("6\n");
	// perspectives, i.e. layouts of windows(panes) in VMArmour
	// You can save and restore them so that you can change layout while VMArour running.
	// make some default perspectives and save them
	wxString perspective_all = m_mgr.SavePerspective();  // some error in fact
	wxString perspective_default = m_mgr.SavePerspective();
	m_perspectives.Add(perspective_default);
    m_perspectives.Add(perspective_all);

	// 主定时器, 1s间隔
	InitMainTimer();

	// 初始化并启动对虚拟机OS的监控
	InitMonitor();

	// 当前虚拟机编号
	m_vm_current_index = -1;  //-1表示没有
	AppendVM(config);  
	if (0 < m_vms.size())
		SetCurrentVM( 0 );

	// "commit" all changes made to wxAuiManager
    m_mgr.Update();
}
VMdefendorFrame::~VMdefendorFrame()
{
	m_mgr.UnInit();   // 退出wxAuiManager
	ExitMainTimer();
	ExitMonitor();
	ExitThreads();
}

bool temp_(VM_vmi &vmi1)
{
	VM_vmi_init("ubuntu14.04",vmi1);//初始化虚拟机
 	printf("exit\n");
	VM_find_process_list(vmi1,vmi1.process);//链式
	return true;
}


void VMdefendorFrame::SetCurrentVM( int index )
{
	// 当前虚拟机编号
	m_vm_current_index = index;  //-1表示没有

	// 无效返回
	if (!(m_vm_current_index < 0 && m_vm_current_index < m_vms.size()))
		return;

	// 保存当前虚拟机
	m_vm_current = m_vms[m_vm_current_index];

	// 清空进程树
	if ( m_process_tree )
		m_process_tree->DeleteAllItems();
}

void VMdefendorFrame::AppendVM( MonitorProfile &profile )
{
	for (size_t i = 0; i < profile.settings.size(); i++) {
		SnapVM snap_vm;
		m_vms.push_back( snap_vm);
	}
}

void VMdefendorFrame::InitMainTimer()
{
	m_timer.SetOwner(this, ID_TIMER_1_SEC);
	m_timer.Start(1000);
}
void VMdefendorFrame::ExitMainTimer()
{
	if (m_timer.IsRunning())
	{
		m_timer.Stop();
	}
}

void VMdefendorFrame::ExitMonitor()
{
	if (m_timer_monitor.IsRunning())
	{
		m_timer_monitor.Stop();
	}
}

void VMdefendorFrame::SetGap(SettingsMoni &conf)
{
	if (conf.repeat == MONITOR_EACH_HOUR)
		conf.t_gap = 60 * 60;
	else if (conf.repeat == MONITOR_HALFDAY)
		conf.t_gap = 12 * 60 * 60;
	else if (conf.repeat == MONITOR_EACH_DAY)
		conf.t_gap = 24 * 60 * 60;
	    //conf.t_gap = 10;
	else if (conf.repeat == MONITOR_WORKDAY_WEEK) // need to adjust for Saturday and Sunday
		conf.t_gap = 24 * 60 * 60;
	else if (conf.repeat == MONITOR_EACH_WEEK)
		conf.t_gap = 7 * 24 * 60 * 60;
	else if (conf.repeat == MONITOR_EACH_BIWEEK)
		conf.t_gap = 14 * 24 * 60 * 60;
	else if (conf.repeat == MONITOR_EACH_MONTH)  // 30 days, need to adjust for months with 31 days
		conf.t_gap = 30 * 24 * 60 * 60;
	else
		conf.t_gap = 20 * 365 * 24 * 60 * 60;              // 20 years
}

void VMdefendorFrame::ComputeNextTime(time_t tnow, SettingsMoni &conf )
{
	conf.t_next = conf.t_monitoring - tnow;
	if (conf.t_next < 0) // 假如初次扫描时刻已经过去，计算距离下次扫描的时长（s）
		conf.t_next = conf.t_gap - ((-conf.t_next) % conf.t_gap );
	conf.t_next += tnow; // to absolute time
	//if ( conf.repeat == MONITOR_EACH_MONTH ) // 须单独处理，暂不支持
}

void VMdefendorFrame::InitMonitor()
{
	// 计算扫描启动间隔(s)
	for (size_t i = 0; i < config.settings.size(); i++) 
		SetGap(config.settings[i]);

	// 
	m_timer_monitor.SetOwner(this, ID_TIMER_MONITOR);

	//
	m_monitor = true;
	((VMStatusBar*)GetStatusBar())->SetMonitorStatus(m_monitor);

	// start
	StartNextTimer();
}

// 计算对虚拟化平台上所有虚拟机扫描的最近的下次启动时刻,用于监控定时器定时
bool VMdefendorFrame::ComputeNextTime(time_t tnow, time_t &tnext )
{
	bool ret = false;
	tnext = tnow + 365*24*60*60 ;  // 最长延时：1年
	for (size_t i = 0; i < config.settings.size(); i++) {
		SettingsMoni &conf = config.settings[i];
		if (conf.repeat == MONITOR_ONCE && conf.t_monitoring < tnow) //已经过时间了
			continue;
		ComputeNextTime(tnow, conf);
		if (tnext > conf.t_next)
			tnext = conf.t_next;
		ret = true;
	}
	return ret;
}

void VMdefendorFrame::StartNextTimer()
{
	time_t tnext;
	time_t tnow = time(NULL);  // 当前时间，度量的起点
	if (!ComputeNextTime(tnow, tnext))
		return;
	// start
	int milisecs = ( tnext - tnow ) * 1000;
	m_timer_monitor.StartOnce(milisecs);
	//m_timer_monitor.StartOnce(5000);
}

void VMdefendorFrame::ExitThreads()
{
	// tell all the threads to terminate: note that they can't terminate while
	// we're deleting them because they will block in their OnExit() -- this is
	// important as otherwise we might access invalid array elements

	{
		wxCriticalSectionLocker locker(wxGetApp().m_critsect);

		// check if we have any threads running first
		const wxArrayThread& threads = wxGetApp().m_threads;
		size_t count = threads.GetCount();

		if (!count)
			return;

		// set the flag indicating that all threads should exit
		wxGetApp().m_shuttingDown = true;
	}

	// now wait for them to really terminate
	wxGetApp().m_semAllDone.Wait();

}


void VMdefendorFrame::InitMenu()
{
	wxMenuBar* mb = new wxMenuBar;

	wxMenu* file_menu = new wxMenu;
	file_menu->Append(ID_PROFILE_SWITCH, wxT("切换当前Profile"));
	file_menu->Append(ID_PROFILE_SAVE, wxT("保存当前Profile"));
	file_menu->AppendSeparator();
	file_menu->Append(wxID_EXIT, wxT("退出"));

	wxMenu* view_menu = new wxMenu;
	view_menu->AppendRadioItem(ID_NotebookArtGloss, wxT("Glossy主题(Default)"));
	view_menu->AppendRadioItem(ID_NotebookArtSimple, wxT("Simple主题"));
	view_menu->AppendSeparator();
	wxMenu* view_menu_tips = new wxMenu;
	view_menu_tips->AppendRadioItem(ID_TransparentHint, wxT("透明的提示"));
	view_menu_tips->AppendRadioItem(ID_VenetianBlindsHint, wxT("软百叶帘提示"));
	view_menu_tips->AppendRadioItem(ID_RectangleHint, wxT("矩形提示"));
	view_menu_tips->AppendRadioItem(ID_NoHint, wxT("无提示"));
	view_menu->AppendSubMenu(view_menu_tips, wxT("提示风格(&F)"));
	wxMenu* view_menu_ani = new wxMenu;
	view_menu_ani->AppendCheckItem(ID_HintFade, wxT("渐变提示"));
	view_menu_ani->AppendCheckItem(ID_AllowFloating, wxT("允许浮动"));
	view_menu_ani->AppendCheckItem(ID_NoVenetianFade, wxT("关闭软百叶帘渐进提示"));
	view_menu_ani->AppendCheckItem(ID_TransparentDrag, wxT("透明拖拽"));
	view_menu_ani->AppendCheckItem(ID_AllowActivePane, wxT("允许活动窗体"));
	view_menu_ani->AppendCheckItem(ID_LiveUpdate, wxT("实时窗体尺寸更新"));
	view_menu->AppendSubMenu(view_menu_ani, wxT("窗口更新风格(&F)"));
	wxMenu* view_menu_caption = new wxMenu;
	view_menu_caption->AppendRadioItem(ID_NoGradient, wxT("窗体标签无渐变"));
	view_menu_caption->AppendRadioItem(ID_VerticalGradient, wxT("窗体标签垂直渐变"));
	view_menu_caption->AppendRadioItem(ID_HorizontalGradient, wxT("窗体标签垂直渐变"));
	view_menu->AppendSubMenu(view_menu_caption, wxT("窗口标题区风格(&F)"));
	view_menu->AppendCheckItem(ID_AllowToolbarResizing, wxT("允许工具栏变更尺寸"));
	view_menu->AppendSeparator();
	wxMenu* view_menu_notebook = new wxMenu;
	view_menu_notebook->AppendRadioItem(ID_NotebookNoCloseButton, wxT("无关闭按钮"));
	view_menu_notebook->AppendRadioItem(ID_NotebookCloseButton, wxT("右侧关闭按钮"));
	view_menu_notebook->AppendRadioItem(ID_NotebookCloseButtonAll, wxT("所有页关闭按钮"));
	view_menu_notebook->AppendRadioItem(ID_NotebookCloseButtonActive, wxT("仅当前页关闭按钮"));
	view_menu_notebook->AppendSeparator();
	view_menu_notebook->AppendRadioItem(ID_NotebookAlignTop, wxT("顶对其"));
	view_menu_notebook->AppendRadioItem(ID_NotebookAlignBottom, wxT("底对齐"));
	view_menu_notebook->AppendSeparator();
	view_menu_notebook->AppendCheckItem(ID_NotebookAllowTabMove, wxT("允许页移动"));
	view_menu_notebook->AppendCheckItem(ID_NotebookAllowTabExternalMove, wxT("允许外部页移动"));
	view_menu_notebook->AppendCheckItem(ID_NotebookAllowTabSplit, wxT("允许分割"));
	view_menu_notebook->AppendCheckItem(ID_NotebookScrollButtons, wxT("滚动条可见"));
	view_menu_notebook->AppendCheckItem(ID_NotebookWindowList, wxT("窗口列表按钮可见"));
	view_menu_notebook->AppendCheckItem(ID_NotebookTabFixedWidth, wxT("固定宽度页"));
	view_menu->AppendSubMenu(view_menu_notebook, wxT("主显示窗口风格(&F)"));

	wxMenu* monitor_menu = new wxMenu;
	monitor_menu->Append(ID_VM_ENUMERATE, wxT("枚举虚拟机"));
	monitor_menu->Append(ID_VM_FIND, wxT("查找虚拟机"));
	monitor_menu->Append(ID_VM_MONITOR_START, wxT("启动/暂停虚拟化平台监控任务"));
	monitor_menu->AppendSeparator();
	monitor_menu->Append(ID_OS_SCAN, wxT("扫描虚拟机OS内核"));
	monitor_menu->Append(ID_OS_SNAP, wxT("虚拟机OS内核快照"));
	monitor_menu->Append(ID_OS_MONITORLIST, wxT("加入/退出虚拟机OS内核监控列表"));
	monitor_menu->Append(ID_OS_MONITOR_START, wxT("启动/暂停虚拟化OS内核监控"));
	monitor_menu->AppendSeparator();
	//monitor_menu->Append(ID_PROCESS_KILL, wxT("Kill进程"));
	//monitor_menu->Append(ID_PROCESS_SUSPEND, wxT("挂起/解挂进程"));
	monitor_menu->Append(ID_PROCESS_INFO, wxT("进程详细信息"));
	monitor_menu->AppendSeparator();
	//monitor_menu->Append(ID_OS_PORT, wxT("TCP/IP端口列表"));

	wxMenu* options_menu = new wxMenu;
	options_menu->Append(ID_TOOLKIT_SCAN_PROCESS, wxT("隐藏进程扫描工具"));
	options_menu->Append(ID_TOOLKIT_SCAN_FILE, wxT("隐藏文件扫描工具"));
	options_menu->Append(ID_TOOLKIT_SCAN_PROCESS_IOVIEW, wxT("基于内外视图的隐藏进程扫描工具"));
	options_menu->AppendSeparator();
	options_menu->Append(ID_SETTINGS, wxT("设置"));

	window_menu = new wxMenu;
	window_menu->Append(ID_WIN_VMS, wxT("虚拟机列表窗口"));
	window_menu->Append(ID_WIN_PROCESS, wxT("进程树形列表窗口"));
	window_menu->Append(ID_WIN_PROCESS_LIST, wxT("进程顺序列表窗口"));
	window_menu->Append(ID_WIN_NTBOOK, wxT("主信息窗口"));
	//window_menu->Check(ID_WIN_PROCESS,true);
	//window_menu->AppendCheckItem(ID_WIN_PORT, wxT("端口列表"));
	window_menu->Append(ID_WIN_FILE, wxT("文件列表窗口"));
	window_menu->Append(ID_WIN_MODULE, wxT("模块列表窗口"));
	window_menu->AppendSeparator();
	window_menu->Append(ID_WIN_MSG, wxT("消息窗口"));
	window_menu->AppendSeparator();
	window_menu->Append(ID_FirstPerspective+0, wxT("恢复默认窗口布局"));

	wxMenu* help_menu = new wxMenu;
	// help_menu->Append(wxID_HELP, wxT("帮助"));
	// help_menu->AppendSeparator();
	help_menu->Append(wxID_ABOUT, wxT("关于"));

	mb->Append(file_menu, wxT("文件(&F)"));
	mb->Append(view_menu, wxT("视图(&V)"));
	mb->Append(monitor_menu, wxT("监控(&M)"));
	mb->Append(options_menu, wxT("工具(&T)"));
	mb->Append(window_menu, wxT("窗口(&W)"));
	mb->Append(help_menu, wxT("帮助(&H)"));

	SetMenuBar(mb);
}
void VMdefendorFrame::InitLog()
{
	//m_panel = new wxPanel(this, wxID_ANY);
	//m_logWindow = new wxTextCtrl(m_panel, wxID_ANY, wxEmptyString,
	//	wxDefaultPosition, wxDefaultSize,
	//	wxTE_READONLY | wxTE_MULTILINE | wxSUNKEN_BORDER);

	//m_logOld = wxLog::SetActiveTarget(new wxLogTextCtrl(m_logWindow));
}


void VMdefendorFrame::InitToolBar()
{
	wxArtProvider::Push(new CustomArtProvider);

	wxAuiToolBarItemArray prepend_items;
	wxAuiToolBarItemArray append_items;
	wxAuiToolBarItem item;
	item.SetKind(wxITEM_SEPARATOR);
	append_items.Add(item);
	item.SetKind(wxITEM_NORMAL);
	item.SetId(ID_CustomizeToolbar);
	item.SetLabel(_("Customize..."));
	append_items.Add(item);

	// create toolbar for 虚拟化平台监控
	wxAuiToolBar* tb2 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		//wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW | wxAUI_TB_HORIZONTAL);
		wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_HORIZONTAL);
	tb2->SetToolBitmapSize(wxSize(32, 48));

	wxBitmap tb2_bmp1 = wxArtProvider::GetBitmap(wxART_ID_VM_EMUERATE, wxART_OTHER, wxSize(32, 48));
	tb2->AddTool(ID_VM_ENUMERATE, wxT("Test"), tb2_bmp1, wxT("枚举虚拟机"));
	wxBitmap tb2_bmp2 = wxArtProvider::GetBitmap(wxART_ID_VM_FIND, wxART_OTHER, wxSize(32, 48));
	tb2->AddTool(ID_VM_FIND, wxT("Test"), tb2_bmp2, wxT("查找虚拟机"));
	tb2->AddSeparator();
	wxBitmap tb2_bmp3 = wxArtProvider::GetBitmap(wxART_ID_VM_MONITOR_START, wxART_OTHER, wxSize(32, 48));
	tb2->AddTool(ID_VM_MONITOR_START, wxT("Test"), tb2_bmp3, wxT("启动/暂停虚拟化平台的目标虚拟机监控"), wxITEM_CHECK);
	tb2->Realize();


	// create toolbar for 单个虚拟机OS监控
	wxAuiToolBar* tb3 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		//wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
		wxAUI_TB_DEFAULT_STYLE );
	tb3->SetToolBitmapSize(wxSize(32, 48));

	m_choice_vms = new wxChoice(tb3, ID_TOOL_CHOICE_VM );
	FillVMs(m_choice_vms);
	m_choice_vms->SetSelection(0);
	tb3->AddControl(m_choice_vms);
	wxBitmap tb3_bmp1 = wxArtProvider::GetBitmap(wxART_ID_OS_SCAN, wxART_OTHER, wxSize(32, 48));
	tb3->AddTool(ID_OS_SCAN, wxT("Monitor"), tb3_bmp1, wxT("扫描当前虚拟机OS内核"));
	wxBitmap tb3_bmp2 = wxArtProvider::GetBitmap(wxART_ID_OS_MONITOR_START, wxART_OTHER, wxSize(32, 48));
	tb3->AddTool(ID_OS_MONITOR_START, wxT("Monitor"), tb3_bmp2, wxT("启动/暂停当前虚拟机OS的完整性监控"), wxITEM_CHECK);
	wxBitmap tb3_bmp3 = wxArtProvider::GetBitmap(wxART_ID_OS_MONITORLIST_ADD, wxART_OTHER, wxSize(32, 48));
	tb3->AddTool(ID_OS_MONITORLIST_ADD, wxT("Monitor"), tb3_bmp3, wxT("加入当前虚拟机OS内核监控清单") );
	wxBitmap tb3_bmp4 = wxArtProvider::GetBitmap(wxART_ID_OS_MONITORLIST_REMOVE, wxART_OTHER, wxSize(32, 48));
	tb3->AddTool(ID_OS_MONITORLIST_REMOVE, wxT("Monitor"), tb3_bmp4, wxT("退出当前虚拟机OS内核监控清单"));
	wxBitmap tb3_bmp5 = wxArtProvider::GetBitmap(wxART_ID_OS_MONITORLIST_SETTINGS, wxART_OTHER, wxSize(32, 48));
	tb3->AddTool(ID_SETTINGS_VM, wxT("Monitor"), tb3_bmp5, wxT("设置当前虚拟机OS的内核监控配置"));
	//tb3->SetCustomOverflowItems(prepend_items, append_items);
	tb3->Realize();

	// create toolbar for 进程处理
	wxAuiToolBar* tb4 = new wxAuiToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
		//wxAUI_TB_DEFAULT_STYLE | wxAUI_TB_OVERFLOW);
		wxAUI_TB_DEFAULT_STYLE );
	tb4->SetToolBitmapSize(wxSize(32, 48));

	//wxChoice* m_choice_process = new wxChoice(tb4, ID_SampleItem + 40+0);
	m_choice_process = new wxChoice(tb4, ID_TOOL_CHOICE_PROCESS , wxDefaultPosition,wxSize(150, -1));
	FillProcesses(m_choice_process);
	m_choice_process->SetSelection(0);
	tb4->AddControl(m_choice_process);
	//wxBitmap tb4_bmp1 = wxArtProvider::GetBitmap(wxART_ID_PROCESS_KILL, wxART_OTHER, wxSize(32, 48));
	//tb4->AddTool(ID_PROCESS_KILL, wxT("Monitor"), tb4_bmp1, wxT("Kill进程"));
	//wxBitmap tb4_bmp2 = wxArtProvider::GetBitmap(wxART_ID_PROCESS_SUSPEND, wxART_OTHER, wxSize(32, 48));
	//tb4->AddTool(ID_PROCESS_SUSPEND, wxT("Monitor"), tb4_bmp2, wxT("挂起/解挂当前进程"), wxITEM_CHECK);
	//wxBitmap tb4_bmp3 = wxArtProvider::GetBitmap(wxART_ID_PROCESS_MONITORLIST_ADD, wxART_OTHER, wxSize(32, 48));
	//tb4->AddTool(ID_PROCESS_MONITORLIST_ADD, wxT("Monitor"), tb4_bmp3, wxT("加入当前进程核监控清单"), wxITEM_CHECK);
	//wxBitmap tb4_bmp4 = wxArtProvider::GetBitmap(wxART_ID_PROCESS_MONITORLIST_REMOVE, wxART_OTHER, wxSize(32, 48));
	//tb4->AddTool(ID_PROCESS_MONITORLIST_REMOVE, wxT("Monitor"), tb4_bmp4, wxT("退出当前进程核监控清单"), wxITEM_CHECK);
	tb4->SetCustomOverflowItems(prepend_items, append_items);
	tb4->Realize();

	m_mgr.AddPane(tb2, wxAuiPaneInfo().
		Name(wxT("tb2")).Caption(wxT("虚拟化平台监控工具栏")).
		ToolbarPane().Top().Row(1));

	m_mgr.AddPane(tb3, wxAuiPaneInfo().
		Name(wxT("tb3")).Caption(wxT("虚拟化内核完整性监控工具栏")).
		ToolbarPane().Top().Row(1).Position(1));

	m_mgr.AddPane(tb4, wxAuiPaneInfo().
		Name(wxT("tb4")).Caption(wxT("进程监控和处理工具栏")).
		ToolbarPane().Top().Row(1).Position(2));

	//m_mgr.AddPane(tb5, wxAuiPaneInfo().
	//	Name(wxT("tb5")).Caption(wxT("文件监控和处理工具栏")).
	//	ToolbarPane().Left().
	//	GripperTop());

	int i, count;
	wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
	for (i = 0, count = all_panes.GetCount(); i < count; ++i)
		if (!all_panes.Item(i).IsToolbar())
			all_panes.Item(i).Hide();

}

void VMdefendorFrame::InitStatusBar()
{
	SetStatusBar(new VMStatusBar(this, wxSTB_DEFAULT_STYLE));
	//ApplyPaneStyle();
	PositionStatusBar();
	GetStatusBar()->SetStatusText(_("Ready"));
	((VMStatusBar*)GetStatusBar())->SetMonitorStatus(m_monitor);
}

void  VMdefendorFrame::FillProcesses(wxChoice *choice) {
	//choice->AppendString(wxT("532-csrss.exe "));
	//choice->AppendString(wxT("496-dwm.exe "));
	//choice->AppendString(wxT("636-csrss.exe "));
	//choice->AppendString(wxT("15034-aduiodg.exe "));
	//choice->AppendString(wxT("2655-mqswe.exe "));
	//choice->AppendString(wxT("5188-nissrv.exe "));
}

// Init panes except toolbars 
void VMdefendorFrame::InitPanels() 
{
	// VM_module mlist;
	VM_vmi vmi;
	// mlist.name = 0;
	// vector<VM_list_vm> vmlist;
	// for (size_t i = 0; i < config.settings.size(); i++) {
	// 	VM_list_vm vm;
	// 	vm.name = config.settings[i].vm_os;
	// 	vmlist.push_back( vm );
	// }

	VM_list_vm vmlist[100];
    //init_cmp_file(vmi1,"/bin/");
	get_vm_list(vmlist);
	
	struct VM_vmi vmi1;
	//temp_(vmi1);
	//VM_module_init(vmi1.module);
	//VM_find_modules_list(vmi1,vmi1.module);

	m_mgr.AddPane(CreateVMList(this, vmlist, m_vmslist,m_choice_vms), 
		wxAuiPaneInfo().Name(WIN_VMS).Caption(wxT("虚拟机列表")).
		Left().Layer(1).Position(0).MinSize(200,-1).
		CloseButton(true).MaximizeButton(true));
	m_choice_vms->SetSelection(0);
	// m_mgr.AddPane(ShowProcessTree(), wxAuiPaneInfo().
	// 	Name(WIN_PROCESS).Caption(wxT("进程列表")).
	// 	Left().Layer(1).Position(1).
	// 	CloseButton(true).MaximizeButton(true));

	// create some center panes

	
	//m_nb_info->AddPage(CreatePanelFile(m_nb_info, vmi1.file_root), wxT("文件信息"), false, page_bmp);	

	// set up default notebook style
	m_notebook_style = wxAUI_NB_DEFAULT_STYLE | wxAUI_NB_TAB_EXTERNAL_MOVE | wxNO_BORDER;
	m_notebook_theme = 0;
	m_mgr.AddPane(CreateNotebook(), wxAuiPaneInfo().Name(WIN_NTBOOK).
		CenterPane().PaneBorder(false));
	// Show them
	m_mgr.GetPane(WIN_VMS).Show().Left().Layer(1).Row(0).Position(0);
	
	m_mgr.GetPane(WIN_MSG).Show().Bottom().Layer(0).Row(0).Position(0);
	m_mgr.GetPane(WIN_NTBOOK).Show();

	
}

wxAuiDockArt* VMdefendorFrame::GetDockArt()
{
    return m_mgr.GetArtProvider();
}

void VMdefendorFrame::DoUpdate()
{
    m_mgr.Update();
}

void VMdefendorFrame::OnEraseBackground(wxEraseEvent& event)
{
    event.Skip();
}

void VMdefendorFrame::OnSize(wxSizeEvent& event)
{
    event.Skip();
}

void VMdefendorFrame::OnSettings(wxCommandEvent& WXUNUSED(evt))
{
	ProfileDialog Dlg(this, config);//传递参数给你的类
	Dlg.ShowModal(); // 确定返回后，profile这就是正确的输入数值了
}
void VMdefendorFrame::OnSettingsVM(wxCommandEvent& WXUNUSED(evt))
{
	SettingDialog Dlg(this, config.settings[0]);//传递参数给你的类
	Dlg.ShowModal(); // 确定返回后，profile这就是正确的输入数值了
}

void VMdefendorFrame::OnCustomizeToolbar(wxCommandEvent& WXUNUSED(evt))
{
    wxMessageBox(_("Customize Toolbar clicked"));
}

void VMdefendorFrame::OnGradient(wxCommandEvent& event)
{
    int gradient = 0;

    switch (event.GetId())
    {
        case ID_NoGradient:         gradient = wxAUI_GRADIENT_NONE; break;
        case ID_VerticalGradient:   gradient = wxAUI_GRADIENT_VERTICAL; break;
        case ID_HorizontalGradient: gradient = wxAUI_GRADIENT_HORIZONTAL; break;
    }

    m_mgr.GetArtProvider()->SetMetric(wxAUI_DOCKART_GRADIENT_TYPE, gradient);
    m_mgr.Update();
}

void VMdefendorFrame::OnToolbarResizing(wxCommandEvent& WXUNUSED(evt))
{
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    const size_t count = all_panes.GetCount();
    for (size_t i = 0; i < count; ++i)
    {
        wxAuiToolBar* toolbar = wxDynamicCast(all_panes[i].window, wxAuiToolBar);
        if (toolbar)
        {
            all_panes[i].Resizable(!all_panes[i].IsResizable());
        }
    }

    m_mgr.Update();
}

void VMdefendorFrame::OnManagerFlag(wxCommandEvent& event)
{
    unsigned int flag = 0;

#if !defined(__WXMSW__) && !defined(__WXMAC__) && !defined(__WXGTK__)
    if (event.GetId() == ID_TransparentDrag ||
        event.GetId() == ID_TransparentHint ||
        event.GetId() == ID_HintFade)
    {
        wxMessageBox(wxT("This option is presently only available on wxGTK, wxMSW and wxMac"));
        return;
    }
#endif

    int id = event.GetId();

    if (id == ID_TransparentHint ||
        id == ID_VenetianBlindsHint ||
        id == ID_RectangleHint ||
        id == ID_NoHint)
    {
        unsigned int flags = m_mgr.GetFlags();
        flags &= ~wxAUI_MGR_TRANSPARENT_HINT;
        flags &= ~wxAUI_MGR_VENETIAN_BLINDS_HINT;
        flags &= ~wxAUI_MGR_RECTANGLE_HINT;
        m_mgr.SetFlags(flags);
    }

    switch (id)
    {
        case ID_AllowFloating: flag = wxAUI_MGR_ALLOW_FLOATING; break;
        case ID_TransparentDrag: flag = wxAUI_MGR_TRANSPARENT_DRAG; break;
        case ID_HintFade: flag = wxAUI_MGR_HINT_FADE; break;
        case ID_NoVenetianFade: flag = wxAUI_MGR_NO_VENETIAN_BLINDS_FADE; break;
        case ID_AllowActivePane: flag = wxAUI_MGR_ALLOW_ACTIVE_PANE; break;
        case ID_TransparentHint: flag = wxAUI_MGR_TRANSPARENT_HINT; break;
        case ID_VenetianBlindsHint: flag = wxAUI_MGR_VENETIAN_BLINDS_HINT; break;
        case ID_RectangleHint: flag = wxAUI_MGR_RECTANGLE_HINT; break;
        case ID_LiveUpdate: flag = wxAUI_MGR_LIVE_RESIZE; break;
    }

    if (flag)
    {
        m_mgr.SetFlags(m_mgr.GetFlags() ^ flag);
    }

    m_mgr.Update();
}


void VMdefendorFrame::OnNotebookFlag(wxCommandEvent& event)
{
    int id = event.GetId();

    if (id == ID_NotebookNoCloseButton ||
        id == ID_NotebookCloseButton ||
        id == ID_NotebookCloseButtonAll ||
        id == ID_NotebookCloseButtonActive)
    {
        m_notebook_style &= ~(wxAUI_NB_CLOSE_BUTTON |
                              wxAUI_NB_CLOSE_ON_ACTIVE_TAB |
                              wxAUI_NB_CLOSE_ON_ALL_TABS);

        switch (id)
        {
            case ID_NotebookNoCloseButton: break;
            case ID_NotebookCloseButton: m_notebook_style |= wxAUI_NB_CLOSE_BUTTON; break;
            case ID_NotebookCloseButtonAll: m_notebook_style |= wxAUI_NB_CLOSE_ON_ALL_TABS; break;
            case ID_NotebookCloseButtonActive: m_notebook_style |= wxAUI_NB_CLOSE_ON_ACTIVE_TAB; break;
        }
    }

    if (id == ID_NotebookAllowTabMove)
    {
        m_notebook_style ^= wxAUI_NB_TAB_MOVE;
    }
    if (id == ID_NotebookAllowTabExternalMove)
    {
        m_notebook_style ^= wxAUI_NB_TAB_EXTERNAL_MOVE;
    }
     else if (id == ID_NotebookAllowTabSplit)
    {
        m_notebook_style ^= wxAUI_NB_TAB_SPLIT;
    }
     else if (id == ID_NotebookWindowList)
    {
        m_notebook_style ^= wxAUI_NB_WINDOWLIST_BUTTON;
    }
     else if (id == ID_NotebookScrollButtons)
    {
        m_notebook_style ^= wxAUI_NB_SCROLL_BUTTONS;
    }
     else if (id == ID_NotebookTabFixedWidth)
    {
        m_notebook_style ^= wxAUI_NB_TAB_FIXED_WIDTH;
    }


    size_t i, count;
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
    {
        wxAuiPaneInfo& pane = all_panes.Item(i);
        if (pane.window->IsKindOf(CLASSINFO(wxAuiNotebook)))
        {
            wxAuiNotebook* nb = (wxAuiNotebook*)pane.window;

            if (id == ID_NotebookArtGloss)
            {
                nb->SetArtProvider(new wxAuiDefaultTabArt);
                m_notebook_theme = 0;
            }
             else if (id == ID_NotebookArtSimple)
            {
                nb->SetArtProvider(new wxAuiSimpleTabArt);
                m_notebook_theme = 1;
            }


            nb->SetWindowStyleFlag(m_notebook_style);
            nb->Refresh();
        }
    }


}


void VMdefendorFrame::OnUpdateUI(wxUpdateUIEvent& event)
{
    unsigned int flags = m_mgr.GetFlags();

    switch (event.GetId())
    {
        case ID_NoGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_NONE);
            break;
        case ID_VerticalGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_VERTICAL);
            break;
        case ID_HorizontalGradient:
            event.Check(m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_GRADIENT_TYPE) == wxAUI_GRADIENT_HORIZONTAL);
            break;
        case ID_AllowToolbarResizing:
        {
            wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
            const size_t count = all_panes.GetCount();
            for (size_t i = 0; i < count; ++i)
            {
                wxAuiToolBar* toolbar = wxDynamicCast(all_panes[i].window, wxAuiToolBar);
                if (toolbar)
                {
                    event.Check(all_panes[i].IsResizable());
                    break;
                }
            }
            break;
        }
        case ID_AllowFloating:
            event.Check((flags & wxAUI_MGR_ALLOW_FLOATING) != 0);
            break;
        case ID_TransparentDrag:
            event.Check((flags & wxAUI_MGR_TRANSPARENT_DRAG) != 0);
            break;
        case ID_TransparentHint:
            event.Check((flags & wxAUI_MGR_TRANSPARENT_HINT) != 0);
            break;
        case ID_LiveUpdate:
            event.Check((flags & wxAUI_MGR_LIVE_RESIZE) != 0);
            break;
        case ID_VenetianBlindsHint:
            event.Check((flags & wxAUI_MGR_VENETIAN_BLINDS_HINT) != 0);
            break;
        case ID_RectangleHint:
            event.Check((flags & wxAUI_MGR_RECTANGLE_HINT) != 0);
            break;
        case ID_NoHint:
            event.Check(((wxAUI_MGR_TRANSPARENT_HINT |
                          wxAUI_MGR_VENETIAN_BLINDS_HINT |
                          wxAUI_MGR_RECTANGLE_HINT) & flags) == 0);
            break;
        case ID_HintFade:
            event.Check((flags & wxAUI_MGR_HINT_FADE) != 0);
            break;
        case ID_NoVenetianFade:
            event.Check((flags & wxAUI_MGR_NO_VENETIAN_BLINDS_FADE) != 0);
            break;

        case ID_NotebookNoCloseButton:
            event.Check((m_notebook_style & (wxAUI_NB_CLOSE_BUTTON|wxAUI_NB_CLOSE_ON_ALL_TABS|wxAUI_NB_CLOSE_ON_ACTIVE_TAB)) != 0);
            break;
        case ID_NotebookCloseButton:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_BUTTON) != 0);
            break;
        case ID_NotebookCloseButtonAll:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_ON_ALL_TABS) != 0);
            break;
        case ID_NotebookCloseButtonActive:
            event.Check((m_notebook_style & wxAUI_NB_CLOSE_ON_ACTIVE_TAB) != 0);
            break;
        case ID_NotebookAllowTabSplit:
            event.Check((m_notebook_style & wxAUI_NB_TAB_SPLIT) != 0);
            break;
        case ID_NotebookAllowTabMove:
            event.Check((m_notebook_style & wxAUI_NB_TAB_MOVE) != 0);
            break;
        case ID_NotebookAllowTabExternalMove:
            event.Check((m_notebook_style & wxAUI_NB_TAB_EXTERNAL_MOVE) != 0);
            break;
        case ID_NotebookScrollButtons:
            event.Check((m_notebook_style & wxAUI_NB_SCROLL_BUTTONS) != 0);
            break;
        case ID_NotebookWindowList:
            event.Check((m_notebook_style & wxAUI_NB_WINDOWLIST_BUTTON) != 0);
            break;
        case ID_NotebookTabFixedWidth:
            event.Check((m_notebook_style & wxAUI_NB_TAB_FIXED_WIDTH) != 0);
            break;
        case ID_NotebookArtGloss:
            event.Check(m_notebook_style == 0);
            break;
        case ID_NotebookArtSimple:
            event.Check(m_notebook_style == 1);
            break;

    }
}

void VMdefendorFrame::OnPaneClose(wxAuiManagerEvent& evt)
{
    if (evt.pane->name == wxT("messages"))
    {
        int res = wxMessageBox(wxT("Are you sure you want to close/hide this pane?"),
                               wxT("wxAUI"),
                               wxYES_NO,
                               this);
        if (res != wxYES)
            evt.Veto();
    }
}

void VMdefendorFrame::OnCreatePerspective(wxCommandEvent& WXUNUSED(event))
{
    wxTextEntryDialog dlg(this, wxT("Enter a name for the new perspective:"),
                          wxT("wxAUI Test"));

    dlg.SetValue(wxString::Format(wxT("Perspective %u"), unsigned(m_perspectives.GetCount() + 1)));
    if (dlg.ShowModal() != wxID_OK)
        return;

    if (m_perspectives.GetCount() == 0)
    {
        m_perspectives_menu->AppendSeparator();
    }

    m_perspectives_menu->Append(ID_FirstPerspective + m_perspectives.GetCount(), dlg.GetValue());
    m_perspectives.Add(m_mgr.SavePerspective());
}

void VMdefendorFrame::OnCopyPerspectiveCode(wxCommandEvent& WXUNUSED(evt))
{
    wxString s = m_mgr.SavePerspective();

#if wxUSE_CLIPBOARD
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(s));
        wxTheClipboard->Close();
    }
#endif
}

void VMdefendorFrame::OnRestorePerspective(wxCommandEvent& evt)
{
    m_mgr.LoadPerspective(m_perspectives.Item(evt.GetId() - ID_FirstPerspective));
}

void VMdefendorFrame::OnNotebookPageClose(wxAuiNotebookEvent& evt)
{
    wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();
    if (ctrl->GetPage(evt.GetSelection())->IsKindOf(CLASSINFO(wxHtmlWindow)))
    {
        int res = wxMessageBox(wxT("Are you sure you want to close/hide this notebook page?"),
                       wxT("wxAUI"),
                       wxYES_NO,
                       this);
        if (res != wxYES)
            evt.Veto();
    }
}

void VMdefendorFrame::OnNotebookPageClosed(wxAuiNotebookEvent& evt)
{
    wxAuiNotebook* ctrl = (wxAuiNotebook*)evt.GetEventObject();

    // selection should always be a valid index
    wxASSERT_MSG( ctrl->GetSelection() < (int)ctrl->GetPageCount(),
                  wxString::Format("Invalid selection %d, only %d pages left",
                                   ctrl->GetSelection(),
                                   (int)ctrl->GetPageCount()) );

    evt.Skip();
}

void VMdefendorFrame::OnAllowNotebookDnD(wxAuiNotebookEvent& evt)
{
    // for the purpose of this test application, explicitly
    // allow all noteboko drag and drop events
    evt.Allow();
}

wxPoint VMdefendorFrame::GetStartPosition()
{
    static int x = 0;
    x += 20;
    wxPoint pt = ClientToScreen(wxPoint(0,0));
    return wxPoint(pt.x + x, pt.y + x);
}

void VMdefendorFrame::OnProfileSwitch(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog filedlg(this, wxT("读取VMArmour监控配置文件"), "", "",
		"profiles (*.conf)|*.conf", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (filedlg.ShowModal() == wxID_OK)
	{
		ExitMonitor();
		wxString fileName = filedlg.GetPath();
		LoadProfile(config, fileName );
		InitMonitor();
	}
}
void VMdefendorFrame::OnProfileSave(wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog filedlg(this, wxT("保存VMArmour监控配置文件"), "", "",
		"profiles (*.conf)|*.conf", wxFD_SAVE | wxFD_OVERWRITE_PROMPT );
	if (filedlg.ShowModal() == wxID_OK)
	{
		wxString fileName = filedlg.GetPath();
		SaveProfile(config, fileName);
	}
}
void VMdefendorFrame::OnCreateTree(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateTreeCtrl(), wxAuiPaneInfo().
                  Caption(wxT("Tree Control")).
                  Float().FloatingPosition(GetStartPosition()).
                  FloatingSize(wxSize(150,300)));
    m_mgr.Update();
}

void VMdefendorFrame::OnCreateGrid(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateGrid(), wxAuiPaneInfo().
                  Caption(wxT("Grid")).
                  Float().FloatingPosition(GetStartPosition()).
                  FloatingSize(wxSize(300,200)));
    m_mgr.Update();
}

void VMdefendorFrame::OnCreateHTML(wxCommandEvent& WXUNUSED(event))
{
    //m_mgr.AddPane(CreateHTMLCtrl(), wxAuiPaneInfo().
    //              Caption(wxT("HTML Control")).
    //              Float().FloatingPosition(GetStartPosition()).
    //              FloatingSize(wxSize(300,200)));
    //m_mgr.Update();
}

void VMdefendorFrame::OnCreateNotebook(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateNotebook(), wxAuiPaneInfo().
                  Caption(wxT("Notebook")).
                  Float().FloatingPosition(GetStartPosition()).
                  //FloatingSize(300,200).
                  CloseButton(true).MaximizeButton(true));
    m_mgr.Update();
}

void VMdefendorFrame::OnCreateText(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateTextCtrl(), wxAuiPaneInfo().
                  Caption(wxT("Text Control")).
                  Float().FloatingPosition(GetStartPosition()));
    m_mgr.Update();
}

void VMdefendorFrame::OnCreateSizeReport(wxCommandEvent& WXUNUSED(event))
{
    m_mgr.AddPane(CreateSizeReportCtrl(), wxAuiPaneInfo().
                  Caption(wxT("Client Size Reporter")).
                  Float().FloatingPosition(GetStartPosition()).
                  CloseButton(true).MaximizeButton(true));
    m_mgr.Update();
}

void VMdefendorFrame::OnChangeContentPane(wxCommandEvent& evt)
{
    m_mgr.GetPane(wxT("grid_content")).Show(evt.GetId() == ID_GridContent);
    m_mgr.GetPane(wxT("text_content")).Show(evt.GetId() == ID_TextContent);
    m_mgr.GetPane(wxT("tree_content")).Show(evt.GetId() == ID_TreeContent);
    m_mgr.GetPane(wxT("sizereport_content")).Show(evt.GetId() == ID_SizeReportContent);
    m_mgr.GetPane(wxT("html_content")).Show(evt.GetId() == ID_HTMLContent);
    m_mgr.GetPane(wxT("nbpages")).Show(evt.GetId() == ID_NotebookContent);
    m_mgr.Update();
}

void VMdefendorFrame::OnDropDownToolbarItem(wxAuiToolBarEvent& evt)
{
    if (evt.IsDropDownClicked())
    {
        wxAuiToolBar* tb = static_cast<wxAuiToolBar*>(evt.GetEventObject());

        tb->SetToolSticky(evt.GetId(), true);

        // create the popup menu
        wxMenu menuPopup;

        wxBitmap bmp = wxArtProvider::GetBitmap(wxART_QUESTION, wxART_OTHER, wxSize(16,16));

        wxMenuItem* m1 =  new wxMenuItem(&menuPopup, 10001, _("Drop Down Item 1"));
        m1->SetBitmap(bmp);
        menuPopup.Append(m1);

        wxMenuItem* m2 =  new wxMenuItem(&menuPopup, 10002, _("Drop Down Item 2"));
        m2->SetBitmap(bmp);
        menuPopup.Append(m2);

        wxMenuItem* m3 =  new wxMenuItem(&menuPopup, 10003, _("Drop Down Item 3"));
        m3->SetBitmap(bmp);
        menuPopup.Append(m3);

        wxMenuItem* m4 =  new wxMenuItem(&menuPopup, 10004, _("Drop Down Item 4"));
        m4->SetBitmap(bmp);
        menuPopup.Append(m4);

        // line up our menu with the button
        wxRect rect = tb->GetToolRect(evt.GetId());
        wxPoint pt = tb->ClientToScreen(rect.GetBottomLeft());
        pt = ScreenToClient(pt);


        PopupMenu(&menuPopup, pt);


        // make sure the button is "un-stuck"
        tb->SetToolSticky(evt.GetId(), false);
    }
}


void VMdefendorFrame::OnTabAlignment(wxCommandEvent &evt)
{
    size_t i, count;
    wxAuiPaneInfoArray& all_panes = m_mgr.GetAllPanes();
    for (i = 0, count = all_panes.GetCount(); i < count; ++i)
    {
        wxAuiPaneInfo& pane = all_panes.Item(i);
        if (pane.window->IsKindOf(CLASSINFO(wxAuiNotebook)))
        {
            wxAuiNotebook* nb = (wxAuiNotebook*)pane.window;

            long style = nb->GetWindowStyleFlag();
            style &= ~(wxAUI_NB_TOP | wxAUI_NB_BOTTOM);
            if (evt.GetId() == ID_NotebookAlignTop)
                style |= wxAUI_NB_TOP;
            else if (evt.GetId() == ID_NotebookAlignBottom)
                style |= wxAUI_NB_BOTTOM;
            nb->SetWindowStyleFlag(style);

            nb->Refresh();
        }
    }
}

void VMdefendorFrame::OnWinMsgDclik(wxCommandEvent &evt)
{	
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16));
	
	//wxString a = m_msgslist->GetString(m_msgslist->GetSelection());
	//wxString b = m_msgslist->GetString(0);
	//string d = string(a.mb_str());
	//string c = string(b.mb_str());
	//cout<<"@@"<<d<<"@@"<<b<<"@@"<<c<<"@@"<<endl;

	if(m_msgslist->GetSelection()==0){
		//for (int i = 0; i < hide_process.size(); ++i)
		//{	 
			panelProcessWindow *panelprocess = new panelProcessWindow(m_nb_info,*hide_process[0]);
  			m_nb_info->AddPage(panelprocess, wxT("隐藏进程"), true, page_bmp);
		//}
		struct VM_vmi vmi1;
		wxTreeItemId rootId[9999];
		temp_(vmi1);
		VM_find_process_tree(vmi1,vmi1.process);
		m_process_tree->DeleteAllItems();
		UpdateTree(vmi1.process,0,rootId,m_process_tree,*hide_process[0]);
	}else 	if(m_msgslist->GetSelection()==1){ 
			wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
				m_nb_info->AddPage(CreatePanelFile(m_nb_info, *hide_file[0]), wxT("file"), true, page_bmp);
	}
	else if(m_msgslist->GetSelection()==2||m_msgslist->GetSelection()==3){
		struct VM_vmi vmi1;
		temp_(vmi1);
		VM_module_init(vmi1.module);
		VM_find_modules_list(vmi1,vmi1.module);
	
		VM_module  *temp_module=&vmi1.module;
		do{
			if(temp_module->rootkid!=NULL){
				wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
				m_nb_info->AddPage(CreatePanelModule(m_nb_info, *temp_module), wxT("Rootkit"), true, page_bmp);
				//AppendMessage(wxT("   找到Rootkid: ")+wxString(temp_module->name, wxConvUTF8));
				break;
			}	
			
			temp_module = VM_list_entry(temp_module->list.next,struct VM_module,list);
		}while(&vmi1.module!=temp_module);
	}
//	wxMessageBox(_("Virtual Machine Bit-Prober\n虚拟机内核恶意攻击检测系统\n(c) Copyright 2017-2017, OS Group, HFUT"), _("About VMArmour"), wxOK, this);

}

void VMdefendorFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void VMdefendorFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(_("Virtual Machine Bit-Prober\n虚拟机内核恶意攻击检测系统\n(c) Copyright 2017-2017, OS Group, HFUT"), _("About VMArmour"), wxOK, this);
}

wxTextCtrl* VMdefendorFrame::CreateTextCtrl(const wxString& ctrl_text)
{
    static int n = 0;

    wxString text;
    if ( !ctrl_text.empty() )
        text = ctrl_text;
    else
        text.Printf(wxT("This is text box %d"), ++n);

    return new wxTextCtrl(this,wxID_ANY, text,
                          wxPoint(0,0), wxSize(150,90),
                          wxNO_BORDER | wxTE_MULTILINE);
}
wxTextCtrl* VMdefendorFrame::CreateLog( )
{
	m_msgs = new wxTextCtrl(this, wxID_ANY, wxT(""),
		wxPoint(0, 0), wxSize(150, 90),
		wxNO_BORDER | wxTE_MULTILINE | wxTE_READONLY);
	return m_msgs;
}
wxListBox* VMdefendorFrame::CreateMsg()
{
	m_msgslist = new wxListBox(this, ID_WIN_MSG,
		wxPoint(0, 0), wxSize(150, 90),0 , NULL,
		wxLB_SINGLE | wxLB_ALWAYS_SB | wxNO_BORDER);
	return m_msgslist;
}

void VMdefendorFrame::AppendMessage( wxString msg )
{
	wxString wxstr = wxDateTime::Now().FormatISOCombined(' ') + wxT(" ") + msg + wxT("\n");  // 2017-02-03 15:34:09 xxxx
	unsigned int temp = m_msgslist->GetCount();
	m_msgslist->InsertItems(1,&wxstr,temp);
	//int n = m_msgslist->Append(wxstr);
	m_msgslist->EnsureVisible( temp );
}
void VMdefendorFrame::UpdateLastMessage(wxString msg)
{
	wxString wxstr = wxDateTime::Now().FormatISOCombined(' ') + wxT(" ") + msg + wxT("\n");  // 2017-02-03 15:34:09 xxxx
	if (m_msgslist->GetCount() >= 1)  // 删除最后一条消息
		m_msgslist->Delete(m_msgslist->GetCount() - 1);
	m_msgslist->EnsureVisible(m_msgslist->Append(wxstr));
}

wxGrid* VMdefendorFrame::CreateGrid()
{
    wxGrid* grid = new wxGrid(this, wxID_ANY,
                              wxPoint(0,0),
                              wxSize(150,250),
                              wxNO_BORDER | wxWANTS_CHARS);
    grid->CreateGrid(50, 20);
    return grid;
}

wxTreeCtrl* VMdefendorFrame::CreateTreeCtrl()
{
    wxTreeCtrl* m_process_tree = new wxTreeCtrl(this, wxID_ANY,
                                      wxPoint(0,0), wxSize(160,250),
                                      wxTR_DEFAULT_STYLE | wxNO_BORDER);

    wxImageList* imglist = new wxImageList(16, 16, true, 2);
    imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
    imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));
    m_process_tree->AssignImageList(imglist);

    wxTreeItemId root = m_process_tree->AddRoot(wxT("Domain-U,Linux-UN"), 0);
    wxArrayTreeItemIds items;

    items.Add(m_process_tree->AppendItem(root, wxT("init"), 0));
    items.Add(m_process_tree->AppendItem(root, wxT("firefox"), 0));
    items.Add(m_process_tree->AppendItem(root, wxT("kthreadd"), 0));
    items.Add(m_process_tree->AppendItem(root, wxT("ksoftirqd"), 0));
    items.Add(m_process_tree->AppendItem(root, wxT("watchdog"), 0));


    int i, count;
    for (i = 0, count = items.Count(); i < count; ++i)
    {
        wxTreeItemId id = items.Item(i);
        m_process_tree->AppendItem(id, wxT("Subitem 1"), 1);
        m_process_tree->AppendItem(id, wxT("Subitem 2"), 1);
        m_process_tree->AppendItem(id, wxT("Subitem 3"), 1);
        m_process_tree->AppendItem(id, wxT("Subitem 4"), 1);
        m_process_tree->AppendItem(id, wxT("Subitem 5"), 1);
    }


    m_process_tree->Expand(root);

    return m_process_tree;
}



wxWindow* VMdefendorFrame::ShowProcessTree()
{
    //m_process_tree = new wxTreeCtrl(this, wxID_ANY,
    //                                  wxPoint(0,0), wxSize(160,250),
    //                                  wxTR_DEFAULT_STYLE | wxNO_BORDER);

    //wxImageList* imglist = new wxImageList(16, 16, true, 2);
    //imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
    //imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));
    //m_process_tree->AssignImageList(imglist);

    //wxTreeItemId root = m_process_tree->AddRoot(wxT("Domain-U,Linux"), 0);
    //wxArrayTreeItemIds items;



    //items.Add(m_process_tree->AppendItem(root, wxT("init"), 0));
    //items.Add(m_process_tree->AppendItem(root, wxT("firefox"), 0));
    //items.Add(m_process_tree->AppendItem(root, wxT("kthreadd"), 0));
    //items.Add(m_process_tree->AppendItem(root, wxT("ksoftirqd"), 0));
    //items.Add(m_process_tree->AppendItem(root, wxT("watchdog"), 0));


    //int i, count;
    //for (i = 0, count = items.Count(); i < count; ++i)
    //{
    //    wxTreeItemId id = items.Item(i);
    //    m_process_tree->AppendItem(id, wxT("Subitem 1"), 1);
    //    m_process_tree->AppendItem(id, wxT("Subitem 2"), 1);
    //    m_process_tree->AppendItem(id, wxT("Subitem 3"), 1);
    //    m_process_tree->AppendItem(id, wxT("Subitem 4"), 1);
    //    m_process_tree->AppendItem(id, wxT("Subitem 5"), 1);
    //}


    //m_process_tree->Expand(root);
    //return m_process_tree;
	VM_process process;
	process.children.next = 0;
	process.comm = "init";

//	VM_process *temp_process = VM_list_entry(vmi1.process.tasks.next->next->next,struct VM_process,tasks);

	wxWindow *window = CreateProcessTree( this, process, m_process_tree ,m_choice_process);

	m_choice_process->SetSelection(0);
	return window;
}

wxSizeReportCtrl* VMdefendorFrame::CreateSizeReportCtrl(int width, int height)
{
    wxSizeReportCtrl* ctrl = new wxSizeReportCtrl(this, wxID_ANY,
                                   wxDefaultPosition,
                                   wxSize(width, height), &m_mgr);
    return ctrl;
}

//wxHtmlWindow* VMdefendorFrame::CreateHTMLCtrl(wxWindow* parent)
//{
//    if (!parent)
//        parent = this;
////
//    wxHtmlWindow* ctrl = new wxHtmlWindow(parent, wxID_ANY,
//                                   wxDefaultPosition,
//                                   wxSize(400,300));
//    ctrl->SetPage(GetIntroText());
//    return ctrl;
//}

wxAuiNotebook* VMdefendorFrame::CreateNotebook()
{
	struct VM_vmi vmi1;

	//temp_(vmi1);
	//VM_process *temp_process = VM_list_entry(vmi1.process.tasks.next->next->next,struct VM_process,tasks);

	VM_process *temp_process = VM_list_entry(vmi1.process.tasks.pre,struct VM_process,tasks);
	//temp_process = VM_list_entry(temp_process->children.next,struct VM_process,sibling);
 	//temp_process = VM_list_entry(temp_process->sibling.next,struct VM_process,sibling);

	VM_module_init(vmi1.module);
	//VM_find_modules_list(vmi1,vmi1.module);

	// create the notebook off-window to avoid flicker
	wxSize client_size = GetClientSize();
	m_nb_info = new wxAuiNotebook(this, wxID_ANY,
                                    wxPoint(client_size.x, client_size.y),
                                    wxSize(430,200),
                                    m_notebook_style);
	m_nb_info->Freeze();
	// default page
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16));
	m_nb_info->AddPage(CreatePanelWelcome(m_nb_info), wxT("Welcome") , false, page_bmp);
	VM_process process;

	//m_nb_info->AddPage(CreatePanelFile(m_nb_info, process), wxT("Welcome"), false, page_bmp);
		//panelProcessWindow *panelprocess2 = new panelProcessWindow(m_nb_info,process);

	//m_nb_info->AddPage(panelprocess2, wxT("进程信息"), false, page_bmp);
	//VM_file file;

	// m_nb_info->AddPage(CreatePanelFile(m_nb_info, file), wxT("Welcome"), false, page_bmp);
   
	//VM_module m;
	//m.name = 0;
	
	wxString name = vmi1.module.name;
	//m_nb_info->AddPage(CreatePanelModule(m_nb_info, vmi1.module), name, false, page_bmp);

	m_nb_info->Thaw();

	return m_nb_info;
}


void VMdefendorFrame::OnStartWorker(wxCommandEvent& WXUNUSED(event))
{
	WorkerProcess *thread = new WorkerProcess(this);

	if (thread->Create() != wxTHREAD_NO_ERROR)
	{
		wxLogError(wxT("Can't create thread!"));
		return;
	}

	wxCriticalSectionLocker enter(wxGetApp().m_critsect);
	wxGetApp().m_threads.Add(thread);

	thread->Run();
}

void VMdefendorFrame::OnWorkerEvent(wxThreadEvent& event)
{
	int n = event.GetInt();
	if (n == -1)
	{
		this->AppendMessage(event.GetString());
		//// the dialog is aborted because the event came from another thread, so
		//// we may need to wake up the main event loop for the dialog to be
		//// really closed
		//wxWakeUpIdle();
	}
	else
	{
		SettingsMoni mon;
		MonitorProfile f;
		MonitorProfile *f2;
		f2 = event.GetPayload<MonitorProfile*>();
		//AppendMessage( event.GetString());
		AppendMessage(f2->filename);
		delete f2;
	}
}
void VMdefendorFrame::OnWorkerEventStart(wxThreadEvent& event)
{
	this->AppendMessage(event.GetString());
}
void VMdefendorFrame::OnWorkerEventEnd(wxThreadEvent& event)
{
	this->AppendMessage(event.GetString());
	VM_process process;
	process = event.GetPayload<VM_process>();
	m_nb_info->Freeze();
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	//m_nb_info->AddPage(CreatePanelProcess(m_nb_info, process), wxT("process"), true, page_bmp);
	VM_module m;
	m_nb_info->AddPage(CreateModuleList(m_nb_info, m, m_module_tree), wxT("process"), true, page_bmp);
	m_nb_info->Thaw();
}

void VMdefendorFrame::OnWorkerEventProcessTree(wxThreadEvent& event)
{
	SettingsMoni mon;
	MonitorProfile f;
	MonitorProfile *f2;
	f2 = event.GetPayload<MonitorProfile*>();
	//AppendMessage( event.GetString());
	AppendMessage(f2->filename);
}
void VMdefendorFrame::OnWorkerEventProcess(wxThreadEvent& event)
{
	VM_process process;
	process = event.GetPayload<VM_process>();
	//AppendMessage( event.GetString());
	wxString s = wxString::Format("%d,%d",event.GetInt(),process.pid);
	AppendMessage(s);
}
void VMdefendorFrame::OnWorkerEventModule(wxThreadEvent& event)
{
	SettingsMoni mon;
	MonitorProfile f;
	MonitorProfile *f2;
	f2 = event.GetPayload<MonitorProfile*>();
	//AppendMessage( event.GetString());
	AppendMessage(f2->filename);
}

void VMdefendorFrame::OnTimer(wxTimerEvent& evt)
{
	(( VMStatusBar*)GetStatusBar())->UpdateClock();

}
void VMdefendorFrame::OnTimerMonitor(wxTimerEvent& evt)
{
	time_t tnow = time(NULL);
	for (size_t i = 0; i < config.settings.size(); i++) {
		SettingsMoni &conf = config.settings[i];
		if (abs(tnow - conf.t_next) < 5) {   //延迟不超过5s
			wxCommandEvent evt2;// just for mismatching-parameter in invoking
			OnStartWorker(evt2);
		}
	}

	// next
	StartNextTimer();
}

void VMdefendorFrame::OnVMEnumerate(wxCommandEvent& evt)
{
	// 此处须调用虚拟机枚举函数（可能需要LibVMI），列出所有的当前虚拟机
	// vms_enumerate( vms ) ;  // uncomment if vms_enumerate() is ok

	// 刷新所有窗口
	m_vmslist->DeleteAllItems();
	m_process_tree->DeleteAllItems();
	m_module_tree->DeleteAllItems();  // 以后替换成真正的内容删除
	m_file_tree->DeleteAllItems();
	m_nb_info->DeleteAllPages();

	// 插入虚拟机信息到窗口
	wxTreeItemId root = m_vmslist->AddRoot(wxT("虚拟机名称"),
		//-1, -1, new MyTreeItemData(VM_Message[0]));
		-1, -1, NULL);
	for (size_t i = 0; i < m_vms.size(); i++)
		m_vmslist->AppendItem(root, m_vms[i].vm.procname, -1, -1, 0); // procname? 

	// 设置当前虚拟机
	if (0 < m_vms.size())
		SetCurrentVM(0);

	// 缺省的详细信息窗口
	m_nb_info->Freeze();
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	m_nb_info->AddPage(CreatePanelWelcome(m_nb_info), wxT("Welcome"), true, page_bmp);
	m_nb_info->Thaw();
}

void VMdefendorFrame::OnVMFind(wxCommandEvent& evt)
{
}
void VMdefendorFrame::OnVMStart(wxCommandEvent& evt)
{
	m_monitor = !m_monitor;
	((VMStatusBar*)GetStatusBar())->SetMonitorStatus(m_monitor);
	if (!m_monitor)
		m_timer_monitor.Stop();

	struct VM_vmi vmi1;
	temp_(vmi1);
	VM_module_init(vmi1.module);
	VM_find_modules_list(vmi1,vmi1.module);

	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	wxString name = vmi1.module.name;
	//m_nb_info->AddPage(CreatePanelModule(m_nb_info, vmi1.module), name, true, page_bmp);

	m_mgr.AddPane(CreateModuleList(this, vmi1.module, m_module_tree), 
		wxAuiPaneInfo().Name(WIN_MODULE).Caption(wxT("模块列表")).
		Right().Layer(1).Position(0).MinSize(200,-1).
		CloseButton(true).MaximizeButton(true));

	// m_mgr.AddPane(CreateFileTree(this,vmi, m_file_tree), wxAuiPaneInfo().
	// 	Name(WIN_FILE).Caption(wxT("文件列表")).
	// 	CloseButton(true).MaximizeButton(true));

	// Give this pane an icon, too, just for testing.
	int iconSize = m_mgr.GetArtProvider()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE);
	// Make it even to use 16 pixel icons with default 17 caption height.
	iconSize &= ~1;

	m_mgr.AddPane(CreateMsg(), wxAuiPaneInfo().
		Name(WIN_MSG).Caption(wxT("系统消息")).
		Bottom().Layer(1).Position(1).
		Icon(wxArtProvider::GetBitmap(wxART_WARNING,
			wxART_OTHER,
			wxSize(iconSize, iconSize))));
	//m_mgr.AddPane(new SettingsPanel(this, this), wxAuiPaneInfo().
	//	Name(wxT("settings")).Caption(wxT("Dock Manager Settings")).
	//	Dockable(false).Float().CenterPane().CloseButton(true).Hide());

	//struct VM_vmi vmi1;
	//temp_(vmi1);
	VM_find_process_tree(vmi1,vmi1.process);

	init_file_tree(vmi1,"/bin/");
	//cmp_file(vmi1,"/bin/");
	//wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16));
	//wxWindow *window = CreateProcessTree( this, vmi1.process, m_process_tree );

	m_mgr.AddPane(CreateProcessTree( this, vmi1.process, m_process_tree ,m_choice_process), wxAuiPaneInfo().
		Name(WIN_PROCESS).Caption(wxT("进程列表")).
		Left().Layer(1).Position(1).MinSize(200,-1).
		CloseButton(true).MaximizeButton(true));
	m_choice_process->SetSelection(0);	

	m_mgr.AddPane(CreateFileTree(this,vmi1, m_file_tree), wxAuiPaneInfo().
		Name(WIN_FILE).Caption(wxT("文件列表")).
		Right().Layer(1).Position(1).MinSize(200,-1).
		CloseButton(true).MaximizeButton(true));

	m_mgr.GetPane(WIN_PROCESS).Show().Left().Layer(1).Row(0).Position(1);
	m_mgr.GetPane(WIN_FILE).Show().Right().Layer(1).Row(0).Position(0);
	m_mgr.GetPane(WIN_MODULE).Show().Right().Layer(1).Row(0).Position(1);
	m_mgr.Update();
}

void VMdefendorFrame::OnOSSnap(wxCommandEvent& evt)
{
	if (!(0 <= m_vm_current_index && m_vm_current_index < m_vms.size()))
		return;

	// 当前虚拟机
	SnapVM  &snap_vm = m_vms[m_vm_current_index] ;
	
	// 进程的根
	VM_process root_process;

	// 此处须调用进程快照函数，列出当前虚拟机的所有进程
	// vms_snap_process( snap_vm.vm.vmi, root ) ;  // uncomment if vms_snap_process() is ok

	// 更新数据结构
	SnapProcess process;
	process.t = time(NULL);  //当前时间
	process.root = root_process;
	snap_vm.snap_process.push_back( process );

	// 更新界面：删除当前虚拟机所有已经打开的进程信息页
	DeleteAllProcessPagesOfVM( snap_vm );
}

void VMdefendorFrame::DeleteAllProcessPagesOfVM(SnapVM  &snap_vm)
{
	// 缺省的详细信息窗口, 以后是实现
	m_nb_info->Freeze();
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	m_nb_info->AddPage(CreatePanelWelcome(m_nb_info), wxT("Welcome"), true, page_bmp);
	m_nb_info->Thaw();
}
void VMdefendorFrame::DeleteAllModulePagesOfVM(SnapVM  &snap_vm)
{
	// 缺省的详细信息窗口, 以后是实现
	m_nb_info->Freeze();
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	m_nb_info->AddPage(CreatePanelWelcome(m_nb_info), wxT("Welcome"), true, page_bmp);
	m_nb_info->Thaw();
}
void VMdefendorFrame::DeleteAllFilePagesOfVM(SnapVM  &snap_vm)
{
	// 缺省的详细信息窗口, 以后是实现
	m_nb_info->Freeze();
	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	m_nb_info->AddPage(CreatePanelWelcome(m_nb_info), wxT("Welcome"), true, page_bmp);
	m_nb_info->Thaw();
}


void VMdefendorFrame::OnOSMonitorlist(wxCommandEvent& evt)
{
}
void VMdefendorFrame::OnOSMonitorlistAdd(wxCommandEvent& evt)
{
	// 当前虚拟机有效？
	if (!(0 <= m_vm_current_index && m_vm_current_index < m_vms.size()))
		return;

	//ok
	SettingsMoni mon;
	mon.t_monitoring = time(NULL) + 24*60*60 ;  //明天此时此刻
	mon.tm_monitoring = *localtime(&mon.t_monitoring );
	mon.os_ds_process = true;
	mon.repeat = MONITOR_EACH_DAY;
	SettingDialog Dlg(this, mon);//传递参数给你的类
	if (wxID_OK != Dlg.ShowModal())
		return;

	// 有效的配置,保存
	config.settings.push_back(mon);

	//重新启动并计算监控定时器，稍后实现
	// ...


	AppendMessage(wxT("当前虚拟机OS内核的监控任务已经添加成功."));
}

void VMdefendorFrame::OnOSMonitorlistRemove(wxCommandEvent& evt)
{
	AppendMessage(wxT("当前虚拟机OS内核的监控任务已经删除."));
}
void VMdefendorFrame::OnOSMonitorStart(wxCommandEvent& evt)
{
	struct VM_vmi vmi1;
	temp_(vmi1);
	VM_find_process_tree(vmi1,vmi1.process);

	m_msgslist->Clear();
	vector<VM_process*> temp_process = cmp_process(vmi1);
	vector<VM_file*> temp_file = cmp_file(vmi1,"/bin/");
	if(!temp_process.empty()){
		for (int i = 0; i < temp_process.size(); ++i){
			hide_process.push_back(temp_process[i]);
		}
		AppendMessage(wxT("   发现隐藏进程:")+wxString(temp_process[0]->comm, wxConvUTF8)+wxT(" pid:")+wxString::Format(wxT("%i"),temp_process[0]->pid));
		//AppendMessage();
	}	
	else{
		AppendMessage(wxT("   没有找到隐藏进程"));
	}
	if(!temp_file.empty()){
		for (int i = 0; i < temp_process.size(); ++i){
			hide_file.push_back(temp_file[i]);
		}
		AppendMessage(wxT("   发现隐藏文件:")+wxString(temp_file[0]->name.data(), wxConvUTF8));
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<temp_file[0]->name<<"\n";
	}else{
		AppendMessage(wxT("   没有找到隐藏文件"));
	}
	VM_module_init(vmi1.module);
	VM_find_modules_list(vmi1,vmi1.module);
	
	VM_module  *temp_module=&vmi1.module;
	do{
		if(temp_module->rootkid!=NULL){
			AppendMessage(wxT("   发现Rootkit: ")+wxString(temp_module->name, wxConvUTF8));
		}	
		//else{
		//	AppendMessage(wxT("   没有找到Rootkid"));
		//}
		temp_module = VM_list_entry(temp_module->list.next,struct VM_module,list);
	}while(&vmi1.module!=temp_module);

	

}
void VMdefendorFrame::OnProcessKill(wxCommandEvent& evt)
{

	//AppendMessage( wxT( "当前进程已经被杀死..." ));
}
void VMdefendorFrame::OnProcessSuspend(wxCommandEvent& evt)
{
	AppendMessage(wxT("当前进程暂停状态处理完成..."));
}
void VMdefendorFrame::OnProcessInfo(wxCommandEvent& evt)
{
}
void VMdefendorFrame::OnToolkitScanProcess(wxCommandEvent& evt)
{
	OnStartWorker(evt);
}
void VMdefendorFrame::OnToolkitScanProcessIOView(wxCommandEvent& evt)
{
	OnStartWorker(evt);
}
void VMdefendorFrame::OnToolkitScanModule(wxCommandEvent& evt)
{
	OnStartWorker(evt);
}
void VMdefendorFrame::OnToolkitScanFile(wxCommandEvent& evt)
{
	OnStartWorker(evt);
}
void VMdefendorFrame::OnToolkitSettings(wxCommandEvent& evt)
{
}
void VMdefendorFrame::OnWinVMs(wxCommandEvent& evt)
{
	m_mgr.GetPane(WIN_VMS).Float();
	m_mgr.GetPane(WIN_VMS).Show();
	m_mgr.Update();
}
void VMdefendorFrame::OnWinProcess(wxCommandEvent& evt)
{
	m_mgr.GetPane(WIN_PROCESS).Show();
	m_mgr.Update();
}
void VMdefendorFrame::OnWinProcessList(wxCommandEvent& evt)
{
	m_mgr.GetPane(WIN_PROCESS).Show();
	m_mgr.Update();
}
void VMdefendorFrame::OnWinFile(wxCommandEvent& evt)
{
	m_mgr.GetPane(WIN_FILE).Float();
	m_mgr.GetPane(WIN_FILE).Show();
	m_mgr.Update();
}
void VMdefendorFrame::OnWinModule(wxCommandEvent& evt)
{
	m_mgr.GetPane(WIN_MODULE).Float();
	m_mgr.GetPane(WIN_MODULE).Show();
	m_mgr.Update();
}
void VMdefendorFrame::OnWinMsg(wxCommandEvent& evt)
{
	m_mgr.GetPane(WIN_MSG).Show();
	m_mgr.Update();
}
void VMdefendorFrame::OnWinNTbook(wxCommandEvent& evt)
{
	m_mgr.GetPane(WIN_NTBOOK).Show();
	m_mgr.Update();
}
void VMdefendorFrame::OnShowPanelProcess(wxTreeEvent& event)
{
	wxTreeItemId itemid = event.GetItem();
	wxString s = event.GetString();
	
	//cout<<"**"<<typeid(*(m_process_tree->GetItemData(itemid))).name()<<"**"<<typeid(MyTreeItemData).name()<<"**"<<endl;
	
	if(typeid(*(m_process_tree->GetItemData(itemid))).name()==typeid(MyTreeItemData).name()){
		MyTreeItemData *item = (MyTreeItemData*)m_process_tree->GetItemData( itemid );
		wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
		VM_process process = item->GetDesc();

		m_nb_info->Freeze();
		wxString name = process.comm;

		panelProcessWindow *panelprocess1 = new panelProcessWindow(m_nb_info,process);
		m_nb_info->AddPage(panelprocess1, name, true, page_bmp);
		m_nb_info->Thaw();
	}
	else if(typeid(*(m_file_tree->GetItemData(itemid))).name()==typeid(FileTreeItemData).name()){
		FileTreeItemData *item = (FileTreeItemData*)m_file_tree->GetItemData( itemid );
		wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
		VM_file file = item->GetDesc();

		m_nb_info->Freeze();
		wxString name = file.name;

		m_nb_info->AddPage(CreatePanelFile(m_nb_info, file), name, true, page_bmp);
		m_nb_info->Thaw();
	}
	//else if(typeid(*(m_module_tree->GetItemData(itemid))).name()==typeid(ModuleTreeItemData).name()){
	//	ModuleTreeItemData *item = (ModuleTreeItemData*)m_module_tree->GetItemData( itemid );
	//	wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16));
	//	VM_module module = item->GetDesc();

	//	m_nb_info->Freeze();
	//	wxString name = wxString(module.name, wxConvUTF8);
	//	m_nb_info->AddPage(CreatePanelModule(m_nb_info, module), name, true, page_bmp);
		
	//	m_nb_info->Thaw();
	//}
	m_mgr.Update();
}
void VMdefendorFrame::OnOSScan(wxCommandEvent& evt)
{
	//OnStartWorker(evt);
	

	//VM_find_process_list(vmi1,vmi1.process);
	//vector<VM_process*> temp_process = cmp_process(vmi1);
	//AppendMessage(wxString(temp_process[0]->comm, wxConvUTF8));

	// for (int i = 0; i < temp_process.size(); ++i)
	// {
	// 	printf("%s\n", );
	// }
	
// 	m_choice_process->Clear();
// 	wxString s = m_choice_vms->GetString(m_choice_vms->GetCurrentSelection());
// 	std::string VM_name;
// 	VM_name = std::string(s);
// 	char *name = const_cast<char*>(VM_name.c_str()); //将string型转换为char*型
// 	//char *name = s.mb_str()
									 
//   /* initialize the libvmi library */
// #ifdef ____LIBVMI____
// 	vmi_instance_t vmi;
// 	if (VMI_FAILURE ==
// 		vmi_init_complete(&vmi, name, VMI_INIT_DOMAINNAME, NULL,
// 			VMI_CONFIG_GLOBAL_FILE_ENTRY, NULL, NULL))
// 	{
// 		printf("Failed to init LibVMI library.\n");
// 		return;
// 	}
// /*****************************/
//     m_process_tree->DeleteAllItems();
//     root = m_process_tree->AddRoot(VM_name, 0);
//     wxArrayTreeItemIds items;

// 	struct info proc2[2000],item_name[2000];
// 	int count_tree = process_tree(vmi,proc2);
// 	int item_count = 1;
// //wxString p_s ="[" + wxString::Format(wxT("%i"),proc2[0].ppid) + "]" + proc2[0].pname;  //将int型pid转为wxString
// //items.Add(m_process_tree->AppendItem(root,p_s, 0));
// 	items.Add(m_process_tree->AppendItem(root,proc2[0].pname, 0));
// 	item_name[0].name = proc2[0].pname;
// 	for(int j=1;j<count_tree;j++){
// 		if(strcmp(proc2[j].pname,proc2[j-1].pname) != 0){
// 			items.Add(m_process_tree->AppendItem(root, proc2[j].pname, 0));
// 			item_name[item_count].name = proc2[j].pname;
// 			item_count++;
// 		}
// 	}

//     int i, count, k = 1;
//     for (i = 0, count = items.Count(); i < count; ++i) {
//         wxTreeItemId id = items.Item(i);
// 		while(k<count_tree){
// 			if(strcmp(proc2[k].pname,item_name[i].name)==0){
// 				m_process_tree->AppendItem(id, proc2[k].name, 1);	
// 				k++;		
// 			}
// 			else{break;}
// 		}
//     }

//     m_process_tree->Expand(root);

// /**************************/
// 	int count_list = 0;
// 	struct info proc1[2000];
// 	count_list = process_list(vmi, proc1);
// 	for (int i = 0;i<count_list;i++) {
// 		m_choice_process->AppendString(proc1[i].name);
// 	}
// 	m_choice_process->SetSelection(0);
// #endif
}

void  VMdefendorFrame::FillVMs(wxChoice *choice) 
{
	//choice->AppendString(wxT("Domain-U, Linux "));
	//choice->AppendString(wxT("Domain-0, Windows 8.1"));

#ifdef ____LIBVMI____
	vmi_instance_t vmi0;
	vmi_mode_t mode;
	int VM_sum = 0;
	char *VM_name[100];
	VM_sum = get_VMname(VM_name);
	for (int i = 0;i<VM_sum;i++) {
		choice->AppendString(VM_name[i]); //添加所有虚拟机名称
		if (VMI_FAILURE != vmi_get_access_mode(vmi0, (void*)VM_name[i],   VMI_INIT_DOMAINNAME, NULL, &mode)) {
			//choice->AppendString(VM_name[i]); //已开启运行的虚拟机名称
			//printf("虚拟机存在.\n");
		}
	}
#endif

}
