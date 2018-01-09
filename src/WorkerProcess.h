///////////////////////////////////////////////////////////////////////////////
// Name:        WorkerProcess.h
// Purpose:     Head file for clas WorkerProcess.cpp. 
// Author:      OS Group
// Modified by: Weidong Tian
// Created:     2017-06-15
// Copyright:   (C) Copyright 2017, OS Group, HFUT, All Rights Reserved.
// Licence:     OS group Licence, Version 1.0
///////////////////////////////////////////////////////////////////////////////

#ifndef __WorkerProcess_H__
#define __WorkerProcess_H__


// ----------------------------------------------------------------------------
// a worker thread
// ----------------------------------------------------------------------------

class WorkerProcess : public wxThread
{
public:
	WorkerProcess(VMdefendorFrame *frame);
	~WorkerProcess();

	// thread execution starts here
	virtual void *Entry();

	// called when the thread exits - whether it terminates normally or is
	// stopped with Delete() (but not when it is Kill()ed!)
	virtual void OnExit();

public:
	VMdefendorFrame *m_frame;
	unsigned m_count;
};

#endif