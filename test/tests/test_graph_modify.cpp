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
    return sc_graph_generate_empty(&mGraphAddr) == SC_TRUE;
}

bool TestGraphModify::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_vertex_creation, "Create vertex");
    RUN_SUBTEST(check_arc_creation, "Create arc");

    return SUBTESTS_RESULT;
}

void TestGraphModify::done()
{

}

bool TestGraphModify::check_vertex_creation()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr));

    sc_addr vertex;
    if (sc_graph_create_vertex(mGraphAddr, &vertex) != SC_RESULT_OK)
        return false;

    // check if vertex created correctly
    return sc_graph_check_vertex(mGraphAddr, vertex) == SC_RESULT_OK;
}

bool TestGraphModify::check_arc_creation()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr));

    sc_addr arc, v1, v2;

    // create
    if (sc_graph_create_vertex(mGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr, v1, v2, &arc) != SC_RESULT_OK)
        return false;

    // check
    if (sc_graph_check_arc(mGraphAddr, arc) != SC_RESULT_OK)
        return false;

    sc_iterator5 *it5 = sc_iterator5_f_a_f_a_f_new(v1,
                                                   sc_type_arc_common | sc_type_const,
                                                   v2,
                                                   sc_type_arc_pos_const_perm,
                                                   mGraphAddr);
    int count = 0;
    while (sc_iterator5_next(it5) == SC_TRUE)
        count++;

    sc_iterator5_free(it5);

    return count == 1;
}
