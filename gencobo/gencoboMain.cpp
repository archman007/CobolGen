/***************************************************************
 * Name:      gencoboMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2019-08-28
 * Copyright: Mr. Arch Brooks (archbrooks.us/b4)
 * License:
 **************************************************************/

#include "gencoboMain.h"
#include <wx/msgdlg.h>
#include <wx/textdlg.h>
#include <wx/filedlg.h>
#include <wx/dirdlg.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <wx/msgdlg.h>

#include <wx/dirdlg.h>
#include <wx/fontdlg.h>
//#include "kwSearch.h"
#include <wx/colordlg.h>
#include <wx/brush.h>
#include <fstream>
#include "boost/date_time/posix_time/posix_time_types.hpp"
#include "cobMain.h"
//(*InternalHeaders(gencoboFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}


//(*IdInit(gencoboFrame)
const long gencoboFrame::ID_PANEL1 = wxNewId();
const long gencoboFrame::ID_MENUITEM1 = wxNewId();
const long gencoboFrame::idMenuQuit = wxNewId();
const long gencoboFrame::ID_MENUITEM2 = wxNewId();
const long gencoboFrame::ID_MENUITEM3 = wxNewId();
const long gencoboFrame::idMenuAbout = wxNewId();
const long gencoboFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(gencoboFrame,wxFrame)
    //(*EventTable(gencoboFrame)
    //*)
END_EVENT_TABLE()

