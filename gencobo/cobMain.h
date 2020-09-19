#ifndef COBMAIN_H
#define COBMAIN_H

//(*Headers(cobMain)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

using namespace std;

struct dlg_area
{
    string progName;
    string author;
    string pid;
    string shortDes;
};



class cobMain: public wxDialog
{
public:

    cobMain(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~cobMain();
    dlg_area dd;

    //(*Declarations(cobMain)
    wxButton* btnCancel;
    wxButton* btnOk;
    wxStaticText* StaticText1;
    wxStaticText* StaticText2;
    wxStaticText* StaticText3;
    wxStaticText* StaticText4;
    wxTextCtrl* edtPid;
    wxTextCtrl* edtProAuth;
    wxTextCtrl* edtProgName;
    wxTextCtrl* edtSDes;
    //*)

protected:

    //(*Identifiers(cobMain)
    static const long ID_STATICTEXT1;
    static const long ID_TEXTCTRL1;
    static const long ID_STATICTEXT2;
    static const long ID_STATICTEXT3;
    static const long ID_TEXTCTRL2;
    static const long ID_TEXTCTRL3;
    static const long ID_BUTTON1;
    static const long ID_BUTTON2;
    static const long ID_STATICTEXT4;
    static const long ID_TEXTCTRL4;
    //*)

private:
    void initField(string inputValue, wxTextCtrl * field);
    string fieldToString(wxTextCtrl * field);
    void initFields();
    void getFields();

    //(*Handlers(cobMain)
    void OnInit(wxInitDialogEvent& event);
    void OnTextCtrl1Text(wxCommandEvent& event);
    void OnTextCtrl1Text1(wxCommandEvent& event);
    void OnTextCtrl1Text2(wxCommandEvent& event);
    void OnButton1Click(wxCommandEvent& event);
    void OnButton2Click(wxCommandEvent& event);
    void OnbtnOkClick(wxCommandEvent& event);
    void OnbtnCancelClick(wxCommandEvent& event);
    void OnbtnOkClick1(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
