///////////////////////////////////////////////////////////////////////////////
// Name:        WMStatusBar.h
// Purpose:     Headfile of WMStatusBar class definition. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#ifndef __WMStatusBar_H__
#define __WMStatusBar_H__

#include "wx/app.h"

enum
{
	// menu items
	StatusBar_Quit = wxID_EXIT,
	StatusBar_About = wxID_ABOUT,

	StatusBar_SetFields = wxID_HIGHEST + 1,
	StatusBar_SetField,
	StatusBar_SetText,
	StatusBar_PushText,
	StatusBar_PopText,
	StatusBar_SetFont,
	StatusBar_ResetFieldsWidth,
	StatusBar_ShowFieldsRect,

	StatusBar_Recreate,
	StatusBar_Toggle,
	StatusBar_Checkbox,
	StatusBar_SetPaneStyle,
	StatusBar_SetPaneStyleNormal,
	StatusBar_SetPaneStyleFlat,
	StatusBar_SetPaneStyleRaised,
	StatusBar_SetPaneStyleSunken,

	StatusBar_SetStyleSizeGrip,
	StatusBar_SetStyleEllipsizeStart,
	StatusBar_SetStyleEllipsizeMiddle,
	StatusBar_SetStyleEllipsizeEnd,
	StatusBar_SetStyleShowTips
};

// A custom status bar which contains controls, icons &c
class VMStatusBar : public wxStatusBar
{
public:
	VMStatusBar(wxWindow *parent, long style = wxSTB_DEFAULT_STYLE);
	virtual ~VMStatusBar();

	void UpdateClock();

	// event handlers
	void OnSize(wxSizeEvent& event);
	void OnToggleClock(wxCommandEvent& event);
	void OnIdle(wxIdleEvent& event);
	void SetMonitorStatus(bool status );

private:
	enum
	{
		Field_Text,
		Field_Launched,
		Field_Monitor,
		Field_Clock,
		Field_Max
	};

	wxDECLARE_EVENT_TABLE();
};

#endif
