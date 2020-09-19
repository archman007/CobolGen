/***************************************************************
 * Name:      gencoboMain.h
 * Purpose:   Defines Application Frame
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2019-08-28
 * Copyright: Mr. Arch Brooks (archbrooks.us/b4)
 * License:
 **************************************************************/

#ifndef GENCOBOMAIN_H
#define GENCOBOMAIN_H
#include <wx/textctrl.h>
#include <fstream>
#include "cobMain.h"
#include "boost/date_time/posix_time/posix_time_types.hpp"

//(*Headers(gencoboFrame)
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
//*)

using namespace std;

class gencoboFrame: public wxFrame
{
public:
    gencoboFrame(wxWindow* parent,wxWindowID id = -1);
    virtual ~gencoboFrame();
//           cobMain dlg;


private:
    ofstream cg;
    string GetText(bool memo, string initVal, string prompt, string caption);
    string GetFileName(string fs);
    string defPath = "";
    string fno = "";
    string fileName = "";
    string SelDir(string initDir);
    void initField(string inputValue, wxTextCtrl * field);
    string fieldToString(wxTextCtrl * field);
    void Xqt(string cmd);
    void ListFilesRecursively(const char *dir, const char* ext);
    wxArrayString strings;
    int yornQues(string caption, string prompt);
    wxColourData colour_data = wxColourData();
    string progAuth = "Mr. Arch Brooks";
    string yPn = "Your-program-name";
    string pNa = "ofl";
    void GenSub01(dlg_area dd );
    void GenSub02(dlg_area dd );
    void GenSub03(dlg_area dd );
    void genMain01();
    string ws = "";
    boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();





    //(*Handlers(gencoboFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnmenXqtOneSelected(wxCommandEvent& event);
    void OnmenFontsSelected(wxCommandEvent& event);
    void OnmenColorSelected(wxCommandEvent& event);
    //*)

    //(*Identifiers(gencoboFrame)
    static const long ID_PANEL1;
    static const long ID_MENUITEM1;
    static const long idMenuQuit;
    static const long ID_MENUITEM2;
    static const long ID_MENUITEM3;
    static const long idMenuAbout;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(gencoboFrame)
    wxColourDialog* ColourDialog1;
    wxFontDialog* FontDialog1;
    wxMenu* Menu3;
    wxMenuItem* menColor;
    wxMenuItem* menFonts;
    wxMenuItem* menXqtOne;
    wxPanel* pan01;
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // GENCOBOMAIN_H
