//
// Created by Rafał Jan Trybus on 22/12/2020.
//


#include "SshConnector.h"
#include <strings.h>
#include <string.h>

#define MAX_XFER_BUF_SIZE 16384

using namespace std;


// server -> local
int SshConnector::copyTest() {

    int access_type;
    sftp_file file;
    char buffer[MAX_XFER_BUF_SIZE];
    int nbytes, nwritten, rc;


    access_type = O_RDONLY;
    file = sftp_open(my_sftp_session, "/home/mion/s/250/rtrybus/capt_udp.txt",
                     access_type, 0);

    if (file == NULL) {
        fprintf(stderr, "Can't open file for reading: %s\n",
                ssh_get_error(my_ssh_session));
        return SSH_ERROR;
    }



    FILE* fd = fopen("/Users/raftry/Desktop/[ZPR]/code/ZPR_projekt/capt_udp.txt", "ab+");


    if (fd == NULL) {
        perror("Failed: ");
        return 1;
    }

    nbytes = sftp_read(file, buffer, sizeof(buffer));
    nwritten = fwrite(buffer, sizeof(char), nbytes, fd);
    sftp_close(file);
    fclose(fd);

    return 0;

}


// local -> server
int SshConnector::copyTest2() {

    ifstream fin("/Users/raftry/Desktop/[ZPR]/code/ZPR_projekt/CMakeLists.txt", ios::binary);
    sftp_file file;
    int access_type = O_WRONLY | O_CREAT | O_TRUNC;

    file = sftp_open(my_sftp_session, "/home/mion/s/250/rtrybus/CMakeLists.txt",
                     access_type, S_IRWXU);

    if (file == NULL)
    {
        fprintf(stderr, "Can't open file for writing: %s\n",
                ssh_get_error(my_ssh_session));
        return SSH_ERROR;
    }

    while (fin)
    {
        char buffer[MAX_XFER_BUF_SIZE];
        fin.read(buffer, sizeof(buffer));
        if (fin.gcount() > 0)
        {
            ssize_t nwritten = sftp_write(file, buffer, fin.gcount());

            if (nwritten != fin.gcount())
            {
                fprintf(stderr, "Can't write data to file: %s\n", ssh_get_error(my_ssh_session));
                sftp_close(file);
                return 1;
            }
        }
    }



    return 0;

}


sftp_session SshConnector::fetchFiles() {

    cout << "--> WILL PRINT SSH DIR TREE" << endl;


    int rc;




    // Open session and set options

    if (this->my_ssh_session == NULL)
        exit(-1);
    ssh_options_set(this->my_ssh_session, SSH_OPTIONS_HOST, (this->_serverName).c_str());

    // Connect to server
    rc = ssh_connect(this->my_ssh_session);
    if (rc != SSH_OK)
    {
        fprintf(stderr, "Error connecting to localhost: %s\n",
                ssh_get_error(this->my_ssh_session));
        ssh_free(this->my_ssh_session);
        exit(-1);
    }

    // Verify the server's identity
    // For the source code of verify_knowhost(), check previous example
    if (this->verify_knownhosts(this->my_ssh_session) < 0)
    {
        ssh_disconnect(this->my_ssh_session);
        ssh_free(this->my_ssh_session);
        exit(-1);
    }

    // Authenticate ourselves
    //password = getpass("Password: ");
    //password = "mJzr7Ty";
    rc = ssh_userauth_password(this->my_ssh_session, NULL, (this->_password).c_str());
    if (rc != SSH_AUTH_SUCCESS)
    {
        fprintf(stderr, "Error authenticating with password: %s\n",
                ssh_get_error(this->my_ssh_session));
        ssh_disconnect(this->my_ssh_session);
        ssh_free(this->my_ssh_session);
        exit(-1);
    }else{
        printf("connected to SSH - ok");

    }



    sftp_session sftp;
    sftp = sftp_new(this->my_ssh_session);
    //scp_receive(my_ssh_session);
    cout << endl;




    this->my_sftp_session = sftp;


    return sftp;
}
int SshConnector::verify_knownhosts(ssh_session session){
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

int SshConnector::checkIfDir(ssh_session session, sftp_session sftp, string path){
    sftp_dir dir;
    sftp_attributes attributes;
    int rc;
    int n = path.length();
    char dirPath[n + 1];
    strcpy(dirPath, path.c_str());


    dir = sftp_opendir(sftp, dirPath);
    if (!dir)
    {
        //cout << path + "<--- FILE";
        return 0;

    }
    else{
       // cout << path + "<--- DIR";
        return 1;
    }

}

int SshConnector::sftp_list_dir(ssh_session session, sftp_session sftp, string rootDir,vector<shared_ptr<File>> &files)
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

   // printf("Name                       Size Perms    Owner\tGroup\n");


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
        //printf("\n");

        string name = rootDir+"/"+attributes->name;
        if(name.back() != '.'){
            //cout << name << " <- ok";
            if(checkIfDir(session,sftp,rootDir+"/"+attributes->name)){
                //cout <<"| DIR";
                files.push_back(make_shared<File>(attributes->name,true, SECOND));
                sftp_list_dir(session,sftp,rootDir+"/"+attributes->name,files.back()->files_);
                files.back()->setCreatorSSH(make_shared<SSHFileCommandFactory>());
                //listVector(files_);


            }
            else{
                //cout << "| FILE";
                files.push_back(make_shared<File>(attributes->name, false, SECOND));
                files.back()->setCreatorSSH(make_shared<SSHFileCommandFactory>());

                //listVector(files_);

            }

        }else {
            //cout << name << " <- bad";


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