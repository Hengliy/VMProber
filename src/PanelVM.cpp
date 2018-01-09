///////////////////////////////////////////////////////////////////////////////
// Name:        PanelVM.cpp
// Purpose:     Dispaly information of one VM. 
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
#include "PanelVM.h"

wxWindow* CreatePanelWM( wxWindow *parent, wxWindowID winid /*= wxID_ANY*/ )
{
   wxPanel *panel = new wxPanel(parent, wxID_ANY );
   wxFlexGridSizer *flex = new wxFlexGridSizer( 4, 2, 0, 0 );
   flex->AddGrowableRow( 0 );
   flex->AddGrowableRow( 3 );
   flex->AddGrowableCol( 1 );
   flex->Add( 5,5 );   flex->Add( 5,5 );
   flex->Add( new wxStaticText( panel, -1, wxT("wxTextCtrl:") ), 0, wxALL|wxALIGN_CENTRE, 5 );
   flex->Add( new wxTextCtrl( panel, -1, wxT(""), wxDefaultPosition, wxSize(100,-1)),
                1, wxALL|wxALIGN_CENTRE, 5 );
   flex->Add( new wxStaticText( panel, -1, wxT("wxSpinCtrl:") ), 0, wxALL|wxALIGN_CENTRE, 5 );
   flex->Add( new wxSpinCtrl( panel, -1, wxT("5"), wxDefaultPosition, wxSize(100,-1),
                wxSP_ARROW_KEYS, 5, 50, 5 ), 0, wxALL|wxALIGN_CENTRE, 5 );
   flex->Add( 5,5 );   flex->Add( 5,5 );
   panel->SetSizer( flex );

   return panel;
}

