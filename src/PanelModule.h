///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#ifndef _PANELMODULE_H
#define _PANELMODULE_H

#include "wx/aui/aui.h"
#include "definition.h"

wxWindow* CreatePanelModule(wxWindow *Notebookone,const VM_module &module, wxWindowID winid = wxID_ANY);

#endif
