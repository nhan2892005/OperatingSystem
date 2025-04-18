#include "bktpool.h"

int bktpool_init()
{
   bkwrk_init_shared_memory();
   return bkwrk_create_worker();
} 
