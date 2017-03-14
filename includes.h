///////////////////////////////////////
// File Name: includes.h
// Author: Chetan 
// 
///////////////////////////////////////

#ifndef INCLUDES_H
#define INCLUDES_H

#include "CacheMemAddrCheck.h"
#include "cache_controller.h"
#include "cache_mem.h"
#include "CacheOperation.h"
#include "BusElements.h"
#include "Bus.h"

// Memory operation which will be done
enum
    {
        MASTER = 1,
        SLAVE = 0
    };


#endif // INCLUDES_H
