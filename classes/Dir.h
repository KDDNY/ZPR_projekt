//
// Created by Rafał Jan Trybus on 27/11/2020.
//

#ifndef UNTITLED1_DIR_H
#define UNTITLED1_DIR_H

#include <filesystem>
#include <iostream>
#include "Command.h"
#include <vector>
#include "File.h"

using namespace std;

enum Choice{
    LOCAL, SSH
};

class Dir {
public:
    Dir() = default;
    explicit Dir(std::string path);
    virtual ~Dir() = default;
    virtual void printInfo() = 0;
    void assignPath(string path);
    void assignFactory(std::shared_ptr<AbstractFactory> factory);
    void addFile();
    void removeFile();
    void renameFile();
    static Dir *make_dir(Choice flag);
    virtual void printTree() = 0;
    virtual void search(ParentDir parentDir) = 0;
protected:
public:
    const vector<std::shared_ptr<File>> &getFiles() const;
protected:
    string path_;
    std::shared_ptr<AbstractFactory> creator_;
    std::vector<std::shared_ptr<File>> files_;
};

class LocalDir : public Dir{
public:
    void printInfo() override;
    void printTree() override;
    void DisplayFileInfo(const filesystem::directory_entry & entry, string & lead, filesystem::path& file_name);
    void DisplayDirTree(const filesystem::path& pathToShow, int level);
    void search(ParentDir parentDir) override;
    std::vector<std::shared_ptr<File>> getFiles();
private:
    void searchTree(const filesystem::path& pathToShow, int level, std::vector<std::shared_ptr<File>> &files, ParentDir parentDir);
};

class SshDir: public Dir{
public:
    void printInfo() override;
    void printTree() override;
    void search(ParentDir parentDir) override;
};

#endif //UNTITLED1_DIR_H
