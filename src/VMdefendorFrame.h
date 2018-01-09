///////////////////////////////////////////////////////////////////////////////
// Name:        VMdefendorFrame.h
// Purpose:     Head file for clas VMdefendorFrame.cpp. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#ifndef __VMdefendorFrame_H__
#define __VMdefendorFrame_H__

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include <iostream>
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
//#include "cmp_file.h"
#include "wx/aui/aui.h"

#include "Profile.h"

#include "vector"
using namespace std;

#include "definition.h"

//#define ____LIBVMI____  1

#define WIN_VMS           (wxT("vms"))
#define WIN_PROCESS       (wxT("process_tree"))
#define WIN_PROCESS_LIST  (wxT("process_list"))
#define WIN_MODULE        (wxT("module"))
#define WIN_FILE          (wxT("file"))
#define WIN_MSG           (wxT("msg"))
#define WIN_NTBOOK        (wxT("ntbook"))

enum
{
	ID_CreateTree = wxID_HIGHEST + 1,
	ID_CreateGrid,
	ID_CreateText,
	ID_CreateHTML,
	ID_CreateNotebook,
	ID_CreateSizeReport,
	ID_GridContent,
	ID_TextContent,
	ID_TreeContent,
	ID_HTMLContent,
	ID_NotebookContent,
	ID_SizeReportContent,
	ID_CreatePerspective,
	ID_CopyPerspectiveCode,
	ID_AllowFloating,
	ID_AllowActivePane,
	ID_TransparentHint,
	ID_VenetianBlindsHint,
	ID_RectangleHint,
	ID_NoHint,
	ID_HintFade,
	ID_NoVenetianFade,
	ID_TransparentDrag,
	ID_NoGradient,
	ID_VerticalGradient,
	ID_HorizontalGradient,
	ID_LiveUpdate,
	ID_AllowToolbarResizing,
	ID_Settings,
	ID_CustomizeToolbar,
	ID_DropDownToolbarItem,
	ID_NotebookNoCloseButton,
	ID_NotebookCloseButton,
	ID_NotebookCloseButtonAll,
	ID_NotebookCloseButtonActive,
	ID_NotebookAllowTabMove,
	ID_NotebookAllowTabExternalMove,
	ID_NotebookAllowTabSplit,
	ID_NotebookWindowList,
	ID_NotebookScrollButtons,
	ID_NotebookTabFixedWidth,
	ID_NotebookArtGloss,
	ID_NotebookArtSimple,
	ID_NotebookAlignTop,
	ID_NotebookAlignBottom,

	ID_PROFILE_SWITCH,
	ID_PROFILE_SAVE,

	ID_VM_ENUMERATE,
	ID_VM_FIND,
	ID_VM_MONITOR_START,

	ID_OS_SCAN,
	ID_OS_SNAP,
	ID_OS_MONITORLIST,
	ID_OS_MONITORLIST_ADD,
	ID_OS_MONITORLIST_REMOVE,
	ID_OS_MONITOR_START,
	ID_OS_INFO,

	ID_PROCESS_KILL,
	ID_PROCESS_SUSPEND,
	ID_PROCESS_MONITORLIST,
	ID_PROCESS_MONITORLIST_ADD,
	ID_PROCESS_MONITORLIST_REMOVE,
	ID_PROCESS_INFO,
	ID_OS_PORT,

	//ID_TOOL_PROCESS,
	//ID_TOOL_FILE,
	//ID_TOOL_PROCESS_IO,
	//ID_SETTINGS,

	ID_WIN_PROCESS,
	ID_WIN_PROCESS_LIST,
	ID_WIN_NTBOOK,
	ID_WIN_VMS,
	ID_WIN_FILE,
	ID_WIN_MODULE,
	ID_WIN_PORT,
	ID_WIN_MSG,
	ID_WIN_LOG,

	ID_TOOLKIT_SCAN_PROCESS,
	ID_TOOLKIT_SCAN_PROCESS_IOVIEW,
	ID_TOOLKIT_SCAN_MODULE,
	ID_TOOLKIT_SCAN_FILE,
	ID_SETTINGS,
	ID_SETTINGS_VM,

	ID_TOOL_CHOICE_VM,
	ID_TOOL_CHOICE_PROCESS,

	ID_TIMER_MONITOR,
	ID_TIMER_1_SEC,

	WORKER_EVENT,           // these ones sent from WorkerThread
	WORKER_EVENT_START,
	WORKER_EVENT_END,
	WORKER_EVENT_PROCESS_TREE,
	WORKER_EVENT_PROCESS_LIST,   
	WORKER_EVENT_MODULE_LIST,   
	WORKER_EVENT_FILE_TREE,   
	WORKER_EVENT_FILE,        
	WORKER_EVENT_PROCESS,   
	WORKER_EVENT_MODULE,   

