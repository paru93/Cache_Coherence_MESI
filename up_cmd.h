#ifndef UP_CMD
#define UP_CMD
typedef struct
{
	char proc_id;
	int addr;
	char RW;
	int data;
}upReq_t;
int get_processor_cmd(FILE *fin,upReq_t *new_cmd);
int data_busy=0;
#endif // UP_CMD


