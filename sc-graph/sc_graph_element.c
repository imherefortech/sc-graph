
#include "sc_graph_keynodes.h"
#include "sc_graph_element.h"
#include "sc_graph_types.h"

/*! Deep first search to build a connective component
 * \param curr_vertex
 *          start vertex for the search
 * \param not_checked_vertices
 *          set of not checked vertices
 * \param curr_conn_comp
 *          connective component that is being built by this search
 * \param graph
 *          sc-addr of graph structure to search connective components
 */
void deep_first_search_for_find_conn_comp(sc_addr curr_vertex, sc_addr not_checked_vertices, sc_addr curr_conn_comp, sc_addr graph)
{
    sc_iterator3 *it3 = sc_iterator3_f_a_f_new(not_checked_vertices,
                                             sc_type_arc_pos_const_perm,
                                             curr_vertex);

    if (sc_iterator3_next(it3) == SC_TRUE)
        sc_memory_element_free(it3->results[1]);

    sc_iterator3_free(it3);

    sc_memory_arc_new(sc_type_arc_pos_const_perm, curr_conn_comp, curr_vertex);

    sc_iterator5 *it5 = sc_iterator5_f_a_a_a_f_new(curr_vertex,
                                                   sc_type_edge_common | sc_type_const,
                                                   sc_type_node | sc_type_const,
                                                   sc_type_arc_pos_const_perm,
                                                   graph);

    while(sc_iterator5_next(it5) == SC_TRUE)
    {
        if (sc_helper_check_arc(not_checked_vertices, it5->results[2],
                                sc_type_arc_pos_const_perm) == SC_TRUE)
            deep_first_search_for_find_conn_comp(it5->results[2], not_checked_vertices, curr_conn_comp, graph);
    }
    sc_iterator5_free(it5);

}

sc_result sc_graph_find_conn_comp(sc_addr graph, sc_addr *conn_comp_set)
{
    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    sc_addr not_checked_vertices, curr_vertex;

    sc_iterator3 *it3;

    sc_iterator5 *it5 = sc_iterator5_f_a_a_a_f_new(graph,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_type_node | sc_type_const,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_graph_keynode_rrel_vertex);

    not_checked_vertices = sc_memory_node_new(sc_type_node | sc_type_const);
    *conn_comp_set = sc_memory_node_new(sc_type_node | sc_type_const);


    while(sc_iterator5_next(it5) == SC_TRUE)
    {
        curr_vertex = it5->results[2];
        sc_memory_arc_new(sc_type_arc_pos_const_perm, not_checked_vertices, curr_vertex);
    }

    sc_iterator5_free(it5);

    it3 = sc_iterator3_f_a_a_new(not_checked_vertices,
                                 sc_type_arc_pos_const_perm,
                                 sc_type_node);

    while(sc_iterator3_next(it3) == SC_TRUE)
    {
        sc_addr curr_conn_comp = sc_memory_node_new(sc_type_node | sc_type_const);
        curr_vertex = it3->results[2];
        if(sc_helper_check_arc(not_checked_vertices, curr_vertex,
                               sc_type_arc_pos_const_perm) == SC_FALSE)
            continue;
        deep_first_search_for_find_conn_comp(curr_vertex, not_checked_vertices, curr_conn_comp, graph);
        sc_memory_arc_new(sc_type_arc_pos_const_perm, *conn_comp_set, curr_conn_comp);
    }

    sc_iterator3_free(it3);
    sc_memory_element_free(not_checked_vertices);

    return SC_RESULT_OK;
}

sc_result search_incident_vertex_arc(sc_addr graph, sc_addr vertex, sc_addr_list **listArc)
{
    sc_iterator3 *it3;
    sc_type arc_type;
    sc_addr sc_graph_keynode_rrel;

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm))
    {
        arc_type = sc_type_edge_common;
        sc_graph_keynode_rrel = sc_graph_keynode_rrel_edge;
    }
    else if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm))
    {
        arc_type = sc_type_arc_common;
        sc_graph_keynode_rrel = sc_graph_keynode_rrel_arc;
    }


    it3 = sc_iterator3_f_a_a_new(vertex,
                                 arc_type,
                                 sc_type_node);
    while(sc_iterator3_next(it3) == SC_TRUE)
    {
        sc_iterator5 *it5 = sc_iterator5_f_a_f_a_f_new(graph,
                                                       sc_type_arc_pos,
                                                       it3->results[1],
                                                       sc_type_arc_pos,
                                                       sc_graph_keynode_rrel);
        while(sc_iterator5_next(it5) == SC_TRUE)
        {
            *listArc = sc_addr_list_append(*listArc);
            (*listArc)->value = it5->results[2];
        }

    }
    return SC_RESULT_OK;

}