	ID_SampleItem,

	ID_FirstPerspective = ID_CreatePerspective + 1000,

};

// 保存所抓取的OS内核数据结构信息的结构
typedef struct _SnapProcess {
	time_t t;  // 抓取时间
	VM_process  root;
} SnapProcess ;
typedef struct _SnapModule {
	time_t t;
	vector<VM_module> m;
} SnapModule;
typedef struct _SnapFile {
	time_t t;
	VM_file  root;
} SnapFile;
typedef struct _SnapVM {
	time_t t;
	VM_vmi vm;
	vector<SnapProcess> snap_process;
	vector<SnapModule> snap_module;
	vector<SnapFile> snap_file;
} SnapVM;

typedef struct _Msg {
	wxString msg;
	union { 
		VM_process *process;
		VM_module *module;
		VM_file *file;
	} d;
} Msg;

// -- main frame class --
class  wxSizeReportCtrl;

class VMdefendorFrame : public wxFrame
{

public:
    VMdefendorFrame(wxWindow* parent,
            wxWindowID id,
            const wxString& title,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxDEFAULT_FRAME_STYLE | wxSUNKEN_BORDER);

    ~VMdefendorFrame();

    wxAuiDockArt* GetDockArt();
    void DoUpdate();

private:
    wxTextCtrl* CreateTextCtrl(const wxString& text = wxEmptyString);
    wxGrid* CreateGrid();
    wxTreeCtrl* CreateTreeCtrl();
    wxSizeReportCtrl* CreateSizeReportCtrl(int width = 80, int height = 80);
    wxPoint GetStartPosition();
    wxAuiNotebook* CreateNotebook();
	wxTextCtrl* CreateLog();
	wxWindow* ShowProcessTree();

	void InitLog();

	void InitMenu();
	void InitToolBar();
	void InitStatusBar();

private:
	void InitPanels();
private:
	void FillVMs(wxChoice *choice);
	void FillProcesses(wxChoice *choice);
	void ExitThreads();
	void InitMonitor();
	void ExitMonitor();
	void InitMainTimer();
	void ExitMainTimer();

	void DeleteAllProcessPagesOfVM(SnapVM  &snap_vm);
	void DeleteAllFilePagesOfVM(SnapVM  &snap_vm);
	void DeleteAllModulePagesOfVM(SnapVM  &snap_vm);

private:

    void OnEraseBackground(wxEraseEvent& evt);
    void OnSize(wxSizeEvent& evt);

	void OnProfileSwitch(wxCommandEvent& evt);
	void OnProfileSave(wxCommandEvent& evt);
	void OnCreateTree(wxCommandEvent& evt);
    void OnCreateGrid(wxCommandEvent& evt);
    void OnCreateHTML(wxCommandEvent& evt);
    void OnCreateNotebook(wxCommandEvent& evt);
    void OnCreateText(wxCommandEvent& evt);
    void OnCreateSizeReport(wxCommandEvent& evt);
    void OnChangeContentPane(wxCommandEvent& evt);
    void OnDropDownToolbarItem(wxAuiToolBarEvent& evt);
    void OnCreatePerspective(wxCommandEvent& evt);
    void OnCopyPerspectiveCode(wxCommandEvent& evt);
    void OnRestorePerspective(wxCommandEvent& evt);
    void OnSettings(wxCommandEvent& evt);
	void OnSettingsVM(wxCommandEvent& evt);
	void OnCustomizeToolbar(wxCommandEvent& evt);
    void OnAllowNotebookDnD(wxAuiNotebookEvent& evt);
    void OnNotebookPageClose(wxAuiNotebookEvent& evt);
    void OnNotebookPageClosed(wxAuiNotebookEvent& evt);
    void OnExit(wxCommandEvent& evt);
    void OnAbout(wxCommandEvent& evt);
    void OnTabAlignment(wxCommandEvent &evt);
	void OnWinMsgDclik(wxCommandEvent &evt);
	

    void OnGradient(wxCommandEvent& evt);
    void OnToolbarResizing(wxCommandEvent& evt);
    void OnManagerFlag(wxCommandEvent& evt);
    void OnNotebookFlag(wxCommandEvent& evt);
    void OnUpdateUI(wxUpdateUIEvent& evt);

    void OnPaneClose(wxAuiManagerEvent& evt);

	void OnVMEnumerate(wxCommandEvent& evt);
	void OnVMFind(wxCommandEvent& evt);
	void OnVMStart(wxCommandEvent& evt);

