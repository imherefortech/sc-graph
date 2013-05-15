#include "test_graph_modify.h"

TestGraphModify::TestGraphModify()
{

}

TestGraphModify::~TestGraphModify()
{

}

const String& TestGraphModify::name() const
{
    static String value = "Graph Modify";
    return value;
}

bool TestGraphModify::prepare()
{
    return (sc_graph_generate_empty(&mGraphAddr_oriented) == SC_TRUE) &&
            (sc_graph_generate_empty(&mGraphAddr_not_oriented) == SC_TRUE);
}

bool TestGraphModify::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_vertex_creation, "Create vertex");
    RUN_SUBTEST(check_edge_creation, "Create edge");
    RUN_SUBTEST(check_arc_creation, "Create arc");
    RUN_SUBTEST(check_adjacency_in_not_oriented_graph, "Elements adjacency in not oriented graph");
    RUN_SUBTEST(check_adjacency_in_oriented_graph, "Elements adjacency in oriented graph");

    return SUBTESTS_RESULT;
}

void TestGraphModify::done()
{

}

bool TestGraphModify::check_vertex_creation()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr_oriented));

    sc_addr vertex;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &vertex) != SC_RESULT_OK)
        return false;

    // check if vertex created correctly
    return sc_graph_check_vertex(mGraphAddr_oriented, vertex) == SC_RESULT_OK;
}

bool TestGraphModify::check_edge_creation()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr_not_oriented));

    sc_addr arc, v1, v2;

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mGraphAddr_not_oriented);

    // create
    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_not_oriented, v1, v2, &arc) != SC_RESULT_OK)
        return false;

    // check
    if (sc_graph_check_arc(mGraphAddr_not_oriented, arc) != SC_RESULT_OK)
        return false;

    sc_iterator5 *it5 = sc_iterator5_f_a_f_a_f_new(v1,
                                                   sc_type_edge_common | sc_type_const,
                                                   v2,
                                                   sc_type_arc_pos_const_perm,
                                                   mGraphAddr_not_oriented);
    int count = 0;
    while (sc_iterator5_next(it5) == SC_TRUE)
        count++;

    sc_iterator5_free(it5);

    return count == 1;
}

bool TestGraphModify::check_arc_creation()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr_oriented));

    sc_addr arc, v1, v2;

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, mGraphAddr_oriented);

    // create
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v1, v2, &arc) != SC_RESULT_OK)
        return false;

    // check
    if (sc_graph_check_arc(mGraphAddr_oriented, arc) != SC_RESULT_OK)
        return false;

    sc_iterator5 *it5 = sc_iterator5_f_a_f_a_f_new(v1,
                                                   sc_type_arc_common | sc_type_const,
                                                   v2,
                                                   sc_type_arc_pos_const_perm,
                                                   mGraphAddr_oriented);
    int count = 0;
    while (sc_iterator5_next(it5) == SC_TRUE)
        count++;

    sc_iterator5_free(it5);

    return count == 1;
}

bool TestGraphModify::check_adjacency_in_not_oriented_graph()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr_not_oriented));

    sc_addr v1, v2, v3, arc;

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mGraphAddr_not_oriented);

    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_not_oriented, v1, v2, &arc) != SC_RESULT_OK)
        return false;

    if (sc_graph_check_elements_adjacency(mGraphAddr_not_oriented, v1, v2) != SC_RESULT_OK)
        return false;

    if (sc_graph_check_elements_adjacency(mGraphAddr_not_oriented, v1, v3) == SC_RESULT_OK)
        return false;

    if (sc_graph_check_elements_adjacency(mGraphAddr_not_oriented, v2, v3) == SC_RESULT_OK)
        return false;

    return true;
}

bool TestGraphModify::check_adjacency_in_oriented_graph()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr_oriented));

    sc_addr v1, v2, v3, arc;

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, mGraphAddr_oriented);

    if (sc_graph_create_vertex(mGraphAddr_oriented, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v1, v2, &arc) != SC_RESULT_OK)
        return false;

    if (sc_graph_check_elements_adjacency(mGraphAddr_oriented, v1, v2) != SC_RESULT_OK)
        return false;

    if (sc_graph_check_elements_adjacency(mGraphAddr_oriented, v1, v3) == SC_RESULT_OK)
        return false;

    if (sc_graph_check_elements_adjacency(mGraphAddr_oriented, v2, v3) == SC_RESULT_OK)
        return false;

    return true;
}