gencoboFrame::gencoboFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(gencoboFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("BCS COBOL Generating Facility"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    pan01 = new wxPanel(this, ID_PANEL1, wxPoint(72,104), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    pan01->SetBackgroundColour(wxColour(0,71,255));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    menXqtOne = new wxMenuItem(Menu1, ID_MENUITEM1, _("Generate COBOL Mainlne Program"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(menXqtOne);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    menFonts = new wxMenuItem(Menu3, ID_MENUITEM2, _("Fonts"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(menFonts);
    menColor = new wxMenuItem(Menu3, ID_MENUITEM3, _("Background Color"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(menColor);
    MenuBar1->Append(Menu3, _("&Enviroment"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    	wxFontData fontData_1;
    	fontData_1.SetInitialFont(*wxNORMAL_FONT);
    FontDialog1 = new wxFontDialog(this, fontData_1);
    ColourDialog1 = new wxColourDialog(this);
    Center();

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gencoboFrame::OnmenXqtOneSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gencoboFrame::OnQuit);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gencoboFrame::OnmenFontsSelected);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gencoboFrame::OnmenColorSelected);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&gencoboFrame::OnAbout);
    //*)

}

void gencoboFrame::genMain01()
{
    cobMain dlg(NULL, wxID_ANY);
    dlg.dd.author = progAuth;
    dlg.dd.pid = yPn ;
    dlg.dd.progName = pNa;
    dlg.dd.shortDes = "Mainline Program Begins Here";



    if (dlg.ShowModal() == wxID_OK)
    {

        cg.open(ws + "/" + dlg.dd.progName + ".cbl");
        cg << "      ******************************************************************" << endl;
        cg << "      * Author: " << dlg.dd.author << endl;
        cg << "      * Date: " << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" << timeLocal.date().day() << " " << timeLocal.time_of_day().hours() << ":" << timeLocal.time_of_day().minutes() << ":" << timeLocal.time_of_day().seconds() << endl;
        cg << "      * Purpose: " << dlg.dd.shortDes << endl;
        cg << "      * Tectonics: cobc" << endl;
        cg << "      ******************************************************************" << endl;
        cg << "       IDENTIFICATION DIVISION." << endl;
        cg << "       PROGRAM-ID. " << dlg.dd.progName << "." << endl;
        cg << "       DATA DIVISION." << endl;
        cg << "       FILE SECTION." << endl;
        cg << "       WORKING-STORAGE SECTION." << endl;
        cg << "       01  DBUFF Pic X(80)." << endl;
        cg << "       PROCEDURE DIVISION." << endl;
        cg << "       MAIN-PROCEDURE." << endl;
        cg << "            DISPLAY \"Hello world\"" << endl;
        cg << "            MOVE \"The Top Place.\" to DBUFF." << endl;
        cg << "            call 'UTIL' using DBUFF;" << endl;
        cg << "            STOP RUN." << endl;
        cg << "       END PROGRAM " << dlg.dd.progName << "." << endl;
        dlg.dd.progName = "UTIL";
        dlg.dd.shortDes = "Display Subroutine";
        gencoboFrame::GenSub01(dlg.dd);
        dlg.dd.progName = "REP01";
        dlg.dd.shortDes = "Report Generator Subroutine";
        gencoboFrame::GenSub02(dlg.dd);
        dlg.dd.progName = "IO01";
        dlg.dd.shortDes = "File Output Subroutine";
        gencoboFrame::GenSub03(dlg.dd);
        cg.close();
    }

}

void gencoboFrame::OnmenXqtOneSelected(wxCommandEvent& event)
{
    ws = SelDir("/home/archman/workspace/oc/");
    if (ws == "")
    {
//        int yorn = yornQues("You did not select a workspace!", "No workspace Selected!");
        int answer = wxMessageBox("No workspace selected!", "Worksapce needed for this", wxYES_NO | wxCANCEL, NULL);

    }
    else
    {
        genMain01();
    }

}

gencoboFrame::~gencoboFrame()
{
    //(*Destroy(gencoboFrame)
    //*)
}

void gencoboFrame::GenSub01(dlg_area dd )
{
    cg << "      ******************************************************************" << endl;
    cg << "      * Author: " << dd.author << endl;
    cg << "      * Date: " << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" << timeLocal.date().day() << " " << timeLocal.time_of_day().hours() << ":" << timeLocal.time_of_day().minutes() << ":" << timeLocal.time_of_day().seconds() << endl;
    cg << "      * Purpose: " << dd.shortDes << endl;
    cg << "      * Tectonics: cobc" << endl;
    cg << "      ******************************************************************" << endl;

    cg << "       IDENTIFICATION DIVISION." << endl;
    cg << "       PROGRAM-ID. '" + dd.progName + "'." << endl;
    cg << "       DATA DIVISION." << endl;
    cg << "       LINKAGE SECTION." << endl;
//  cg << "       01 LS-STUDENT-ID PIC 9(4)." << endl;
    cg << "       01 DISPLAY_BUFF PIC x(80)." << endl;
    cg << "       PROCEDURE DIVISION USING DISPLAY_BUFF" << "." << endl;
    cg << "           DISPLAY \"In Called Program\"." << endl;
    cg << "           DISPLAY DISPLAY_BUFF." << endl;
    cg << "       EXIT-PROGRAM." << endl;
    cg << "       END PROGRAM " << dd.progName << "." << endl;

}

void gencoboFrame::GenSub02(dlg_area dd )
{

    /*
           IDENTIFICATION DIVISION.
           PROGRAM-ID. 'UTIL'.
           DATA DIVISION.
           LINKAGE SECTION.
           01 LS-STUDENT-ID PIC 9(4).
           01 DISPLAY_BUFF PIC x(80).
           PROCEDURE DIVISION USING DISPLAY_BUFF.
               DISPLAY 'In Called Program'.
               display DISPLAY_BUFF.
           EXIT-PROGRAM.

    */
//    cobMain::dd.
    cg << "      ******************************************************************" << endl;
    cg << "      * Author: " << dd.author << endl;
    cg << "      * Date: " << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" << timeLocal.date().day() << " " << timeLocal.time_of_day().hours() << ":" << timeLocal.time_of_day().minutes() << ":" << timeLocal.time_of_day().seconds() << endl;
    cg << "      * Purpose: " << dd.shortDes << endl;
    cg << "      * Tectonics: cobc" << endl;
    cg << "      ******************************************************************" << endl;

    cg << "       IDENTIFICATION DIVISION." << endl;
    cg << "       PROGRAM-ID. '" + dd.progName + "'." << endl;
    cg << "       ENVIRONMENT DIVISION." << endl;
    cg << "       INPUT-OUTPUT SECTION." << endl;
    cg << "       FILE-CONTROL." << endl;
    cg << "           SELECT PRINTFILE ASSIGN TO \"STOCK-SUMMARY\"." << endl;
    cg << "       DATA DIVISION." << endl;
    cg << "       FILE SECTION." << endl;
    cg << "       FD  PRINTFILE" << endl;
    cg << "           REPORT IS STOCK-SUMMARY." << endl;
    cg << "       LINKAGE SECTION." << endl;
//  cg << "       01 LS-STUDENT-ID PIC 9(4)." << endl;
    cg << "       01 DISPLAY_BUFF PIC x(80)." << endl;
    cg << "       REPORT SECTION." << endl;
    cg << "       RD  STOCK-SUMMARY" << endl;
//    cg << "           HEADING 1" << endl;
//    cg << "           FIRST DETAIL 5" << endl;
    cg << "           PAGE LIMIT 64." << endl;
    cg << "       01  TYPE PH." << endl;
    cg << "           05  TL PIC X(80)." << endl;
    cg << "       01  TYPE DE." << endl;
    cg << "           05  DEE PIC X(80)." << endl;
    cg << "       01  TYPE CF." << endl;
    cg << "           05  CFF PIC X(80)." << endl;
    cg << "       PROCEDURE DIVISION USING DISPLAY_BUFF" << "." << endl;
    cg << "           DISPLAY \"In Called Program REP01\"." << endl;
    cg << "           DISPLAY DISPLAY_BUFF." << endl;
    cg << "       EXIT-PROGRAM." << endl;
    cg << "       END PROGRAM " << dd.progName << "." << endl;

    /*
    REPORT SECTION.
    RD STOCK-SUMMARY

    */
}

void gencoboFrame::GenSub03(dlg_area dd )
{
    cg << "      ******************************************************************" << endl;
    cg << "      * Author: " << dd.author << endl;
    cg << "      * Date: " << timeLocal.date().year() << "-" << timeLocal.date().month() << "-" << timeLocal.date().day() << " " << timeLocal.time_of_day().hours() << ":" << timeLocal.time_of_day().minutes() << ":" << timeLocal.time_of_day().seconds() << endl;
    cg << "      * Purpose: " << dd.shortDes << endl;
    cg << "      * Tectonics: cobc" << endl;
    cg << "      ******************************************************************" << endl;

    cg << "       IDENTIFICATION DIVISION." << endl;
    cg << "       PROGRAM-ID. '" + dd.progName + "'." << endl;
    cg << "       ENVIRONMENT DIVISION." << endl;
    cg << "       INPUT-OUTPUT SECTION." << endl;
    cg << "       FILE-CONTROL." << endl;
    cg << "           SELECT OF01 ASSIGN TO \"STOCK-SUMMARY\"." << endl;
    cg << "       DATA DIVISION." << endl;
    cg << "       FILE SECTION." << endl;
    cg << "       FD  OF01" << endl;
    cg << "           RECORDING MODE IS F." << endl;
    cg << "       01  OUT-REC." << endl;
    cg << "           05  LID PIC X(5)." << endl;
    cg << "           05  LNO PIC 999. " << endl;
    cg << "           05  EOL PIC X(72) VALUE \"n\". " << endl;
    cg << "       LINKAGE SECTION." << endl;
    cg << "       01 DISPLAY_BUFF PIC x(80)." << endl;
    cg << "       PROCEDURE DIVISION USING DISPLAY_BUFF" << "." << endl;
    cg << "           DISPLAY \"In Called Program IO01\"." << endl;
    cg << "           DISPLAY DISPLAY_BUFF." << endl;
    cg << "           OPEN OUTPUT OF01." << endl;
    cg << "           PERFORM 0010-WRITE VARYING LNO FROM 1 BY 1 UNTIL LNO > 74." << endl;
    cg << "           CLOSE OF01." << endl;
    cg << "       EXIT-PROGRAM." << endl;
    cg << "           GOBACK." << endl;
    cg << "       0010-WRITE." << endl;
    cg << "           MOVE \"LINE\" TO LID." << endl;
    cg << "           WRITE OUT-REC." << endl;
    cg << "       END PROGRAM " << dd.progName << "." << endl;

}

void gencoboFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void gencoboFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

string gencoboFrame::GetText(bool memo, string initVal, string prompt, string caption)
{
    wxString wxInit;
    wxInit = initVal;
    string rval;
    if (memo)
    {
        wxTextEntryDialog dlg(this, prompt, caption, wxInit, (wxCANCEL | wxOK | wxTE_MULTILINE), wxPoint(50, 50));
        if (dlg.ShowModal() == wxID_OK)
        {
            // We can be certain that this string contains letters only.
            wxString value = dlg.GetValue();
            rval = value;
            return rval;
        }
        else
        {
            rval = "";
            return rval;
        }
    }
    else
    {
        wxTextEntryDialog dlg(this, prompt, caption, wxInit, (wxCANCEL | wxOK), wxPoint(50, 50));
        if (dlg.ShowModal() == wxID_OK)
        {
            // We can be certain that this string contains letters only.
            wxString value = dlg.GetValue();
            rval = value;
            return rval;
        }
        else
        {
            rval = "";
            return rval;
        }

    }
}

string gencoboFrame::GetFileName(string fs)
{
    wxFileDialog openFileDialog(this, _("Open Any file"), defPath, fno, fs, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
        fileName = " ";
    }
    else
    {
        fileName = openFileDialog.GetPath();
    }

    return fileName;

}

std::string gencoboFrame::SelDir(string initDir)
{
    string selDir;
    wxDirDialog dlg(NULL, "Choose input directory", initDir, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK)
    {
        selDir = dlg.GetPath().ToStdString();
        return selDir;

    }
    dlg.Destroy();

}

void gencoboFrame::initField(string inputValue, wxTextCtrl * field)
{
    wxString dv = inputValue;
    field->Clear();
    field->SetEditable(true);
    field->ChangeValue(dv);
}

string gencoboFrame::fieldToString(wxTextCtrl * field)
{
    string rstr;
    wxString s1 = field->GetValue();
    rstr = s1.ToStdString();
    return rstr;
}

void gencoboFrame::Xqt(string cmd)
{
    cmd = cmd + " & ";
    int idet = -1;
    if ( boost::filesystem::exists( "/home/archbrooks" ) )
    {
        string frst = "/archman/";
        idet = cmd.find(frst);
        if (idet != -1)
        {
            boost::replace_all(cmd, "/archman/", "/archbrooks/");
        }
    }
    const char * c = cmd.c_str();
    int retval = -1;
    retval = system(c);
}

void gencoboFrame::ListFilesRecursively(const char *dir, const char* ext)
{
    strings.Clear();
    boost::filesystem::recursive_directory_iterator rdi(dir);
    boost::filesystem::recursive_directory_iterator end_rdi;

    std::string buf = "";

    std::string ext_str0(ext);
    for (; rdi != end_rdi; rdi++)
    {
        //rdi++;

        if (ext_str0.compare((*rdi).path().extension().string()) == 0)
        {
            buf = (*rdi).path().string();
            strings.Add(buf);
            std::cout << (*rdi).path().string() << std::endl;
        }
    }
    strings.Sort();
}

int gencoboFrame::yornQues(string caption, string prompt)
{
    int answer;
    answer = wxMessageBox(caption, prompt, wxYES_NO | wxCANCEL, NULL);
    return answer;
}


void gencoboFrame::OnmenFontsSelected(wxCommandEvent& event)
{
    wxFontData fontData;
    wxFont     theFont;
    wxColour   colour;

    theFont = pan01->GetFont();
    fontData.SetInitialFont(theFont);
//    colour pan01->GetForegroundColour();
//    colour = lbxCats->GetForegroundColour();
    fontData.SetColour(colour);
    fontData.SetShowHelp(true);

    wxFontDialog *dialog = new wxFontDialog(this);
//	dlgFont *dialog = new dlgFont( this, &fontData );
    if ( dialog->ShowModal() == wxID_OK )
    {
        fontData = dialog->GetFontData();
        theFont = 	fontData.GetChosenFont();
        pan01->SetFont(theFont);
        /*        lbxCats->SetFont(theFont);
                lbxCats->SetForegroundColour(fontData.GetColour());
                lbxLinks->SetFont(theFont);
                lbxLinks->SetForegroundColour(fontData.GetColour());
                */
    }

}

void gencoboFrame::OnmenColorSelected(wxCommandEvent& event)
{
    wxColourDialog dlgColour(this, &colour_data);

    if (dlgColour.ShowModal() == wxID_OK)
    {
        wxColourData retData = dlgColour.GetColourData();
        wxColour col = retData.GetColour();
        wxBrush brush(col, wxSOLID);
        pan01->SetBackgroundColour(col);

    }

}
