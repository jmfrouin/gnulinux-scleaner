/////////////////////////////////////////////////////////////////////////////
// Name:        interfaceapp.cpp
// Purpose:     
// Author:      Frouin Jean-Michel
// Modified by: 
// Created:     Fri 17 Aug 2007 23:52:34 CEST
// RCS-ID:      
// Copyright:   Project are under GNU GPL v3
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "interfaceapp.h"

////@begin XPM images

////@end XPM images


/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( InterfaceApp )
////@end implement app


/*!
 * InterfaceApp type definition
 */

IMPLEMENT_CLASS( InterfaceApp, wxApp )


/*!
 * InterfaceApp event table definition
 */

BEGIN_EVENT_TABLE( InterfaceApp, wxApp )

////@begin InterfaceApp event table entries
////@end InterfaceApp event table entries

END_EVENT_TABLE()


/*!
 * Constructor for InterfaceApp
 */

InterfaceApp::InterfaceApp()
{
    Init();
}


/*!
 * Member initialisation
 */

void InterfaceApp::Init()
{
////@begin InterfaceApp member initialisation
////@end InterfaceApp member initialisation
}

/*!
 * Initialisation for InterfaceApp
 */

bool InterfaceApp::OnInit()
{    
////@begin InterfaceApp initialisation
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.

#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
////@end InterfaceApp initialisation

    return true;
}


/*!
 * Cleanup for InterfaceApp
 */

int InterfaceApp::OnExit()
{    
////@begin InterfaceApp cleanup
    return wxApp::OnExit();
////@end InterfaceApp cleanup
}

