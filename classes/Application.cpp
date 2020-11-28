//
// Created by kddny on 28.11.2020.
//

#include "Application.h"

using namespace std;

vector<Profile *> Application::profiles;

void Application::add_profile(Profile* P){
    Application::profiles.push_back(P);
}

std::vector<Profile *> Application::getProfiles() {
    return profiles;
}

