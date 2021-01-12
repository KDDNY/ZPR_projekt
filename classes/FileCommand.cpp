//
// Created by Marcin Piotrowski on 30.12.2020.
//

#include "FileCommand.h"
#include <iostream>

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
            filesystem::path targetParent = file_.getDir()->getProfile()->getDir2()->getPath() + file_.getRelPath();
            auto target = targetParent / src.filename();
            CopyRecursive(src,target);
        } else {
            cout << "Local copy of " << file_.getName() << endl;
            cout << "from " << file_.getPath() << endl;
            cout << "to " << file_.getDir()->getProfile()->getDir1()->getPath() + file_.getRelPath() << endl;
            filesystem::path src = file_.getPath() + "/" + file_.getName();
            filesystem::path targetParent = file_.getDir()->getProfile()->getDir1()->getPath() + file_.getRelPath();
            auto target = targetParent / src.filename();
            CopyRecursive(src,target);
        }
    } else {
        cout << "Copy from local to ssh of " << file_.getName() << endl;
        string source = file_.getPath() + "/" + file_.getName();
        string target = file_.getDir()->getProfile()->getDir2()->getPath() + file_.getRelPath() + "/" + file_.getName();
        cout << "from: " << source << endl;
        cout << "to: " << target << endl;
        file_.getDir()->getProfile()->getDir2()->getSshConnector()->copyLS(source,target);
    }
}

void LocalCopyFileCommand::CopyRecursive(const filesystem::path& src, const filesystem::path& target) noexcept
{
    try
    {
        filesystem::copy(src, target, filesystem::copy_options::overwrite_existing | filesystem::copy_options::recursive);
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }
}

void SSHRemoveFileCommand::execute() {
    cout << "SSH remove of " << file_.getName() << endl;
}

void SSHSkipFileCommand::execute() {
    cout << "SSH skip of " << file_.getName() << endl;
}

void SSHCopyFileCommand::execute() {
    cout << "SSH copy of " << file_.getName() << endl;
    string source2 = file_.getPath() + "/" + file_.getName();
    string xD = file_.getRelPath();
    string source = file_.getDir()->getPath() + "/" + file_.getName();
    string target = file_.getDir()->getProfile()->getDir1()->getPath() + file_.getRelPath() + "/" + file_.getName();
    cout << "from: " << source2 << endl;
    cout << "to: " << target << endl;
    file_.getDir()->getSshConnector()->copySL(source2, target);
}