#include "test_find_conn_comp.h"

TestFindConnComp::TestFindConnComp()
{
}

TestFindConnComp::~TestFindConnComp()
{

}

const String& TestFindConnComp::name() const
{
    static String value = "Find connective components";
    return value;
}

bool TestFindConnComp::prepare()
{
    return sc_graph_generate_empty(&mOrGraphAddr) == SC_TRUE &&
            sc_graph_generate_empty(&mNotOrGraphAddr) == SC_TRUE;
}

bool TestFindConnComp::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_find_conn_comp_not_or, "Find connective components for not oriented graph");
    RUN_SUBTEST(check_find_conn_comp_or, "Find connective components for oriented graph");

    return SUBTESTS_RESULT;
}

void TestFindConnComp::done()
{

}

bool TestFindConnComp::check_find_conn_comp_not_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mNotOrGraphAddr));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mNotOrGraphAddr);

    sc_addr v1, v2, v3, v4, arc1, arc2;

    sc_addr_list *conn_comp_set;

    if (sc_graph_create_vertex(mNotOrGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v1, v2, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v2, v3, &arc2) != SC_RESULT_OK)
        return false;

    if (sc_graph_find_conn_comp(mNotOrGraphAddr, &conn_comp_set) != SC_RESULT_OK)
            return false;

    sc_addr conn_comp = conn_comp_set->value;

    if (sc_helper_check_arc(sc_graph_keynode_not_oriented_graph, conn_comp,
                            sc_type_arc_pos_const_perm) == SC_FALSE)
        return false;

    sc_iterator5 *graph_it5 = sc_iterator5_f_a_a_a_f_new(conn_comp,
                                                        sc_type_arc_pos_const_perm,
                                                        sc_type_node,
                                                        sc_type_arc_pos_const_perm,
                                                        sc_graph_keynode_rrel_vertex);


    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], v4))
        return false;
    if (sc_iterator5_next(graph_it5) == SC_TRUE)
        return false;

    sc_iterator5_free(graph_it5);

    graph_it5 = sc_iterator5_f_a_a_a_f_new(conn_comp,
                                           sc_type_arc_pos_const_perm,
                                           sc_type_edge_common,
                                           sc_type_arc_pos_const_perm,
                                           sc_graph_keynode_rrel_edge);

    if (sc_iterator5_next(graph_it5) == SC_TRUE)
        return false;

    conn_comp_set = sc_addr_list_next(conn_comp_set);
    conn_comp = conn_comp_set->value;

    sc_iterator5_free(graph_it5);

    graph_it5 = sc_iterator5_f_a_a_a_f_new(conn_comp,
                                           sc_type_arc_pos_const_perm,
                                           sc_type_node,
                                           sc_type_arc_pos_const_perm,
                                           sc_graph_keynode_rrel_vertex);

    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], v3))
        return false;
    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], v2))
        return false;
    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], v1))
        return false;

    if (sc_iterator5_next(graph_it5) == SC_TRUE)
        return false;

    sc_iterator5_free(graph_it5);

    graph_it5 = sc_iterator5_f_a_a_a_f_new(conn_comp,
                                           sc_type_arc_pos_const_perm,
                                           sc_type_edge_common,
                                           sc_type_arc_pos_const_perm,
                                           sc_graph_keynode_rrel_edge);

    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], arc2))
        return false;
    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], arc1))
        return false;

    if (sc_iterator5_next(graph_it5) == SC_TRUE)
        return false;

    return true;
}

bool TestFindConnComp::check_find_conn_comp_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mOrGraphAddr));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, mOrGraphAddr);

    sc_addr v1, v2, v3, v4, arc1, arc2;

    sc_addr_list *conn_comp_set;

    if (sc_graph_create_vertex(mOrGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v1, v2, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v2, v3, &arc2) != SC_RESULT_OK)
        return false;

    if (sc_graph_find_conn_comp(mOrGraphAddr, &conn_comp_set) != SC_RESULT_OK)
            return false;

    sc_addr conn_comp = conn_comp_set->value;

    if (sc_helper_check_arc(sc_graph_keynode_oriented_graph, conn_comp,
                            sc_type_arc_pos_const_perm) == SC_FALSE)
        return false;

    sc_iterator5 *graph_it5 = sc_iterator5_f_a_a_a_f_new(conn_comp,
                                                        sc_type_arc_pos_const_perm,
                                                        sc_type_node,
                                                        sc_type_arc_pos_const_perm,
                                                        sc_graph_keynode_rrel_vertex);


    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], v4))
        return false;
    if (sc_iterator5_next(graph_it5) == SC_TRUE)
        return false;

    sc_iterator5_free(graph_it5);

    graph_it5 = sc_iterator5_f_a_a_a_f_new(conn_comp,
                                           sc_type_arc_pos_const_perm,
                                           sc_type_arc_common,
                                           sc_type_arc_pos_const_perm,
                                           sc_graph_keynode_rrel_arc);

    if (sc_iterator5_next(graph_it5) == SC_TRUE)
        return false;

    conn_comp_set = sc_addr_list_next(conn_comp_set);
    conn_comp = conn_comp_set->value;

    sc_iterator5_free(graph_it5);

    graph_it5 = sc_iterator5_f_a_a_a_f_new(conn_comp,
                                           sc_type_arc_pos_const_perm,
                                           sc_type_node,
                                           sc_type_arc_pos_const_perm,
                                           sc_graph_keynode_rrel_vertex);

    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], v3))
        return false;
    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], v2))
        return false;
    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], v1))
        return false;

    if (sc_iterator5_next(graph_it5) == SC_TRUE)
        return false;

    sc_iterator5_free(graph_it5);

    graph_it5 = sc_iterator5_f_a_a_a_f_new(conn_comp,
                                           sc_type_arc_pos_const_perm,
                                           sc_type_arc_common,
                                           sc_type_arc_pos_const_perm,
                                           sc_graph_keynode_rrel_arc);

    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], arc2))
        return false;
    if (sc_iterator5_next(graph_it5) == SC_FALSE)
        return false;
    if (!SC_ADDR_IS_EQUAL(graph_it5->results[2], arc1))
        return false;

    if (sc_iterator5_next(graph_it5) == SC_TRUE)
        return false;

    return true;
}
