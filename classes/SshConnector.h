//
// Created by Rafał Jan Trybus on 22/12/2020.
//

#ifndef UNTITLED1_SSHCONNECTOR_H
#define UNTITLED1_SSHCONNECTOR_H

#include <iostream>
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <fcntl.h>
#include "File.h"
#include <stdio.h>



class SshConnector {
public:

    std::string _serverName;
    std::string _password;
    std::string _sshFilePath;



    SshConnector(std::string serverName, std::string password, std::string filePath) : _serverName(serverName), _password(password),
    _sshFilePath(filePath) {my_ssh_session = ssh_new();}
    ssh_session my_ssh_session;
    sftp_session my_sftp_session;
    int verify_knownhosts(ssh_session session);
    sftp_session fetchFiles();
    int checkIfDir(ssh_session session, sftp_session sftp, std::string path);
    int sftp_list_dir(ssh_session session, sftp_session sftp, std::string rootDir,std::vector<std::shared_ptr<File>> &files);
    int copyTest();
    int copyTest2();
    i



};


#endif //UNTITLED1_SSHCONNECTOR_H
