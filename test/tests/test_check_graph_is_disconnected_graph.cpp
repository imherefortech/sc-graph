#include "test_check_graph_is_disconnected_graph.h"


TestCheckGraphIsDisconnectedGraph::TestCheckGraphIsDisconnectedGraph()
{

}

TestCheckGraphIsDisconnectedGraph::~TestCheckGraphIsDisconnectedGraph()
{

}

const String& TestCheckGraphIsDisconnectedGraph::name() const
{
    static String value = "Disconnected graph";
    return value;
}

bool TestCheckGraphIsDisconnectedGraph::prepare()
{
    if ( sc_graph_generate_empty(&mGraphAddrOrient) != SC_TRUE)
        return false;
    if ( sc_graph_generate_empty(&mGraphAddrNotOrient) != SC_TRUE)
        return false;

    return true;
}

bool TestCheckGraphIsDisconnectedGraph::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_graph_is_disconnected_not_or, "Check not oriented graph is disconnected");
    RUN_SUBTEST(check_graph_is_disconnected_or, "Check oriented graph is disconnected");
    return SUBTESTS_RESULT;
}

void TestCheckGraphIsDisconnectedGraph::done()
{

}

bool TestCheckGraphIsDisconnectedGraph::check_graph_is_disconnected_not_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddrNotOrient));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mGraphAddrNotOrient);

    sc_addr vertex1, vertex2, vertex3, vertex4, vertex5;

    if (sc_graph_create_vertex(mGraphAddrNotOrient, &vertex1) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrNotOrient, vertex1) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(mGraphAddrNotOrient, &vertex2) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrNotOrient, vertex2) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(mGraphAddrNotOrient, &vertex3) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrNotOrient, vertex3) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(mGraphAddrNotOrient, &vertex4) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrNotOrient, vertex4) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(mGraphAddrNotOrient, &vertex5) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrNotOrient, vertex5) != SC_RESULT_OK)
        return false;

    sc_bool check;

    if(sc_graph_is_disconnected(mGraphAddrNotOrient, &check) != SC_RESULT_OK)
        return false;
    else if(check != SC_TRUE)
        return false;

   return true;
}

bool TestCheckGraphIsDisconnectedGraph::check_graph_is_disconnected_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddrOrient));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, mGraphAddrOrient);

    sc_addr vertex1, vertex2, vertex3, vertex4;

    if (sc_graph_create_vertex(mGraphAddrOrient, &vertex1) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrOrient, vertex1) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(mGraphAddrOrient, &vertex2) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrOrient, vertex2) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(mGraphAddrOrient, &vertex3) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrOrient, vertex3) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(mGraphAddrOrient, &vertex4) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(mGraphAddrOrient, vertex4) != SC_RESULT_OK)
        return false;

    sc_bool check;

    if(sc_graph_is_disconnected(mGraphAddrOrient, &check) != SC_RESULT_OK)
        return false;
    else if(check != SC_TRUE)
        return false;

   return true;
}
