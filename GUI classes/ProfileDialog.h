//
// Created by kddny on 22.11.2020.
//

#ifndef UNTITLED1_PROFILEDIALOG_H
#define UNTITLED1_PROFILEDIALOG_H

#include <wx/wx.h>
#include <memory>
#include "StartFrame.h"

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
    std::string profile_name;
    std::string path1;
    std::string path2;
    int flag1;
    int flag2;
    wxRadioButton *rb1;
    wxRadioButton *rb2;
    wxTextCtrl* tc;
    wxTextCtrl* tc1;
    wxTextCtrl* tc2;
    StartFrame* startFrame_;
};

#endif //UNTITLED1_PROFILEDIALOG_H
