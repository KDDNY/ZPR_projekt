//
// Created by kddny on 09.11.2020.
//

#ifndef UNTITLED1_APPLICATION_H
#define UNTITLED1_APPLICATION_H


#include <vector>
#include <memory>
#include "Profile.h"

///Klasa służąca do przechowywania profili
class Application {
public:
    ///przechowuje wskaźniki do profilów
    static std::vector<Profile*> profiles;
    ///getter wektora wskaźników do profili
    static std::vector<Profile*> getProfiles();
    ///dodaje wskaźnik do profilu do wektora
    ///@param wskaźnik do profilu, który ma zostać dodany
    static void addProfile(Profile* P);
    void synchronize(std::shared_ptr<Profile> P);
};


#endif //UNTITLED1_APPLICATION_H
