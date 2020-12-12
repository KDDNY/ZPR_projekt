//
// Created by Rafał Jan Trybus on 27/11/2020.
//

#include "Dir.h"

#include <utility>
#include "Command.cpp"

Dir::Dir(std::string path) : path_(std::move(path)) {}

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

void Dir::assignPath(string path){
    path_ = path;

}

void Dir::assignFactory(std::shared_ptr<AbstractFactory> factory) {
    creator_ = factory;
}

void Dir::addFile(){
    std::shared_ptr<Command> command = creator_->createAdd();
    command->execute();
}

void Dir::removeFile(){
    std::shared_ptr<Command> command = creator_->createRemove();
    command->execute();
}

void Dir::renameFile(){
    std::shared_ptr<Command> command = creator_->createRename();
    command->execute();
}

const vector<std::shared_ptr<File>> &Dir::getFiles() const {
    return files_;
}

/*LocalDir implementations starts here*/
void LocalDir::search() {
    std::filesystem::path pathToShow(path_);
    searchTree(pathToShow,0,files_);
}

void LocalDir::searchTree(const filesystem::path& pathToShow, int level, vector<shared_ptr<File>> &files){
    if(filesystem::exists(pathToShow) && filesystem::is_directory(pathToShow)){
        auto lead = std::string(level * 3, ' ');
        for (const auto& entry : filesystem::directory_iterator(pathToShow)){
            auto filename = entry.path().filename();
            if(filesystem::is_directory(entry.status()))
            {
                files.push_back(make_shared<File>(filename));
                searchTree(entry, level + 1,files.back()->files_);
            }
        }
    }
}

vector<shared_ptr<File>> LocalDir::getFiles() {
    return files_;
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

void LocalDir::printInfo(){
    std::cout << "#LOCAL DIR PATH: " << path_ <<std::endl;
}

void LocalDir::printTree(){
    std::filesystem::path pathToShow(path_);
    DisplayDirTree(pathToShow,0);
}
/*LocalDir implementations ends here*/

/*SshDir implementations starts here*/
void SshDir::printInfo(){
    std::cout << "#SSH DIR PATH: " << path_ <<std::endl;
}

void SshDir::printTree(){
    cout << "--> WILL PRINT SSH DIR TREE" << endl;
}

void SshDir::search() {
    cout <<"SEARCHING SSH DIR" << endl;
}
/*SshDir implementations ends here*/