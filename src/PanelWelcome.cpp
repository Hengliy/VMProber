///////////////////////////////////////////////////////////////////////////////
// Name:        PanelWelcome.cpp
// Purpose:     Display welcome information. 
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

#include "wx/aui/aui.h"
#include "PanelWelcome.h"

wxString GetIntroText()
{
	const char* text =
		"<html><body>"
		"<h1><font size='10' color='blue' face='Times New Roman'><b>Welcome to VMProber</font></b></h1>"
		"<br/><font size='6' face='Times New Roman'><b>Overview</b><br/>"
		"<font size='4' face='Times New Roman'>"
		"<p>VMProber is a specialized safety software for monitering and checking virtual machines in virtualization platform. Key technologies applied in VMProber is VMI, i.e. Virtual Machine Introspection.</p> "
		"<p>Traditionally information safety in computer is based on OS because OS is regarded as the lowest software level in the computer safety architecture.</p> "
		"<p>Different from these traditional OS-based safety softwares, VMProber runns on hypervisor other than OS in virtual machine. Therefore even though OS is hacked, VMProber is till safe while those traditional ones will be disability.</p> "
		"</body></html>";

	return wxString::FromAscii(text);
}

wxHtmlWindow* CreatePanelWelcome(wxWindow *parent, wxWindowID winid /*= wxID_ANY*/)
{
	wxHtmlWindow* ctrl = new wxHtmlWindow(parent, winid,
		wxDefaultPosition,
		wxSize(400, 300));
	ctrl->SetPage(GetIntroText());
	return ctrl;
}
