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
void LocalDir::search(WhichDir whichDir) {
    files_.clear();
    std::filesystem::path pathToShow(path_);
    searchTree(pathToShow, 0, files_, whichDir, nullptr);
}

void LocalDir::searchTree(const filesystem::path& pathToShow, int level, vector<shared_ptr<File>> &files,
                          WhichDir whichDir, shared_ptr<File> prev){
    if(filesystem::exists(pathToShow) && filesystem::is_directory(pathToShow)){
        auto lead = std::string(level * 3, ' ');
        for (const auto& entry : filesystem::directory_iterator(pathToShow)){
            auto filename = entry.path().filename();
            if(filesystem::is_directory(entry.status()))
            {
                files.push_back(make_shared<File>(filename, true, whichDir));
                if(prev){
                    files.back()->setPath(prev->getPath() + "/" + prev->getName());
                } else files.back()->setPath(this->path_);
                prev = files.back();
                searchTree(entry, level + 1, files.back()->files_, whichDir, prev);
            }   else if (filesystem::is_regular_file(entry.status())) {
                files.push_back(make_shared<File>(filename, false, whichDir));
                if(prev){
                    files.back()->setPath(prev->getPath() + "/" + prev->getName());
                } else files.back()->setPath(this->path_);
            }
            prev = nullptr;
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

int SshDir::verify_knownhosts(ssh_session session){
    int state, hlen;
    unsigned char *hash = NULL;
    char *hexa;
    char buf[10];

    state = ssh_is_server_known(session);

    hlen = ssh_get_pubkey_hash(session, &hash);
    if (hlen < 0)
        return -1;

    switch (state)
    {
        case SSH_SERVER_KNOWN_OK:
            break; /* ok */

        case SSH_SERVER_KNOWN_CHANGED:
            fprintf(stderr, "Host key for server changed: it is now:\n");
            ssh_print_hexa("Public key hash", hash, hlen);
            fprintf(stderr, "For security reasons, connection will be stopped\n");
            free(hash);
            return -1;

        case SSH_SERVER_FOUND_OTHER:
            fprintf(stderr, "The host key for this server was not found but an other"
                            "type of key exists.\n");
            fprintf(stderr, "An attacker might change the default server key to"
                            "confuse your client into thinking the key does not exist\n");
            free(hash);
            return -1;

        case SSH_SERVER_FILE_NOT_FOUND:
            fprintf(stderr, "Could not find known host file.\n");
            fprintf(stderr, "If you accept the host key here, the file will be"
                            "automatically created.\n");
            /* fallback to SSH_SERVER_NOT_KNOWN behavior */

        case SSH_SERVER_NOT_KNOWN:
            hexa = ssh_get_hexa(hash, hlen);
            fprintf(stderr,"The server is unknown. Do you trust the host key?\n");
            fprintf(stderr, "Public key hash: %s\n", hexa);
            free(hexa);
            if (fgets(buf, sizeof(buf), stdin) == NULL)
            {
                free(hash);
                return -1;
            }
            if (strncasecmp(buf, "yes", 3) != 0)
            {
                free(hash);
                return -1;
            }
            if (ssh_write_knownhost(session) < 0)
            {
                fprintf(stderr, "Error %s\n", strerror(errno));
                free(hash);
                return -1;
            }
            break;

        case SSH_SERVER_ERROR:
            fprintf(stderr, "Error %s", ssh_get_error(session));
            free(hash);
            return -1;
    }

    free(hash);
    return 0;

}


void SshDir::buildTree(ssh_session session, sftp_session sftp,string rootDir) {
    sftp_list_dir(session,sftp,rootDir);

}

int SshDir::checkIfDir(ssh_session session, sftp_session sftp, string path){
    sftp_dir dir;
    sftp_attributes attributes;
    int rc;
    int n = path.length();
    char dirPath[n + 1];
    strcpy(dirPath, path.c_str());


    dir = sftp_opendir(sftp, dirPath);
    if (!dir)
    {
        cout << path + "<--- FILE";
        return 0;

    }
    else{
        cout << path + "<--- DIR";
        return 1;
    }

}

void SshDir::listVector(std::vector<std::shared_ptr<File>> files){
    cout << endl << "VECTOR ROOT: " << endl;
    for(const auto& element: files){
        cout << endl << element->getName();


    }

}

int SshDir::sftp_list_dir(ssh_session session, sftp_session sftp, string rootDir)
{
    sftp_dir dir;
    sftp_attributes attributes;
    int rc;
    int n = rootDir.length();
    char dirPath[n + 1];
    strcpy(dirPath, rootDir.c_str());



    dir = sftp_opendir(sftp, dirPath);
    if (!dir)
    {
        fprintf(stderr, "Directory not opened: %s\n",
                ssh_get_error(session));
        return SSH_ERROR;
    }

    printf("Name                       Size Perms    Owner\tGroup\n");


    while ((attributes = sftp_readdir(sftp, dir)) != NULL)
    {

        /*printf("%-20s %10llu %.8o %s(%d)\t%s(%d)\n",
               attributes->name,
               (long long unsigned int) attributes->size,
               attributes->permissions,
               attributes->owner,
               attributes->uid,
               attributes->group,
               attributes->gid);*/
        printf("\n");

        string name = rootDir+"/"+attributes->name;
        if(name.back() != '.'){
            cout << name << " <- ok";
            if(checkIfDir(session,sftp,rootDir+"/"+attributes->name)){
                cout <<"| DIR";
                File *f = new File(attributes->name,true, FIRST);
                files_.push_back(static_cast<const shared_ptr<File>>(f));
                sftp_list_dir(session,sftp,rootDir+"/"+attributes->name);
                //listVector(f->files_);


            }
            else{
                cout << "| FILE";
                File *f = new File(attributes->name,false,FIRST);
                f->files_.push_back(static_cast<const shared_ptr<File>>(f));
                listVector(f->files_);

            }

        }else {
            cout << name << " <- bad";


        }


        sftp_attributes_free(attributes);

    }




    if (!sftp_dir_eof(dir))
    {
        fprintf(stderr, "Can't list directory: %s\n",
                ssh_get_error(session));
        sftp_closedir(dir);
        return SSH_ERROR;
    }

    rc = sftp_closedir(dir);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Can't close directory: %s\n",
                ssh_get_error(session));
        return rc;
    }
}

void SshDir::printTree(){

    cout << "--> WILL PRINT SSH DIR TREE" << endl;

    ssh_session my_ssh_session;
    int rc;
    char *password;

    // Open session and set options
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL)
        exit(-1);
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, "rtrybus@mion.elka.pw.edu.pl");

    // Connect to server
    rc = ssh_connect(my_ssh_session);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error connecting to localhost: %s\n",
                ssh_get_error(my_ssh_session));
        ssh_free(my_ssh_session);
        exit(-1);
    }

    // Verify the server's identity
    // For the source code of verify_knowhost(), check previous example
    if (verify_knownhosts(my_ssh_session) < 0)
    {
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }

    // Authenticate ourselves
    //password = getpass("Password: ");
    password = "mJzr7Ty";
    rc = ssh_userauth_password(my_ssh_session, NULL, password);
    if (rc != SSH_AUTH_SUCCESS)
    {
        fprintf(stderr, "Error authenticating with password: %s\n",
                ssh_get_error(my_ssh_session));
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        exit(-1);
    }else{
        printf("connected to SSH - ok");

    }



    sftp_session sftp;
    sftp = sftp_new(my_ssh_session);
    //scp_receive(my_ssh_session);
    cout << endl;
    buildTree(my_ssh_session,sftp,"/home/mion/s/250/rtrybus");
    listVector(files_);



    ssh_disconnect(my_ssh_session);
    ssh_free(my_ssh_session);


}
/*SshDir implementations ends here*/



void SshDir::search(WhichDir parentDir) {
    cout <<"SEARCHING SSH DIR" << endl;
}
/*SshDir implementations ends here*/
