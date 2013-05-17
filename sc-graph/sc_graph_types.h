#ifndef _sc_graph_types_h_
#define _sc_graph_types_h_

#include "sc_graph_prerequest.h"

typedef struct _sc_addr_list sc_addr_list;

struct _sc_addr_list
{
    sc_addr_list *next;
    sc_addr_list *prev;
    sc_addr value;
};

/*! Append sc-addr to list. New item inserts into the begin of the list
 * \param list Pointer to start of the list. If this pointer is null, then function create new list.
 * \return Returns pointer to new list begin item.
 * \note The return value is the new start of the list, which may have changed, so make sure you store the new value.
 */
sc_addr_list* sc_addr_list_append(sc_addr_list *list);

/*! Return next element in sc_addr_list
 * \param item Pointer to current list item
 * \return Returns next to \p item element. If \p item is the last one, then return null pointer
 */
sc_addr_list* sc_addr_list_next(sc_addr_list *item);


#endif // _sc_graph_types_h_
