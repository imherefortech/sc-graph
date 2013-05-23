#include "test_is_complete_graph.h"

TestIsCompleteGraph::TestIsCompleteGraph()
{

}

TestIsCompleteGraph::~TestIsCompleteGraph()
{

}

const String& TestIsCompleteGraph::name() const
{
    static String value = "Search incident vertex arc";
    return value;
}

bool TestIsCompleteGraph::prepare()
{
    return (sc_graph_generate_empty(&mGraphAddr_oriented) == SC_TRUE) &&
            (sc_graph_generate_empty(&mGraphAddr_not_oriented) == SC_TRUE);
}

bool TestIsCompleteGraph::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_is_complete_graph, "check is complete graph");
   // RUN_SUBTEST(check_search_incident_vertex_arc, "Search incident vertex arc");

    return SUBTESTS_RESULT;
}

void TestIsCompleteGraph::done()
{

}


bool TestIsCompleteGraph::check_is_complete_graph()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr_oriented));

    sc_addr arc1, arc2, arc3, arc4, arc5, arc6, arc7, v1, v2, v3, v4;
    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, mGraphAddr_oriented);

    // create
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v1, v2, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v1, v3, &arc2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v2, v1, &arc3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v3, v1, &arc4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v2, v3, &arc5) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v3, v2, &arc6) != SC_RESULT_OK)
        return false;

    if (is_complete_graph(mGraphAddr_oriented) != SC_RESULT_OK)
        return false;

return true;
}
