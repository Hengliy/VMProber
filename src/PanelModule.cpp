///////////////////////////////////////////////////////////////////////////////
// Name:        PanelProcess.h
// Purpose:     head of UI of PanelProcess.cpp. 
// Author:      OS Group
// Modified by: Haoyu Yaobei
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
#include "sstream"
#include "iomanip"
#include "wx/aui/aui.h"
#include "PanelModule.h"
#include "definition.h"

static const long ID_FRAMENEW = wxNewId();
static const long ID_NOTEBOOKONE = wxNewId();
static const long ID_NOTEBOOKTWO = wxNewId();;
static const long ID_SCROLLEDWINDOWONE = wxNewId();
static const long ID_SCROLLEDWINDOWTWO = wxNewId();
static const long ID_SCROLLEDWINDOWTHREE = wxNewId();
static const long ID_SCROLLEDWINDOWFOUR = wxNewId();
static const long ID_GRIDONE = wxNewId();
static const long ID_TEXTCTRLONE = wxNewId();
static const long ID_TEXTCTRLTWO = wxNewId();
static const long ID_TEXTCTRLTHREE = wxNewId();
static const long ID_TEXTCTRLT = wxNewId();
static const long ID_NOTEBOOK2 = wxNewId();
static const long ID_SCROLLEDWINDOWF = wxNewId();


