

////////////////////////////////////////////////////
// CacheController.c
//
//
////////////////////////////////////////////////////

#include "CacheController.h"
#include "cachemem.h"
#include "upcmd.h"

//Before calling MESI,match the tag value in the cache controller
MESI_t MESI(ccheCtrl_t cc,int HIT,int memRd,MESI_t state)
{
	//If the tag are not equal, the data for that tag is either not present 
	//or eviction for the same tag has not takedn place
	//When there are no read/write signals generated from the cache controller,
	//The cache will change state as per snooping else based on R/W from CPU and HIT/HITM 
	if((Read==0) &&  (Write==0)) 
	{
		switch(state)
		{
			case I: if((cc.RW==1) && (HIT&&memRd))
						return S;
					else if((cc.RW==1)&&(~HIT)&&(memRd))
						return E;
					else
						return M;//Verify(when cc.RW==0)
					//break;
			case S:	if(((cc.RW==1))
						return S;
					else
						return M;
					//break;	
			case E:	if(((cc.RW==1))
						return E;
					else
						return M;
					//break;
			case M:	return M;
					//break;			
			/*if(((cc.RW==0))
					cacheMem[cc.index].MESI=M;*/
					
		}
	}
	//Read and 
	else if((Read!=0) || (Write!=0))
	{
		switch(state)
		{
			case I:	return I;
					//Read=1;
				//break;		
			case S:if(Read==1)	
						return S;
					else if(Write==1)
						return I;
			case E:if(Read==1)	
						return S;
					else if(Write==1)
						return I;
			case M:if(Read==1)	
						return S;
					else if(Write==1)
						return I;
							
		}
	}		
}
