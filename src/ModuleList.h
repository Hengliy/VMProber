///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef _MODULELIST_H
#define _MODULELIST_H

#include "wx/aui/aui.h"
#include "definition.h"
class ModuleTreeItemData : public wxTreeItemData{
public:
    ModuleTreeItemData(const VM_module& desc){
    	mdesc = desc;
    }
    VM_module mdesc;
    const VM_module& GetDesc(){
        return mdesc;
    }
private:
    wxString m_desc;
};

enum{

	ID_SCROLLEDWINDOWSIX,
	ID_TREE
};



wxWindow* CreateModuleList(wxWindow *Notebookone,VM_module &module, wxTreeCtrl* TreeCtrlone, wxWindowID winid = wxID_ANY);

#endif
