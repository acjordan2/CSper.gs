#ifndef SPERGS_USERS_H_INCLUDED
#define SPERGS_USERS_H_INCLUDED
struct spergs_user {
    MYSQL *mysql;
    int user_id;
    char *username;
};

int spergs_authenticate(struct spergs_user *authuser, char *password);
#endif
