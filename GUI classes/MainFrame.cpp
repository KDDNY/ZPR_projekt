//
// Created by kddny on 21.11.2020.
//

#include "MainFrame.h"
#include "StartFrame.h"

using namespace std;

MainFrame::MainFrame(wxPoint pos, int index)
        : profile_(Application::getProfiles().at(index)) ,wxFrame(nullptr, wxID_ANY, "Uniklon", pos, wxSize(800,600) ) {
/*
    profile_->summary();
    profile_->printTree1();
    profile_->printTree2();
*/

    wxBoxSizer *vbox = new wxBoxSizer(wxHORIZONTAL);

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

    mainHbox->Add(list_ctrl_, 0, wxEXPAND);

    wxBoxSizer *rightVbox = new wxBoxSizer(wxVERTICAL);
    wxButton* btn1 = new wxButton(this, 3, wxT("Zmień kierunek"));
    wxButton* btn2 = new wxButton(this, 4, wxT("Synchronizuj"));
    wxButton* btn3 = new wxButton(this, 5, wxT("Skanuj"));
    wxButton* btn4 = new wxButton(this, 6, wxT("Pomiń"));
    rightVbox->Add(btn1, 0, wxBOTTOM, 15);
    rightVbox->Add(btn4, 0, wxBOTTOM, 15);
    rightVbox->Add(btn2, 0, wxBOTTOM, 15);
    rightVbox->Add(btn3, 0, wxBOTTOM, 15);


    vbox->Add(mainHbox,1, wxLEFT | wxBOTTOM | wxTOP | wxEXPAND,15);
    vbox->Add(rightVbox, 1, wxLEFT | wxBOTTOM | wxTOP | wxEXPAND, 15);
    this->SetSizer(vbox);

    Centre();

    Connect(1, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::changeProfileClicked));
    Connect(2, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::scanClicked));
    Connect(3, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::changeClicked));
    Connect(4, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::goClicked));
    Connect(5, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::scanClicked));
    Connect(6, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::skipClicked));
}

void MainFrame::skipClicked(wxCommandEvent &event){
    long lSelectedItem = list_ctrl_->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    int selection = profile_->getDif().size()-lSelectedItem-1;
    if(lSelectedItem >= 0) {
        profile_->getDif().at(selection)->setAction(SKIP);
    }
    fillListCtrl();
}

void MainFrame::changeClicked(wxCommandEvent &event){
    long lSelectedItem = list_ctrl_->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    int selection = profile_->getDif().size()-lSelectedItem-1;
    if(lSelectedItem >= 0) {
        if(profile_->getDif().at(selection)->getAction() == COPY) {
            profile_->getDif().at(selection)->setAction(REMOVE);
        } else {
            profile_->getDif().at(selection)->setAction(COPY);
        }
    }
    fillListCtrl();
}

void MainFrame::goClicked(wxCommandEvent &event){
    profile_->synchronize();
}

void MainFrame::changeProfileClicked(wxCommandEvent &event){
    this->Close(true);
    wxPoint pos = this->GetPosition();
    StartFrame *startFrame = new StartFrame(pos);
    startFrame->Show(true);
}

void MainFrame::scanClicked(wxCommandEvent &event){
    profile_->scan();
    fillListCtrl();
}



void MainFrame::fillListCtrl() {
    list_ctrl_->DeleteAllItems();
    for(const auto& el : profile_->getDif()) {
        if (el->which_dir_ == FIRST) {
            long itemIndex = list_ctrl_->InsertItem(0, el->getName());
            if(el->getAction() == COPY) list_ctrl_->SetItem(itemIndex, 1, "     ->");
            if(el->getAction() == REMOVE) list_ctrl_->SetItem(itemIndex, 1, "     <-");
            if(el->getAction() == SKIP) list_ctrl_->SetItem(itemIndex, 1, "     --");
        }
        if (el->which_dir_ == SECOND) {
            long itemIndex = list_ctrl_->InsertItem(0, "");
            if(el->getAction() == COPY) list_ctrl_->SetItem(itemIndex, 1, "     <-");
            if(el->getAction() == REMOVE) list_ctrl_->SetItem(itemIndex, 1, "     ->");
            if(el->getAction() == SKIP) list_ctrl_->SetItem(itemIndex, 1, "     --");
            list_ctrl_->SetItem(itemIndex, 2, el->getName());
        }
    }
}