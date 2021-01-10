//
// Created by Marcin Piotrowski on 22.11.2020.
//

#ifndef UNTITLED1_STARTFRAME_H
#define UNTITLED1_STARTFRAME_H

#include <wx/wx.h>

///Implementuje startowe okno programu
class StartFrame : public wxFrame{
public:
    ///Konstruktor
    ///@param pos współrzędne ekranu na których ma pojawić się okno
    StartFrame(wxPoint pos);
    ///Uaktualnia tabelę z listą profili
    void updateListBox();
private:
    wxListBox* lb_;
    void onAdd(wxCommandEvent& event);
    void chooseClicked(wxCommandEvent &event);
};


#endif //UNTITLED1_STARTFRAME_H
