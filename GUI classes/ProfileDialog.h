//
// Created by kddny on 22.11.2020.
//

#ifndef UNTITLED1_PROFILEDIALOG_H
#define UNTITLED1_PROFILEDIALOG_H

#include <wx/wx.h>

///Wyswietla kolejne okna interfejsu dodwania nowego profilu
class ProfileDialog : public wxFrame{
public:
    ProfileDialog();
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
};



#endif //UNTITLED1_PROFILEDIALOG_H
