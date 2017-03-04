

/////////////////////////////////////////////////////////
// File Name: Shared memory.c
//
// This function is the representation of the shared memory
// Parameters: Addr, Data, RW#
// 
// If the data is to be accessed from this memory block 
// then there is a delay. After the delay is exceeded the 
// data is available for read/write.
// 
////////////////////////////////////////////////////////

void SharedMem(int Addr, unsigned char data, char RW)
{
	static unsigned char mem[1024] = {0};
	static unsigned char cnt = 0;	// count for the delay 
	unsigned short delaycnt = 0;
	
	if(cnt < 5) 
	  for(delaycnt = 0; delaycnt < 1000000; delaycnt++);
	else
    {
		if(RW)		// for read operation
		{
			return mem[Addr];		// return the data requested from teh mem
		}
		else		// for write operation
		{
			mem[Addr] = data;		// write the data in the memory 
		}
	}	
	return 
}