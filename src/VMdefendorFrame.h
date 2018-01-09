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

// ������ץȡ��OS�ں����ݽṹ��Ϣ�Ľṹ
typedef struct _SnapProcess {
	time_t t;  // ץȡʱ��
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

	wxChoice* m_choice_process;// ����ѡ��ؼ���������
	wxChoice* m_choice_vms;    // �����ѡ��ؼ���������

	wxTimer m_timer;             // ����ʱ����1s���

	// �����б���
	//
	wxTreeCtrl *m_vmslist;       // ������б���ʾ�ؼ���������б���
	//wxTreeCtrl *m_process;     // �����б��ڣ�����
	wxTreeCtrl* m_process_tree;            // �����б���ʾ�ؼ��������б��ڣ�����
	wxTreeItemId root;           // ����m_process_tree	
	wxTreeCtrl *m_process_list;  // �����б���ʾ�ؼ��������б��ڣ����ԣ�
	wxAuiNotebook *m_nb_info;    // ��Ϣ��ʾ���ؼ���notebook for ������ϸ��Ϣҳ
	wxTreeCtrl *m_module_tree;       // ģ���б���ʾ�ؼ���ģ���б���
	wxTreeCtrl* m_file_tree;     // �ļ��б���ʾ�ؼ����ļ��б��ڣ�����
	wxTextCtrl *m_msgs;          // ��Ϣ��ʾ�ؼ�����ϵͳ��Ϣ�����ڣ�obsolete
	wxListBox *m_msgslist;       // ��Ϣ��ʾ�ؼ�����ϵͳ��Ϣ������
								 
	// ��Ϣ���ڶ�Ӧ����Ϣ�б�
	//
	vector<Msg> m_msglist;   // ��Ϣ��������ʾ��������Ϣ��ѭ�����У����10000��������İ���FIFOԭ�򶪵��� 

	// ��������ץȡ�������OS�ں����ݽṹ��Ϣ�����ṹ��
	vector<SnapVM> m_vms;       // ������б�
	SnapVM m_vm_current;        // ��ǰ�����������vms����
	int  m_vm_current_index;    // ��ǰ�������������vms�����±�

	// ��̨������ݽṹ��
	// ���ϵͳ����Ԥ����OS�ں˼��ʱ�䣬�������ض���������ض���⶯��
	//
	MonitorProfile config;       // ��������������ϸ��ز�������
	bool m_monitor;              // ����Ƿ��Ѿ�����
	wxDateTime m_monitor_time;   // ���μ�ص�����ʱ��
	wxTimer m_timer_monitor;     // �����´�ɨ���������ʱ��
	vector<VM_process*> hide_process;
	vector<VM_file*> hide_file;

    wxDECLARE_EVENT_TABLE();
};

#endif
