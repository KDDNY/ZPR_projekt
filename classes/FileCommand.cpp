//
// Created by kddny on 30.12.2020.
//

#include "FileCommand.h"
#include <iostream>
using namespace std;

void LocalRemoveFileCommand::execute() {
    cout << "Local remobe" << endl;
}

void LocalSkipFileCommand::execute() {
    cout << "Local skip" << endl;
}

void LocalCopyFileCommand::execute() {
    cout << "Local copy" << endl;
}