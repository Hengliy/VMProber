/***************************************************************
 * Name:      SettingMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2017-10-06
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef SettingMAIN_H
#define SettingMAIN_H
#include "Profile.h"
#include <wx/filedlg.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>


class SettingDialog: public wxDialog
{
    public:

        SettingDialog(wxWindow* parent,SettingsMoni &Setting,wxWindowID id = -1);

        virtual ~SettingDialog();

    private:
        void ShowPreConfig(SettingsMoni PreConfig);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);

        static const long ID_STATICTEXT1;
        static const long ID_CHOICE1;
        static const long ID_STATICTEXT2;
        static const long ID_CHOICE2;
        static const long ID_CHOICE3;
        static const long ID_CHOICE4;
        static const long ID_CHOICE5;
        static const long ID_STATICTEXT3;
        static const long ID_CHOICE6;
        static const long ID_CHOICE7;
        static const long ID_STATICTEXT4;
        static const long ID_CHECKBOX1;
        static const long ID_CHECKBOX2;
        static const long ID_CHECKBOX3;
        static const long ID_STATICTEXT5;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_CHOICE8;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT11;

        wxFileDialog* FileDialog1;
        wxButton* Button3;
        wxChoice* Choice3;
        wxButton* Button1;
        wxCheckBox* CheckBox1;
        wxButton* Button2;
        wxChoice* Choice2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxChoice* Choice4;
        wxChoice* Choice5;
        wxChoice* Choice1;
        wxCheckBox* CheckBox2;
        wxTextCtrl* TextCtrl1;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText2;
        wxCheckBox* CheckBox3;
        wxChoice* Choice6;
        wxChoice* Choice7;
        wxChoice* Choice8;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxStaticText* StaticText9;
        wxStaticText* StaticText10;
        wxStaticText* StaticText11;

        SettingsMoni* TempSetting=NULL;
        DECLARE_EVENT_TABLE()
};

#endif // SettingMAIN_H
