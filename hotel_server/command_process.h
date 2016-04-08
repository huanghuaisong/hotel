#ifndef CMDMAND_PROCESS_H
#define CMDMAND_PROCESS_H
#include "define.h"
#include <string.h>
#include "c_socket.h"
typedef struct cmd_process
{
   int  cmd;
   void* (*cmd_handle)(int ,void *,client_config_t *); 
}CMD_PROCESS_T;
extern CMD_PROCESS_T g_cmd_list[];

// ×¢²á´¦Àí
void* do_register(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_login(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_send_room_data_to_phone(int c_sid,void *data,client_config_t *cli_cfg_info);
void *do_user_room_reservation(int c_sid,void *data,client_config_t *cli_cfg_info);
void *do_cancel_user_room_reservation(int c_sid,void *data,client_config_t *cli_cfg_info); 
void* do_change_passwd(int c_sid,void *data,client_config_t *cli_cfg_info);
 
 void show_list();

#endif
