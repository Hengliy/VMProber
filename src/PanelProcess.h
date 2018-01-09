///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#ifndef __PanelProcess_H__
#define __PanelProcess_H__

#include "wx/aui/aui.h"
#include "definition.h"
#include "sstream"

#include "iomanip"
enum{
ID_FRAMENEW,
ID_NOTEBOOKONE,
ID_NOTEBOOKTWO,
ID_SCROLLEDWINDOWONE,
ID_SCROLLEDWINDOWTWO,
ID_SCROLLEDWINDOWTHREE,
ID_SCROLLEDWINDOWFOUR,
ID_SCROLLEDWINDOWF,
ID_GRIDONE,
ID_TEXTCTRLONE,
ID_TEXTCTRLTWO,
ID_TEXTCTRLTHREE,
ID_NOTEBOOK2,
ID_TEXT1,
ID_TEXT2,
ID_TEXT3,
ID_TEXT4,
ID_TEXT5,
ID_TEXT6,
ID_TEXT7,
ID_TEXT8,
ID_BUT1,
ID_BUT2,
ID_BUT3,
ID_BUT4,
ID_STATICTEXT, 
ID_STATICTEXT2, 
ID_STATICTEXT3,
ID_STATICTEXT4,  
ID_TEXTCTRLT
};



class panelProcessWindow: public wxScrolledWindow
{
public:
	panelProcessWindow(wxWindow *Notebookone, VM_process &process, wxWindowID winid = wxID_ANY);
	virtual ~panelProcessWindow();
	VM_process upprocess;

private:
	wxString getHEX_addr(unsigned long l);
	wxString getHEX_data(int l);
	void ProcessMessage(wxGrid* Gridone,VM_process &process);
	void ProcessCode(wxTextCtrl* TextCtrlone,VM_process &process);
	void DataCode(wxTextCtrl* TextCtrlone,VM_process &process);
	void StackCode(wxTextCtrl* TextCtrlone,VM_process &process);
	void OnButton1Click(wxCommandEvent& event);
	wxTextCtrl* Text1;
	wxTextCtrl* Text2;
	wxTextCtrl* Text3;
	wxTextCtrl* Text4;
	wxTextCtrl* Text5;
	wxTextCtrl* Text6;
	wxTextCtrl* Text7;
	wxTextCtrl* Text8;
	wxTextCtrl* TextCtrlone;
};


#endif
