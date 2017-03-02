

////////////////////////////////////////////////////
// CacheController.c
//
//
////////////////////////////////////////////////////

#include "CacheController.h"

void CacheRead(int tag,int index,MESI_t state,ccheCtrl_t cc)
{
	if(state==I)
	{
		//Read from the memory
		Read=1;
		memRd=1;
		
	}
	else if(cc.tag==tag)
		Dataout=cacheMem[index].data;
	else if(cc.tag!=tag)
	{
		//Evict the data from the location
			if(cacheMem[index].MESI==M)
			{
				wMemData=cacheMem[index].data;
				memwrite=1;
				memRd=1;
			}
		//Read from memory
		Read=1;	
	}
	
}
void CacheWrite(int tag,int index,int data)
{
	if(tag==cacheMem[index].tag)
	{
		write=1;
	}
	//tags do not match
	else
	{
		if(cacheMem[index].MESI=M)
		{
			wMemData=cacheMem[index].data;
			
		}
		memwrite=1;
		write=1;
	}
	CacheMem[index].data=data;
	write=1;
	
}


/*unsigned char CacheRead(ccheCtrl_t cc)
{
	if(cc.RW)		// On read operation this will be high
	{
		if(cacheMem[cc.index].MESI == I)	// check if the state is invalid 
		{
			// if invalid then return that no address matches 
			// Read from the memory
			// After data fetched from memory then update the cache block address 
			cc.RW = WRITE; 	// after the data from the mem is fetched then it will be written in the cache 
			snoop = 1;		// Set the flag to enable the write w/o read 
			return NOTFOUND_IN_CACHE;
		}
		else	
		{
			if(cacheMem[cc.index].tag == cc.tag)	// Check if the tag address match
				cc.data = cacheMem[cc.index].data;	// the data is in cache. It may be in either Modified state, Exclusive state or Shared state 
			else
			{
				cc.RW = WRITE;						// Must have been evicted from the cache memory 
				return NOTFOUND_IN_CACHE;
			}
		}
	}
	return FOUND_IN_CACHE;
}*/

/*unsigned char CacheWrite(ccheCtrl_t cc)
{
	if(cc.RW == WRITE) // cache write 
	{
		if(snoop)		// check if the write 
		{
			cc.data = MemData;		// store the data read from the memory
			cacheMem[cc.index].data = cc.data;
			cacheMem[cc.index].MESI = E;		// the state changes from Invalid to exclusive 
			snoop = 0;				// clear the snooping flag 
		}
		else 
		{
			// CHANGE TO SWITCH CASE 
			// Check if data is present in the cache 
			if((cacheMem[cc.index].MESI == I) || 
			   (cacheMem[cc.index].tag != cc.tag))	
					// READ FROM MEMORY
			else
			{
				cacheMem[cc.index].data = cc.data;		// the location found in cache overwrite the data present in the cache 
				cacheMem[cc.index].MESI = M;
			}
		}
		
	}
	return cc.data;		// return the data to the processor 
}*/

// This function gets the input from the processor's request 
char CacheCtrllr(upReq_t up)	
{
	static ccheCtrl_t cc;				// initialize the cahce controller 
	static cache_t cacheMem[256];	// initialize the cache memory 
	static unsigned char snoop = 0;	// flag used to check if the data is to be written in the cache after the read miss
	
	unsigned char res;
	MESI_t state;
	// load the values of tag, index and R/W# from the data given by the processor
	cc.index = up.addr;
	cc.tag = up.addr;		
	cc.RW = up.RW;		// Read operation 
	cc.RW ? (up.data = cc.data):(cc.data = up.data);		// read/write the data from processor/memory
	//*********Check the code bellow **********************************************
	//This will cause a problem if the tag value is checked before calling MESI
	//For instance when the cache is in the invalid state, the tag values coming from
	//cpu will not obviously match hence there will be no state transition for that.
	if(cc.tag==cacheMem[cc.index].tag)
	{
	 cacheMem[cc.index].MESI=MESI(ccheCtrl_t cc,HIT,memRd,cacheMem[cc.index].MESI);
	}	
	
	
	// Check if the operation to be done is read
	if(cc.RW == READ)
		res = CacheRead(cc);
	else
		res = CacheWrite(cc);
	
	return res;
}