//
// Created by Rafał Jan Trybus on 27/11/2020.
//

#include "Dir.h"
#include "Command.cpp"

Dir *Dir::make_dir(Choice flag)
{
    if (flag == LOCAL){
        LocalDir* local_directory = new LocalDir;
        local_directory->assignFactory(make_shared<LocalFactory>());
        return local_directory;
    }
    else if (flag == SSH){
        SshDir* ssh_directory = new SshDir;
        ssh_directory->assignFactory(make_shared<SshFactory>());
        return ssh_directory;
    }
    else
        return nullptr;
}


void LocalDir::DisplayFileInfo(const filesystem::directory_entry & entry, string & lead, filesystem::path& file_name){
    cout << lead << " " << file_name;
}

void LocalDir::DisplayDirTree(const filesystem::path& pathToShow, int level){
    if(filesystem::exists(pathToShow) && filesystem::is_directory(pathToShow)){
        auto lead = std::string(level * 3, ' ');
        for (const auto& entry : filesystem::directory_iterator(pathToShow)){
            auto filename = entry.path().filename();
            if(filesystem::is_directory(entry.status()))
            {
                cout << lead << "[+] " << filename << endl;
                DisplayDirTree(entry, level + 1);
            } else if (filesystem::is_regular_file(entry.status())){
                DisplayFileInfo(entry, lead, filename);
                cout <<endl;
            } else cout << lead << " [?]" << filename << endl;
        }
    }
}