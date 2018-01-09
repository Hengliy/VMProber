///////////////////////////////////////////////////////////////////////////////
// Name:        WorkerProcess.cpp
// Purpose:     Thread for checking process. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif
#include "process_list.h"
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


#include "wx/aui/aui.h"

#include "VMdefendor.h"
#include "VMdefendorFrame.h"
#include "SizeReportCtrl.h"
#include "SettingsPanel.h"
#include "PanelVM.h"
#include "PanelProcess.h"
#include "CustomArtProv.h"
#include "Profile.h"
#include "WorkerProcess.h"


WorkerProcess::WorkerProcess(VMdefendorFrame *frame)
	: wxThread()
{
	m_frame = frame;
	m_count = 0;
}

WorkerProcess::~WorkerProcess()
{
	wxCriticalSectionLocker locker(wxGetApp().m_critsect);

	wxArrayThread& threads = wxGetApp().m_threads;
	threads.Remove(this);

	if (threads.IsEmpty())
	{
		// signal the main thread that there are no more threads left if it is
		// waiting for us
		if (wxGetApp().m_shuttingDown)
		{
			wxGetApp().m_shuttingDown = false;

			wxGetApp().m_semAllDone.Post();
		}
	}

}

void WorkerProcess::OnExit()
{
}
extern bool temp_(VM_vmi &vmi1);
wxThread::ExitCode WorkerProcess::Entry()
{
	wxThreadIdType tid = this->GetId();

	wxThreadEvent event_start(wxEVT_THREAD, WORKER_EVENT_START);
	event_start.SetInt(-1); // that's all
	event_start.SetString(wxT("虚拟机扫描开始")); // that's all
	wxQueueEvent(m_frame, event_start.Clone());

	for (m_count = 0; m_count < 1; m_count++)
	{
		// check if we were asked to exit
		if (TestDestroy())
			break;

		// create any type of command event here
		wxThreadEvent event(wxEVT_THREAD, WORKER_EVENT_PROCESS);
		event.SetInt(m_count);  //主ID
		//event.SetString(wxString::Format("%d, %d", tid, m_count)); // that's all

		//// 传递结构到主线程
		//SettingsMoni mon;                         
		//mon.path = "C:\\T";
		//mon.t_gap = 10000;
		//event.SetPayload(mon);
		//// 传递指针到主线程
		//MonitorProfile *f2 = new MonitorProfile; 
		//f2->settings.push_back(mon);
		//f2->filename = "D:\\adasd";
		//f2->settings.push_back(mon);
		//event.SetPayload(f2);
		// VM_process
		//VM_process process;
		// VM_vmi vmi1;
	 //    VM_vmi_init("ubuntu14.04",vmi1);
	 //    VM_find_process_tree(vmi1,vmi1.process);
	    
	    //event.SetPayload(process);
		// process.pid = 12349876;
		// event.SetPayload(process);

		// send in a thread-safe way
		wxQueueEvent(m_frame, event.Clone());

		wxMilliSleep(50);
	}

	wxThreadEvent event_end(wxEVT_THREAD, WORKER_EVENT_END);
	event_end.SetInt(-1); // that's all
	event_end.SetString( wxT("虚拟机扫描结束") ); // that's all
	VM_process process;
	process.pid = 123498760;
	event_end.SetPayload(process);
	wxQueueEvent(m_frame, event_end.Clone());

	return NULL;
}

