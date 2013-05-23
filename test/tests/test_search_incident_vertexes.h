#ifndef _TEST_SEARCH_INCIDENT_VERTEXES_h
#define _TEST_SEARCH_INCIDENT_VERTEXES_h

#include "test.h"


class TestSearchIncidentVertexes : public Test
{
public:
   explicit TestSearchIncidentVertexes();
    virtual ~TestSearchIncidentVertexes();

protected:
    //! \copydoc Test::name
    const String& name() const;
    //! \copydoc Test::run
    bool run();
   //! \copydoc Test::prepare
    bool prepare();
    //! \copydoc Test::done
    void done();

private:
    bool check_search_incident_edge_vertexes();
    bool check_search_incident_arc_vertexes();


private:
    //! Graph structure for modification
    sc_addr mOrGraphAddr;
    sc_addr mNotOrGraphAddr;


};

#endif // TEST_SEARCH_INCIDENT_VERTEXES_H
