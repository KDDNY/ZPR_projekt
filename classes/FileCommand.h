//
// Created by kddny on 30.12.2020.
//

#ifndef UNTITLED1_FILECOMMAND_H
#define UNTITLED1_FILECOMMAND_H

class File;

class FileCommand {
public:
    FileCommand(const File& file) : file_(file) {};
    virtual void execute() = 0;
    const File& file_;
};

class LocalCopyFileCommand : public FileCommand{
public:
    LocalCopyFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
};

class LocalSkipFileCommand : public FileCommand{
public:
    LocalSkipFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
};

class LocalRemoveFileCommand : public FileCommand{
public:
    LocalRemoveFileCommand(const File& file) : FileCommand(file) {}
    void execute() override;
};

#endif //UNTITLED1_FILECOMMAND_H
