///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef _FILETREE_H
#define _FILETREE_H

#include "wx/aui/aui.h"
#include "definition.h"

class FileTreeItemData : public wxTreeItemData{
public:
    FileTreeItemData(const VM_file& desc){mdesc = desc;}
    VM_file mdesc;
    const VM_file& GetDesc(){
        return mdesc;
    }
private:
    wxString m_desc;
};


enum{
	ID_TREECTRLTEN,
	ID_SCROLLEDWINDOWTEN
};


wxWindow* CreateFileTree(wxWindow *Notebookone, VM_vmi &vmi, wxTreeCtrl *&TreeCtrlone, wxWindowID winid = wxID_ANY);

#endif
