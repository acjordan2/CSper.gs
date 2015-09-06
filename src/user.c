#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <assert.h>
#include "../lib/mpsw/mpsw.h"
#include "../lib/bcrypt/bcrypt.h"
#include "user.h"

#define BCRYPT_WORKFACTOR 10

struct spergs_user *user_init(MYSQL *mysql) {
    struct spergs_user *authuser = malloc(sizeof(struct spergs_user));
    authuser->mysql = mysql;
    return authuser;
}

int user_authenticate(struct spergs_user *authuser, char *username, char *password) {
    MYSQL_STMT *stmt;
    const char *query;
    char field_data[1][STRING_SIZE], **result_data;
    unsigned long *field_length, *data_length;
    int num_rows = 0;

    char user_hash[BCRYPT_HASHSIZE];
    char hash[BCRYPT_HASHSIZE];
    int user_id;
    
    int ret;

    strncpy(field_data[0], username, STRING_SIZE);

    query = "SELECT `user_id`, `password`, `email`, `private_email` FROM `Users` WHERE `username` = ?";   
    if ((stmt = mysql_stmt_init(authuser->mysql)) == 0) {
        return -1;
    }

    if ((mpsw_stmt_prepare(stmt, query, field_data, &field_length, &result_data, &data_length)) != 0) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return -1;
    }
    mysql_stmt_execute(stmt);

    while (mysql_stmt_fetch(stmt) == 0) {
        user_id = atoi(result_data[0]);
        strncpy (user_hash, result_data[1], BCRYPT_HASHSIZE); 
        num_rows++;
    }
    
    mysql_stmt_free_result(stmt);
    mpsw_stmt_free(&result_data, mysql_stmt_field_count(stmt), &field_length, &data_length);
    mysql_stmt_close(stmt);

    if (num_rows == 0) {
        printf("Login failed");
        authuser->username = username;
        return 0;
    }

    ret = bcrypt_hashpw(password, user_hash, hash);
    assert(ret == 0);

    if (strcmp(user_hash, hash) == 0) {
        authuser->user_id = user_id;
        authuser->username = username;
        printf("User ID: %d\n", authuser->user_id);
        printf("Username: %s\n", authuser->username);
        printf("Success\n");
        return 1;
    } else {
        printf("Invalid Login Credentials\n");
        printf("%s\n", hash);
        printf("%s\n", user_hash);
        return 0;
    }
}

int user_free(struct spergs_user *authuser) {
    free(authuser);
    return 0;
}
