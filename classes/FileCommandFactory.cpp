//
// Created by Marcin Piotrowski on 29.12.2020.
//

#include <iostream>
#include "FileCommandFactory.h"
#include "File.h"
using namespace std;

std::shared_ptr<FileCommand> LocalFileCommandFactory::createAction(const File& file) {
    if(file.getAction()==COPY) return createCopy(file);
    if(file.getAction()==REMOVE) return createRemove(file);
    else return createSkip(file);
}

std::shared_ptr<FileCommand> LocalFileCommandFactory::createCopy(const File& file) {
    return make_shared<LocalCopyFileCommand>(file);
}

std::shared_ptr<FileCommand> LocalFileCommandFactory::createRemove(const File& file) {
    return make_shared<LocalRemoveFileCommand>(file);
}

std::shared_ptr<FileCommand> LocalFileCommandFactory::createSkip(const File& file) {
    return make_shared<LocalSkipFileCommand>(file);
}

// SSH implementation

std::shared_ptr<FileCommand> SSHFileCommandFactory::createAction(const File& file) {
    if(file.getAction()==COPY) return createCopy(file);
    if(file.getAction()==REMOVE) return createRemove(file);
    else return createSkip(file);
}

std::shared_ptr<FileCommand> SSHFileCommandFactory::createCopy(const File& file) {
    return make_shared<SSHCopyFileCommand>(file);
}

std::shared_ptr<FileCommand> SSHFileCommandFactory::createRemove(const File& file) {
    return make_shared<SSHRemoveFileCommand>(file);
}

std::shared_ptr<FileCommand> SSHFileCommandFactory::createSkip(const File& file) {
    return make_shared<SSHSkipFileCommand>(file);
}