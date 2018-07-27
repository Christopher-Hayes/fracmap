/* ThreadedFractalCreate.h
 *  Created by Shammah Chancellor on 07/11/2008.
 *  Copyright 2008 University Of Neveda, Reno. All rights reserved.
 * Modified: (07/18/18) Chris Hayes
 */
#pragma once
#include <wx/wx.h>
#include <wx/thread.h>
#include "PostTextEvent.h"
#include "../fractal/fractal.h"

enum
{
	ADDMONOMER = 100,
	REMMONOMER ,
	FRACTAL_DONE,
};

class ThreadedFractalCreate : public wxThread
{
	Fractal* _base;
	long _fractal_size;
	
public:
	ThreadedFractalCreate( wxFrame* parent, Fractal *frac, long size );
	
	ExitCode Entry( );
	
	void PostText( const wxString& text, long EventType = wxID_ANY);
	
protected:
	wxFrame* m_parent;
};
