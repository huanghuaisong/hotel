//#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "server_management.h"
#include "define.h"
#include "server_data.h"
//#include "mysql.h"
using namespace std;
int main()
{
  //init_sql();//连接数据库等
  //display_select(conn);//从数据库加载数据到链表
	//  init_group_info(conn);
   //display_group_info(conn);
    init_server();
    return 0;
}

