//
// Created by kddny on 21.11.2020.
//

#include "MainFrame.h"

MainFrame::MainFrame(wxPoint pos)
        : wxFrame(nullptr, wxID_ANY, "Uniklon", pos, wxSize(800,600) ) {
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *file = new wxMenu;
    wxMenu *help = new wxMenu;
    file->Append(wxID_ANY, wxT("&Wyjście"));
    file->Append(wxID_ANY, wxT("&Zmień Profil"));
    help->Append(wxID_ANY,wxT("&O Programie"));
    menuBar->Append(file, wxT("&Synchronizacja"));
    menuBar->Append(help,wxT("&Pomoc"));
    SetMenuBar(menuBar);

    vbox->Add(-1,10);
    //  vbox->Add
//    wxImage::AddHandler(new wxPNGHandler);
//
//    wxBitmap exit(wxT("images.png"), wxBITMAP_TYPE_PNG);
//    wxToolBar *toolbar = CreateToolBar();
//    toolbar->AddTool(wxID_ANY,wxT("Exit application"), exit);
//    toolbar->Realize();
    wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *st1 = new wxStaticText(this, wxID_ANY, wxT("Sciezka do pierwszego katalogu:"));
    wxStaticText *st2 = new wxStaticText(this, wxID_ANY, wxT("Sciezka do pierwszego katalogu:"));
    wxStaticText *st3 = new wxStaticText(this, wxID_ANY, wxT("Sciezka do pierwszego katalogu:"));
    hbox1->Add(st1, 0, wxRIGHT, 10);
    hbox1->Add(st2, 0, wxRIGHT, 10);
    hbox1->Add(st3, 0, wxRIGHT, 10);
    vbox->Add(hbox1,wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);

    this->SetSizer(vbox);

    Centre();
}