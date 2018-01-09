///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
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

//#include "../rc/icon/process_normal.xpm"
#include "wx/aui/aui.h"
#include "ProcessTree.h"
#include "definition.h"

bool UpdateTree(VM_process &process,int b,wxTreeItemId rootId[],wxTreeCtrl* TreeCtrl1,VM_process hide_process){
	VM_list_head *temp = NULL;
	VM_process *temp_process=NULL;

	if(process.parent_pid==9999){
		if(process.pid==hide_process.pid)
			rootId[process.pid] = TreeCtrl1->AddRoot(wxString(process.comm,
        			wxConvUTF8),1,1,new MyTreeItemData(process)); 
		else
			rootId[process.pid] = TreeCtrl1->AddRoot(wxString(process.comm,
        			wxConvUTF8),0,0,new MyTreeItemData(process)); 
	}
			
   	else if(process.sibling_pid==9999){
		if(process.pid==hide_process.pid)
			rootId[process.pid] = TreeCtrl1->PrependItem(rootId[process.parent_pid],
        			wxString(process.comm,wxConvUTF8),1,1,new MyTreeItemData(process));
		else
			rootId[process.pid] = TreeCtrl1->PrependItem(rootId[process.parent_pid],
        			wxString(process.comm,wxConvUTF8),0,0,new MyTreeItemData(process));
	}
        	
   	else{
		if(process.pid==hide_process.pid)
			rootId[process.pid] = TreeCtrl1->InsertItem(rootId[process.parent_pid],
        			rootId[process.sibling_pid],wxString(process.comm,wxConvUTF8),1,1,new MyTreeItemData(process));
		else
			rootId[process.pid] = TreeCtrl1->InsertItem(rootId[process.parent_pid],
        			rootId[process.sibling_pid],wxString(process.comm,wxConvUTF8),0,0,new MyTreeItemData(process));

	}
        	
	if (NULL!=process.children.next)
	{
		for (temp = process.children.next;temp!=&process.children ;temp = temp->next)
		{
			temp_process = VM_list_entry(temp,struct VM_process,sibling);
			UpdateTree(*temp_process,b+1,rootId,TreeCtrl1,hide_process);

		}

	}
	return 1;

}


bool ShowTree(VM_process &process,int b,wxTreeItemId rootId[],wxTreeCtrl* TreeCtrl1,wxChoice* m_choice_process){
	VM_list_head *temp = NULL;
	VM_process *temp_process=NULL;

	m_choice_process->AppendString(wxString(process.comm,
        		wxConvUTF8));
	if(process.parent_pid==9999)
		rootId[process.pid] = TreeCtrl1->AddRoot(wxString(process.comm,
        		wxConvUTF8),0,0,new MyTreeItemData(process)); 	
   	else if(process.sibling_pid==9999)
        	rootId[process.pid] = TreeCtrl1->PrependItem(rootId[process.parent_pid],
        		wxString(process.comm,wxConvUTF8),0,0,new MyTreeItemData(process));
   	else
        	rootId[process.pid] = TreeCtrl1->InsertItem(rootId[process.parent_pid],
        		rootId[process.sibling_pid],wxString(process.comm,wxConvUTF8),0,0,new MyTreeItemData(process));

	if (NULL!=process.children.next)
	{
		for (temp = process.children.next;temp!=&process.children ;temp = temp->next)
		{
			temp_process = VM_list_entry(temp,struct VM_process,sibling);
			ShowTree(*temp_process,b+1,rootId,TreeCtrl1,m_choice_process);

		}

	}
	return 1;

}

wxWindow* CreateProcessTree(wxWindow* Notebookone, VM_process &process, wxTreeCtrl * &TreeCtrlone,wxChoice* &m_choice_process , wxWindowID winid /*= wxID_ANY*/)
{
	wxBoxSizer* Boxone;
	//wxTreeCtrl* TreeCtrlone;
	wxScrolledWindow* ScrolledWindowone;
	
	ScrolledWindowone = new wxScrolledWindow(Notebookone, ID_SCROLLEDWINDOWFIVE,
		wxPoint(33, 79), wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWONE"));
	TreeCtrlone = new wxTreeCtrl(ScrolledWindowone, ID_TREECTRLONE, wxDefaultPosition, 
		wxDefaultSize, wxTR_DEFAULT_STYLE|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TREECTRLONE"));

	wxImageList* imglist = new wxImageList(16, 16,true,2);//true,2
	//imglist->Add(wxIcon(process_normal_xpm));
	imglist->Add(wxBitmap("rc/icon/process_normal.xpm"));
	imglist->Add(wxBitmap("rc/icon/process_error.xpm"));
	//imglist->Add(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16,16)));
	//imglist->Add(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16)));
	TreeCtrlone->AssignImageList(imglist);

	Boxone = new wxBoxSizer(wxVERTICAL);
	Boxone->Add(TreeCtrlone, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowone->SetSizer(Boxone);
	Boxone->Fit(ScrolledWindowone);
	Boxone->SetSizeHints(ScrolledWindowone);

	wxTreeItemId rootId[9999];

	ShowTree(process,0,rootId,TreeCtrlone,m_choice_process);

	return ScrolledWindowone;
}


