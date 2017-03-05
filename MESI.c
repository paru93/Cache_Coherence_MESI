

////////////////////////////////////////////////////
// CacheController.c
//
//
////////////////////////////////////////////////////

#include "includes.h"

//Before calling MESI,match the tag value in the cache controller
void MESICtrllr(CacheCtrl_t cc,unsigned char HIT,unsigned char memRd, unsigned char Read, unsigned char Write,
            CacheMem_t *CacheMem)
{
    MESI_t nextState;

	//If the tag are not equal, the data for that tag is either not present
	//or eviction for the same tag has not takedn place
	//When there are no read/write signals generated from the cache controller,
	//The cache will change state as per snooping else based on R/W from CPU and HIT/HITM
	if((Read == 0) && (Write == 0))
	{
		switch(CacheMem->mesi)
		{
			case I: if((cc.rw == READ) && (HIT && memRd))
						nextState = S;
					else if((cc.rw == READ) && (!HIT && memRd))
						nextState = E;
                    // This case will not arise because in invalid the Read/Write flags are set before entering
                    // this loop
					//else if(cc.RW == WRITE)
					//	nextState = M;
					break;

			case S:	if(cc.rw == READ)
						nextState = S;
					else    // in case of write
						nextState = M;
					break;

			case E:	if(cc.rw == READ)
						nextState = E;
					else
						nextState = M;
					break;

			case M:	nextState = M;
					break;

		}
	}

	else if(Read || Write)
	{
		switch(CacheMem->mesi)
		{
			case I:	nextState = I;
					break;

			case S: if(Read)
                      nextState = S;
                    else if(Write)
                      nextState = I;
                    break;

			case E: if(Read)
                      nextState = S;
					else if(Write)
                      nextState = I;
                    break;

			case M: if(Read)
                      nextState = S;
					else if(Write)
                      nextState = I;
                    break;
		}
	}
	CacheMem->mesi = nextState;
}

