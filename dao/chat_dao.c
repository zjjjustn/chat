#include"chat_dao.h"
#include<stdlib.h>
#include<stdio.h>

int chat_open_db(const char * db_flie_path)
{
    int ret = sqlite3_open(db_flie_path,&p_db);
    if(ret != SQLITE_OK)
    {
        printf("open sqlite :%s fault!\n");
        return -1;
    }
    return ret;
}

int chat_exec_sql(const char *sql,sqlite3_callback callback,void *callback_arg,char **errmsg)
{
    int ret = sqlite3_exec(p_db,sql,callback,callback_arg,errmsg);
    return ret;
}

int chat_query_table(const char *sql,char ** result,int *row,int *col,char **errmsg)
{
    return sqlite3_get_table(p_db,sql,&result,row,col,errmsg);
}

void chat_free_result(char **result)
{
    sqlite3_free_table(result);
}

void chat_close_db()
{
    sqlite3_close(p_db);
}