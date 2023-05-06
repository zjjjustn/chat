#include<sqlite3.h>

sqlite3 ** p_db;

int chat_open_db(const char * db_flie_path);

int chat_exec_sql(const char *sql,sqlite3_callback callback,void *callback_arg,char **errmsg);

int chat_query_table(const char *sql,char ** result,int *row,int *col,char **errmsg);

void chat_free_result(char **result);

void chat_close_db();