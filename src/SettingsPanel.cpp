///////////////////////////////////////////////////////////////////////////////
// Name:        SettingsPanel.cpp
// Purpose:     Settings frame of the application. 
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

#include "VMdefendorFrame.h"
#include "SettingsPanel.h"

wxBEGIN_EVENT_TABLE(SettingsPanel, wxPanel)
    EVT_SPINCTRL(ID_PaneBorderSize, SettingsPanel::OnPaneBorderSize)
    EVT_SPINCTRL(ID_SashSize, SettingsPanel::OnSashSize)
    EVT_SPINCTRL(ID_CaptionSize, SettingsPanel::OnCaptionSize)
    EVT_BUTTON(ID_BackgroundColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_SashColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_InactiveCaptionColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_InactiveCaptionGradientColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_InactiveCaptionTextColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_ActiveCaptionColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_ActiveCaptionGradientColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_ActiveCaptionTextColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_BorderColor, SettingsPanel::OnSetColor)
    EVT_BUTTON(ID_GripperColor, SettingsPanel::OnSetColor)
wxEND_EVENT_TABLE()

SettingsPanel::SettingsPanel(wxWindow* parent, VMdefendorFrame* frame)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize),
	m_frame(frame)
{
	//wxBoxSizer* vert = new wxBoxSizer(wxVERTICAL);

	//vert->Add(1, 1, 1, wxEXPAND);

	wxBoxSizer* s1 = new wxBoxSizer(wxHORIZONTAL);
	m_border_size = new wxSpinCtrl(this, ID_PaneBorderSize, wxString::Format(wxT("%d"), frame->GetDockArt()->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE)), wxDefaultPosition, wxSize(50, 20), wxSP_ARROW_KEYS, 0, 100, frame->GetDockArt()->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE));
	s1->Add(1, 1, 1, wxEXPAND);
	s1->Add(new wxStaticText(this, wxID_ANY, wxT("Pane Border Size:")));
	s1->Add(m_border_size);
	s1->Add(1, 1, 1, wxEXPAND);
	s1->SetItemMinSize((size_t)1, 180, 20);
	//vert->Add(s1, 0, wxEXPAND | wxLEFT | wxBOTTOM, 5);

	wxBoxSizer* s2 = new wxBoxSizer(wxHORIZONTAL);
	m_sash_size = new wxSpinCtrl(this, ID_SashSize, wxString::Format(wxT("%d"), frame->GetDockArt()->GetMetric(wxAUI_DOCKART_SASH_SIZE)), wxDefaultPosition, wxSize(50, 20), wxSP_ARROW_KEYS, 0, 100, frame->GetDockArt()->GetMetric(wxAUI_DOCKART_SASH_SIZE));
	s2->Add(1, 1, 1, wxEXPAND);
	s2->Add(new wxStaticText(this, wxID_ANY, wxT("Sash Size:")));
	s2->Add(m_sash_size);
	s2->Add(1, 1, 1, wxEXPAND);
	s2->SetItemMinSize((size_t)1, 180, 20);
	//vert->Add(s2, 0, wxEXPAND | wxLEFT | wxBOTTOM, 5);

	wxBoxSizer* s3 = new wxBoxSizer(wxHORIZONTAL);
	m_caption_size = new wxSpinCtrl(this, ID_CaptionSize, wxString::Format(wxT("%d"), frame->GetDockArt()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE)), wxDefaultPosition, wxSize(50, 20), wxSP_ARROW_KEYS, 0, 100, frame->GetDockArt()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE));
	s3->Add(1, 1, 1, wxEXPAND);
	s3->Add(new wxStaticText(this, wxID_ANY, wxT("Caption Size:")));
	s3->Add(m_caption_size);
	s3->Add(1, 1, 1, wxEXPAND);
	s3->SetItemMinSize((size_t)1, 180, 20);
	//vert->Add(s3, 0, wxEXPAND | wxLEFT | wxBOTTOM, 5);

	//vert->Add(1, 1, 1, wxEXPAND);


	wxBitmap b = CreateColorBitmap(*wxBLACK);

	wxBoxSizer* s4 = new wxBoxSizer(wxHORIZONTAL);
	m_background_color = new wxBitmapButton(this, ID_BackgroundColor, b, wxDefaultPosition, wxSize(50, 25));
	s4->Add(1, 1, 1, wxEXPAND);
	s4->Add(new wxStaticText(this, wxID_ANY, wxT("Background Color:")));
	s4->Add(m_background_color);
	s4->Add(1, 1, 1, wxEXPAND);
	s4->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s5 = new wxBoxSizer(wxHORIZONTAL);
	m_sash_color = new wxBitmapButton(this, ID_SashColor, b, wxDefaultPosition, wxSize(50, 25));
	s5->Add(1, 1, 1, wxEXPAND);
	s5->Add(new wxStaticText(this, wxID_ANY, wxT("Sash Color:")));
	s5->Add(m_sash_color);
	s5->Add(1, 1, 1, wxEXPAND);
	s5->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s6 = new wxBoxSizer(wxHORIZONTAL);
	m_inactive_caption_color = new wxBitmapButton(this, ID_InactiveCaptionColor, b, wxDefaultPosition, wxSize(50, 25));
	s6->Add(1, 1, 1, wxEXPAND);
	s6->Add(new wxStaticText(this, wxID_ANY, wxT("Normal Caption:")));
	s6->Add(m_inactive_caption_color);
	s6->Add(1, 1, 1, wxEXPAND);
	s6->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s7 = new wxBoxSizer(wxHORIZONTAL);
	m_inactive_caption_gradient_color = new wxBitmapButton(this, ID_InactiveCaptionGradientColor, b, wxDefaultPosition, wxSize(50, 25));
	s7->Add(1, 1, 1, wxEXPAND);
	s7->Add(new wxStaticText(this, wxID_ANY, wxT("Normal Caption Gradient:")));
	s7->Add(m_inactive_caption_gradient_color);
	s7->Add(1, 1, 1, wxEXPAND);
	s7->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s8 = new wxBoxSizer(wxHORIZONTAL);
	m_inactive_caption_text_color = new wxBitmapButton(this, ID_InactiveCaptionTextColor, b, wxDefaultPosition, wxSize(50, 25));
	s8->Add(1, 1, 1, wxEXPAND);
	s8->Add(new wxStaticText(this, wxID_ANY, wxT("Normal Caption Text:")));
	s8->Add(m_inactive_caption_text_color);
	s8->Add(1, 1, 1, wxEXPAND);
	s8->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s9 = new wxBoxSizer(wxHORIZONTAL);
	m_active_caption_color = new wxBitmapButton(this, ID_ActiveCaptionColor, b, wxDefaultPosition, wxSize(50, 25));
	s9->Add(1, 1, 1, wxEXPAND);
	s9->Add(new wxStaticText(this, wxID_ANY, wxT("Active Caption:")));
	s9->Add(m_active_caption_color);
	s9->Add(1, 1, 1, wxEXPAND);
	s9->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s10 = new wxBoxSizer(wxHORIZONTAL);
	m_active_caption_gradient_color = new wxBitmapButton(this, ID_ActiveCaptionGradientColor, b, wxDefaultPosition, wxSize(50, 25));
	s10->Add(1, 1, 1, wxEXPAND);
	s10->Add(new wxStaticText(this, wxID_ANY, wxT("Active Caption Gradient:")));
	s10->Add(m_active_caption_gradient_color);
	s10->Add(1, 1, 1, wxEXPAND);
	s10->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s11 = new wxBoxSizer(wxHORIZONTAL);
	m_active_caption_text_color = new wxBitmapButton(this, ID_ActiveCaptionTextColor, b, wxDefaultPosition, wxSize(50, 25));
	s11->Add(1, 1, 1, wxEXPAND);
	s11->Add(new wxStaticText(this, wxID_ANY, wxT("Active Caption Text:")));
	s11->Add(m_active_caption_text_color);
	s11->Add(1, 1, 1, wxEXPAND);
	s11->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s12 = new wxBoxSizer(wxHORIZONTAL);
	m_border_color = new wxBitmapButton(this, ID_BorderColor, b, wxDefaultPosition, wxSize(50, 25));
	s12->Add(1, 1, 1, wxEXPAND);
	s12->Add(new wxStaticText(this, wxID_ANY, wxT("Border Color:")));
	s12->Add(m_border_color);
	s12->Add(1, 1, 1, wxEXPAND);
	s12->SetItemMinSize((size_t)1, 180, 20);

	wxBoxSizer* s13 = new wxBoxSizer(wxHORIZONTAL);
	m_gripper_color = new wxBitmapButton(this, ID_GripperColor, b, wxDefaultPosition, wxSize(50, 25));
	s13->Add(1, 1, 1, wxEXPAND);
	s13->Add(new wxStaticText(this, wxID_ANY, wxT("Gripper Color:")));
	s13->Add(m_gripper_color);
	s13->Add(1, 1, 1, wxEXPAND);
	s13->SetItemMinSize((size_t)1, 180, 20);

	wxGridSizer* grid_sizer = new wxGridSizer(2);
	grid_sizer->SetHGap(5);
	grid_sizer->Add(s1);  grid_sizer->Add(s4);
	grid_sizer->Add(s2);  grid_sizer->Add(s5);
	grid_sizer->Add(s3);  grid_sizer->Add(s13);
	grid_sizer->Add(1, 1); grid_sizer->Add(s12);
	grid_sizer->Add(s6);  grid_sizer->Add(s9);
	grid_sizer->Add(s7);  grid_sizer->Add(s10);
	grid_sizer->Add(s8);  grid_sizer->Add(s11);

	wxBoxSizer* cont_sizer = new wxBoxSizer(wxVERTICAL);
	cont_sizer->Add(grid_sizer, 1, wxEXPAND | wxALL, 5);
	SetSizer(cont_sizer);
	GetSizer()->SetSizeHints(this);

	m_border_size->SetValue(frame->GetDockArt()->GetMetric(wxAUI_DOCKART_PANE_BORDER_SIZE));
	m_sash_size->SetValue(frame->GetDockArt()->GetMetric(wxAUI_DOCKART_SASH_SIZE));
	m_caption_size->SetValue(frame->GetDockArt()->GetMetric(wxAUI_DOCKART_CAPTION_SIZE));

	UpdateColors();
}
