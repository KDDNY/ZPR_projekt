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
        filesystem::remove(path);
    } catch(exception e){
        cout << e.what() << endl;
    }
}

void LocalSkipFileCommand::execute() {
    cout << "Local skip of " << file_.getName() << endl;
//    cout << file_.getDir()->getProfile()->getDir1()->getPath() << endl;
//    cout << file_.getDir()->getPath() << endl;
}

void LocalCopyFileCommand::execute() {
    cout << "Local copy of " << file_.getName() << endl;
}
