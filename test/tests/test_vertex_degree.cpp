#include "test_vertex_degree.h"

TestVertexDegree::TestVertexDegree()
{

}

TestVertexDegree::~TestVertexDegree()
{

}

const String& TestVertexDegree::name() const
{
    static String value = "Vertex degree";
    return value;
}

bool TestVertexDegree::prepare()
{
    if ( sc_graph_generate_empty(&not_oriented_graph) != SC_TRUE)
        return false;
    if ( sc_graph_generate_empty(&oriented_graph) != SC_TRUE)
        return false;

    return true;
}

bool TestVertexDegree::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_vertex_degree_in_not_oriented_graph, "Vertex degree in not oriented graph");
    RUN_SUBTEST(check_vertex_degree_in_oriented_graph, "Vertex degree in oriented graph");
    return SUBTESTS_RESULT;
}

void TestVertexDegree::done()
{

}


bool TestVertexDegree::check_vertex_degree_in_not_oriented_graph()
{
    assert(SC_ADDR_IS_NOT_EMPTY(not_oriented_graph));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, not_oriented_graph);

    // add vertex to the graph
    sc_addr vertex1, vertex2, vertex3;

    if (sc_graph_create_vertex(not_oriented_graph, &vertex1) != SC_RESULT_OK)
        return false;

    // check if vertex created correctly
    if ( sc_graph_check_vertex(not_oriented_graph, vertex1) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(not_oriented_graph, &vertex2) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(not_oriented_graph, vertex2) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(not_oriented_graph, &vertex3) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(not_oriented_graph, vertex3) != SC_RESULT_OK)
        return false;

    sc_addr arc12, arc13;

    // Create a new arc between vertex2 and vertex1
    if (sc_graph_create_arc(not_oriented_graph, vertex2, vertex1, &arc12) != SC_RESULT_OK)
        return false;
    // check
    if (sc_graph_check_arc(not_oriented_graph, arc12) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_arc(not_oriented_graph, vertex1, vertex3, &arc13) != SC_RESULT_OK)
        return false;
    if (sc_graph_check_arc(not_oriented_graph, arc13) != SC_RESULT_OK)
        return false;

    int degree = 0;

    if(sc_graph_vertex_degree(not_oriented_graph, vertex1, &degree) != SC_RESULT_OK)
        return false;
    else if (degree != 2)
    {
        return false;
    }

   return true;
}

bool TestVertexDegree::check_vertex_degree_in_oriented_graph()
{
    assert(SC_ADDR_IS_NOT_EMPTY(oriented_graph));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, oriented_graph);

    // add vertex to the graph
    sc_addr vertex1, vertex2, vertex3;

    if (sc_graph_create_vertex(oriented_graph, &vertex1) != SC_RESULT_OK)
        return false;

    // check if vertex created correctly
    if ( sc_graph_check_vertex(oriented_graph, vertex1) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(oriented_graph, &vertex2) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(oriented_graph, vertex2) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_vertex(oriented_graph, &vertex3) != SC_RESULT_OK)
        return false;
    if ( sc_graph_check_vertex(oriented_graph, vertex3) != SC_RESULT_OK)
        return false;

    sc_addr arc12, arc13;

    // Create a new arc between vertex2 and vertex1
    if (sc_graph_create_arc(oriented_graph, vertex2, vertex1, &arc12) != SC_RESULT_OK)
        return false;
    // check
    if (sc_graph_check_arc(oriented_graph, arc12) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_arc(oriented_graph, vertex1, vertex3, &arc13) != SC_RESULT_OK)
        return false;
    if (sc_graph_check_arc(oriented_graph, arc13) != SC_RESULT_OK)
        return false;

    int degree = 0;

    if(sc_graph_vertex_degree(oriented_graph, vertex1, &degree) != SC_RESULT_OK)
        return false;
    else if (degree != 2)
    {
        return false;
    }

   return true;
}
