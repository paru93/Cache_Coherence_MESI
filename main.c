///////////////////////////////////////
// File Name: main.c
// Author: Chetan
//
///////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "includes.h"

// Flow of Program
// Instruction read from text file
// As per processor ID it is used to select the cache controller
// The cache controller:
//      1. Check if the address is present in cache
//      2. If address found then read/write data
//      3. If address not found then read from other cache
//      4. After data read from other cache update the requested cache



// Variables
unsigned char shareData = 0;
unsigned char lookInOthrSrc = 0;
unsigned char DataFrmMem = 0;
unsigned int  MissCounter = 0;

//

int main()
{
    unsigned int addr = 0;
    unsigned int upData = 0;
    unsigned int upRW = 0;
    unsigned int procId = 0;

    FILE *fin;
    fin = fopen("instr.txt","r");
    if(fin == 0)
        printf("File not open\n");

    printf("proc_ID address RW# data\n");

    while(fscanf(fin,"%d 0x%x %d 0x%x\n",&procId,&addr,&upRW,&upData) != EOF)
    {
        printf("%d 0x%x %d 0x%x\n",procId,addr,upRW,upData);
        switch(procId)
        {
            case 1: Bus(CACHECTRL1, addr, upData, upRW);
                    break;

            case 2: Bus(CACHECTRL2, addr, upData, upRW);
                    break;

            case 3: Bus(CACHECTRL3, addr, upData, upRW);
                    break;

            case 4: Bus(CACHECTRL4, addr, upData, upRW);
                    break;

            default: printf("No processor found\n");
        }
    }
    printf("Total Miss: %d", MissCounter);  // display the number of times the memory had to be accessed

    return 0;
}
