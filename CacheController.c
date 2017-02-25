

////////////////////////////////////////////////////
// CacheController.c
//
//
////////////////////////////////////////////////////

#include "CacheController.h"

unsigned char CacheRead(ccheCtrl_t cc)
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
}

unsigned char CacheWrite(ccheCtrl_t cc)
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
}

// This function gets the input from the processor's request 
char CacheCtrllr(upReq_t up)	
{
	static ccheCtrl_t cc;				// initialize the cahce controller 
	static cache_t cacheMem[256];	// initialize the cache memory 
	static unsigned char snoop = 0;	// flag used to check if the data is to be written in the cache after the read miss
	
	unsigned char res;
	
	// load the values of tag, index and R/W# from the data given by the processor
	cc.index = up.addr;
	cc.tag = up.addr;		
	cc.RW = up.RW;		// Read operation 
	cc.RW ? (up.data = cc.data):(cc.data = up.data);		// read/write the data from processor/memory
	
	// Check if the operaiton to be done is read
	if(cc.RW == READ)
		res = CacheRead(cc);
	else
		res = CacheWrite(cc);
	
	return res;
}