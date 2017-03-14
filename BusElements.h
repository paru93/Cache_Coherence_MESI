///////////////////////////////////////
// File Name: BusElements.h
// Author: Chetan
//
///////////////////////////////////////

#ifndef BUSELEMENTS_H_INCLUDED
#define BUSELEMENTS_H_INCLUDED

enum
{
    S0, S1
};

unsigned char CacheCtrllr(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done, unsigned char *InvalidateSig);

unsigned char CacheCtrllr2(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done, unsigned char *InvalidateSig);

unsigned char CacheCtrllr3(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done, unsigned char *InvalidateSig);

unsigned char CacheCtrllr4(unsigned int addr, unsigned char upData, unsigned char upRW,
                          unsigned char *done, unsigned char *InvalidateSig);

unsigned char SharedMemRd(unsigned int addr);

#endif // BUSELEMENTS_H_INCLUDED
