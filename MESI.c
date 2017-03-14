
///////////////////////////////////////
// File Name: MESI.c
// Author: Chetan
//
///////////////////////////////////////

#include "includes.h"

//Before calling MESI,match the tag value in the cache controller
void MESICtrllr(unsigned char Mstr_nSlv, unsigned char Opr, unsigned char *state, unsigned char Hit)
{


	//If the tag are not equal, the data for that tag is either not present
	//or eviction for the same tag has not takedn place
	//When there are no read/write signals generated from the cache controller,
	//The cache will change state as per snooping else based on R/W from CPU and HIT/HITM
	if(Mstr_nSlv == MASTER)
	{
		switch(*state)
		{
			case I: if((Opr == READ) && Hit)
						*state = S;
					else if((Opr == READ) && !Hit)
						*state = E;
                    else if(Opr == WRITE)
                        *state = M;
					break;

		 	case S:	if(Opr == READ)
						*state = S;
					else    // in case of write
						*state = M;
					break;

			case E:	if(Opr == READ)
						*state = E;
					else
						*state = M;
					break;

			case M:	*state = M;
					break;
		}
	}

	else // Slave
	{
		switch(*state)
		{
			case I:	*state = I;
					break;

			case S: if(Opr == READ)
                      *state = S;
                    else if(Opr == WRITE)
                      *state = I;
                    break;

			case E: if(Opr == READ)
                      *state = S;
					else if(Opr == WRITE)
                      *state = I;
                    break;

			case M: if(Opr == READ)
                      *state = S;
					else if(Opr == WRITE)
                      *state = I;
                    break;
		}
	}
}

