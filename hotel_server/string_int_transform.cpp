#include "string_int_transform.h"
#include <stdio.h>
#include <assert.h>
#define ABS(cond) (cond>0?cond:-cond) 
int my_atoi(const char *str){  
    //argument check first!   
    assert(NULL != str);  
    int ret=0,sign=1;  
    //skip tab and space   
    for(; *str==' '||*str=='\t'; str++);  
    if(*str == '-')sign = -1;  
    if(*str == '-' || *str == '+')str++;  
    while(isdigit(*str)){  
        ret = ret*10 + *str - '0';  
        str++;  
        }  
    return sign*ret;  
} 

char *my_itoa(int value,char *string,int radix)  
{  
    assert(string!=NULL);  
    char tmp[32]={'\0'};  
    int tmpval=ABS(value);  
    int i,j;  
    for(i=0;i<32;i++)  
    {                  
        tmp[i]=(tmpval%radix)+'0';  
        tmpval=tmpval/radix;  
        if(tmpval==0)  
            break;  
    }  
    if(value<0)tmp[++i]='-';  
    for(j=0;i>=0;i--)  
         string[j++]=tmp[i];  
    string[j]='\0';  
    return string;  
}  

