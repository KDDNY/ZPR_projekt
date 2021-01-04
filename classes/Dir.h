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
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <stdlib.h>
#include <memory.h>
#include "SshConnector.h"

using namespace std;

class Profile;

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
    virtual void search(WhichDir parentDir) = 0;
    Choice getFlag() const;
    const vector<std::shared_ptr<File>> &getFiles() const;
    Profile* getProfile() const;
    void setProfile(Profile* profile);
    void setChoice(Choice choice);
    const string &getPath() const;

public:
protected:
    string path_;
    std::shared_ptr<AbstractFactory> creator_;
    std::vector<std::shared_ptr<File>> files_;
    Profile* profile_;
    Choice choice_;
};

class LocalDir : public Dir{
public:
    LocalDir();
    void printInfo() override;
    void printTree() override;
    void DisplayFileInfo(const filesystem::directory_entry & entry, string & lead, filesystem::path& file_name);
    void DisplayDirTree(const filesystem::path& pathToShow, int level);
    void search(WhichDir whichDir) override;
    std::vector<std::shared_ptr<File>> getFiles();
private:
    void searchTree(const filesystem::path& pathToShow, int level, std::vector<std::shared_ptr<File>> &files,
                    WhichDir whichDir, std::shared_ptr<File> prev);
};

//TO DO: file ma w konstrutorze informacje w którym dirze się znajduje, uwzględnić to w metodach sshdir
//Na razie wpisałem wszędzie wartość z enum FIRST aby sie kompilowalo
class SshDir: public Dir{
public:
    void printInfo() override;
    void printTree() override;



    void search(WhichDir parentDir) override;
    int verify_knownhosts(ssh_session session);

    int sftp_list_dir(ssh_session session, sftp_session sftp, string rootDir,vector<shared_ptr<File>> &files);
    void buildTree(ssh_session session, sftp_session sftp, string rootDir);
    int checkIfDir(ssh_session session, sftp_session sftp, string rootDir);
    void listVector(std::vector<std::shared_ptr<File>> files);
    void printDir();
};


#endif //UNTITLED1_DIR_H
