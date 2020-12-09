//
// Created by kddny on 22.11.2020.
//

#ifndef UNTITLED1_MAINFRAME_H
#define UNTITLED1_MAINFRAME_H

#include <wx/wx.h>
#include "../classes/Profile.h"
#include "../classes/Application.h"

/// Implementuje główne okno programu.
///
/// Jest to okno w którym dokonuje się synchronizacji na wybranym profilu.
class MainFrame : public wxFrame{
public:
    MainFrame(wxPoint pos, int index);
private:
    void changeProfileClicked(wxCommandEvent &event);
    void updateLb();
    wxListBox* lb1_;
    wxListBox* lb2_;
    Profile* profile_;
};



#endif //UNTITLED1_MAINFRAME_H
