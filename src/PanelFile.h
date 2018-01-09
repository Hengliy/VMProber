///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////
#ifndef _PANELFILE_H
#define _PANELFILE_H
#include "wx/aui/aui.h"
#include "definition.h"

wxWindow* CreatePanelFile(wxWindow *Notebookone, VM_file &file_root, wxWindowID winid = wxID_ANY);

#endif
