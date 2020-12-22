//
// Created by kddny on 21.11.2020.
//

#include "MainFrame.h"
#include "StartFrame.h"

using namespace std;

MainFrame::MainFrame(wxPoint pos, int index)
        : profile_(Application::getProfiles().at(index)) ,wxFrame(nullptr, wxID_ANY, "Uniklon", pos, wxSize(800,600) ) {
    profile_->summary();
    profile_->printTree1();
    profile_->printTree2();

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *file = new wxMenu;
    wxMenu *help = new wxMenu;
    file->Append(1, wxT("&Zmień Profil"));
    file->Append(2, wxT("&Skanuj"));
    file->Append(3,wxT("&Synchronizuj"));
    file->Append(4,wxT("&Zmień kierunek"));
    file->Append(5, wxT("&Wyjście"));
    help->Append(6,wxT("&O Programie"));
    menuBar->Append(file, wxT("&Synchronizacja"));
    menuBar->Append(help,wxT("&Pomoc"));
    SetMenuBar(menuBar);

    vbox->Add(-1,10);

    wxBoxSizer *mainHbox = new wxBoxSizer(wxHORIZONTAL);
    list_ctrl_ = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

    col0_ = new wxListItem();
    col1_ = new wxListItem();
    col2_ = new wxListItem();
    col3_ = new wxListItem();
    col0_->SetId(7);
    col1_->SetId(8);
    col2_->SetId(9);
    col3_->SetId(10);
    col0_->SetText( _("Pierwszy katalog") );
    col1_->SetText( _("Akcja") );
    col2_->SetText( _("Drugi katalog") );
    col3_->SetText( _("Sciezka") );
    col0_->SetWidth(150);
    col1_->SetWidth(50);
    col2_->SetWidth(150);
    col3_->SetWidth(150);
    list_ctrl_->InsertColumn(0, *col0_);
    list_ctrl_->InsertColumn(1, *col1_);
    list_ctrl_->InsertColumn(2, *col2_);
    list_ctrl_->InsertColumn(3, *col3_);

    mainHbox->Add(list_ctrl_,1, wxEXPAND);

    vbox->Add(mainHbox,1, wxLEFT | wxBOTTOM,15);
    this->SetSizer(vbox);

    Centre();

    Connect(1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::changeProfileClicked));
    Connect(2,wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::scanClicked));
}

void MainFrame::changeProfileClicked(wxCommandEvent &event){
    this->Close(true);
    wxPoint pos = this->GetPosition();
    StartFrame *startFrame = new StartFrame(pos);
    startFrame->Show(true);
}

void MainFrame::scanClicked(wxCommandEvent &event){
    list_ctrl_->DeleteAllItems();
    profile_->scan();
    for(const auto& el : profile_->getDif()) {
        if (el->which_dir_ == FIRST) {
            long itemIndex = list_ctrl_->InsertItem(0, el->getName());
            list_ctrl_->SetItem(itemIndex, 1, "     ->");
        }
        if (el->which_dir_ == SECOND) {
            long itemIndex = list_ctrl_->InsertItem(0, "");
            list_ctrl_->SetItem(itemIndex, 1, "     <-");
            list_ctrl_->SetItem(itemIndex, 2, el->getName());
        }
    }
}
