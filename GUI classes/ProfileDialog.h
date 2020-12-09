//
// Created by kddny on 22.11.2020.
//

#ifndef UNTITLED1_PROFILEDIALOG_H
#define UNTITLED1_PROFILEDIALOG_H

#include <wx/wx.h>
#include <memory>
#include "StartFrame.h"
#include "../classes/Dir.h"

///Wyswietla kolejne okna interfejsu dodwania nowego profilu
class ProfileDialog : public wxFrame{
public:
    ProfileDialog(StartFrame *startFrame);
private:
    void NextButtonClicked(wxCommandEvent& event);
    void ConfrimClicked(wxCommandEvent& event);
    wxSizer* getNextSizer();
    wxSizer *getFirstSizer();
    void closeClicked(wxCommandEvent &event);
    std::string profile_name_;
    std::string path1_;
    std::string path2_;
    Choice flag1_;
    Choice flag2_;
    wxRadioButton *rb1_;
    wxRadioButton *rb2_;
    wxTextCtrl* tc_;
    wxTextCtrl* tc1_;
    wxTextCtrl* tc2_;
    StartFrame* startFrame_;
};

#endif //UNTITLED1_PROFILEDIALOG_H
