//
// Created by Marcin Piotrowski on 22.11.2020.
//

#ifndef UNTITLED1_PROFILEDIALOG_H
#define UNTITLED1_PROFILEDIALOG_H

#include <wx/wx.h>
#include <memory>
#include "StartFrame.h"
#include "../classes/Dir.h"

///Implementuje kolejne okna kreatora profili
class ProfileDialog : public wxFrame{
public:
    ///Konstruktor
    ///@param startFrame wskaźnik na okno startowe programu
    ProfileDialog(StartFrame *startFrame);
private:
    void NextButtonClicked(wxCommandEvent& event);
    void ConfrimLocalClicked(wxCommandEvent& event);
    void ConfrimSSHClicked(wxCommandEvent& event);

    wxSizer* getNextLocalSizer();
    wxSizer* getNextSshSizer();
    wxSizer *getFirstSizer();
    void closeClicked(wxCommandEvent &event);
    std::string profile_name_;
    std::string path1_;
    std::string path2_;
    std::string username_;
    std::string password_;
    Choice flag1_;
    Choice flag2_;
    wxRadioButton *rb1_;
    wxRadioButton *rb2_;
    wxTextCtrl* tc_;
    wxTextCtrl* tc1_;
    wxTextCtrl* tc2_;
    wxTextCtrl* tc3_;
    wxTextCtrl* tc4_;
    StartFrame* startFrame_;
};

#endif //UNTITLED1_PROFILEDIALOG_H
