#include "sc_graph_keynodes.h"

#include <string.h>
#include <stdio.h>

sc_addr sc_graph_keynode_graph;
sc_addr sc_graph_keynode_not_oriented_graph;
sc_addr sc_graph_keynode_oriented_graph;
sc_addr sc_graph_keynode_rrel_vertex;
sc_addr sc_graph_keynode_rrel_edge;
sc_addr sc_graph_keynode_rrel_arc;

const char sc_graph_keynode_graph_str[] = "graph_graph";
const char sc_graph_keynode_not_oriented_graph_str[] = "graph_not_oriented_graph";
const char sc_graph_keynode_oriented_graph_str[] = "graph_oriented_graph";
const char sc_graph_keynode_rrel_vertex_str[] = "graph_rrel_vertex";
const char sc_graph_keynode_rrel_edge_str[] = "graph_rrel_edge";
const char sc_graph_keynode_rrel_arc_str[] = "graph_rrel_arc";


#define resolve_keynode(keynode, type) \
    if (sc_helper_resolve_system_identifier(keynode##_str, &keynode) == SC_FALSE) \
    { \
        printf("Create keynode: %s\n", keynode##_str); \
        keynode = sc_memory_node_new(sc_type_node | type); \
        sc_helper_set_system_identifier(keynode, (sc_char*)keynode##_str, strlen(keynode##_str)); \
    }

sc_bool sc_graph_initialize_keynodes()
{
    // try to resolve keynode
    resolve_keynode(sc_graph_keynode_graph, sc_type_node_struct);
    resolve_keynode(sc_graph_keynode_not_oriented_graph, sc_type_node_struct);
    resolve_keynode(sc_graph_keynode_oriented_graph, sc_type_node_struct);
    resolve_keynode(sc_graph_keynode_rrel_vertex, sc_type_node_role);
    resolve_keynode(sc_graph_keynode_rrel_edge, sc_type_node_role);
    resolve_keynode(sc_graph_keynode_rrel_arc, sc_type_node_role);

    return SC_TRUE;
}
