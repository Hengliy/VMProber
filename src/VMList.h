///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef _VMLIST_H
#define _VMLIST_H

#include "wx/aui/aui.h"
#include "definition.h"

enum{

	ID_SCROLLEDWINDOWSEVEN,
	ID_TREECTRL
};



wxWindow* CreateVMList(wxWindow *Notebookone, VM_list_vm VM_Message[], wxTreeCtrl *&TreeCtrlone,wxChoice* &m_choice_vms, wxWindowID winid = wxID_ANY);

#endif
