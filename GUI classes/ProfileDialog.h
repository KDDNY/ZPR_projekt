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
    ///Czyści okno w celu wyświetlenia nowej zawartości
    void NextButtonClicked(wxCommandEvent& event);
    ///Zapisuje zmiany i zamyka okno tworzenia profilu
    void ConfrimClicked(wxCommandEvent& event);
    ///Generuje początkową zawartość okna
    ///@return obiekt klasy wxSizer zawierający rozmieszczone elementy interfejsu
    wxSizer* getNextSizer();
    ///Generuje zawartość okna po kliknięciu przycisku "dalej"
    ///@return obiekt klasy wxSizer zawierający rozmieszczone elementy interfejsu
    wxSizer *getFirstSizer();
    ///Zamyka okno bez zapisywania podanych informacji
    void closeClicked(wxCommandEvent &event);
private:
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
