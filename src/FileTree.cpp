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
#include "FileTree.h"
#include "definition.h"


void ShowTree(VM_file* fileNode,int deep,wxTreeItemId ItemId,wxTreeCtrl* TreeCtrl1)
{

//	cout<<endl;
//	cout<<"ShowTree"<<endl;
//	cout<<endl;
	VM_list_head* p;

    for(p=fileNode->subdirs.next;p!=&(fileNode->subdirs);p=p->next){
		VM_file* tempNode=VM_list_entry(p,struct VM_file,bro);
		//for(int i=0;i<deep;i++)  cout<<"  ";
//		cout<<tempNode->name<<endl;
		wxTreeItemId FatherId = TreeCtrl1->PrependItem(ItemId,
			wxString(tempNode->name.c_str()),-1,-1,new FileTreeItemData(*tempNode));
		if(tempNode->subdirs.next){
			ShowTree(tempNode,deep+1,FatherId,TreeCtrl1);
		}		
	}
}

wxWindow* CreateFileTree(wxWindow* Notebookone, VM_vmi &vmi, wxTreeCtrl *&TreeCtrlone, wxWindowID winid /*= wxID_ANY*/)
{
	wxBoxSizer* Boxone;
	//wxTreeCtrl* TreeCtrlone;
	wxScrolledWindow* ScrolledWindowone;
	
	ScrolledWindowone = new wxScrolledWindow(Notebookone, ID_SCROLLEDWINDOWTEN,
		wxPoint(33, 79), wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWONE"));
	TreeCtrlone = new wxTreeCtrl(ScrolledWindowone, ID_TREECTRLTEN, wxDefaultPosition, 
		wxDefaultSize, wxTR_DEFAULT_STYLE|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TREECTRLONE"));

	Boxone = new wxBoxSizer(wxVERTICAL);
	Boxone->Add(TreeCtrlone, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowone->SetSizer(Boxone);
	Boxone->Fit(ScrolledWindowone);
	Boxone->SetSizeHints(ScrolledWindowone);

	wxTreeItemId ItemId = TreeCtrlone->AddRoot(wxString(vmi.file_root.name.c_str()),
		-1,-1,new FileTreeItemData(vmi.file_root));

//	cout<<"**********************************************";
//	cout<<vmi.file_root.name<<endl;

	ShowTree(&vmi.file_root,0,ItemId,TreeCtrlone);
	
	return ScrolledWindowone;
}


