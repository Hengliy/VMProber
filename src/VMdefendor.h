///////////////////////////////////////////////////////////////////////////////
// Name:        WMdefendor.h
// Purpose:     Headfile of WMdefendorApp class definition, the main app extended from wxApp. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////


#ifndef __WMdefendor_H__
#define __WMdefendor_H__

#include "wx/app.h"

WX_DEFINE_ARRAY_PTR(wxThread *, wxArrayThread);

// -- application --
class VMDefendorApp : public wxApp
{
public:
    bool OnInit();

	// critical section protects access to all of the fields below
	wxCriticalSection m_critsect;

	// all the threads currently alive - as soon as the thread terminates, it's
	// removed from the array
	wxArrayThread m_threads;

	// semaphore used to wait for the threads to exit, see OnQuit() in frame
	wxSemaphore m_semAllDone;

	// indicates that we're shutting down and all threads should exit
	bool m_shuttingDown;

};

extern VMDefendorApp & wxGetApp();


#endif