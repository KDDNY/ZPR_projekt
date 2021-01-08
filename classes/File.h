//
// Created by kddny on 10.12.2020.
//
#ifndef UNTITLED1_FILE_H
#define UNTITLED1_FILE_H

#include <string>
#include <vector>
#include <memory>
//#include <openssl/sha.h>
#include <fstream>
#include "FileCommandFactory.h"

class Dir;

enum WhichDir{
    FIRST, SECOND
};

enum Action{
    COPY, REMOVE, SKIP
};
///Reprezentuje pojedynczy plik w katalogu, może być pod katalogiem i przechowywać wskaźniki do obiektów tej samej klasy.
class File{
public:
    File() = default;
    File(const std::string &name, bool directory, WhichDir whichDir);
    File(const std::string &name, bool directory, WhichDir whichDir, std::string home_dir_path);
    ///Określa czy plik znajduje się w pierwszym bądź drugim katalogu.
    WhichDir which_dir_;
    ///Wektor wskaźników do obiektów tej samej klasy.
    std::vector<std::shared_ptr<File>> files_;
    void setPath(const std::string &path);
    ///Setter służący do ustawiania akcji, która ma zostać wykonana w ramach synchronizacji.
    ///@param action enum określające akcje
    void setAction(Action action);
    ///Setter służący do ustawiania fabryki komend do synchronizacji.
    ///@param wskaźnik na fabrykę komend
    void setCreator(std::shared_ptr<LocalFileCommandFactory> creator);
    ///Setter wskaźnika do katalogu w którym znajduje się plik
    void setDir(Dir* dir);
    ///Określa czy plik jest katalogiem.
    ///@return true jeśli plik jest katalogiem, false gdy nie nim nie jest
    bool isDirectory() const;
    //Getters
    const std::string &getName() const;
    const std::vector<std::shared_ptr<File>> &getFiles() const;
    const std::string &getPath() const;
    ///Oblicza ścieżke do pliku z pominięciem ścieżki do katalogu.
    ///@return ścieżka do pliku z pominięciem ścieżki do katalogu
    std::string getRelPath() const;
    ///Getter enum mówiącego, w którym katalogu znajduje sie plik.
    WhichDir getWhichDir() const;
    ///Getter funkcji skrótu pliku.
    const std::string &getHash() const;
    ///Getter enum mówiącego jaka akcja ma zostać wykonana w celu synchronizacji.
    Action getAction() const;
    ///Getter katalogu, w którym znajduje się plik.
    ///@return wskaźnik na katalog w którym znajduje się plik
    Dir* getDir() const;
    //Others
    ///Generuje komendę służącą do synchronizacji według dostarczonej fabryki.
    ///@return wskaźnik na obiekt klasy Command
    std::shared_ptr<FileCommand> generateCommand();
    ///Generuje funkcje skrótu dla pliku i zapisuje ją.
    void genHash();
private:
    std::string name_;
    std::string path_;
    std::string home_dir_path_;
    bool directory_;
    std::string hash_;
    Action action = COPY;
    std::shared_ptr<FileCommandFactory> creator_;
    Dir* dir_;
};

#endif //UNTITLED1_FILE_H
