///////////////////////////////////////////////////////////////////////////////
// Name:        VMdefendorFrame.cpp
// Purpose:     Main frame of the application. 
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
#include "wx/filedlg.h"


#include "wx/aui/aui.h"
#include "../rc/VMdefendor.xpm"

#include "CustomArtProv.h"

wxBitmap CustomArtProvider::CreateBitmap(const wxArtID& id,
	const wxArtClient& client,
	const wxSize &WXUNUSED(size))
{
	//if(id == wxART_ID_VM_EMUERATE)
	//	return wxBitmap(wxART_MAKE_ART_ID(IDB_VM_EMUMERATE),wxBITMAP_TYPE_BMP_RESOURCE);
	//if (client == wxART_MESSAGE_BOX)
	//{
	/*	if (id == wxART_ID_VM_EMUERATE)
			return wxBITMAP(IDB_VM_ENUMERATE);
		if (id == wxART_ID_VM_FIND)
			return wxBITMAP(IDB_VM_FIND);
		if (id == wxART_ID_VM_MONITOR_START)
			return wxBITMAP(IDB_VM_MONITOR_START);
		if (id == wxART_ID_OS_SCAN)
			return wxBITMAP(IDB_OS_SCAN);
		if (id == wxART_ID_OS_MONITOR_START)
			return wxBITMAP(IDB_OS_MONITOR_START);
		if (id == wxART_ID_OS_MONITORLIST_ADD)
			return wxBITMAP(IDB_OS_MONITORLIST_ADD);
		if (id == wxART_ID_OS_MONITORLIST_REMOVE)
			return wxBITMAP(IDB_OS_MONITORLIST_REMOVE);
		if (id == wxART_ID_PROCESS_KILL)
			return wxBITMAP(IDB_PROCESS_KILL);
		if (id == wxART_ID_PROCESS_SUSPEND)
			return wxBITMAP(IDB_PROCESS_SUSPEND);
		if (id == wxART_ID_PROCESS_MONITORLIST_ADD)
			return wxBITMAP(IDB_PROCESS_MONITORLIST_ADD);
		if (id == wxART_ID_PROCESS_MONITORLIST_REMOVE)
			return wxBITMAP(IDB_PROCESS_MONITORLIST_REMOVE);
		}    
	return wxNullBitmap; */
		if (id == wxART_ID_VM_EMUERATE)
			return wxBitmap("rc/icon/enumeration.xpm");

		if (id == wxART_ID_VM_FIND)
			return wxBitmap("rc/icon/search.xpm");

		if (id == wxART_ID_VM_MONITOR_START)
			return wxBitmap("rc/icon/start_whole_monitor.xpm");

		if (id == wxART_ID_OS_SCAN)
			return wxBitmap("rc/icon/scan.xpm");

		if (id == wxART_ID_OS_MONITOR_START)
			return wxBitmap("rc/icon/start_os_monitor.xpm");

		if (id == wxART_ID_OS_MONITORLIST_ADD)
			return wxBitmap("rc/icon/add_os_monitor.xpm");

		if (id == wxART_ID_OS_MONITORLIST_REMOVE)
			return wxBitmap("rc/icon/exit_os_monitor.xpm");

		if (id == wxART_ID_PROCESS_KILL)
			return wxBitmap("rc/icon/kill_process.xpm");

		if (id == wxART_ID_PROCESS_SUSPEND)
			return wxBitmap("rc/icon/pause_os_monitor.xpm");

		if (id == wxART_ID_PROCESS_MONITORLIST_ADD)
			return wxBitmap("rc/icon/add_process_monitor.xpm");

		if (id == wxART_ID_PROCESS_MONITORLIST_REMOVE)
			return wxBitmap("rc/icon/exit_process_monitor.xpm");

		if (id == wxART_ID_OS_MONITORLIST_SETTINGS)
			return wxBitmap("rc/icon/setting.xpm");
	//	}    

	return wxNullBitmap;
}

