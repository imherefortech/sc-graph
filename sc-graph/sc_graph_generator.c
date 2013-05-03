#include "sc_graph_generator.h"
#include "sc_graph_keynodes.h"

sc_bool sc_graph_generate_empty(sc_addr *graph)
{
    *graph = sc_memory_node_new(sc_type_node_struct | sc_type_node | sc_type_const);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_graph, *graph);

    return SC_TRUE;
}
