#include "prerequest.h"
#include "test.h"

#include <string.h>
#include <stdlib.h>

#include "tests/test_graph_gen.h"
#include "tests/test_graph_modify.h"
#include "tests/test_find_conn_comp.h"
#include "tests/test_search_incident_vertex_arc.h"


typedef std::vector<Test*> tTestVector;


const char hypermedia_nrel_system_identifier_str[] = "hypermedia_nrel_system_identifier";

bool find_system_identifier_keynode()
{

    sc_addr *results = 0;
    sc_uint32 results_count = 0;
    sc_stream *stream = sc_stream_memory_new(hypermedia_nrel_system_identifier_str,
                                             sizeof(sc_uchar) * strlen(hypermedia_nrel_system_identifier_str),
                                             SC_STREAM_READ, SC_FALSE);
    sc_uint32 i = 0;
    sc_iterator5 *it = 0;
    sc_bool found = SC_FALSE;
    sc_addr addr1, addr2;

    // try to find hypermedia_nrel_system_identifier strings
    if (sc_memory_find_links_with_content(stream, &results, &results_count) == SC_RESULT_OK)
    {
        for (i = 0; i < results_count; i++)
        {
            it = sc_iterator5_a_a_f_a_a_new(sc_type_node | sc_type_const | sc_type_node_norole,
                                            sc_type_arc_common | sc_type_const,
                                            results[i],
                                            sc_type_arc_pos_const_perm,
                                            sc_type_const | sc_type_node | sc_type_node_norole);

            while (sc_iterator5_next(it))
            {

                addr1 = sc_iterator5_value(it, 0);
                addr2 = sc_iterator5_value(it, 4);
                // comare begin sc-element and attribute, they must be equivalent
                if (SC_ADDR_IS_EQUAL(addr1, addr2))
                {
                    if (found == SC_FALSE)
                    {
                        found = SC_TRUE;
                    }else
                    {
                        sc_iterator5_free(it);
                        sc_stream_free(stream);
                        free(results);
                        return false;
                    }
                }
            }

            sc_iterator5_free(it);
        }

        free(results);
    }else
        return false;

    sc_stream_free(stream);

    return found == SC_TRUE;
}

void prepare()
{
    // first of all create system identifier node if it's not exist
    if (!find_system_identifier_keynode())
    {
        sc_addr idtf, arc, link;
        sc_stream *stream;

        stream = sc_stream_memory_new(hypermedia_nrel_system_identifier_str,
                                      strlen(hypermedia_nrel_system_identifier_str),
                                      SC_STREAM_READ,
                                      SC_FALSE);

        idtf = sc_memory_node_new(sc_type_node | sc_type_node_norole | sc_type_const);
        link = sc_memory_link_new();

        sc_memory_set_link_content(link, stream);

        arc = sc_memory_arc_new(sc_type_arc_common | sc_type_const, idtf, link);
        sc_memory_arc_new(sc_type_arc_pos_const_perm, idtf, arc);

        sc_stream_free(stream);
        stream = (sc_stream*)nullptr;
    }
}

int main(int argc, char *argv[])
{
    // initialize sc-memory
    sc_memory_initialize("repo", 0);

    prepare();

    // ------------------
    sc_helper_init();

    sc_graph_initialize();


    // ----- create test there -----
    printf("Create tests...\n");
    tTestVector tests;
    tests.push_back(new TestGraphGen());
    tests.push_back(new TestGraphModify());
    tests.push_back(new TestFindConnComp());
    tests.push_back(new TestSearchIncidentVertexArc());

    // ------ run tests ----------
    printf("Run tests...\n");
    tTestVector::iterator it, itEnd = tests.end();
    bool result = false;
    for (it = tests.begin(); it != itEnd; ++it)
    {
        Test *test = *it;

        printf("\t%s\n", test->name().c_str());
        printf("\t\tPrepare...");
        result = test->prepare();
        PRINT_TEST_RESULT(result);
        if (!result) continue; // go to next test

        printf("\n\t\tRun...");
        result = test->run();

        printf("\n\t\tShutdown...");
        printf("\n\t---> ");
        PRINT_TEST_RESULT(result);
        printf("\n");
        test->done();
    }


    // ------ destroy tests ------
    printf("Destroy tests...\n");
    for (it = tests.begin(); it != itEnd; ++it)
        delete *it;
    tests.clear();

    sc_graph_shutdown();

    sc_memory_shutdown();
    return 0;
}
