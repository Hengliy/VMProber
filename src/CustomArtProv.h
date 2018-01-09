///////////////////////////////////////////////////////////////////////////////
// Name:        CustomArtProv.h
// Purpose:     Headfile of CustomArtProv.cpp. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#ifndef __CustomArtProv_H__
#define __CustomArtProv_H__

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/aui/aui.h"

// ArtIDs in toolbars for wxWidgets
#define  wxART_ID_VM_EMUERATE                 wxART_MAKE_ART_ID(wxART_ID_VM_EMUERATE)
#define  wxART_ID_VM_FIND                     wxART_MAKE_ART_ID(wxART_ID_VM_FIND)
#define  wxART_ID_VM_MONITOR_START            wxART_MAKE_ART_ID(wxART_ID_VM_MONITOR_START)
#define  wxART_ID_OS_SCAN                     wxART_MAKE_ART_ID(wxART_ID_OS_SCAN)
#define  wxART_ID_OS_MONITOR_START            wxART_MAKE_ART_ID(wxART_ID_OS_MONITOR_START)
#define  wxART_ID_OS_MONITORLIST_ADD          wxART_MAKE_ART_ID(wxART_ID_OS_MONITORLIST_ADD)
#define  wxART_ID_OS_MONITORLIST_REMOVE       wxART_MAKE_ART_ID(wxART_ID_OS_MONITORLIST_REMOVE)
#define  wxART_ID_PROCESS_KILL                wxART_MAKE_ART_ID(wxART_ID_PROCESS_KILL)
#define  wxART_ID_PROCESS_SUSPEND             wxART_MAKE_ART_ID(wxART_ID_PROCESS_SUSPEND)
#define  wxART_ID_PROCESS_MONITORLIST_ADD     wxART_MAKE_ART_ID(wxART_ID_PROCESS_MONITORLIST_ADD)
#define  wxART_ID_PROCESS_MONITORLIST_REMOVE  wxART_MAKE_ART_ID(wxART_ID_PROCESS_MONITORLIST_REMOVE)
#define  wxART_ID_OS_MONITORLIST_SETTINGS  wxART_MAKE_ART_ID(wxART_ID_OS_MONITORLIST_SETTINGS)

class CustomArtProvider : public wxArtProvider
{
protected:
	wxBitmap CreateBitmap(const wxArtID& id,
		const wxArtClient& client,
		const wxSize &size);

};

#endif