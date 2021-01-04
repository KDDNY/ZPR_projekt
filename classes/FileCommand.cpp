//
// Created by kddny on 30.12.2020.
//

#include "FileCommand.h"
#include <iostream>
#include <filesystem>
using namespace std;
#include "File.h"
#include "Dir.h"
#include "Profile.h"

void LocalRemoveFileCommand::execute() {
    cout << "Local remove of " << file_.getName() << endl;
    filesystem::path path = file_.getPath() + "/" + file_.getName();
    cout << path << endl;
    try{
        filesystem::remove_all(path);
    } catch(exception e){
        cout << e.what() << endl;
    }
}

void LocalSkipFileCommand::execute() {
    cout << "Local skip of " << file_.getName() << endl;
}

void LocalCopyFileCommand::execute() {
    if(file_.getDir()->getProfile()->getDir1()->getFlag() == LOCAL &&
    file_.getDir()->getProfile()->getDir2()->getFlag() == LOCAL) {
        if (file_.getWhichDir() == FIRST) {
            cout << "Local copy of " << file_.getName() << endl;
            cout << "from " << file_.getPath() << endl;
            cout << "to " << file_.getDir()->getProfile()->getDir2()->getPath() + file_.getRelPath() << endl;
            filesystem::path src = file_.getPath() + "/" + file_.getName();
            filesystem::path target = file_.getDir()->getProfile()->getDir2()->getPath() + file_.getRelPath();
        } else {
            cout << "Local copy of " << file_.getName() << endl;
            cout << "from " << file_.getPath() << endl;
            cout << "to " << file_.getDir()->getProfile()->getDir1()->getPath() + file_.getRelPath() << endl;
            filesystem::path src = file_.getPath() + "/" + file_.getName();
            filesystem::path target = file_.getDir()->getProfile()->getDir1()->getPath() + file_.getRelPath();
        }
    }
}
