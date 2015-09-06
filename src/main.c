#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include "../lib/mpsw/mpsw.h"
#include "../lib/bcrypt/bcrypt.h"
#include "user.h"

#define DB_HOST  ""
#define DB_USER  ""
#define DB_PASS  ""
#define DB_NAME  ""

int main(int argc, char *argv[]) {
    MYSQL *mysql;
    struct spergs_user *authuser;
    int c;
    char *username, *password;

    while ((c = getopt(argc, argv, "u:p:")) != -1) {
        switch(c) {
            case 'u':
                username = optarg;
                break;
            case 'p':
                password = optarg;
                break;
            default:
                printf("Invalid Option: %d\n", c);
                exit(EXIT_FAILURE);
        }
    }

    if (argc < 4) {
        printf("Usage: %s -u [username] -p [password]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
 
    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "Could not initialize MySQL libary\n");
        exit(EXIT_FAILURE);
    }

    mysql = mysql_init(NULL);
   
    if (mysql_real_connect(mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "No connection could be made to the database");
        return -1;
    } else {
        // Database connection available, do cool stuff
        authuser = user_init(mysql);
        user_authenticate(authuser, username, password);
        user_free(authuser);
    }

    mysql_close(mysql);
    mysql_library_end();
    exit(EXIT_SUCCESS);
}
