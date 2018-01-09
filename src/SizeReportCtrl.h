///////////////////////////////////////////////////////////////////////////////
// Name:        SizeReportCtrl.h
// Purpose:     Head file of SizeReportCtrl.cpp. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-03-15
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

// -- wxSizeReportCtrl --
// (a utility control that always reports it's client size)

class wxSizeReportCtrl : public wxControl
{
public:

    wxSizeReportCtrl(wxWindow* parent, wxWindowID id = wxID_ANY,
                     const wxPoint& pos = wxDefaultPosition,
                     const wxSize& size = wxDefaultSize,
                     wxAuiManager* mgr = NULL)
                     : wxControl(parent, id, pos, size, wxNO_BORDER)
    {
        m_mgr = mgr;
    }

private:

    void OnPaint(wxPaintEvent& WXUNUSED(evt))
    {
        wxPaintDC dc(this);
        wxSize size = GetClientSize();
        wxString s;
        int h, w, height;

        s.Printf(wxT("Size: %d x %d"), size.x, size.y);

        dc.SetFont(*wxNORMAL_FONT);
        dc.GetTextExtent(s, &w, &height);
        height += 3;
        dc.SetBrush(*wxWHITE_BRUSH);
        dc.SetPen(*wxWHITE_PEN);
        dc.DrawRectangle(0, 0, size.x, size.y);
        dc.SetPen(*wxLIGHT_GREY_PEN);
        dc.DrawLine(0, 0, size.x, size.y);
        dc.DrawLine(0, size.y, size.x, 0);
        dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2));

        if (m_mgr)
        {
            wxAuiPaneInfo pi = m_mgr->GetPane(this);

            s.Printf(wxT("Layer: %d"), pi.dock_layer);
            dc.GetTextExtent(s, &w, &h);
            dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*1));

            s.Printf(wxT("Dock: %d Row: %d"), pi.dock_direction, pi.dock_row);
            dc.GetTextExtent(s, &w, &h);
            dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*2));

            s.Printf(wxT("Position: %d"), pi.dock_pos);
            dc.GetTextExtent(s, &w, &h);
            dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*3));

            s.Printf(wxT("Proportion: %d"), pi.dock_proportion);
            dc.GetTextExtent(s, &w, &h);
            dc.DrawText(s, (size.x-w)/2, ((size.y-(height*5))/2)+(height*4));
        }
    }

    void OnEraseBackground(wxEraseEvent& WXUNUSED(evt))
    {
        // intentionally empty
    }

    void OnSize(wxSizeEvent& WXUNUSED(evt))
    {
        Refresh();
    }
private:

    wxAuiManager* m_mgr;

    wxDECLARE_EVENT_TABLE();
};
