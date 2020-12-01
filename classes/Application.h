//
// Created by kddny on 09.11.2020.
//

#ifndef UNTITLED1_APPLICATION_H
#define UNTITLED1_APPLICATION_H


#include <vector>
#include <memory>
#include "Profile.h"

class Application {
public:
    static std::vector<Profile*> profiles;
    static std::vector<Profile*> getProfiles();
    static void addProfile(Profile* P);
    void synchronize(std::shared_ptr<Profile> P);
};


#endif //UNTITLED1_APPLICATION_H
