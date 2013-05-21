#include "test_search_incident_vertex_arc.h"

TestSearchIncidentVertexArc::TestSearchIncidentVertexArc()
{

}

TestSearchIncidentVertexArc::~TestSearchIncidentVertexArc()
{

}

const String& TestSearchIncidentVertexArc::name() const
{
    static String value = "Search incident vertex arc";
    return value;
}

bool TestSearchIncidentVertexArc::prepare()
{
    return (sc_graph_generate_empty(&mGraphAddr_oriented) == SC_TRUE) &&
            (sc_graph_generate_empty(&mGraphAddr_not_oriented) == SC_TRUE);
}

bool TestSearchIncidentVertexArc::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_search_incident_vertex_edge, "Search incident vertex edge");
    RUN_SUBTEST(check_search_incident_vertex_arc, "Search incident vertex arc");

    return SUBTESTS_RESULT;
}

void TestSearchIncidentVertexArc::done()
{

}


bool TestSearchIncidentVertexArc::check_search_incident_vertex_edge()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr_not_oriented));

    sc_addr arc1, arc2, arc3, arc4, v1, v2, v3, v4;
    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mGraphAddr_not_oriented);

    // create
    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_not_oriented, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_not_oriented, v1, v2, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_not_oriented, v1, v3, &arc2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_not_oriented, v2, v3, &arc3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_not_oriented, v3, v4, &arc4) != SC_RESULT_OK)
        return false;
    if(sc_graph_check_arc(mGraphAddr_not_oriented,arc1) != SC_RESULT_OK)
        return false;

    sc_addr_list *arcc = (sc_addr_list*)nullptr;
    if (search_incident_vertex_arc(mGraphAddr_not_oriented, v1, &arcc) != SC_RESULT_OK)
            return false;

    if(!SC_ADDR_IS_EQUAL(arcc->value, arc1))
        return false;

    arcc = sc_addr_list_next(arcc);

    if(!SC_ADDR_IS_EQUAL(arcc->value, arc2))
        return false;

return true;
}

bool TestSearchIncidentVertexArc::check_search_incident_vertex_arc()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mGraphAddr_oriented));

    sc_addr arc1, arc2, arc3,v1,v2, v3, v4;

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, mGraphAddr_oriented);

    // create
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mGraphAddr_oriented, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v1, v2, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v1, v3, &arc2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mGraphAddr_oriented, v1, v4, &arc3) != SC_RESULT_OK)
        return false;
    if(sc_graph_check_arc(mGraphAddr_oriented,arc1) != SC_RESULT_OK)
        return false;

    sc_addr_list *arcc = (sc_addr_list*)nullptr;
    if (search_incident_vertex_arc(mGraphAddr_oriented, v1, &arcc) != SC_RESULT_OK)
            return false;

    if(!SC_ADDR_IS_EQUAL(arcc->value, arc1))
        return false;

    arcc = sc_addr_list_next(arcc);

    if(!SC_ADDR_IS_EQUAL(arcc->value, arc2))
        return false;

    arcc = sc_addr_list_next(arcc);

    if(!SC_ADDR_IS_EQUAL(arcc->value, arc3))
        return false;

return true;
}
