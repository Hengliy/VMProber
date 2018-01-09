///////////////////////////////////////////////////////////////////////////////
// Name:        WMStatusBar.cpp
// Purpose:     StatusBar class of the application. 
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

#include "VMdefendor.h"
#include "VMdefendorFrame.h"
#include "VMStatusBar.h"


wxBEGIN_EVENT_TABLE(VMStatusBar, wxStatusBar)
    EVT_SIZE(VMStatusBar::OnSize)
    EVT_IDLE(VMStatusBar::OnIdle)
wxEND_EVENT_TABLE()

static const char *numlockIndicators[] = { "OFF", "NUM" };
static const char *capslockIndicators[] = { "", "CAPS" };
static const wxString monitor[] = { wxT("监控已启动"), wxT("监控已关闭") };
static const char *datetime[] = { "2017-07-12 16:12:34" };

VMStatusBar::VMStatusBar(wxWindow *parent, long style)
	: wxStatusBar(parent, wxID_ANY, style, "VMStatusBar")
{
	// compute the size needed for num lock indicator pane
	wxClientDC dc(this);
	wxSize sizemonitor = dc.GetTextExtent(monitor[0]);
	wxSize sizedatetime = dc.GetTextExtent(datetime[0]);

	int widths[Field_Max];
	widths[Field_Text] = -1;    // growable
	// widths[Field_Launched] = sizedatetime.x;  // 启动时间  
	//widths[Field_Monitor] = sizemonitor.x;
	// widths[Field_Clock] = sizedatetime.x;  // 当前时间，可关闭
	widths[Field_Launched] = 160;  // 启动时间  
	widths[Field_Monitor] = 100;
	widths[Field_Clock] = 170;  // 当前时间，可关闭
	SetFieldsCount(Field_Max);
	SetStatusWidths(Field_Max, widths);

	SetMinHeight(sizemonitor.y);

	SetStatusText(wxDateTime::Now().FormatISOCombined(' '), Field_Launched);
	UpdateClock();
}

VMStatusBar::~VMStatusBar()
{
}

void VMStatusBar::OnSize(wxSizeEvent& event)
{
	event.Skip();
}

void VMStatusBar::OnToggleClock(wxCommandEvent& WXUNUSED(event))
{
}

void VMStatusBar::OnIdle(wxIdleEvent& event)
{
	event.Skip();
}

void VMStatusBar::SetMonitorStatus( bool status )
{
	if ( status )
		SetStatusText(monitor[0], Field_Monitor);
	else
		SetStatusText(monitor[1], Field_Monitor);

}

void VMStatusBar::UpdateClock()
{
	SetStatusText(wxDateTime::Now().FormatISOCombined(' '), Field_Clock);
}
