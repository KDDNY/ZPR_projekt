//
// Created by kddny on 20.11.2020.
//

#include "StartFrame.h"
#include "ProfileDialog.h"
#include "MainFrame.h"

using namespace std;

StartFrame::StartFrame(wxPoint pos)
        : wxFrame(nullptr, wxID_ANY, "Uniklon", pos, wxSize(350,600) ) {
    wxPanel *panel = new wxPanel(this, -1);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st1 =  new wxStaticText(panel, wxID_ANY, wxT("Wybierz lub stworz nowy profil"));

    hbox1->Add(st1, 0, wxRIGHT, 8);

    vbox->Add(hbox1, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st2 = new wxStaticText(panel, wxID_ANY, wxT("Lista profili:"));

    hbox2->Add(st2, 0);
    vbox->Add(hbox2, 0, wxLEFT | wxTOP, 10);

    vbox->Add(-1, 10);

    wxBoxSizer *hbox3 = new wxBoxSizer(wxHORIZONTAL);
    wxListBox *lb = new wxListBox(panel, wxID_ANY);
    lb->Insert("Pierwszy",0);
    lb->Insert("Drugi",1);
    lb->Insert("Trzeci",2);
//    wxTextCtrl *tc2 = new wxTextCtrl(panel, wxID_ANY, wxT(""),wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);
    hbox3->Add(lb, 1, wxEXPAND);
    vbox->Add(hbox3, 1, wxLEFT | wxRIGHT | wxEXPAND, 10);

    vbox->Add(-1, 25);

    vbox->Add(-1, 25);

    wxBoxSizer *hbox5 = new wxBoxSizer(wxHORIZONTAL);
    wxButton *btn1 = new wxButton(panel, 1, wxT("Dodaj"));
    hbox5->Add(btn1, 0);
    wxButton *btn2 = new wxButton(panel, 2, wxT("Wybierz"));
    hbox5->Add(btn2, 0, wxLEFT | wxBOTTOM , 5);
    vbox->Add(hbox5, 0, wxALIGN_RIGHT | wxRIGHT, 10);

    panel->SetSizer(vbox);

    Centre();

    Connect(2, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(StartFrame::chooseClicked));
    Connect(1, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(StartFrame::onAdd));
}

void StartFrame::chooseClicked(wxCommandEvent &event){
    wxPoint pos = this->GetPosition();
    this->Close(true);
    MainFrame *mainFrame = new MainFrame(pos);
    mainFrame->Show(true);
}

void StartFrame::onAdd(wxCommandEvent &event) {
    ProfileDialog *profileDialog = new ProfileDialog();
    profileDialog->Show(true);
}