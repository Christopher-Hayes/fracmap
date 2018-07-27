/*
 *  ThreadedFractalCreate.cpp
 *  wxFractals
 *
 *  Created by eluusive on 07/11/2008.
 *  Copyright 2008 University Of Neveda, Reno. All rights reserved.
 *
 */

#include "ThreadedFractalCreate.h"

ThreadedFractalCreate::ThreadedFractalCreate( wxFrame* parent , Fractal *frac, long size ) 
: wxThread(wxTHREAD_JOINABLE)
{
	_fractal_size = size;
	_base = frac;
	m_parent = parent;
}

wxThread::ExitCode ThreadedFractalCreate::Entry( )
{	
  _base->generate_fractal(_fractal_size);
  PostText( _T("Fractal complete!"), FRACTAL_DONE);
	return 0;
}

void ThreadedFractalCreate::PostText( const wxString & text, long evtType )
{	
	PostTextEvent event(evtType, text);
	wxPostEvent( m_parent,  event);
}
