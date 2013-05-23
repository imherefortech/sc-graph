#include "test_search_incident_arcs.h"

TestSearchIncidentArcs::TestSearchIncidentArcs()
{

}

TestSearchIncidentArcs::~TestSearchIncidentArcs()
{

}

const String& TestSearchIncidentArcs::name() const
{
    static String value = "Search incident arcs";
    return value;
}

bool TestSearchIncidentArcs::prepare()
{
    return (sc_graph_generate_empty(&mOrGraphAddr) == SC_TRUE) &&
            (sc_graph_generate_empty(&mNotOrGraphAddr) == SC_TRUE);
}

bool TestSearchIncidentArcs::run()
{
    PREPARE_SUBTESTS();
    RUN_SUBTEST(check_search_incident_edges, "Search incident edges");
    RUN_SUBTEST(check_search_incident_arcs, "Search incident arcs");

    return SUBTESTS_RESULT;
}

void TestSearchIncidentArcs::done()
{

}


bool TestSearchIncidentArcs::check_search_incident_edges()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mNotOrGraphAddr));

    sc_addr arc1, arc2, arc3, arc4, v1, v2, v3, v4;
    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_not_oriented_graph, mNotOrGraphAddr);

    // create
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mNotOrGraphAddr, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v1, v2, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v1, v3, &arc2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v2, v3, &arc3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mNotOrGraphAddr, v3, v4, &arc4) != SC_RESULT_OK)
        return false;
    if(sc_graph_check_arc(mNotOrGraphAddr,arc1) != SC_RESULT_OK)
        return false;

    sc_addr_list *arcc = (sc_addr_list*)nullptr;
    if (search_incident_vertex_arc(mNotOrGraphAddr, v1, &arcc) != SC_RESULT_OK)
            return false;

    if(!SC_ADDR_IS_EQUAL(arcc->value, arc1))
        return false;

    arcc = sc_addr_list_next(arcc);

    if(!SC_ADDR_IS_EQUAL(arcc->value, arc2))
        return false;

return true;
}

bool TestSearchIncidentArcs::check_search_incident_arcs()
{
    assert(SC_ADDR_IS_NOT_EMPTY(mOrGraphAddr));

    sc_addr arc1, arc2, arc3,v1,v2, v3, v4;

    sc_memory_arc_new(sc_type_arc_pos_const_perm, sc_graph_keynode_oriented_graph, mOrGraphAddr);

    // create
    if (sc_graph_create_vertex(mOrGraphAddr, &v1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v3) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_vertex(mOrGraphAddr, &v4) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v1, v2, &arc1) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v1, v3, &arc2) != SC_RESULT_OK)
        return false;
    if (sc_graph_create_arc(mOrGraphAddr, v1, v4, &arc3) != SC_RESULT_OK)
        return false;
    if(sc_graph_check_arc(mOrGraphAddr,arc1) != SC_RESULT_OK)
        return false;

    sc_addr_list *arcc = (sc_addr_list*)nullptr;
    if (search_incident_vertex_arc(mOrGraphAddr, v1, &arcc) != SC_RESULT_OK)
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
