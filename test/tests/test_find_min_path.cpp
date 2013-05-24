#include "test_find_min_path.h"

TestFindMinPath::TestFindMinPath()
{
}

TestFindMinPath::~TestFindMinPath()
{

}

const String& TestFindMinPath::name() const
{
    static String value = "Find minimal path";
    return value;
}

bool TestFindMinPath::prepare()
{
    return sc_graph_generate_empty(&mOrGraphAddr) == SC_TRUE &&
            sc_graph_generate_empty(&mNotOrGraphAddr) == SC_TRUE;
}

bool TestFindMinPath::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_find_min_path_not_or, "Find minimal route in not oriented graph");
    RUN_SUBTEST(check_find_min_path_or, "Find minimal path in oriented graph");

    return SUBTESTS_RESULT;
}

void TestFindMinPath::done()
{

}

bool TestFindMinPath::check_find_min_path_not_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mNotOrGraphAddr));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mNotOrGraphAddr);

    sc_addr v1, v2, v3, v4, v5, v6, arc1, arc2, arc3, arc4, arc5, arc6, arc7, arc8, arc9;

    if (sc_graph_create_vertex(mNotOrGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v5) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v6) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v1, v4, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v1, v3, &arc2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v1, v2, &arc3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v4, v3, &arc4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v3, v2, &arc5) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v3, v5, &arc6) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v4, v5, &arc7) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v2, v6, &arc8) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v5, v6, &arc9) != SC_RESULT_OK)
        return false;

    sc_addr_list *route;

    if (sc_graph_find_min_path(mNotOrGraphAddr, v1, v6, &route) != SC_RESULT_OK)
            return false;

    if (SC_ADDR_IS_EQUAL(route->value, v1) != SC_TRUE)
        return false;
    if ((route = sc_addr_list_next(route)) == nullptr)
        return false;
    if (SC_ADDR_IS_EQUAL(route->value, v2) != SC_TRUE)
        return false;
    if ((route = sc_addr_list_next(route)) == nullptr)
        return false;
    if (SC_ADDR_IS_EQUAL(route->value, v6) != SC_TRUE)
        return false;
    if ((route = sc_addr_list_next(route)) != nullptr)
        return false;

    return true;
}

bool TestFindMinPath::check_find_min_path_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mOrGraphAddr));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mOrGraphAddr);

    sc_addr v1, v2, v3, v4, v5, v6, arc1, arc2, arc3, arc4, arc5, arc6, arc7, arc8, arc9;

    if (sc_graph_create_vertex(mOrGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v5) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v6) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v1, v4, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v1, v3, &arc2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v1, v2, &arc3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v4, v3, &arc4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v3, v2, &arc5) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v3, v5, &arc6) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v4, v5, &arc7) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v2, v6, &arc8) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v5, v6, &arc9) != SC_RESULT_OK)
        return false;

    sc_addr_list *route;

    if (sc_graph_find_min_path(mOrGraphAddr, v1, v6, &route) != SC_RESULT_OK)
            return false;

    if (SC_ADDR_IS_EQUAL(route->value, v1) != SC_TRUE)
        return false;
    if ((route = sc_addr_list_next(route)) == nullptr)
        return false;
    if (SC_ADDR_IS_EQUAL(route->value, v2) != SC_TRUE)
        return false;
    if ((route = sc_addr_list_next(route)) == nullptr)
        return false;
    if (SC_ADDR_IS_EQUAL(route->value, v6) != SC_TRUE)
        return false;
    if ((route = sc_addr_list_next(route)) != nullptr)
        return false;

    return true;
}
