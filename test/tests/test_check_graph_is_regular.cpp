#include "test_check_graph_is_regular.h"

TestCheckGraphIsRegular::TestCheckGraphIsRegular()
{

}

TestCheckGraphIsRegular::~TestCheckGraphIsRegular()
{

}

const String& TestCheckGraphIsRegular::name() const
{
    static String value = "Regular graph";
    return value;
}

bool TestCheckGraphIsRegular::prepare()
{
    if ( sc_graph_generate_empty(&mGraphAddrOrient) != SC_TRUE)
        return false;
    if ( sc_graph_generate_empty(&mGraphAddrNotOrient) != SC_TRUE)
        return false;

    return true;
}

bool TestCheckGraphIsRegular::run()
{
    PREPARE_SUBTESTS();
   // RUN_SUBTEST(check_graph_is_regular, "Check graph is regular");
    RUN_SUBTEST(check_graph_is_regular_not_or, "Check not oriented graph is regular");
    RUN_SUBTEST(check_graph_is_regular_or, "Check oriented graph is regular");
    return SUBTESTS_RESULT;
}

void TestCheckGraphIsRegular::done()
{

}

bool TestCheckGraphIsRegular::check_graph_is_regular_not_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddrNotOrient));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mGraphAddrNotOrient);

    sc_addr vertex1, vertex2, vertex3;

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

    sc_addr arc12, arc13, arc32;

    if (sc_graph_create_arc(mGraphAddrNotOrient, vertex2, vertex1, &arc12) != SC_RESULT_OK)
        return false;
    if (sc_graph_check_arc(mGraphAddrNotOrient, arc12) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_arc(mGraphAddrNotOrient, vertex1, vertex3, &arc13) != SC_RESULT_OK)
        return false;
    if (sc_graph_check_arc(mGraphAddrNotOrient, arc13) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_arc(mGraphAddrNotOrient, vertex3, vertex2, &arc32) != SC_RESULT_OK)
        return false;
    if (sc_graph_check_arc(mGraphAddrNotOrient, arc32) != SC_RESULT_OK)
        return false;

    sc_bool check;

    if(sc_graph_is_regular(mGraphAddrNotOrient, &check) != SC_RESULT_OK)
        return false;
    else if(check != SC_TRUE)
        return false;

   return true;
}

bool TestCheckGraphIsRegular::check_graph_is_regular_or()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddrOrient));

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, mGraphAddrOrient);

    sc_addr vertex1, vertex2, vertex3;

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

    sc_addr arc12, arc13, arc32;

    if (sc_graph_create_arc(mGraphAddrOrient, vertex2, vertex1, &arc12) != SC_RESULT_OK)
        return false;
    if (sc_graph_check_arc(mGraphAddrOrient, arc12) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_arc(mGraphAddrOrient, vertex1, vertex3, &arc13) != SC_RESULT_OK)
        return false;
    if (sc_graph_check_arc(mGraphAddrOrient, arc13) != SC_RESULT_OK)
        return false;

    if (sc_graph_create_arc(mGraphAddrOrient, vertex3, vertex2, &arc32) != SC_RESULT_OK)
        return false;
    if (sc_graph_check_arc(mGraphAddrOrient, arc32) != SC_RESULT_OK)
        return false;

    sc_bool check;

    if(sc_graph_is_regular(mGraphAddrOrient, &check) != SC_RESULT_OK)
        return false;
    else if(check != SC_TRUE)
        return false;

   return true;
}
