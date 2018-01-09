/***************************************************************
 * Name:      ProfileMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2017-10-06
 * Copyright:  ()
 * License:
 **************************************************************/

#include "ProfileMain.h"
#include <wx/msgdlg.h>

#include "Profile.h"
#include <wx/string.h>
#include <wx/intl.h>

#include <wx/wx.h>
//helper functions
enum wxbuildinfoformat {
    short_f, long_f };


const long ProfileDialog::ID_STATICTEXT1 = wxNewId();
const long ProfileDialog::ID_CHOICE1 = wxNewId();
const long ProfileDialog::ID_STATICTEXT2 = wxNewId();
const long ProfileDialog::ID_CHOICE2 = wxNewId();
const long ProfileDialog::ID_CHOICE3 = wxNewId();
const long ProfileDialog::ID_CHOICE4 = wxNewId();
const long ProfileDialog::ID_CHOICE5 = wxNewId();
const long ProfileDialog::ID_STATICTEXT3 = wxNewId();
const long ProfileDialog::ID_CHOICE6 = wxNewId();
const long ProfileDialog::ID_STATICTEXT4 = wxNewId();
const long ProfileDialog::ID_CHECKBOX1 = wxNewId();
const long ProfileDialog::ID_CHECKBOX2 = wxNewId();
const long ProfileDialog::ID_CHECKBOX3 = wxNewId();
const long ProfileDialog::ID_STATICTEXT5 = wxNewId();
const long ProfileDialog::ID_TEXTCTRL1 = wxNewId();
const long ProfileDialog::ID_BUTTON1 = wxNewId();
const long ProfileDialog::ID_BUTTON2 = wxNewId();
const long ProfileDialog::ID_CHOICE7 = wxNewId();
const long ProfileDialog::ID_BUTTON3 = wxNewId();
const long ProfileDialog::ID_CHOICE8 = wxNewId();
const long ProfileDialog::ID_STATICTEXT6 = wxNewId();
const long ProfileDialog::ID_STATICTEXT7 = wxNewId();
const long ProfileDialog::ID_STATICTEXT8 = wxNewId();
const long ProfileDialog::ID_STATICTEXT9 = wxNewId();
const long ProfileDialog::ID_STATICTEXT10 = wxNewId();
const long ProfileDialog::ID_STATICTEXT11 = wxNewId();

BEGIN_EVENT_TABLE(ProfileDialog,wxDialog)
    //(*EventTable(ProfileDialog)
    //*)
    EVT_BUTTON(wxID_OK,ProfileDialog::OnButton1Click)
END_EVENT_TABLE()

