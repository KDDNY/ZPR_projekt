//
// Created by kddny on 29.12.2020.
//
#ifndef UNTITLED1_FILECOMMANDFACTORY_H
#define UNTITLED1_FILECOMMANDFACTORY_H
#include <memory>
#include "FileCommand.h"

class File;

class FileCommandFactory {
public:
    virtual std::shared_ptr<FileCommand> createAction(const File& file) = 0;
    virtual std::shared_ptr<FileCommand> createCopy(const File& file) = 0;
    virtual std::shared_ptr<FileCommand> createRemove(const File& file) = 0;
    virtual std::shared_ptr<FileCommand> createSkip(const File& file) = 0;
};

class LocalFileCommandFactory : public FileCommandFactory{
public:
    std::shared_ptr<FileCommand> createAction(const File& file) override;
    std::shared_ptr<FileCommand> createCopy(const File& file) override;
    std::shared_ptr<FileCommand> createRemove(const File& file) override;
    std::shared_ptr<FileCommand> createSkip(const File& file) override;
};


#endif //UNTITLED1_FILECOMMANDFACTORY_H
