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

#include "wx/aui/aui.h"
#include "VMList.h"
#include "definition.h"

class VMTreeItemData : public wxTreeItemData{
public:
    VMTreeItemData(const VM_list_vm& desc){
    	// m_desc.name = desc.name;
    	// m_desc.id = desc.id;
    	// m_desc.mem = desc.mem;
    	// m_desc.cpu = desc.cpu;
    	// m_desc.num = desc.num;
    	// m_desc.time = desc.time;
    	// m_desc.stat = desc.stat;
    }
    const VM_list_vm& GetDesc(){
        return m_desc;
    }
private:
    VM_list_vm m_desc;
};

bool ShowList(VM_list_vm VM_Message[],wxTreeCtrl* TreeCtrlone,wxChoice* m_choice_vms){
	wxTreeItemId ItemId = TreeCtrlone->AddRoot(wxT("ÐéÄâ»úÃû³Æ"),
		-1,-1,new VMTreeItemData(VM_Message[0]));
	for (size_t i = 0; i < VM_Message[0].num; i++) {
		TreeCtrlone->PrependItem(ItemId,
         		wxString(VM_Message[i].name.c_str()),-1,-1,new VMTreeItemData(VM_Message[i]));
		m_choice_vms->AppendString(wxString(VM_Message[i].name.c_str()));
	}

	return true;
}

wxWindow* CreateVMList(wxWindow* Notebookone, VM_list_vm VM_Message[], wxTreeCtrl *&TreeCtrlone,wxChoice* &m_choice_vms, wxWindowID winid /*= wxID_ANY*/)
{
	wxBoxSizer* Boxone;
	wxScrolledWindow* ScrolledWindowone;
	
	ScrolledWindowone = new wxScrolledWindow(Notebookone, ID_SCROLLEDWINDOWSEVEN,
		wxPoint(33, 79), wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWONE"));
	//wxTreeCtrl* TreeCtrlone = new wxTreeCtrl(ScrolledWindowone, ID_TREECTRL, wxDefaultPosition, 
	TreeCtrlone = new wxTreeCtrl(ScrolledWindowone, ID_TREECTRL, wxDefaultPosition,
		wxDefaultSize, wxTR_DEFAULT_STYLE|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TREECTRLONE"));

    Boxone = new wxBoxSizer(wxVERTICAL);
    Boxone->Add(TreeCtrlone, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

	ScrolledWindowone->SetSizer(Boxone);
	
	//Boxone->Fit(ScrolledWindowone);
	//Boxone->SetSizeHints(ScrolledWindowone);
	ShowList(VM_Message,TreeCtrlone,m_choice_vms);
	return ScrolledWindowone;
}


