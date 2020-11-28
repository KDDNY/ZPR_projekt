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
    void add_profile(std::shared_ptr<Profile> P);
    void scan(std::shared_ptr<Profile> P);
    void synchronize(std::shared_ptr<Profile> P);
private:
    std::vector<std::shared_ptr<Profile>> Profiles;
};


#endif //UNTITLED1_APPLICATION_H
