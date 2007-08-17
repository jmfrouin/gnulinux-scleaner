/////////////////////////////////////////////////////////////////////////////
// Name:        interfaceapp.h
// Purpose:     
// Author:      Frouin Jean-Michel
// Modified by: 
// Created:     Fri 17 Aug 2007 23:52:34 CEST
// RCS-ID:      
// Copyright:   Project are under GNU GPL v3
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _INTERFACEAPP_H_
#define _INTERFACEAPP_H_

/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * InterfaceApp class declaration
 */

class InterfaceApp: public wxApp
{    
    DECLARE_CLASS( InterfaceApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    InterfaceApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin InterfaceApp event handler declarations
////@end InterfaceApp event handler declarations

////@begin InterfaceApp member function declarations
////@end InterfaceApp member function declarations

////@begin InterfaceApp member variables
////@end InterfaceApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(InterfaceApp)
////@end declare app

#endif
    // _INTERFACEAPP_H_