	void OnOSScan(wxCommandEvent& evt);
	void OnOSSnap(wxCommandEvent& evt);
	void OnOSMonitorlist(wxCommandEvent& evt);
	void OnOSMonitorlistAdd(wxCommandEvent& evt);
	void OnOSMonitorlistRemove(wxCommandEvent& evt);
	void OnOSMonitorStart(wxCommandEvent& evt);

	void OnToolkitScanProcess(wxCommandEvent& evt);
	void OnToolkitScanProcessIOView(wxCommandEvent& evt);
	void OnToolkitScanModule(wxCommandEvent& evt);
	void OnToolkitScanFile(wxCommandEvent& evt);
	void OnToolkitSettings(wxCommandEvent& evt);

	void OnWinProcess(wxCommandEvent& evt);
	void OnWinProcessList(wxCommandEvent& evt);
	void OnWinVMs(wxCommandEvent& evt);
	void OnWinFile(wxCommandEvent& evt);
	void OnWinModule(wxCommandEvent& evt);
	void OnWinMsg(wxCommandEvent& evt);
	void OnWinNTbook(wxCommandEvent& evt);

	void OnProcessKill(wxCommandEvent& evt);
	void OnProcessSuspend(wxCommandEvent& evt);
	void OnProcessInfo(wxCommandEvent& evt);

	void OnStartWorker(wxCommandEvent& WXUNUSED(event));
	void OnTimer(wxTimerEvent& evt);
	void OnTimerMonitor(wxTimerEvent& evt);
	void OnShowPanelProcess(wxTreeEvent& event);

	void OnWorkerEvent(wxThreadEvent& event);
	void OnWorkerEventStart(wxThreadEvent& event);
	void OnWorkerEventEnd(wxThreadEvent& event);
	void OnWorkerEventProcessTree(wxThreadEvent& event);
	void OnWorkerEventProcess(wxThreadEvent& event);
	void OnWorkerEventModule(wxThreadEvent& event);

	void SetCurrentVM(int index);
	void AppendVM(MonitorProfile &profile );

public:
	void AppendMessage(wxString msg);
	bool ComputeNextTime(time_t tnow, time_t &tnext);
	void ComputeNextTime(time_t tnow, SettingsMoni &conf);
	void SetGap(SettingsMoni &conf);
	void StartNextTimer();
	wxListBox* CreateMsg();
	void UpdateLastMessage(wxString msg);
	
private:
    wxAuiManager m_mgr;
    wxArrayString m_perspectives;
    wxMenu* m_perspectives_menu;
	wxMenu* window_menu;

    long m_notebook_style;
    long m_notebook_theme;

	wxChoice* m_choice_process;// 进程选择控件，工具栏
	wxChoice* m_choice_vms;    // 虚拟机选择控件，工具栏

	wxTimer m_timer;             // 主定时器：1s间隔

	// 所有列表窗口
	//
	wxTreeCtrl *m_vmslist;       // 虚拟机列表显示控件，虚拟机列表窗口
	//wxTreeCtrl *m_process;     // 进程列表窗口（树）
	wxTreeCtrl* m_process_tree;            // 进程列表显示控件，进程列表窗口（树）
	wxTreeItemId root;           // 根，m_process_tree	
	wxTreeCtrl *m_process_list;  // 进程列表显示控件，进程列表窗口（线性）
	wxAuiNotebook *m_nb_info;    // 信息显示集控件，notebook for 所有详细信息页
	wxTreeCtrl *m_module_tree;       // 模块列表显示控件，模块列表窗口
	wxTreeCtrl* m_file_tree;     // 文件列表显示控件，文件列表窗口（树）
	wxTextCtrl *m_msgs;          // 消息显示控件，“系统消息”窗口，obsolete
	wxListBox *m_msgslist;       // 消息显示控件，“系统消息”窗口
								 
	// 消息窗口对应的消息列表
	//
	vector<Msg> m_msglist;   // 消息窗口中显示的所有消息，循环队列（最多10000条，多余的按照FIFO原则丢掉） 

	// 保存所有抓取的虚拟机OS内核数据结构信息（树结构）
	vector<SnapVM> m_vms;       // 虚拟机列表
	SnapVM m_vm_current;        // 当前虚拟机，来自vms数组
	int  m_vm_current_index;    // 当前虚拟机的索引，vms数组下标

	// 后台监控数据结构。
	// 监控系统根据预定的OS内核检测时间，启动对特定虚拟机的特定检测动作
	//
	MonitorProfile config;       // 被监控虚拟机的详细监控参数设置
	bool m_monitor;              // 监控是否已经启动
	wxDateTime m_monitor_time;   // 本次监控的启动时间
	wxTimer m_timer_monitor;     // 启动下次扫描的启动定时器
	vector<VM_process*> hide_process;
	vector<VM_file*> hide_file;

    wxDECLARE_EVENT_TABLE();
};

#endif
