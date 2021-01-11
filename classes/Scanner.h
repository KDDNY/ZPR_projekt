//
// Created by Marcin Piotrowski on 29.12.2020.
//

#ifndef UNTITLED1_SCANNER_H
#define UNTITLED1_SCANNER_H

#include <vector>
#include <memory>
#include "File.h"
#include "FileCommandFactory.h"

///Klasa implementująca operacje wykonywane w celu synchronizacji.
class Scanner {
public:
    ///Synchronizuje dwa katalogi. Dla każdego pliku z dostarczonego wektora tworzy odpowiednią komendę (obiekt klasy
    ///FileCommand) i wykonuje ją.
    ///@param diff wektor wskaźników na pliki będących różnicami pomiędzy katalogami.
    static void synchronize(const std::vector<std::shared_ptr<File>>& diff);
};


#endif //UNTITLED1_SCANNER_H