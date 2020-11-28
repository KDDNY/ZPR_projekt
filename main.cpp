#include <iostream>
#include <wx/wx.h>
#include <gtest/gtest.h>

#include "classes/LocalDirectory.h"
#include "classes/ScannerVisitor.h"
#include "GUI classes/StartFrame.h"

/// Inicjuje bibliotekę graficzną
class MainpApp : public wxApp{
    /// Wywyoływana w momencie uruchomienia aplikacji. Wyświetla startowe okno programu.
    bool OnInit(){
        wxPoint pos;
        start_frame_ = new StartFrame(pos);
        start_frame_->Show(true);
        return true;
    }
    StartFrame* start_frame_;
};

wxIMPLEMENT_APP(MainpApp);
