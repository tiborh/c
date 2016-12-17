#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <my_global.h>
#include <mysql.h>

typedef struct
{
    char host[20];
    char user[25];
    char pass[50];
}DB_CONN_PARAMS;

MYSQL * connect_db(DB_CONN_PARAMS *params)
{
    MYSQL *connection = mysql_init(NULL);//init connection
    if (connection == NULL)
    {//check init worked
        fprintf(stderr, "%s\n", mysql_error(connection));
        exit(EXIT_FAILURE);
    }
    //connect:
    if (mysql_real_connect(
            connection,
            params->host,
            params->user,
            params->pass,
            NULL,0,NULL,0)
        ==NULL)
    {//connection failed?
        fprintf(stderr, "%s\n", mysql_error(connection));
        mysql_close(connection);
        exit(EXIT_FAILURE);
    }
    return connection;
}

int main()
{
    MYSQL *db;
    DB_CONN_PARAMS *params = calloc(1,sizeof(DB_CONN_PARAMS));
    //just an alternative way of passing connection params, find a struct easier
    strcpy(params->host,"127.0.0.1");
    strcpy(params->user,"etibhar");
    strcpy(params->pass,"Aikotoba12.");
    MYSQL * connect_db(DB_CONN_PARAMS *params);
    db = connect_db(params);
    //we don't need the struct anymore
    free(params);
    params = NULL;
    //do stuff
    mysql_close(db);//close connection, of course!
    return EXIT_SUCCESS;
}
