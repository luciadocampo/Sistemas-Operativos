#ifndef __STRUCT_LISTAS_H__
#define __STRUCT_LISTAS_H__

#include "list.h"

struct Listas{
     list command_list;
     list malloc_list;
     list mmap_list;
     list shared_list;
};

#endif
