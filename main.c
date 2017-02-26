#include <stdio.h>
#include <stdlib.h>
#include "UP_CMD.h"
int main()
{
    FILE *fin;
    //char RW,proc_id;
    int addr,data,RW,proc_id;
    upReq_t up1,up;
    //char *fs;
	//int data;
    //upReq_t new_cmd;
    fin=fopen("in.txt","r");
    //get_processor_cmd(fin,&new_cmd);
    //printf("%d 0x%x %d 0x%x\n",new_cmd.proc_id,new_cmd.addr,new_cmd.RW,new_cmd.data);
  //  fscanf(fin,"%d 0x%x %d 0x%x\n",&proc_id,&addr,&RW,&data);
    //printf("%d 0x%x %d 0x%x\n",proc_id,addr,RW,data);

    while(fscanf(fin,"%d 0x%x %d 0x%x\n",&proc_id,&addr,&RW,&data)!=EOF)
    {

        //while(data_busy);
        up.addr=addr;
        up.proc_id=proc_id;
        up.RW=RW;
        up.data=data;
        if(RW==0)
        {
            up.data=data;
        }
        else
        {
            up.data=NULL;
        }

        printf("%d 0x%x %d 0x%x\n",up.proc_id,up.addr,up.RW,up.data);
        if(proc_id==1)
        {


        }
        else
        {


        }
    }
    fflush(fin);
    fclose(fin);
    return 0;
}
//format proc_ID address r/wbar data
//example: 1      0xaf5    1     0xaf00
//for read, data is 0
int get_processor_cmd(FILE *fin,upReq_t *new_cmd)
{

    if(fscanf(fin, "%d 0x%x %d 0x%x\n", new_cmd->proc_id,new_cmd->addr,new_cmd->RW,new_cmd->data ) != EOF)
        return 1;
    else
        return 0;
}



