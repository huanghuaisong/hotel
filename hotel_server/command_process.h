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
void* do_add_friend1(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_add_friend2(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_init_friend_list(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_init_group_list(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_init_group_member_list(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_del_friend(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_notify_state(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_update_friend(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_update_group(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_get_head_num(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_chat_p2p(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_offline_msg(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_creat_group(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_del_group(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_join_group_1(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_join_group_2(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_exit_group(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_group_chat(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_login(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_download_file(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_upload_file(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_change_passwd(int c_sid,void *data,client_config_t *cli_cfg_info);
void* do_set_headnum(int c_sid,void *data,client_config_t *cli_cfg_info);

#endif
