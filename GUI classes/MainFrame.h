//
// Created by Marcin Piotrowski on 22.11.2020.
//

#ifndef UNTITLED1_MAINFRAME_H
#define UNTITLED1_MAINFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "../classes/Profile.h"
#include "../classes/Application.h"

///Implementuje główne okno programu
class MainFrame : public wxFrame{
public:
    ///Konstruktor głównego okna.
    ///@param pos współrzędne na ekranie na których ma pojawić się okno
    ///@param index numer wybranego profilu na ekranie startowym
    MainFrame(wxPoint pos, int index);
private:
    void changeProfileClicked(wxCommandEvent &event);
    void scanClicked(wxCommandEvent &event);
    void changeClicked(wxCommandEvent &event);
    void goClicked(wxCommandEvent &event);
    void skipClicked(wxCommandEvent &event);
    void fillListCtrl();
    wxListBox* lb1_;
    wxListBox* lb2_;
    wxListBox* lb3_;
    wxListItem *col0_;
    wxListItem *col1_;
    wxListItem *col2_;
    wxListItem *col3_;
    wxListCtrl* list_ctrl_;
    Profile* profile_;
};

#endif //UNTITLED1_MAINFRAME_H
