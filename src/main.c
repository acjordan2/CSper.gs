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
 
    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "Could not initialize MySQL libary\n");
        return -1;
    }

    mysql = mysql_init(NULL);
   
    if (mysql_real_connect(mysql, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "No connection could be made to the database");
        return -1;
    } else {
        // Database connection available, do cool stuff
        struct spergs_user authuser;
        authuser.username = "";
        authuser.mysql = mysql;   
        spergs_authenticate(&authuser, "");
    }
    printf("test");
}
