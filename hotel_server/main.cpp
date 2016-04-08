#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include "server_management.h"
#include "define.h"
#include "server_data.h"
#include "mysql.h"
#include "command_process.h"
using namespace std;
int main()
{
    init_sql();//connect to mysql
  	//create_room_data();
    load_room_data_from_mysql_database(conn);
    load_user_data_from_mysql_database(conn);
	show_list();
    init_server();
    return 0;
}

