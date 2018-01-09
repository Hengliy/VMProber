///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.cpp
// Purpose:     Display process information. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
// Created:     2017-10-01
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
#include <wx/colour.h>
#include <wx/settings.h>
#include "wx/aui/aui.h"
#include "PanelProcess.h"

panelProcessWindow::panelProcessWindow(wxWindow *Notebookone, VM_process &process, wxWindowID winid /*= wxID_ANY*/)
{
	wxGrid* Gridone;
	
	upprocess = process;
	// main window
	Create(Notebookone, 
		ID_SCROLLEDWINDOWONE, wxPoint(33, 79), wxDefaultSize, 
		wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWONE"));

	wxBoxSizer* Boxtwo = new wxBoxSizer(wxVERTICAL);

	// Part1 : main information of process
	//
	Gridone = new wxGrid(this, ID_GRIDONE, wxDefaultPosition,
		wxDefaultSize, wxSIMPLE_BORDER | wxVSCROLL | wxHSCROLL, _T("ID_GRIDONE"));
	Gridone->CreateGrid(6, 4);
	Gridone->EnableEditing(false);
	Gridone->EnableGridLines(true);
	Gridone->SetDefaultColSize(151, true);
	Gridone->HideColLabels();
	Gridone->HideRowLabels();
	Gridone->SetCellValue(0, 0, wxT("进程名称:"));
    Gridone->SetCellValue(0, 2, wxT("PID:"));
    Gridone->SetCellValue(1, 0, wxT("代码段开始地址:"));
    Gridone->SetCellValue(1, 2, wxT("代码段结束地址:"));
    Gridone->SetCellValue(2, 0, wxT("进程状态:"));
    Gridone->SetCellValue(2, 2, wxT("代码段长度:"));
    Gridone->SetCellValue(3, 0, wxT("标记:"));
    Gridone->SetCellValue(3, 2, wxT("父进程PID:"));
    Gridone->SetCellValue(4, 0, wxT("前一个兄弟ID:"));
    Gridone->SetCellValue(4, 2, wxT("动态优先级:"));
    Gridone->SetCellValue(5, 0, wxT("静态优先级:"));
    Gridone->SetCellValue(5, 2, wxT("实时优先级:"));
	Boxtwo->Add(Gridone, 4, wxALL | wxEXPAND | wxFIXED_MINSIZE | 
		wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	// Part 2: detail information of process, displayed in some pages managed by another notebook
	//
		wxNotebook* Notebooktwo = new wxNotebook(this, ID_NOTEBOOKTWO, wxDefaultPosition, wxSize(600, 0), 0, _T("ID_NOTEBOOKTWO"));
	wxScrolledWindow* ScrolledWindowtwo = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWTWO, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWTWO"));
	wxScrolledWindow* ScrolledWindowthree = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWTHREE, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWTHREE"));
	wxScrolledWindow* ScrolledWindowfour = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWFOUR, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWfour"));
	wxScrolledWindow* ScrolledWindowfive = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWF, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWfour"));

	wxBoxSizer* Boxthree = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* Boxfour = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* Boxfive = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* Boxsix = new wxBoxSizer(wxVERTICAL);
	TextCtrlone = new wxTextCtrl(ScrolledWindowtwo, ID_TEXTCTRLONE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLONE"));
	wxTextCtrl* TextCtrltwo = new wxTextCtrl(ScrolledWindowthree, ID_TEXTCTRLTWO, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLTWO"));
	wxTextCtrl* TextCtrlthree = new wxTextCtrl(ScrolledWindowfour, ID_TEXTCTRLTHREE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLTHREE"));
	wxTextCtrl* TextCtrlfour = new wxTextCtrl(ScrolledWindowfive, ID_TEXTCTRLT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLTHREE"));

	wxFont TextCtrl1Font(11, wxTELETYPE, wxFONTSTYLE_NORMAL, wxNORMAL, false, _T("Ubuntu Mono"), wxFONTENCODING_DEFAULT);
	TextCtrlone->SetFont(TextCtrl1Font);
	TextCtrltwo->SetFont(TextCtrl1Font);
	TextCtrlthree->SetFont(TextCtrl1Font);
	TextCtrlfour->SetFont(TextCtrl1Font);

	Boxthree->Add(TextCtrlone, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	Boxfour->Add(TextCtrltwo, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	Boxfive->Add(TextCtrlthree, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	wxBoxSizer* BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Text1 = new wxTextCtrl(ScrolledWindowtwo, ID_TEXT1, wxEmptyString, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    BoxSizer1->Add(Text1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxStaticText* StaticText1 = new wxStaticText(ScrolledWindowtwo, ID_STATICTEXT, _("-"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer1->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Text2 = new wxTextCtrl(ScrolledWindowtwo, ID_TEXT2, wxEmptyString, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer1->Add(Text2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxButton* But1 = new wxButton(ScrolledWindowtwo, ID_BUT1, wxT("抽取"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer1->Add(But1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Boxthree->Add(BoxSizer1, 0, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	
	wxBoxSizer* BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Text3 = new wxTextCtrl(ScrolledWindowthree, ID_TEXT3, wxEmptyString, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("ID_TEXCTRL1"));
    BoxSizer2->Add(Text3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxStaticText* StaticText2 = new wxStaticText(ScrolledWindowthree, ID_STATICTEXT2, _("-"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATITEXT1"));
    BoxSizer2->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Text4 = new wxTextCtrl(ScrolledWindowthree, ID_TEXT4, wxEmptyString, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("ID_TEXTCRL2"));
    BoxSizer2->Add(Text4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxButton* But2 = new wxButton(ScrolledWindowthree, ID_BUT2, wxT("抽取"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTON1"));
    BoxSizer2->Add(But2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Boxfour->Add(BoxSizer2, 0, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	wxBoxSizer* BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    Text5 = new wxTextCtrl(ScrolledWindowfour, ID_TEXT5, wxEmptyString, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("ID_TETCTRL1"));
    BoxSizer3->Add(Text5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxStaticText* StaticText3 = new wxStaticText(ScrolledWindowfour, ID_STATICTEXT3, _("-"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TATICTEXT1"));
    BoxSizer3->Add(StaticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Text6 = new wxTextCtrl(ScrolledWindowfour, ID_TEXT6, wxEmptyString, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("ID_EXTCTRL2"));
    BoxSizer3->Add(Text6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxButton* But3 = new wxButton(ScrolledWindowfour, ID_BUT3, wxT("抽取"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("I_BUTTON1"));
    BoxSizer3->Add(But3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Boxfive->Add(BoxSizer3, 0, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	ScrolledWindowtwo->SetSizer(Boxthree);
	Boxthree->Fit(ScrolledWindowtwo);
	Boxthree->SetSizeHints(ScrolledWindowtwo);
	ScrolledWindowthree->SetSizer(Boxfour);
	Boxfour->Fit(ScrolledWindowthree);
	Boxfour->SetSizeHints(ScrolledWindowthree);
	ScrolledWindowfour->SetSizer(Boxfive);
	Boxfive->Fit(ScrolledWindowfour);
	Boxfive->SetSizeHints(ScrolledWindowfour);

	Boxsix->Add(TextCtrlfour, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	
	wxBoxSizer* BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    Text7 = new wxTextCtrl(ScrolledWindowfive, ID_TEXT7, wxEmptyString, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("ID_TETCTRL1"));
    BoxSizer4->Add(Text7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxStaticText* StaticText4 = new wxStaticText(ScrolledWindowfive, ID_STATICTEXT4, _("-"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TATICTEXT1"));
    BoxSizer4->Add(StaticText4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Text8 = new wxTextCtrl(ScrolledWindowfive, ID_TEXT8, wxEmptyString, wxDefaultPosition, wxSize(200,-1), 0, wxDefaultValidator, _T("ID_EXTCTRL2"));
    BoxSizer4->Add(Text8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    wxButton* But4 = new wxButton(ScrolledWindowfive, ID_BUT4, wxT("抽取"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("I_BUTTON1"));
    BoxSizer4->Add(But4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Boxsix->Add(BoxSizer4, 0, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	ScrolledWindowfive->SetSizer(Boxsix);
	Boxsix->Fit(ScrolledWindowfive);
	Boxsix->SetSizeHints(ScrolledWindowfive);

	
	Notebooktwo->AddPage(ScrolledWindowfive, wxT("代码段"), false);
	Notebooktwo->AddPage(ScrolledWindowthree, wxT("堆栈段"), false);
	Notebooktwo->AddPage(ScrolledWindowfour, wxT("数据段"), false);
	Notebooktwo->AddPage(ScrolledWindowtwo, wxT("代码段-数据"), false);

	Boxtwo->Add(Notebooktwo, 9, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	this->SetSizer(Boxtwo);
	Boxtwo->Fit(this);
	Boxtwo->SetSizeHints(this);

	Connect(ID_BUT1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&panelProcessWindow::OnButton1Click);
	// Fill information from a VM_process instance
	//
	for(int i=0;i<6;i++){
		Gridone->SetCellBackgroundColour(i,0,*wxLIGHT_GREY); 
		Gridone->SetCellBackgroundColour(i,2,*wxLIGHT_GREY); 
	}
	
	
	size_t j;
        for (j = 0; j < process.asm_count; j++) {
		wxString temps = getHEX_addr(process.insn[j].address)+"  "+wxString(process.insn[j].mnemonic, wxConvUTF8)+"  "+wxString(process.insn[j].op_str, wxConvUTF8) + "\n";
		TextCtrlfour->AppendText(temps);
        //    printf("0x%"PRIx64":\t%s\t\t%s\n", process.insn[j].address, process.insn[j].mnemonic,
        //        process.insn[j].op_str);
        }
	
	

	ProcessMessage(Gridone, process);

	ProcessCode(TextCtrlone, process);

	DataCode(TextCtrlthree, process);

	StackCode(TextCtrltwo, process);
	
}

panelProcessWindow::~panelProcessWindow(){

}

wxString panelProcessWindow::getHEX_addr(unsigned long l){//转十六进制
    stringstream ss;
    ss<<setiosflags(ios::uppercase) << hex<<l;
    string c;
    ss>>c;
    int len = c.length();
    for(int i=0;i<(16-len);i++){
    	c = "0"+c;
    }
    return wxString(c.c_str());
}

wxString panelProcessWindow::getHEX_data(int l){
	stringstream ss;
	string c,b="0";
	ss<<setiosflags(ios::uppercase) << hex<<l;
	if(l<16){
		ss>>c;
		b+=c;
	}
    else
		ss>>b;
		
    return wxString(b.c_str());
}

void panelProcessWindow::ProcessMessage(wxGrid* Gridone,VM_process &process)
{
	Gridone->SetCellValue(0, 1, wxString(process.comm, wxConvUTF8));	

	Gridone->SetCellValue(0, 3, wxString::Format("%i", process.pid));

	Gridone->SetCellValue(1, 1, wxString(getHEX_addr(process.start_code_address).c_str()));
	Gridone->SetCellValue(1, 3, wxString(getHEX_addr(process.end_code_address).c_str()));
	switch (process.state) {
	case 0:
		Gridone->SetCellValue(2, 1, wxT("TASK_RUNNING"));
		break;
	case 1:
		Gridone->SetCellValue(2, 1, wxT("TASK_INTERRUPTIBLE"));
		break;
	case 2:
		Gridone->SetCellValue(2, 1, wxT("TASK_UNINTERRUPTIBLE"));
		break;
	case 4:
		Gridone->SetCellValue(2, 1, wxT("TASK_STOPPED"));
		break;
	case 8:
		Gridone->SetCellValue(2, 1, wxT("TASK_TRACED"));
		break;
	case 16:
		Gridone->SetCellValue(2, 1, wxT("EXIT_ZOMBIE"));
		break;
	case 32:
		Gridone->SetCellValue(2, 1, wxT("EXIT_DEAD"));
		break;
	case 64:
		Gridone->SetCellValue(2, 1, wxT("TASK_DEAD"));
		break;
	case 128:
		Gridone->SetCellValue(2, 1, wxT("TASK_WAKEKILL"));
		break;
	case 256:
		Gridone->SetCellValue(2, 1, wxT("TASK_WAKING"));
		break;
	}
	Gridone->SetCellValue(2, 3, wxString::Format(wxT("%ld"), process.end_code_address - process.start_code_address));
	Gridone->SetCellValue(3, 1, wxString::Format(wxT("%i"), process.flag));
	if (process.parent_pid == 9999)
		Gridone->SetCellValue(3, 3, wxT("无父进程"));
	else
		Gridone->SetCellValue(3, 3, wxString::Format(wxT("%i"), process.parent_pid));
	if (process.sibling_pid == 9999)
		Gridone->SetCellValue(4, 1, wxT("第一个子进程"));
	else
		Gridone->SetCellValue(4, 1, wxString::Format(wxT("%i"), process.sibling_pid));
	Gridone->SetCellValue(4, 3, wxString::Format(wxT("%i"), process.prio));
	Gridone->SetCellValue(5, 1, wxString::Format(wxT("%i"), process.static_prio));
	Gridone->SetCellValue(5, 3, wxString::Format(wxT("%i"), process.rt_priority));

}

void panelProcessWindow::ProcessCode(wxTextCtrl* TextCtrlone,VM_process &process){
	int row = (process.end_code_address - process.start_code_address) / 16;
	int record = 0;
	int temp;
	for (int i = 0;i<300;i++) {
		TextCtrlone->AppendText(wxString(getHEX_addr(process.start_code_address + record).c_str()));
		TextCtrlone->AppendText("  ");
		temp = record;
		for (int j = 0;j<16;j++) {
			// if (process.code[record] == 0)
			// 	TextCtrlone->AppendText("0");
			TextCtrlone->AppendText(wxString(getHEX_data(process.code[record]).c_str()));
			TextCtrlone->AppendText(" ");
			record++;
		}
		TextCtrlone->AppendText("  ");
		for (int j = 0;j<16;j++) {
			if (33>process.code[temp]||process.code[temp]>=127)
				TextCtrlone->AppendText(".");
			else {
				char* t = new char[2];
				t[0] = (char)process.code[temp];
				t[1] = '\0';
				TextCtrlone->AppendText(wxString(t, wxConvUTF8));
			}
			temp++;
		}
		TextCtrlone->AppendText("\n");
	}
}

void panelProcessWindow::DataCode(wxTextCtrl* TextCtrlone,VM_process &process){
	int row = (process.end_date_address - process.start_date_address) / 16;
	int record = 0;
	int temp;
	for (int i = 0;i<300;i++) {
		TextCtrlone->AppendText(wxString(getHEX_addr(process.start_date_address + record).c_str()));
		TextCtrlone->AppendText("  ");
		temp = record;
		for (int j = 0;j<16;j++) {
			// if (process.code[record] == 0)
			// 	TextCtrlone->AppendText("0");
			TextCtrlone->AppendText(wxString(getHEX_data(process.date[record]).c_str()));
			TextCtrlone->AppendText(" ");
			record++;
		}
		TextCtrlone->AppendText("  ");
		for (int j = 0;j<16;j++) {
			if (33>process.date[temp]||process.date[temp]>=127)
				TextCtrlone->AppendText(".");
			else {
				char* t = new char[2];
				t[0] = (char)process.date[temp];
				t[1] = '\0';
				TextCtrlone->AppendText(wxString(t, wxConvUTF8));
			}
			temp++;
		}
		TextCtrlone->AppendText("\n");
	}
}

void panelProcessWindow::StackCode(wxTextCtrl* TextCtrlone,VM_process &process){
	int row = (process.end_stack_address - process.start_stack_address) / 16;
	int record = 0;
	int temp;
	for (int i = 0;i<300;i++) {
		TextCtrlone->AppendText(wxString(getHEX_addr(process.start_stack_address + record).c_str()));
		TextCtrlone->AppendText("  ");
		temp = record;
		for (int j = 0;j<16;j++) {
			// if (process.code[record] == 0)
			// 	TextCtrlone->AppendText("0");
			TextCtrlone->AppendText(wxString(getHEX_data(process.stack[record]).c_str()));
			TextCtrlone->AppendText(" ");
			record++;
		}
		TextCtrlone->AppendText("  ");
		for (int j = 0;j<16;j++) {
			if (33>process.stack[temp]||process.stack[temp]>=127)
				TextCtrlone->AppendText(".");
			else {
				char* t = new char[2];
				t[0] = (char)process.stack[temp];
				t[1] = '\0';
				TextCtrlone->AppendText(wxString(t, wxConvUTF8));
			}
			temp++;
		}
		TextCtrlone->AppendText("\n");
	}
}

void panelProcessWindow::OnButton1Click(wxCommandEvent& event)
{
	TextCtrlone->Clear();

	unsigned long num1,num2;
    stringstream ss1,ss2;
    ss1<<hex<<(string)(Text1->GetLineText(0));
    ss1>>hex>>num1;
    ss2<<hex<<(string)(Text2->GetLineText(0));
    ss2>>hex>>num2;

	unsigned long row = (num2-num1) / 16;
	unsigned long record = num1-upprocess.start_code_address;
	unsigned long temp;
	for (int i = 0;i<=row;i++) {
		TextCtrlone->AppendText(wxString(getHEX_addr(upprocess.start_code_address + record).c_str()));
		TextCtrlone->AppendText("  ");
		temp = record;
		for (int j = 0;j<16;j++) {
			// if (process.code[record] == 0)
			// 	TextCtrlone->AppendText("0");
			TextCtrlone->AppendText(wxString(getHEX_data(upprocess.code[record]).c_str()));
			TextCtrlone->AppendText(" ");
			record++;
		}
		TextCtrlone->AppendText("  ");
		for (int j = 0;j<16;j++) {
			if (33>upprocess.code[temp]||upprocess.code[temp]>=127)
				TextCtrlone->AppendText(".");
			else {
				char* t = new char[2];
				t[0] = (char)upprocess.code[temp];
				t[1] = '\0';
				TextCtrlone->AppendText(wxString(t, wxConvUTF8));
			}
			temp++;
		}
		TextCtrlone->AppendText("\n");
	}
}