ProfileDialog::ProfileDialog(wxWindow* parent,MonitorProfile &Profile,wxWindowID id)
{
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;

    Create(parent, id, _("wxWidgets app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
  	BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, wxT("监控对象"), wxDefaultPosition, wxSize(170,-1), 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, wxT("监控启动的时间点"), wxDefaultPosition, wxSize(170,-1), 0, _T("ID_STATICTEXT2"));  
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, wxT("监控的重复周期"), wxDefaultPosition, wxSize(170,-1), 0, _T("ID_STATICTEXT3"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, wxT("监控OS内核数据结构"), wxDefaultPosition, wxSize(170,-1), 0, _T("ID_STATICTEXT4"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, wxT("文件监控的路径"), wxDefaultPosition, wxSize(170,-1), 0, _T("ID_STATICTEXT5"));
    Choice1 = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice2 = new wxChoice(this, ID_CHOICE2, wxDefaultPosition, wxSize(50,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
	Choice3 = new wxChoice(this, ID_CHOICE3, wxDefaultPosition, wxSize(50,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    Choice4 = new wxChoice(this, ID_CHOICE4, wxDefaultPosition, wxSize(50,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE4"));
    Choice5 = new wxChoice(this, ID_CHOICE5, wxDefaultPosition, wxSize(50,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE5"));
    Choice6 = new wxChoice(this, ID_CHOICE6, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE6"));
    Choice7 = new wxChoice(this, ID_CHOICE7, wxDefaultPosition, wxSize(65,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE7"));
    Choice8 = new wxChoice(this, ID_CHOICE8, wxDefaultPosition, wxSize(50,-1), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE8"));
    StaticText6 = new wxStaticText(this, ID_STATICTEXT1, wxT("年-"), wxDefaultPosition, wxSize(20,-1), 0, _T("ID_STATICTEXT1"));
    StaticText7 = new wxStaticText(this, ID_STATICTEXT2, wxT("月-"), wxDefaultPosition, wxSize(20,-1), 0, _T("ID_STATICTEXT2"));
    StaticText8 = new wxStaticText(this, ID_STATICTEXT3, wxT("日 "), wxDefaultPosition, wxSize(20,-1), 0, _T("ID_STATICTEXT3"));
    StaticText9 = new wxStaticText(this, ID_STATICTEXT4, wxT(":"), wxDefaultPosition, wxSize(20,-1), 0, _T("ID_STATICTEXT4"));
    StaticText10 = new wxStaticText(this, ID_STATICTEXT5, wxT(":"), wxDefaultPosition, wxSize(20,-1), 0, _T("ID_STATICTEXT5"));
    StaticText11 = new wxStaticText(this, ID_STATICTEXT6, wxT(""), wxDefaultPosition, wxSize(20,-1), 0, _T("ID_STATICTEXT6"));
   
    CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, wxT("进程"), wxDefaultPosition, wxSize(80,-1), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox2 = new wxCheckBox(this, ID_CHECKBOX2, wxT("模块"), wxDefaultPosition, wxSize(80,-1), 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBox3 = new wxCheckBox(this, ID_CHECKBOX3, wxT("文件"), wxDefaultPosition, wxSize(80,-1), 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(500,-1), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    Button1 = new wxButton(this, ID_BUTTON1, wxT("确认"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button2 = new wxButton(this, ID_BUTTON2, wxT("取消"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    Button3 = new wxButton(this, ID_BUTTON3, wxT("..."), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    
	for(int i=1;i<=12;i++)
        Choice2->Append(wxString::Format("%i",i));
    for(int i=1;i<=31;i++)
        Choice3->Append(wxString::Format("%i",i));
    for(int i=0;i<=9;i++)
        Choice4->Append(wxT("0")+wxString::Format("%i",i));
    for(int i=10;i<=23;i++)
        Choice4->Append(wxString::Format("%i",i));
    for(int i=0;i<=9;i++)
        Choice5->Append(wxT("0")+wxString::Format("%i",i));
    for(int i=10;i<=59;i++)
        Choice5->Append(wxString::Format("%i",i));
    for(int i=0;i<=9;i++)
        Choice8->Append(wxString::Format("%i",i));
    for(int i=10;i<=59;i++)
        Choice8->Append(wxString::Format("%i",i));
    for(int i=2017;i<=2050;i++)
        Choice7->Append(wxString::Format("%i",i));
    
    Choice6->Append(wxT("仅一次"));
    Choice6->SetSelection( Choice6->Append(wxT("每小时")) );
    Choice6->Append(wxT("每半天"));
    Choice6->Append(wxT("每天"));
    Choice6->Append(wxT("每个工作日"));
    Choice6->Append(wxT("每周"));
    Choice6->Append(wxT("每两周"));
    Choice6->Append(wxT("每个月"));

    Choice2->SetSelection(6);
    Choice3->SetSelection(15);
	Choice4->SetSelection(11);
	Choice5->SetSelection(29);
    Choice7->SetSelection(1);
    Choice8->SetSelection(8);

	CheckBox1->SetValue(false);
    CheckBox2->SetValue(false);
    CheckBox3->SetValue(false);

    BoxSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2->Add(Choice1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(Choice7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(StaticText6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3->Add(Choice2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(StaticText7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(Choice3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(StaticText8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(Choice4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(StaticText9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(Choice5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(StaticText10, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(Choice8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(StaticText11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);



    BoxSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(Choice6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(CheckBox1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(CheckBox2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(CheckBox3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer5, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6->Add(StaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6->Add(TextCtrl1, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6->Add(Button3, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer7->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer7->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    TempProfile = &Profile;

	//虚拟机列表读入
    // VM_list_vm vmlist[100];
    // get_vm_list(vmlist);
    // for (size_t i = 0; i < vmlist[0].num; i++)
    // 	Choice1->Append(wxString(vmlist[i].name.c_str()));

    Choice1->Append(TempProfile->settings[0].vm_os);
    Choice1->Append(TempProfile->settings[1].vm_os);

    ShowPreConfig(TempProfile->settings[0]);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProfileDialog::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProfileDialog::OnButton2Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ProfileDialog::OnButton3Click);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&ProfileDialog::OnChoice1Select);

}

ProfileDialog::~ProfileDialog()
{
    //(*Destroy(ProfileDialog)
    //*)
}

void ProfileDialog::ShowPreConfig(SettingsMoni PreConfig){

    //显示配置
    Choice1->SetSelection(Choice1->FindString(PreConfig.vm_os));
	Choice2->SetSelection(PreConfig.tm_monitoring.tm_mon-1);
	Choice3->SetSelection(PreConfig.tm_monitoring.tm_mday-1);
	Choice4->SetSelection(PreConfig.tm_monitoring.tm_hour);
	Choice5->SetSelection(PreConfig.tm_monitoring.tm_min);
    Choice8->SetSelection(PreConfig.tm_monitoring.tm_sec);
    Choice6->SetSelection(PreConfig.repeat-1);
    Choice7->SetSelection(PreConfig.tm_monitoring.tm_year-2017);
    CheckBox1->SetValue(PreConfig.os_ds_process);
    CheckBox2->SetValue(PreConfig.os_ds_module);
    CheckBox3->SetValue(PreConfig.os_ds_file);
    TextCtrl1->Clear();
    TextCtrl1->AppendText(PreConfig.path);

}

void ProfileDialog::OnButton1Click(wxCommandEvent& event)
{
	//获取当前配置
	
    //NewConfig.vm_os = Choice1->GetString(Choice1->GetSelection());

    TempProfile->settings[Choice1->GetSelection()].tm_monitoring.tm_year = Choice7->GetSelection()+2017;
    TempProfile->settings[Choice1->GetSelection()].tm_monitoring.tm_mon = Choice2->GetSelection();
    TempProfile->settings[Choice1->GetSelection()].tm_monitoring.tm_mday= Choice3->GetSelection();
    TempProfile->settings[Choice1->GetSelection()].tm_monitoring.tm_hour = Choice4->GetSelection();
    TempProfile->settings[Choice1->GetSelection()].tm_monitoring.tm_min = Choice5->GetSelection();
    TempProfile->settings[Choice1->GetSelection()].tm_monitoring.tm_sec = Choice8->GetSelection();
    TempProfile->settings[Choice1->GetSelection()].repeat = (MonitorRepeatType)(Choice6->GetSelection()+1);
    TempProfile->settings[Choice1->GetSelection()].os_ds_process = CheckBox1->GetValue();
    TempProfile->settings[Choice1->GetSelection()].os_ds_module = CheckBox2->GetValue();
    TempProfile->settings[Choice1->GetSelection()].os_ds_file = CheckBox3->GetValue();
    TempProfile->settings[Choice1->GetSelection()].path = TextCtrl1->GetLineText(0);
    Close();
}

void ProfileDialog::OnButton2Click(wxCommandEvent& event)
{
    Close();
}

void ProfileDialog::OnButton3Click(wxCommandEvent& event)
{
    FileDialog1 = new wxFileDialog(this, wxT("选取监控路径"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr,
         wxFD_DEFAULT_STYLE|wxFD_OPEN|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FileDialog1->ShowModal();  
    TextCtrl1->Clear();
    TextCtrl1->AppendText(FileDialog1->GetCurrentlySelectedFilename());
}

void ProfileDialog::OnChoice1Select(wxCommandEvent& event)
{
    ShowPreConfig(TempProfile->settings[Choice1->GetSelection()]);
}
