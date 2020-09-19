/***************************************************************
 * Name:      gencoboApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2019-08-28
 * Copyright: Mr. Arch Brooks (archbrooks.us/b4)
 * License:
 **************************************************************/

#include "gencoboApp.h"

//(*AppHeaders
#include "gencoboMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(gencoboApp);

bool gencoboApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	gencoboFrame* Frame = new gencoboFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
