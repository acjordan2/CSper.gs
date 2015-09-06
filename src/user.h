#ifndef SPERGS_USERS_H_INCLUDED
#define SPERGS_USERS_H_INCLUDED
struct spergs_user {
    MYSQL *mysql;
    int user_id;
    char *username;
};

struct spergs_user *user_init(MYSQL *mysql);

int user_authenticate(struct spergs_user *authuser, char *username, char *password);

int user_free(struct spergs_user *authuser);
#endif