wxString getHEX_addr(unsigned long l){
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

wxString getHEX_data(int l){
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

void DataCode(wxTextCtrl* TextCtrlone,const VM_module &module){
	//int row = (process.end_date_address - process.start_date_address) / 16;
	int record = 0;
	int temp;
	for (int i = 0;i<300;i++) {
		TextCtrlone->AppendText(wxString(getHEX_addr(module.init_code_address + record).c_str()));
		TextCtrlone->AppendText("  ");
		temp = record;
		for (int j = 0;j<16;j++) {
			// if (process.code[record] == 0)
			// 	TextCtrlone->AppendText("0");
			TextCtrlone->AppendText(wxString(getHEX_data(module.code[record]).c_str()));
			TextCtrlone->AppendText(" ");
			record++;
		}
		TextCtrlone->AppendText("  ");
		for (int j = 0;j<16;j++) {
			if (33>module.code[temp]||module.code[temp]>=127)
				TextCtrlone->AppendText(".");
			else {
				char* t = new char[2];
				t[0] = (char)module.code[temp];
				t[1] = '\0';
				TextCtrlone->AppendText(wxString(t, wxConvUTF8));
			}
			temp++;
		}
		TextCtrlone->AppendText("\n");
	}
}

void ModuleMessage(wxGrid* Gridone,const VM_module &module)
{
	Gridone->SetCellValue(0,1,wxString(module.name, wxConvUTF8));
	Gridone->SetCellValue(1,1,wxString::Format(wxT("%i"), module.size));
	Gridone->SetCellValue(2,1,wxString::Format(wxT("%ld"), module.used_by_number));
	int i=0;
	string temp_name = "";
	if(module.used_by_name.size()!=0){
		temp_name += module.used_by_name[i];
		i++;
		while(i!=module.used_by_name.size()){
			temp_name += ",";
			temp_name += module.used_by_name[i];
			i++;
		}
		Gridone->SetCellValue(0,3,wxString(temp_name.c_str()));
	}
	else
		Gridone->SetCellValue(0,3,wxT("无"));
	
	if(module.version)
		Gridone->SetCellValue(1,3,wxString(module.version, wxConvUTF8));
	if(module.srcversion)
	Gridone->SetCellValue(2,3,wxString(module.srcversion, wxConvUTF8));
	Gridone->SetCellValue(3,1,wxString(getHEX_addr(module.init_code_address).c_str()));
	if(module.args)
		Gridone->SetCellValue(3,3,wxString(module.args, wxConvUTF8));
	else
		Gridone->SetCellValue(3,3,wxT("无"));
	Gridone->SetCellValue(4,1,wxString::Format(wxT("%i"), module.text_size));

}

void ModuleCode(wxTextCtrl* TextCtrlone,const VM_module &module )
{
	
}

wxWindow* CreatePanelModule(wxWindow *Notebookone, const VM_module &module, wxWindowID winid /*= wxID_ANY*/)
{
	wxGrid* Gridone;
	wxTextCtrl* TextCtrlone;

	// main window
	wxScrolledWindow *ScrolledWindowone = new wxScrolledWindow(Notebookone, 
		ID_SCROLLEDWINDOWONE, wxPoint(33, 79), wxDefaultSize, 
		wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWONE"));

	wxBoxSizer* Boxtwo = new wxBoxSizer(wxVERTICAL);

	// Part1 : main information of process
	//
	Gridone = new wxGrid(ScrolledWindowone, ID_GRIDONE, wxDefaultPosition,
		wxDefaultSize, wxSIMPLE_BORDER | wxVSCROLL | wxHSCROLL, _T("ID_GRIDONE"));
	Gridone->CreateGrid(5, 4);
	Gridone->EnableEditing(false);
	Gridone->EnableGridLines(true);
	Gridone->SetDefaultColSize(151, true);
	Gridone->HideColLabels();
	Gridone->HideRowLabels();
	Gridone->SetCellValue(0, 0, wxT("模块名称:"));
	Gridone->SetCellValue(0, 2, wxT("使用者:"));
	Gridone->SetCellValue(1, 0, wxT("模块大小："));
	Gridone->SetCellValue(1, 2, wxT("版本："));
	Gridone->SetCellValue(2, 0, wxT("使用人数:"));
	Gridone->SetCellValue(2, 2, wxT("资源版本:"));
	Gridone->SetCellValue(3, 0, wxT("代码段开始地址:"));
	Gridone->SetCellValue(3, 2, wxT("命令行参数:"));
 	Gridone->SetCellValue(4, 0, wxT("代码段长度:"));
	//Gridone->SetCellValue(4, 2, wxT(":"));
	//Gridone->SetCellValue(5, 0, wxT(":"));
	//Gridone->SetCellValue(5, 2, wxT(":"));
	Boxtwo->Add(Gridone, 4, wxALL | wxEXPAND | wxFIXED_MINSIZE | 
		wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	// Part 2: detail information of process, displayed in some pages managed by another notebook
	//
	wxNotebook* Notebooktwo = new wxNotebook(ScrolledWindowone, ID_NOTEBOOKTWO, wxDefaultPosition, wxSize(600, 0), 0, _T("ID_NOTEBOOKTWO"));
	wxScrolledWindow* ScrolledWindowtwo = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWTWO, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWTWO"));
	//wxScrolledWindow* ScrolledWindowthree = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWTHREE, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWTHREE"));
	//wxScrolledWindow* ScrolledWindowfour = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWFOUR, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWfour"));
	wxScrolledWindow* ScrolledWindowfive = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWF, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWfour"));

	wxBoxSizer* Boxthree = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Boxfour = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Boxfive = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Boxsix = new wxBoxSizer(wxHORIZONTAL);
	TextCtrlone = new wxTextCtrl(ScrolledWindowtwo, ID_TEXTCTRLONE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLONE"));
	//wxTextCtrl* TextCtrltwo = new wxTextCtrl(ScrolledWindowthree, ID_TEXTCTRLTWO, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLTWO"));
	//wxTextCtrl* TextCtrlthree = new wxTextCtrl(ScrolledWindowfour, ID_TEXTCTRLTHREE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLTHREE"));
	wxTextCtrl* TextCtrlfour = new wxTextCtrl(ScrolledWindowfive, ID_TEXTCTRLT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLTHREE"));

	wxFont TextCtrl1Font(11, wxTELETYPE, wxFONTSTYLE_NORMAL, wxNORMAL, false, _T("Ubuntu Mono"), wxFONTENCODING_DEFAULT);
	TextCtrlone->SetFont(TextCtrl1Font);
	//TextCtrltwo->SetFont(TextCtrl1Font);
	//TextCtrlthree->SetFont(TextCtrl1Font);
	TextCtrlfour->SetFont(TextCtrl1Font);

	Boxthree->Add(TextCtrlone, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowtwo->SetSizer(Boxthree);
	Boxthree->Fit(ScrolledWindowtwo);
	Boxthree->SetSizeHints(ScrolledWindowtwo);
	//Boxfour->Add(TextCtrltwo, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	//ScrolledWindowthree->SetSizer(Boxfour);
	Boxfour->Fit(ScrolledWindowtwo);
	Boxfour->SetSizeHints(ScrolledWindowtwo);
	//Boxfive->Add(TextCtrlthree, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	//ScrolledWindowfour->SetSizer(Boxfive);
	Boxfive->Fit(ScrolledWindowtwo);
	Boxfive->SetSizeHints(ScrolledWindowtwo);

	Boxsix->Add(TextCtrlfour, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowfive->SetSizer(Boxsix);
	Boxsix->Fit(ScrolledWindowfive);
	Boxsix->SetSizeHints(ScrolledWindowfive);
	

	Notebooktwo->AddPage(ScrolledWindowfive, wxT("代码段"), false);
	//Notebooktwo->AddPage(ScrolledWindowthree, wxT("堆栈段"), false);
	//Notebooktwo->AddPage(ScrolledWindowfour, wxT("数据段"), false);
	Notebooktwo->AddPage(ScrolledWindowtwo, wxT("代码段-数据"), false);

	Boxtwo->Add(Notebooktwo, 9, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowone->SetSizer(Boxtwo);
	Boxtwo->Fit(ScrolledWindowone);
	Boxtwo->SetSizeHints(ScrolledWindowone);

	for(int i=0;i<6;i++){
		Gridone->SetCellBackgroundColour(i,0,*wxLIGHT_GREY); 
		Gridone->SetCellBackgroundColour(i,2,*wxLIGHT_GREY); 
	}
	// Fill information from a VM_process instance
	//

	
	size_t j;
	for (j = 0; j < module.asm_count; j++) {
		wxString temps = getHEX_addr(module.insn[j].address)+"  "+wxString(module.insn[j].mnemonic, wxConvUTF8)+"  "+wxString(module.insn[j].op_str, wxConvUTF8) + "\n";
		TextCtrlfour->AppendText(temps);
		//printf("0x%"PRIx64":\t%s\t\t%s\n", process.insn[j].address, process.insn[j].mnemonic,
		//process.insn[j].op_str);
   	}
	

	ModuleMessage(Gridone,module);
	ModuleCode(TextCtrlone,module);
	DataCode(TextCtrlone,module);
	return ScrolledWindowone;
}


