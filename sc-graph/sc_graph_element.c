
#include "sc_graph_keynodes.h"
#include "sc_graph_element.h"

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
void deep_first_search_for_find_conn_comp(sc_addr curr_vertex, sc_addr_list **not_checked_vertices, sc_addr *curr_conn_comp, sc_addr graph)
{
    sc_type arc_type;
    sc_iterator5 *it5;

    *not_checked_vertices = sc_addr_list_remove(*not_checked_vertices);

    sc_memory_arc_new(sc_type_arc_pos_const_perm, *curr_conn_comp, curr_vertex);

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm))
        arc_type = sc_type_edge_common;
    else if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm))
        arc_type = sc_type_arc_common;

    it5 = sc_iterator5_f_a_a_a_f_new(curr_vertex,
                                     arc_type | sc_type_const,
                                     sc_type_node | sc_type_const,
                                     sc_type_arc_pos_const_perm,
                                     graph);

    while(sc_iterator5_next(it5) == SC_TRUE)
    {
        if (sc_addr_list_is_included(*not_checked_vertices, it5->results[2]) == SC_TRUE)
            deep_first_search_for_find_conn_comp(it5->results[2], not_checked_vertices, curr_conn_comp, graph);
    }
    sc_iterator5_free(it5);

}

sc_result sc_graph_find_conn_comp(sc_addr graph, sc_addr_list **conn_comp_set)
{
    sc_addr curr_vertex;
    sc_addr_list *not_checked_vertices = nullptr;

    sc_iterator5 *it5 = sc_iterator5_f_a_a_a_f_new(graph,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_type_node | sc_type_const,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_graph_keynode_rrel_vertex);

    if (sc_helper_check_arc(sc_graph_keynode_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    *conn_comp_set = nullptr;

    while(sc_iterator5_next(it5) == SC_TRUE)
    {
        curr_vertex = it5->results[2];
        not_checked_vertices = sc_addr_list_append(not_checked_vertices);
        not_checked_vertices->value = curr_vertex;
    }

    sc_iterator5_free(it5);

    while (not_checked_vertices != nullptr)
    {
        sc_addr curr_conn_comp = sc_memory_node_new(sc_type_node | sc_type_const);
        curr_vertex = not_checked_vertices->value;
        deep_first_search_for_find_conn_comp(curr_vertex, &not_checked_vertices, &curr_conn_comp, graph);
        *conn_comp_set = sc_addr_list_append(*conn_comp_set);
        (*conn_comp_set)->value = curr_conn_comp;
    }

    return SC_RESULT_OK;
}


