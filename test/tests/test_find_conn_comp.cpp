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
    return sc_graph_generate_empty(&mGraphAddr) == SC_TRUE;
}

bool TestFindConnComp::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_find_conn_comp, "Find connective components");

    return SUBTESTS_RESULT;
}

void TestFindConnComp::done()
{

}

bool TestFindConnComp::check_find_conn_comp()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mGraphAddr);

    sc_addr v1, v2, v3, v4, arc1, arc2, conn_comp_set;

    sc_iterator3 *it3;

    bool res = false;

    if (sc_graph_create_vertex(mGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr, v1, v2, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr, v2, v3, &arc2) != SC_RESULT_OK)
        return false;

    if (sc_graph_find_conn_comp(mGraphAddr, &conn_comp_set) != SC_RESULT_OK)
            return false;

    it3 = sc_iterator3_f_a_a_new(conn_comp_set,
                                 sc_type_arc_pos_const_perm,
                                 sc_type_node);

    while (sc_iterator3_next(it3) == SC_TRUE)
    {
        sc_iterator3 *vert_it3 = sc_iterator3_f_a_a_new(it3->results[2],
                                                       sc_type_arc_pos_const_perm,
                                                       sc_type_node);
        int count = 0;
        res = true;

        while (sc_iterator3_next(vert_it3) == SC_TRUE)
            count++;

        sc_iterator3_free(vert_it3);
        vert_it3 = sc_iterator3_f_a_a_new(it3->results[2],
                                          sc_type_arc_pos_const_perm,
                                          sc_type_node);
        if (count == 3) {
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
        }
        else if (count == 1)
        {
            sc_addr vert;
            sc_iterator3_next(vert_it3);
            vert = vert_it3->results[2];
            if (sc_iterator3_next(vert_it3) == SC_TRUE)
                return false;
            if (!SC_ADDR_IS_EQUAL(vert, v4))
                return false;
        }
        else return false;


        sc_iterator3_free(vert_it3);

    }

    sc_iterator3_free(it3);

    return res;
}

