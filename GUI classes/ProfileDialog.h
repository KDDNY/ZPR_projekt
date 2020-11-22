//
// Created by kddny on 22.11.2020.
//

#ifndef UNTITLED1_PROFILEDIALOG_H
#define UNTITLED1_PROFILEDIALOG_H

#include <wx/wx.h>

class ProfileDialog : public wxFrame{
public:
    ProfileDialog();
    void NextButtonClicked(wxCommandEvent& event);
    void ConfrimClicked(wxCommandEvent& event);


    wxSizer* getNextSizer();

    wxSizer *getFirstSizer();

    void closeClicked(wxCommandEvent &event);
};



#endif //UNTITLED1_PROFILEDIALOG_H
