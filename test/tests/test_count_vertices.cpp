#include "test_count_vertices.h"

TestCountVertices::TestCountVertices()
{

}

TestCountVertices::~TestCountVertices()
{

}

const String& TestCountVertices::name() const
{
    static String value = "Count Vertices";
    return value;
}

bool TestCountVertices::prepare()
{
    return sc_graph_generate_empty(&mGraphAddr) == SC_TRUE;
}

bool TestCountVertices::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_count_vertices, "Count vertices");

    return SUBTESTS_RESULT;
}

void TestCountVertices::done()
{

}

bool TestCountVertices::check_count_vertices()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr));

    sc_addr v1, v2, v3, v4;

    if (sc_graph_create_vertex(mGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v4) != SC_RESULT_OK)
        return false;

    int number;
    if (sc_graph_count_vertices(mGraphAddr, &number) != SC_RESULT_OK)
        return false;

    if (number != 4)
        return false;

    return true;
}
