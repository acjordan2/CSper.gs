#include <string.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include "../lib/mpsw/mpsw.h"
#include "../lib/bcrypt/bcrypt.h"
#include "user.h"

#define BCRYPT_WORKFACTOR 12

int spergs_authenticate(struct spergs_user *authuser, char *password) {
    MYSQL_STMT *stmt;
    const char *query;
    char field_data[1][STRING_SIZE], **result_data;
    unsigned long *field_length, *data_length;
    int num_rows = 0;

    char user_hash[BCRYPT_HASHSIZE];
    char salt[BCRYPT_HASHSIZE];
    char hash[BCRYPT_HASHSIZE];
    int ret;

    strncpy(field_data[0], authuser->username, STRING_SIZE);

    query = "SELECT `user_id`, `password` FROM `Users` WHERE `username` = ?";   
    if ((stmt = mysql_stmt_init(authuser->mysql)) == 0) {
        return -1;
    }

    if ((mpsw_stmt_prepare(stmt, query, field_data, &field_length, &result_data, &data_length)) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return -1;
    }
    mysql_stmt_execute(stmt);

    while (mysql_stmt_fetch(stmt) == 0) {
        strncpy (user_hash, result_data[1], BCRYPT_HASHSIZE); 
        num_rows++;
    }

    if (num_rows == 0) {
        return 0;
    }

    printf("%s", user_hash);

}
