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

#include "wx/aui/aui.h"
#include "PanelFile.h"
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
static const long ID_NOTEBOOK2 = wxNewId();

void FileMessage(wxGrid* Gridone,VM_file &fileNode)
{
	if(fileNode.isfile==true)
		Gridone->SetCellValue(0, 3, wxT("否"));
	else
		Gridone->SetCellValue(0, 3, wxT("是"));
	Gridone->SetCellValue(0, 1, wxString(fileNode.name.c_str()));
	Gridone->SetCellValue(1, 1, wxString::Format(wxT("%ld"), fileNode.id));
	Gridone->SetCellValue(1, 3, wxString::Format(wxT("%ld"), fileNode.state));
	Gridone->SetCellValue(2, 1, wxString::Format(wxT("%i"), fileNode.user_id));
	Gridone->SetCellValue(2, 3, wxString::Format(wxT("%i"), fileNode.bytes));
	Gridone->SetCellValue(3, 1, wxString::Format(wxT("%i"), fileNode.mode));
	Gridone->SetCellValue(3, 3, wxString(fileNode.mtime.c_str()));
	Gridone->SetCellValue(4, 1, wxString::Format(wxT("%i"), fileNode.i_gid));
	Gridone->SetCellValue(4, 3, wxString::Format(wxT("%i"), fileNode.i_flags));
	Gridone->SetCellValue(5, 1, wxString(fileNode.s_type.c_str()));
	Gridone->SetCellValue(5, 3, wxString::Format(wxT("%i"), fileNode.i_rdev));
	Gridone->SetCellValue(6, 1, wxString::Format(wxT("%i"), fileNode.i_version));
	Gridone->SetCellValue(6, 3, wxString::Format(wxT("%i"), fileNode.i_count));
	Gridone->SetCellValue(7, 1, wxString(fileNode.parent_name.c_str()));
}

void FileCode(wxTextCtrl* TextCtrlone,VM_file &fileNode)
{
	
}


wxWindow* CreatePanelFile(wxWindow *Notebookone, VM_file &file_root, wxWindowID winid /*= wxID_ANY*/)
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
	Gridone->CreateGrid(8, 4);
	Gridone->EnableEditing(false);
	Gridone->EnableGridLines(true);
	Gridone->SetDefaultColSize(151, true);
	Gridone->HideColLabels();
	Gridone->HideRowLabels();
	Gridone->SetCellValue(0, 0, wxT("目录项名称:"));
    Gridone->SetCellValue(0, 2, wxT("是否是目录:"));
    Gridone->SetCellValue(1, 0, wxT("INODE_ID:"));
    Gridone->SetCellValue(1, 2, wxT("状态:"));
    Gridone->SetCellValue(2, 0, wxT("使用者ID:"));
    Gridone->SetCellValue(2, 2, wxT("所占用字节数:"));
    Gridone->SetCellValue(3, 0, wxT("权限:"));
    Gridone->SetCellValue(3, 2, wxT("最后一次修改时间:"));
    Gridone->SetCellValue(4, 0, wxT("用户组:"));
    Gridone->SetCellValue(4, 2, wxT("文件系统标志:"));
    Gridone->SetCellValue(5, 0, wxT("文件系统类型:"));
    Gridone->SetCellValue(5, 2, wxT("设备编号:"));
    Gridone->SetCellValue(6, 0, wxT("版本号:"));
    Gridone->SetCellValue(6, 2, wxT("引用计数:"));
    Gridone->SetCellValue(7, 0, wxT("父母录名称:"));
	Boxtwo->Add(Gridone, 2, wxALL | wxEXPAND | wxFIXED_MINSIZE | 
		wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	// Part 2: detail information of process, displayed in some pages managed by another notebook
	//
	wxNotebook* Notebooktwo = new wxNotebook(ScrolledWindowone, ID_NOTEBOOKTWO, wxDefaultPosition, wxSize(600, 0), 0, _T("ID_NOTEBOOKTWO"));
	wxScrolledWindow* ScrolledWindowtwo = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWTWO, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWTWO"));
	wxScrolledWindow* ScrolledWindowthree = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWTHREE, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWTHREE"));
	wxScrolledWindow* ScrolledWindowfour = new wxScrolledWindow(Notebooktwo, ID_SCROLLEDWINDOWFOUR, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxHSCROLL, _T("ID_SCROLLEDWINDOWfour"));

	wxBoxSizer* Boxthree = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Boxfour = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* Boxfive = new wxBoxSizer(wxHORIZONTAL);
	TextCtrlone = new wxTextCtrl(ScrolledWindowtwo, ID_TEXTCTRLONE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLONE"));
	wxTextCtrl* TextCtrltwo = new wxTextCtrl(ScrolledWindowthree, ID_TEXTCTRLTWO, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLTWO"));
	wxTextCtrl* TextCtrlthree = new wxTextCtrl(ScrolledWindowfour, ID_TEXTCTRLTHREE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxVSCROLL | wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRLTHREE"));

	wxFont TextCtrl1Font(11, wxTELETYPE, wxFONTSTYLE_NORMAL, wxNORMAL, false, _T("Ubuntu Mono"), wxFONTENCODING_DEFAULT);
	TextCtrlone->SetFont(TextCtrl1Font);
	TextCtrltwo->SetFont(TextCtrl1Font);
	TextCtrlthree->SetFont(TextCtrl1Font);

	Boxthree->Add(TextCtrlone, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowtwo->SetSizer(Boxthree);
	Boxthree->Fit(ScrolledWindowtwo);
	Boxthree->SetSizeHints(ScrolledWindowtwo);
	Boxfour->Add(TextCtrltwo, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowthree->SetSizer(Boxfour);
	Boxfour->Fit(ScrolledWindowtwo);
	Boxfour->SetSizeHints(ScrolledWindowtwo);
	Boxfive->Add(TextCtrlthree, 1, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowfour->SetSizer(Boxfive);
	Boxfive->Fit(ScrolledWindowtwo);
	Boxfive->SetSizeHints(ScrolledWindowtwo);

	Notebooktwo->AddPage(ScrolledWindowtwo, wxT("代码段"), false);
	Notebooktwo->AddPage(ScrolledWindowthree, wxT("堆栈段"), false);
	Notebooktwo->AddPage(ScrolledWindowfour, wxT("数据段"), false);

	Boxtwo->Add(Notebooktwo, 3, wxALL | wxEXPAND | wxFIXED_MINSIZE | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	ScrolledWindowone->SetSizer(Boxtwo);
	Boxtwo->Fit(ScrolledWindowone);
	Boxtwo->SetSizeHints(ScrolledWindowone);

	for(int i=0;i<8;i++){
		Gridone->SetCellBackgroundColour(i,0,*wxLIGHT_GREY); 
		Gridone->SetCellBackgroundColour(i,2,*wxLIGHT_GREY); 
	}

	FileMessage(Gridone,file_root);
	FileCode(TextCtrlone,file_root);

	return ScrolledWindowone;
}

