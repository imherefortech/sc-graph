#include "sc_graph_types.h"

#include <stdlib.h>
#include <memory.h>

sc_addr_list* sc_addr_list_append(sc_addr_list *list)
{
    sc_addr_list *res = malloc(sizeof(sc_addr_list));

    memset(res, 0, sizeof(sc_addr_list));

    if (list != nullptr)
        list->prev = res;
    res->next = list;

    return res;
}

sc_addr_list* sc_addr_list_next(sc_addr_list *item)
{
    return item->next;
}

