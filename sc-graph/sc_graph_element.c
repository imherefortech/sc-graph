
#include "sc_graph_keynodes.h"
#include "sc_graph_element.h"
#include "sc_graph_struct.h"

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

/*! Calculates vertex degree
 * \param graph
 *          graph that contains vertex for degree calculation
 * \param vertex
 *          vertex for deegree calculation
 * \param result
 *          vertex degree
 */

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

/*! Find adjacent vertex from wave to get next vertex of a path
 * \param graph
 *        sc_addr of a graph where we looking for minimal path
 * \param wave
 *          wave to search adjacent vertex in
 * \param curr_vertex
 *        vertex to search adjacent to
 * \param result
 *          next vertex of path
 */

sc_addr find_adjacent_from_wave(sc_addr graph, sc_addr wave, sc_addr curr_vertex)
{
    sc_iterator3 *it3;

    it3 = sc_iterator3_f_a_a_new(wave,
                                 sc_type_arc_pos_const_perm,
                                 sc_type_node | sc_type_const);

    while (sc_iterator3_next(it3) == SC_TRUE)
        if (sc_graph_check_elements_adjacency(graph, curr_vertex, it3->results[2]) == SC_RESULT_OK)
            return it3->results[2];
}

/*! Creates wave of adjacent not  checked vertices
 * \param cur_wave
 *          wave to build new wave on
 * \param graph
 *        sc_addr of a graph where we looking for minimal path
 * \param not_checked_vertices
 *        list of not checked vertices
 * \param result
 *          new wave
 */

sc_addr create_wave(sc_addr cur_wave, sc_addr graph, sc_addr_list **not_checked_vertices)
{
    sc_addr_list *cur_item;
    sc_addr new_wave;
    sc_iterator3 *it3 = sc_iterator3_f_a_a_new(cur_wave,
                                               sc_type_arc_pos_const_perm,
                                               sc_type_node | sc_type_const);
    sc_type arc_type;

    new_wave = sc_memory_node_new(sc_type_node | sc_type_const);

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
        arc_type = sc_type_edge_common;
    else if(sc_helper_check_arc(sc_graph_keynode_oriented_graph, graph, sc_type_arc_pos_const_perm) == SC_TRUE)
        arc_type = sc_type_arc_common;
    while (sc_iterator3_next(it3) == SC_TRUE)
    {
        sc_addr cur_vertex = it3->results[2];

        sc_iterator5 *it5 = sc_iterator5_f_a_a_a_f_new(cur_vertex,
                                                       arc_type | sc_type_const,
                                                       sc_type_node | sc_type_const,
                                                       sc_type_arc_pos_const_perm,
                                                       graph);
        while (sc_iterator5_next(it5) == SC_TRUE)
        {
            cur_item = *not_checked_vertices;
            do {
                if (SC_ADDR_IS_EQUAL(cur_item->value, it5->results[2]) == SC_TRUE)
                {
                    if (cur_item == *not_checked_vertices)
                        *not_checked_vertices = sc_addr_list_remove(*not_checked_vertices);
                    else cur_item = sc_addr_list_remove(cur_item);

                    sc_memory_arc_new(sc_type_arc_pos_const_perm, new_wave, it5->results[2]);
                    break;
                }
            } while((cur_item = sc_addr_list_next(cur_item)) != nullptr);
        }
    }
    return new_wave;
}

sc_result sc_graph_find_min_path(sc_addr graph, sc_addr beg_vertex, sc_addr end_vertex, sc_addr_list **path)
{
    sc_addr curr_vertex, cur_wave;
    sc_addr_list *not_checked_vertices = nullptr, *wave_list_head = nullptr, *path_head = nullptr;
    sc_iterator3 *wave_it;
    sc_iterator5 *it5 = sc_iterator5_f_a_a_a_f_new(graph,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_type_node | sc_type_const,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_graph_keynode_rrel_vertex);

    if (sc_helper_check_arc(sc_graph_keynode_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return SC_RESULT_ERROR_INVALID_PARAMS;


    while (sc_iterator5_next(it5) == SC_TRUE)
    {
        if (SC_ADDR_IS_EQUAL(beg_vertex, it5->results[2]) == SC_FALSE)
        {
            not_checked_vertices = sc_addr_list_append(not_checked_vertices);
            not_checked_vertices->value = it5->results[2];
        }
    }

    cur_wave = sc_memory_node_new(sc_type_node | sc_type_const);
    sc_memory_arc_new(sc_type_arc_pos_const_perm, cur_wave, beg_vertex);

    wave_list_head = sc_addr_list_append(wave_list_head);
    wave_list_head->value = cur_wave;

    do {
        cur_wave = create_wave(cur_wave, graph, &not_checked_vertices);

        wave_it = sc_iterator3_f_a_a_new(cur_wave,
                                         sc_type_arc_pos_const_perm,
                                         sc_type_node | sc_type_const);

        if (sc_iterator3_next(wave_it) == SC_FALSE)
            //TODO clear memory
            return SC_RESULT_ERROR;

        wave_list_head = sc_addr_list_append(wave_list_head);
        wave_list_head->value = cur_wave;

    } while(sc_helper_check_arc(cur_wave, end_vertex, sc_type_arc_pos_const_perm) == SC_FALSE);

    path_head = sc_addr_list_append(path_head);
    path_head->value = end_vertex;
    curr_vertex = end_vertex;
    wave_list_head = sc_addr_list_next(wave_list_head);
    do {
        curr_vertex = find_adjacent_from_wave(graph, wave_list_head->value, curr_vertex);
        path_head = sc_addr_list_append(path_head);
        path_head->value = curr_vertex;
    } while((wave_list_head = sc_addr_list_next(wave_list_head)) != nullptr);

    *path = path_head;
    return SC_RESULT_OK;
}
