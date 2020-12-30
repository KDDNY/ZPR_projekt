//
// Created by kddny on 30.12.2020.
//

#include "FileCommand.h"
#include <iostream>
using namespace std;
#include "File.h"

void LocalRemoveFileCommand::execute() {
    cout << "Local remove of " << file_.getName() << endl;
}

void LocalSkipFileCommand::execute() {
    cout << "Local skip of " << file_.getName() << endl;
}

void LocalCopyFileCommand::execute() {
    cout << "Local copy of " << file_.getName() << endl;
}
