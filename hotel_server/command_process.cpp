#include "command_process.h"
#include "protocol.h"
#include "cJSON.h"
#include "server_data.h"
#include <string.h>
#include <unistd.h>
//void *memcpy(void *dest, const void *src, size_t n);

unsigned long  register_id = 123456;
CMD_PROCESS_T g_cmd_list[] =
{
    {USER_REGISTER,         do_register},
	{LOGIN,                 do_login},
    {-1,NULL}
};

void* do_register(int c_sid,void *data,client_config_t *cli_cfg_info)
{
	msg_t genmsg_rep;
	memset(&genmsg_rep,0,sizeof(genmsg_rep));
	reg_t *reg=(reg_t *)data;
	if(strcmp(reg->usr_name,"huanghuaisong")==0 && strcmp(reg->usr_passwd,"123456")==0)
	{	
		cJSON * register_json = NULL;
		register_json = cJSON_CreateObject();
		if(NULL == register_json)
		{
			//error happend here
			plog("cJSON_CreateObject error ");
			return NULL;
		}
		cJSON_AddStringToObject(register_json, "ok", "hello world");
		cJSON_AddNumberToObject(register_json, "ack", 10010);
		char send_buffer[1024];
		memcpy(send_buffer,cJSON_Print(register_json),strlen(cJSON_Print(register_json)));
		write(c_sid,send_buffer,sizeof(send_buffer));
	}
}

void* do_login(int c_sid,void *data,client_config_t *cli_cfg_info)
{
	msg_t genmsg_rep;
	memset(&genmsg_rep,0,sizeof(genmsg_rep));
	reg_t *reg=(reg_t *)data;
	if(strcmp(reg->usr_name,"huanghuaisong")==0 && strcmp(reg->usr_passwd,"123456")==0)
	{	
		cJSON * register_json = NULL;
		register_json = cJSON_CreateObject();
		if(NULL == register_json)
		{
			//error happend here
			plog("cJSON_CreateObject error ");
			return NULL;
		}
		cJSON_AddStringToObject(register_json, "ok", "hello world");
		cJSON_AddNumberToObject(register_json, "ack", 10010);
		char send_buffer[1024];
		memcpy(send_buffer,cJSON_Print(register_json),strlen(cJSON_Print(register_json)));
		write(c_sid,send_buffer,sizeof(send_buffer));
	}

}


