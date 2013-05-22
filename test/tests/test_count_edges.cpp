#include "test_count_edges.h"

TestCountEdges::TestCountEdges()
{

}

TestCountEdges::~TestCountEdges()
{

}

const String& TestCountEdges::name() const
{
    static String value = "Count Edges";
    return value;
}

bool TestCountEdges::prepare()
{
    return sc_graph_generate_empty(&mGraphAddr) == SC_TRUE;
}

bool TestCountEdges::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_count_edges, "Count edges");

    return SUBTESTS_RESULT;
}

void TestCountEdges::done()
{

}

bool TestCountEdges::check_count_edges()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr));


    sc_addr v1, v2, v3, v4, v5, v6, arc1, arc2, arc3, arc4, arc5, arc6;

 


    if (sc_graph_create_vertex(mGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v5) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v6) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_arc(mGraphAddr, v1, v2, &arc1) != SC_RESULT_OK)
    if (sc_graph_create_arc(mGraphAddr, v1, v4, &arc2) != SC_RESULT_OK)
    if (sc_graph_create_arc(mGraphAddr, v1, v5, &arc3) != SC_RESULT_OK)
    if (sc_graph_create_arc(mGraphAddr, v5, v3, &arc4) != SC_RESULT_OK)
    if (sc_graph_create_arc(mGraphAddr, v4, v6, &arc5) != SC_RESULT_OK)
    if (sc_graph_create_arc(mGraphAddr, v6, v3, &arc6) != SC_RESULT_OK)



        return false;

    int number;
    if (sc_graph_count_edges(mGraphAddr, &number) != SC_RESULT_OK)
        return false;


    if (number != 6)

        return false;

    return true;
}
