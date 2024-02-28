#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

int main()
{
    sqlite3 *mydb = NULL;
    /* 打开数据库 */
    int ret = sqlite3_open("test.db", &mydb);

    
    if (ret != SQLITE_OK)
    {
        perror("open error");
        exit(-1);
    }

    char * errormsg = NULL;
    /* 创建一个表 create table 表名 */
    const char * sql = "create table if not exists user(id int primary  key not NULL, age int not NULL, name char not NULL)";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3 error:%s\n", errormsg);
        exit(-1);
    }

    /* 插入数据 */
    sql = "insert into user values (1001, 20, 'zhangsan')";
    sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3 error:%s\n", errormsg);
        exit(-1);
    }

    /* 查询数据 */
    char **result = NULL;
    int row = 0;
    int column = 0;
    sql = "select * from user";
    ret = sqlite3_get_table(mydb, sql, &result, &row, &column, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3 error:%s\n", errormsg);
        exit(-1);
    }
    /* row 和column就是表格的大小 有几行几列 */
    printf("row : %d\tcolumn:%d\n", row, column);

    for (int idx = 0; idx < row + 1; idx++)
    {
        for (int jdx = 0; jdx < column; jdx++)
        {
            printf("%s\t", result[idx * column + jdx]);
        }
        printf("\n");
    }

#if 0
    /* 删除表 drop table 表名 */
    sql = "drop table user";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3 error:%s\n", errormsg);
        exit(-1);
    }
#endif

    /* 更新表的数据 */
    sql = "update user set name = 'wangjunkai' where id = 1";

    /* 关闭数据库 */
    sqlite3_close(mydb);

    return 0;
}