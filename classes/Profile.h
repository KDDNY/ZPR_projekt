//
// Created by kddny on 09.11.2020.
//

#ifndef UNTITLED1_PROFILE_H
#define UNTITLED1_PROFILE_H
#include "Dir.h"
#include "Scanner.h"

///Reprezentuje profil użytkownika. Przechowuje dwa synchronizowane katalogi i umożliwa porównywanie katalogów
///oraz ich synchronizacje.
class Profile {
public:
    ///Konstruktor.
    ///@param directory1 wskaźnik na pierwszy synchronizowany katalog
    ///@param directory2 wskaźnik na drugi synchronizowany katalog
    ///@param name nazwa profilu
    Profile(Dir* directory1, Dir* directory2, std::string name);
    ///Porównuje rekurencyjnie dwa katalogi i szuka różnic.
    void scan();
    ///Synchronizuje dwa katalogi.
    void synchronize();
    ///Dodaje katalogi do profilu
    ///@param flag1 enum mówiące o tym czy katalog jest lokalny czy na serwerze.
    ///@param flag2 enum mówiące o tym czy katalog jest lokalny czy na serwerze.
    ///@param path1 ścieżka do pierwszego katalogu
    ///@param path2 ścieżka do drugiego katalogu
    void addDirectories(std::string path1, std::string path2,Choice flag1, Choice flag2);
    void addDirectories(std::string path1, std::string path2,Choice flag1, Choice flag2, std::string servername, std::string password);
    void summary();
    void printTree1();
    void printTree2();
    ~Profile(){delete dir1_; delete dir2_;}
    ///Zwraca nazwe profilu
    ///@return nazwa profilu
    std::string getName();
    ///Zwraca wektor wskaźników do klasy File będących plikami które stanowią różnice pomiędzy katalogami
    ///@return wektor wskaźników do klasy File
    const vector<std::shared_ptr<File>> &getDif() const;
    ///Zwraca wskaźnik na pierwszy katalog
    ///@return pierwszy katalog
    Dir *getDir1() const;
    ///Zwraca wskaźnik na drugi katalog
    ///@return drugi katalog
    Dir *getDir2() const;
    bool findInVector(std::vector<std::shared_ptr<File>> vector1, std::shared_ptr<File> file);
    int getIndex(std::vector<std::shared_ptr<File>> vector1, std::shared_ptr<File> file);
private:
    std::vector<std::shared_ptr<File>> differences_;
    std::string name_;
    Dir* dir1_;
    Dir* dir2_;
    void lookForDifference(std::vector<std::shared_ptr<File>> vector1, std::vector<std::shared_ptr<File>> vector2);
};


#endif //UNTITLED1_PROFILE_H
