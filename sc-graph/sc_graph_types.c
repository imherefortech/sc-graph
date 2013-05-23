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

sc_addr_list* sc_addr_list_remove(sc_addr_list *item)
{
    if (item->next != nullptr)
        item->next->prev = item->prev;
    if (item->prev != nullptr)
        item->prev->next = item->next;

    sc_addr_list *r = item->next;
    free(item);

    return r;
}

sc_bool sc_addr_list_is_included(sc_addr_list *head, sc_addr elem)
{
    do {
        if (SC_ADDR_IS_EQUAL(head->value, elem) == SC_TRUE)
            return SC_TRUE;
    } while((head = sc_addr_list_next(head)) != nullptr);

    return SC_FALSE;
}
