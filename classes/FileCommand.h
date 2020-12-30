//
// Created by kddny on 30.12.2020.
//

#ifndef UNTITLED1_FILECOMMAND_H
#define UNTITLED1_FILECOMMAND_H


class FileCommand {
public:
    virtual void execute() = 0;
};

class LocalCopyFileCommand : public FileCommand{
public:
    void execute() override;
};

class LocalSkipFileCommand : public FileCommand{
public:
    void execute() override;
};

class LocalRemoveFileCommand : public FileCommand{
public:
    void execute() override;
};

#endif //UNTITLED1_FILECOMMAND_H
