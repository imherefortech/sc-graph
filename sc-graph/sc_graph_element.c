
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
void deep_first_search_for_find_conn_comp(sc_addr curr_vertex, sc_addr_list **not_checked_vertices, sc_addr *curr_conn_comp, sc_addr graph)
{
    sc_addr arc, rrel_keynode;
    sc_type arc_type;
    sc_iterator5 *it5;

    *not_checked_vertices = sc_addr_list_remove(*not_checked_vertices);

    arc = sc_memory_arc_new(sc_type_arc_pos_const_perm, *curr_conn_comp, curr_vertex);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_rrel_vertex, arc);

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

    it5 = sc_iterator5_f_a_a_a_f_new(curr_vertex,
                                     arc_type | sc_type_const,
                                     sc_type_node | sc_type_const,
                                     sc_type_arc_pos_const_perm,
                                     graph);

    while(sc_iterator5_next(it5) == SC_TRUE)
    {
        if (sc_addr_list_is_included(*not_checked_vertices, it5->results[2]) == SC_TRUE)
        {
            arc = sc_memory_arc_new(sc_type_arc_pos_const_perm, *curr_conn_comp, it5->results[1]);
            sc_memory_arc_new(sc_type_arc_pos_const_perm, rrel_keynode, arc);
            deep_first_search_for_find_conn_comp(it5->results[2], not_checked_vertices, curr_conn_comp, graph);
        }
    }
    sc_iterator5_free(it5);

}

sc_result sc_graph_find_conn_comp(sc_addr graph, sc_addr_list **conn_comp_set)
{
    sc_addr curr_vertex, graph_keynode;
    sc_addr_list *not_checked_vertices = nullptr;

    sc_iterator5 *it5 = sc_iterator5_f_a_a_a_f_new(graph,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_type_node | sc_type_const,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_graph_keynode_rrel_vertex);

    if (sc_helper_check_arc(sc_graph_keynode_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
        graph_keynode = sc_graph_keynode_not_oriented_graph;
    else if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
        graph_keynode = sc_graph_keynode_oriented_graph;
    else return SC_RESULT_ERROR_INVALID_PARAMS;

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
        sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_graph, curr_conn_comp);
        sc_memory_arc_new(sc_type_arc_pos_const_perm, graph_keynode, curr_conn_comp);
        curr_vertex = not_checked_vertices->value;
        deep_first_search_for_find_conn_comp(curr_vertex, &not_checked_vertices, &curr_conn_comp, graph);
        *conn_comp_set = sc_addr_list_append(*conn_comp_set);
        (*conn_comp_set)->value = curr_conn_comp;
    }

    return SC_RESULT_OK;
}

sc_result sc_graph_vertex_degree(sc_addr graph, sc_addr vertex, int *result)
{
    int degree = 0;
    sc_type arc_type = 0;
    sc_iterator3 *it3;

    if (sc_helper_check_arc(sc_graph_keynode_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    //Check if vertex belongs to this garph
    if (sc_graph_check_vertex(graph, vertex) != SC_RESULT_OK)
        return SC_RESULT_ERROR_INVALID_PARAMS;

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
    {
        arc_type = sc_type_edge_common;
    }
    else if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
    {
        arc_type = sc_type_arc_common;
    }
    else return SC_RESULT_ERROR_INVALID_PARAMS;

    it3 = sc_iterator3_f_a_a_new(vertex, arc_type, sc_type_node);

    while (sc_iterator3_next(it3) == SC_TRUE)
        // The arc must belong to the current graph
        if (sc_graph_check_arc(graph,it3->results[1]) == SC_RESULT_OK)
        degree++;

    if (arc_type == sc_type_edge_common)
    {
        *result = degree;
        return SC_RESULT_OK;
    }

    it3 = sc_iterator3_a_a_f_new(sc_type_node, arc_type, vertex);

    while (sc_iterator3_next(it3) == SC_TRUE)
        if (sc_graph_check_arc(graph,it3->results[1]) == SC_RESULT_OK)
        degree++;

    *result = degree;
    return SC_RESULT_OK;

}

sc_result search_incident_vertexes(sc_addr graph, sc_addr arc, sc_addr_list **listVertex)
{
    sc_iterator3 *it3;
    sc_iterator5 *it5;
    sc_type arc_type;
   // sc_addr sc_graph_keynode_rrel;

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm))
        arc_type = sc_type_edge_common;

    else if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm))
        arc_type = sc_type_arc_common;

    it5 = sc_iterator5_f_a_a_a_f_new(graph,
                                                   sc_type_arc_pos,
                                                   sc_type_node,
                                                   sc_type_arc_pos,
                                                   sc_graph_keynode_rrel_vertex);


    while(sc_iterator5_next(it5) == SC_TRUE)
    {
        it3 = sc_iterator3_f_a_a_new(it5->results[2],
                                     arc_type,
                                     sc_type_node);
        while(sc_iterator3_next(it3) == SC_TRUE)
        {
            if(SC_ADDR_IS_EQUAL(it3->results[1],arc))
            {
                *listVertex = sc_addr_list_append(*listVertex);
                (*listVertex)->value = it3->results[0];
                *listVertex = sc_addr_list_append(*listVertex);
                (*listVertex)->value = it3->results[2];
            }
        }

    }

    sc_iterator5_free(it5);
    sc_iterator3_free(it3);

    return SC_RESULT_OK;
}

sc_result search_incident_vertex_arc(sc_addr graph, sc_addr vertex, sc_addr_list **listArc)
{
    sc_iterator3 *it3;
    sc_iterator5 *it5;
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
        it5 = sc_iterator5_f_a_f_a_f_new(graph,
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

     sc_iterator5_free(it5);
     sc_iterator3_free(it3);

     return SC_RESULT_OK;

}





