///////////////////////////////////////////////////////////////////////////////
// Name:        WMdefendor.cpp
// Purpose:     WMdefendorApp class definition, the main app extended from wxApp. 
// Author:      OS Group
// Modified by: Weidong Tian
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
#include "wx/aui/aui.h"

#include "VMdefendor.h"
#include "VMdefendorFrame.h"

DECLARE_APP(VMDefendorApp)
IMPLEMENT_APP(VMDefendorApp)

bool VMDefendorApp::OnInit()
{
    if ( !wxApp::OnInit() )
        return false;

    wxFrame* frame = new VMdefendorFrame(NULL,
                                 wxID_ANY,
                                 wxT("虚拟化平台虚拟机OS内核监控与诊断系统VMProber"),
                                 wxDefaultPosition,
                                 wxSize(1280, 768));
    frame->Show();

    return true;
}
