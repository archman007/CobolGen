#include "cobMain.h"

//(*InternalHeaders(cobMain)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(cobMain)
const long cobMain::ID_STATICTEXT1 = wxNewId();
const long cobMain::ID_TEXTCTRL1 = wxNewId();
const long cobMain::ID_STATICTEXT2 = wxNewId();
const long cobMain::ID_STATICTEXT3 = wxNewId();
const long cobMain::ID_TEXTCTRL2 = wxNewId();
const long cobMain::ID_TEXTCTRL3 = wxNewId();
const long cobMain::ID_BUTTON1 = wxNewId();
const long cobMain::ID_BUTTON2 = wxNewId();
const long cobMain::ID_STATICTEXT4 = wxNewId();
const long cobMain::ID_TEXTCTRL4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(cobMain,wxDialog)
    //(*EventTable(cobMain)
    //*)
END_EVENT_TABLE()

cobMain::cobMain(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(cobMain)
    Create(parent, id, _("BCS COBOL Input Parameters"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxSize(400,318));
    Move(wxDefaultPosition);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Program Name"), wxPoint(8,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    edtProgName = new wxTextCtrl(this, ID_TEXTCTRL1, _("ofl"), wxPoint(8,32), wxSize(168,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Program Author"), wxPoint(8,72), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Prigram ID"), wxPoint(8,136), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    edtProAuth = new wxTextCtrl(this, ID_TEXTCTRL2, _("Mr. Arch Brooks"), wxPoint(8,96), wxSize(384,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    edtPid = new wxTextCtrl(this, ID_TEXTCTRL3, _("Your-program-name"), wxPoint(8,160), wxSize(384,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    btnOk = new wxButton(this, ID_BUTTON1, _("OK"), wxPoint(64,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    btnCancel = new wxButton(this, ID_BUTTON2, _("Cancel"), wxPoint(192,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Short Description"), wxPoint(8,200), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    edtSDes = new wxTextCtrl(this, ID_TEXTCTRL4, _("Short Description Goes Here"), wxPoint(8,224), wxSize(384,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cobMain::OnTextCtrl1Text);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cobMain::OnTextCtrl1Text1);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cobMain::OnTextCtrl1Text2);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cobMain::OnbtnOkClick1);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cobMain::OnbtnCancelClick);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&cobMain::OnInit);
    //*)

}

void cobMain::initFields()
{
    initField(dd.author, edtProAuth);
    initField(dd.pid, edtPid);
    initField(dd.progName, edtProgName);
    initField(dd.shortDes, edtSDes);

}

void cobMain::getFields()
{
    dd.pid = fieldToString(edtPid);
    dd.author = fieldToString(edtProAuth);
    dd.progName =  fieldToString(edtProgName);
    dd.shortDes = fieldToString(edtSDes);
}

cobMain::~cobMain()
{
    //(*Destroy(cobMain)
    //*)
    initFields();
}


void cobMain::OnInit(wxInitDialogEvent& event)
{
}

void cobMain::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void cobMain::OnTextCtrl1Text1(wxCommandEvent& event)
{
}

void cobMain::OnTextCtrl1Text2(wxCommandEvent& event)
{
}

void cobMain::OnbtnOkClick(wxCommandEvent& event)
{
    /*
        if (fieldToString(edtPid)== "")
        {
            EndModal(22);

        }
    */

    EndModal(wxID_OK);
}

void cobMain::OnbtnCancelClick(wxCommandEvent& event)
{
    EndModal(wxID_CANCEL);
}

void cobMain::initField(string inputValue, wxTextCtrl * field)
{
    wxString dv = inputValue;
    field->Clear();
    field->SetEditable(true);
    field->ChangeValue(dv);
}

string cobMain::fieldToString(wxTextCtrl * field)
{
    string rstr;
    wxString s1 = field->GetValue();
    rstr = s1.ToStdString();
    return rstr;
}



void cobMain::OnbtnOkClick1(wxCommandEvent& event)
{
    getFields();

    if ((dd.pid > "") && (dd.author > "") && (dd.progName > "") && (dd.shortDes > ""))
    {
        EndModal(wxID_OK);
    }


}

