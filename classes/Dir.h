//
// Created by Rafał Jan Trybus on 27/11/2020.
//

#ifndef UNTITLED1_DIR_H
#define UNTITLED1_DIR_H

#include <filesystem>
#include <iostream>
#include <vector>
#include "File.h"
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <stdlib.h>
#include <memory.h>
#include "SshConnector.h"

using namespace std;

class Profile;
///Enum służące do określania wyboru użytkownika.
enum Choice{
    LOCAL, SSH
};

///Klasa abstrakcyjna reprezentująca katalog. Przechowuje informacje takie jak ścieżka oraz pliki które zawiera.
///Dostarcza metody do rekurencyjnego przeszukiwania katalogu.
class Dir {
public:
    Dir() = default;
    explicit Dir(std::string path);
    virtual ~Dir() = default;
    virtual void printInfo() = 0;
    ///Przypisuje ścieżkę
    ///@param path ścieżka do katalogu
    void assignPath(string path);
    void addFile();
    void removeFile();
    void renameFile();
    ///Tworzy pusty obiekt klasy Dir.
    ///@param flag określa czy katalog jest lokalny czy na serwerze ssh
    ///@return wskaźnik na utworzony katalog
    static Dir *make_dir(Choice flag);
    static Dir *make_dir(Choice flag, std::string servername, std::string password, std::string path);
    virtual void printTree() = 0;
    ///Przeszukuje rekurencyjnie katalog i tworzy drzewiastą strukturę podfolderów.
    ///@param parentDir określa który katalog jest przeszukiwany(pierwszy czy drugi)
    virtual void search(WhichDir parentDir) = 0;
    Choice getFlag() const;
    const vector<std::shared_ptr<File>> &getFiles() const;
    Profile* getProfile() const;
    void setProfile(Profile* profile);
    void setChoice(Choice choice);
    const string &getPath() const;
    SshConnector *getSshConnector() const;
protected:
    string path_;
    ///Wektor  przechowujący pliki katalogu jako wskaźniki do obiektów klasy File.
    std::vector<std::shared_ptr<File>> files_;
    ///wskaźnik do profilu, w którym znajduje się katalog.
    Profile* profile_;
    ///określa czy jest to katalog lokalny czy znajdujący sie na serwerze ssh.
    Choice choice_;
    SshConnector* sshConnector_;
};
///Implementacja dla katalogu lokalnego.
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
    SshDir(std::string serverN,std::string password,std::string path) : servername_(serverN), password_(password),path_(path) {
        choice_ = SSH;
    };
    void printInfo() override;
    void printTree() override;

    void search(WhichDir parentDir) override;
    void searchTree(SshConnector* s);
    void listVector(std::vector<std::shared_ptr<File>> files);
    void printDir();
private:
    string servername_;
    string password_;
    string path_;
};



#endif //UNTITLED1_DIR_H
