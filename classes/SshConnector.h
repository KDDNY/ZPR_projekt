//
// Created by Rafał Jan Trybus on 22/12/2020.
//

#ifndef UNTITLED1_SSHCONNECTOR_H
#define UNTITLED1_SSHCONNECTOR_H

#include <libssh/libssh.h>
#include <libssh/sftp.h>


class SshConnector {
public:

    SshConnector(){my_ssh_session = ssh_new();}
    ssh_session my_ssh_session;
    int verify_knownhosts(ssh_session session);

};


#endif //UNTITLED1_SSHCONNECTOR_H
