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

    sc_iterator3 *it3;

    bool res = false;

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
    int count = 0;

    sc_iterator3 *vert_it3 = sc_iterator3_f_a_a_new(conn_comp,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_type_node);

    while (sc_iterator3_next(vert_it3) == SC_TRUE)
        count++;

    sc_iterator3_free(vert_it3);
    vert_it3 = sc_iterator3_f_a_a_new(conn_comp,
                                      sc_type_arc_pos_const_perm,
                                      sc_type_node);

    if (count != 1)
        return false;

    sc_iterator3_next(vert_it3);
    if (sc_iterator3_next(vert_it3) == SC_TRUE)
        return false;
    if (!SC_ADDR_IS_EQUAL(vert_it3->results[2], v4))
        return false;

    sc_iterator3_free(vert_it3);

    conn_comp_set = sc_addr_list_next(conn_comp_set);
    conn_comp = conn_comp_set->value;

    vert_it3 = sc_iterator3_f_a_a_new(conn_comp,
                                      sc_type_arc_pos_const_perm,
                                      sc_type_node);

    count = 0;
    while (sc_iterator3_next(vert_it3) == SC_TRUE)
        count++;

    sc_iterator3_free(vert_it3);
    vert_it3 = sc_iterator3_f_a_a_new(conn_comp,
                                      sc_type_arc_pos_const_perm,
                                      sc_type_node);

    if (count != 3)
        return false;

    sc_addr vert1, vert2, vert3;
    sc_iterator3_next(vert_it3);
    vert1 = vert_it3->results[2];
    sc_iterator3_next(vert_it3);
    vert2 = vert_it3->results[2];
    sc_iterator3_next(vert_it3);
    vert3 = vert_it3->results[2];

    if (sc_iterator3_next(vert_it3) == SC_TRUE)
        return false;

    if (!SC_ADDR_IS_EQUAL(vert1, v1) &&
        !SC_ADDR_IS_EQUAL(vert1, v2) &&
        !SC_ADDR_IS_EQUAL(vert1, v3) )
        return false;
    if (!SC_ADDR_IS_EQUAL(vert2, v1) &&
        !SC_ADDR_IS_EQUAL(vert2, v2) &&
        !SC_ADDR_IS_EQUAL(vert2, v3) )
        return false;
    if (!SC_ADDR_IS_EQUAL(vert3, v1) &&
        !SC_ADDR_IS_EQUAL(vert3, v2) &&
        !SC_ADDR_IS_EQUAL(vert3, v3) )
        return false;
    if (SC_ADDR_IS_EQUAL(vert1, vert2) ||
        SC_ADDR_IS_EQUAL(vert2, vert3) ||
        SC_ADDR_IS_EQUAL(vert1, vert3) )
        return false;

    sc_iterator3_free(vert_it3);

    sc_iterator3_free(it3);

    return true;
}

bool TestFindConnComp::check_find_conn_comp_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mOrGraphAddr));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mOrGraphAddr);

    sc_addr v1, v2, v3, v4, arc1, arc2;

    sc_addr_list *conn_comp_set;

    sc_iterator3 *it3;

    bool res = false;

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
    int count = 0;

    sc_iterator3 *vert_it3 = sc_iterator3_f_a_a_new(conn_comp,
                                                   sc_type_arc_pos_const_perm,
                                                   sc_type_node);

    while (sc_iterator3_next(vert_it3) == SC_TRUE)
        count++;

    sc_iterator3_free(vert_it3);
    vert_it3 = sc_iterator3_f_a_a_new(conn_comp,
                                      sc_type_arc_pos_const_perm,
                                      sc_type_node);

    if (count != 1)
        return false;

    sc_iterator3_next(vert_it3);
    if (sc_iterator3_next(vert_it3) == SC_TRUE)
        return false;
    if (!SC_ADDR_IS_EQUAL(vert_it3->results[2], v4))
        return false;

    sc_iterator3_free(vert_it3);

    conn_comp_set = sc_addr_list_next(conn_comp_set);
    conn_comp = conn_comp_set->value;

    vert_it3 = sc_iterator3_f_a_a_new(conn_comp,
                                      sc_type_arc_pos_const_perm,
                                      sc_type_node);

    count = 0;
    while (sc_iterator3_next(vert_it3) == SC_TRUE)
        count++;

    sc_iterator3_free(vert_it3);
    vert_it3 = sc_iterator3_f_a_a_new(conn_comp,
                                      sc_type_arc_pos_const_perm,
                                      sc_type_node);

    if (count != 3)
        return false;

    sc_addr vert1, vert2, vert3;
    sc_iterator3_next(vert_it3);
    vert1 = vert_it3->results[2];
    sc_iterator3_next(vert_it3);
    vert2 = vert_it3->results[2];
    sc_iterator3_next(vert_it3);
    vert3 = vert_it3->results[2];

    if (sc_iterator3_next(vert_it3) == SC_TRUE)
        return false;

    if (!SC_ADDR_IS_EQUAL(vert1, v1) &&
        !SC_ADDR_IS_EQUAL(vert1, v2) &&
        !SC_ADDR_IS_EQUAL(vert1, v3) )
        return false;
    if (!SC_ADDR_IS_EQUAL(vert2, v1) &&
        !SC_ADDR_IS_EQUAL(vert2, v2) &&
        !SC_ADDR_IS_EQUAL(vert2, v3) )
        return false;
    if (!SC_ADDR_IS_EQUAL(vert3, v1) &&
        !SC_ADDR_IS_EQUAL(vert3, v2) &&
        !SC_ADDR_IS_EQUAL(vert3, v3) )
        return false;
    if (SC_ADDR_IS_EQUAL(vert1, vert2) ||
        SC_ADDR_IS_EQUAL(vert2, vert3) ||
        SC_ADDR_IS_EQUAL(vert1, vert3) )
        return false;

    sc_iterator3_free(vert_it3);

    sc_iterator3_free(it3);

    return true;
}
