#include "test_graph_gen.h"

TestGraphGen::TestGraphGen()
{

}

TestGraphGen::~TestGraphGen()
{

}

const String& TestGraphGen::name() const
{
    static String value = "Graph Generation";
    return value;
}

bool TestGraphGen::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_empty_graph_generation, "Empty graph");

    return SUBTESTS_RESULT;
}

bool TestGraphGen::prepare()
{
    return true;
}

void TestGraphGen::done()
{

}

bool TestGraphGen::check_empty_graph_generation()
{
    sc_addr graph;

    if (sc_graph_generate_empty(&graph) != SC_TRUE)
        return false;

    if (sc_helper_check_arc(sc_graph_keynode_graph, graph, sc_type_arc_pos_const_perm) == SC_FALSE)
        return false;

    return true;
}
