///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef _PROCESSTREE_H
#define _PROCESSTREE_H

#include "wx/aui/aui.h"
#include "definition.h"

enum{
	ID_TREECTRLONE,
	ID_SCROLLEDWINDOWFIVE
};

class MyTreeItemData : public wxTreeItemData {
public:
	MyTreeItemData(const VM_process& desc) { mdesc = desc; }
	VM_process mdesc;
	const VM_process& GetDesc() {
		return mdesc;
	}
private:
	wxString m_desc;
};

bool UpdateTree(VM_process &process,int b,wxTreeItemId rootId[],wxTreeCtrl* TreeCtrl1,VM_process hide_process);

wxWindow* CreateProcessTree(wxWindow *Notebookone, VM_process &process, wxTreeCtrl * &tree,wxChoice* &m_choice_process,  wxWindowID winid = wxID_ANY);

#endif
