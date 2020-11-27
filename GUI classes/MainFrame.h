//
// Created by kddny on 22.11.2020.
//

#ifndef UNTITLED1_MAINFRAME_H
#define UNTITLED1_MAINFRAME_H

#include <wx/wx.h>
/// Implementuje główne okno programu.
///
/// Jest to okno w którym dokonuje się synchronizacji na wybranym profilu.
class MainFrame : public wxFrame{
public:
    MainFrame(wxPoint pos);
    ///Zamyka obecne okno i otwiera okno startowe
    void changeProfileClicked(wxCommandEvent &event);
};



#endif //UNTITLED1_MAINFRAME_H
