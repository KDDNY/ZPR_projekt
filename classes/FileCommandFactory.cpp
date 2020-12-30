//
// Created by kddny on 29.12.2020.
//

#include <iostream>
#include "FileCommandFactory.h"
#include "File.h"
using namespace std;

std::shared_ptr<FileCommand> LocalFileCommandFactory::createAction(const File& file) {
    if(file.getAction()==COPY) return createCopy();
    if(file.getAction()==REMOVE) return createRemove();
    else return createSkip();
}

std::shared_ptr<FileCommand> LocalFileCommandFactory::createCopy() {
    return make_shared<LocalCopyFileCommand>();
}

std::shared_ptr<FileCommand> LocalFileCommandFactory::createRemove() {
    return make_shared<LocalRemoveFileCommand>();
}

std::shared_ptr<FileCommand> LocalFileCommandFactory::createSkip() {
    return make_shared<LocalSkipFileCommand>();
}