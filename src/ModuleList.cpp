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
#include "ModuleList.h"
#include "definition.h"
#include "module.h"



void ModuleList(wxTreeCtrl* TreeCtrlone,VM_module& module){
	wxTreeItemId ItemId = TreeCtrlone->AddRoot(wxT("模块名称"),
		-1,-1,new ModuleTreeItemData(module));

	VM_module  *temp_module=&module;
	do{
		TreeCtrlone->PrependItem(ItemId,
         		wxString(temp_module->name, wxConvUTF8),-1,-1,new ModuleTreeItemData(*temp_module));
		temp_module = VM_list_entry(temp_module->list.next,struct VM_module,list);
	}while(&module!=temp_module);
}

wxWindow* CreateModuleList(wxWindow* Notebookone,VM_module &module, wxTreeCtrl* TreeCtrlone, wxWindowID winid /*= wxID_ANY*/)
{
	wxBoxSizer* Boxone;
	wxScrolledWindow* ScrolledWindowone;
	
	ScrolledWindowone = new wxScrolledWindow(Notebookone, ID_SCROLLEDWINDOWSIX,
		wxPoint(33, 79), wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWONE"));
    TreeCtrlone = new wxTreeCtrl(ScrolledWindowone, ID_TREE, wxDefaultPosition, 
		wxDefaultSize, wxTR_DEFAULT_STYLE|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TREE"));

    Boxone = new wxBoxSizer(wxVERTICAL);
    Boxone->Add(TreeCtrlone, 1, wxALL|wxEXPAND|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

	ScrolledWindowone->SetSizer(Boxone);
	Boxone->Fit(ScrolledWindowone);
	Boxone->SetSizeHints(ScrolledWindowone);

	// wxTreeItemId ItemId = TreeCtrlone->AddRoot(wxT("模块名称"),
	// 	-1,-1,new ModuleTreeItemData(module));
	// TreeCtrlone->PrependItem(ItemId,
 //         		wxString(module.name, wxConvUTF8),-1,-1,new ModuleTreeItemData(module));
	ModuleList(TreeCtrlone,module);

	return ScrolledWindowone;
}


