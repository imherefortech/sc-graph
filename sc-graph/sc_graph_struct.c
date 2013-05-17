#include "sc_graph_struct.h"
#include "sc_graph_keynodes.h"



sc_result sc_graph_create_vertex(sc_addr graph, sc_addr *vertex)
{
    sc_addr arc;

    if (SC_ADDR_IS_EMPTY(graph))
        return SC_RESULT_ERROR_INVALID_PARAMS;

    *vertex = sc_memory_node_new(sc_type_node | sc_type_const);
    arc = sc_memory_arc_new(sc_type_arc_pos_const_perm, graph, *vertex);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_rrel_vertex, arc);

    return SC_RESULT_OK;
}

sc_result sc_graph_create_arc(sc_addr graph, sc_addr v1, sc_addr v2, sc_addr *arc)
{
    sc_addr a, rrel_keynode;
    sc_type arc_type = 0;

    // first of all check if v1 and v2 are verticies of graph structure
    if (sc_graph_check_element(graph, v1) != SC_RESULT_OK)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    if (sc_graph_check_element(graph, v2) != SC_RESULT_OK)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    // determine graph type
    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
    {
        arc_type = sc_type_edge_common;
        rrel_keynode = sc_graph_keynode_rrel_edge;
    }
    else if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
    {
        arc_type = sc_type_arc_common;
        rrel_keynode = sc_graph_keynode_rrel_arc;
    }
    else return SC_RESULT_ERROR_INVALID_PARAMS;

    // generate element
    *arc = sc_memory_arc_new(arc_type | sc_type_const, v1, v2);
    a = sc_memory_arc_new(sc_type_arc_pos_const_perm, graph, *arc);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, rrel_keynode, a);

    return SC_RESULT_OK;
}

sc_result sc_graph_check_vertex(sc_addr graph, sc_addr vertex)
{
    if (sc_helper_check_arc(sc_graph_keynode_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    // check if vertex created correctly
    sc_iterator5 *it5 = sc_iterator5_f_a_f_a_f_new(graph,
                                                   sc_type_arc_pos_const_perm,
                                                   vertex,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_graph_keynode_rrel_vertex);
    int count = 0;
    while (sc_iterator5_next(it5) == SC_TRUE)
        count++;

    sc_iterator5_free(it5);

    return count == 1 ? SC_RESULT_OK : SC_RESULT_ERROR;
}

sc_result sc_graph_check_arc(sc_addr graph, sc_addr arc)
{
    sc_addr arc_type;

    if (sc_helper_check_arc(sc_graph_keynode_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
    {
        arc_type = sc_graph_keynode_rrel_edge;
    }
    else if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
    {
        arc_type = sc_graph_keynode_rrel_arc;
    }
    else return SC_RESULT_ERROR_INVALID_PARAMS;

    // check if arc created correctly
    sc_iterator5 *it5 = sc_iterator5_f_a_f_a_f_new(graph,
                                                   sc_type_arc_pos_const_perm,
                                                   arc,
                                                   sc_type_arc_pos_const_perm,
                                                   arc_type);
    int count = 0;
    while (sc_iterator5_next(it5) == SC_TRUE)
        count++;

    sc_iterator5_free(it5);

    return count == 1 ? SC_RESULT_OK : SC_RESULT_ERROR;
}

sc_result sc_graph_check_element(sc_addr graph, sc_addr element)
{
    if (sc_graph_check_vertex(graph, element) == SC_RESULT_OK)
        return SC_RESULT_OK;

    if (sc_graph_check_arc(graph, element) == SC_RESULT_OK)
        return SC_RESULT_OK;

    return SC_RESULT_ERROR;
}

sc_result sc_graph_check_elements_adjacency(sc_addr graph, sc_addr v1, sc_addr v2)
{
    sc_type arc_type;
    if (sc_graph_check_element(graph, v1) != SC_RESULT_OK)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    if (sc_graph_check_element(graph, v2) != SC_RESULT_OK)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
    {
        arc_type = sc_type_edge_common | sc_type_const;
    }
    else if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
    {
        arc_type = sc_type_arc_common | sc_type_const;
    }
    else return SC_RESULT_ERROR_INVALID_PARAMS;

    sc_iterator5 *it5 = sc_iterator5_f_a_f_a_f_new(v1,
                                                   arc_type,
                                                   v2,
                                                   sc_type_arc_pos_const_perm,
                                                   graph);
    int count = 0;
    while (sc_iterator5_next(it5) == SC_TRUE)
        count++;

    sc_iterator5_free(it5);

    return count == 1 ? SC_RESULT_OK : SC_RESULT_ERROR;
}

sc_result sc_graph_count_vertices(sc_addr graph, int *number)
{    
    sc_iterator5 *it5 = sc_iterator5_f_a_a_a_f_new(graph,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_type_node,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_graph_keynode_rrel_vertex);

    if (sc_helper_check_arc(sc_graph_keynode_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    *number = 0;
    while (sc_iterator5_next(it5) == SC_TRUE)
        (*number)++;

    sc_iterator5_free(it5);

    return SC_RESULT_OK;
}
