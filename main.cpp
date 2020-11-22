#include <iostream>
#include <wx/wx.h>
#include <gtest/gtest.h>

#include "tests/Tests.cpp"
#include "classes/LocalDirectory.h"
#include "classes/ScannerVisitor.h"
#include "GUI classes/StartFrame.h"

class MainpApp : public wxApp{
    bool OnInit(){
        start_frame_ = new StartFrame();
        start_frame_->Show(true);
//        ProfileDialog *profileDialog = new ProfileDialog();
//        profileDialog->Show(true);
        return true;
    }
    StartFrame* start_frame_;
};

wxIMPLEMENT_APP(MainpApp);

/*

int main(int argc, char *argv[]) {
    Application application;
    auto local1 = std::make_shared<LocalDirectory>();
    auto local2 = std::make_shared<LocalDirectory>();
    ScannerVisitor scannerVisitor;
    local1->accept(scannerVisitor);

    Profile profile(local1, local2, "fist profile");

    */
/* sposób na wylistyowanie zawartości katalogu
    std::string path = "/home/kddny/CLionProjects/untitled1/test_dir";
    for(const auto & entry : std::filesystem::directory_iterator(path)){
        std::cout << entry.path().string().substr(path.length()+1) << std::endl;
    }
    *//*


 //   ::testing::InitGoogleTest(&argc, argv);
 //   return RUN_ALL_TESTS();
}
*/
