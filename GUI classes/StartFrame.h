//
// Created by kddny on 22.11.2020.
//

#ifndef UNTITLED1_STARTFRAME_H
#define UNTITLED1_STARTFRAME_H

#include <wx/wx.h>

class StartFrame : public wxFrame{
public:
    StartFrame(wxPoint pos);
    void updateListBox();
private:
    wxListBox* lb;
    void onAdd(wxCommandEvent& event);
    void chooseClicked(wxCommandEvent &event);
};



#endif //UNTITLED1_STARTFRAME_H
