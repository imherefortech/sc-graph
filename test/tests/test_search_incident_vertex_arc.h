#ifndef _TEST_SEARCH_INCIDENT_VERTEX_ARC_h
#define _TEST_SEARCH_INCIDENT_VERTEX_ARC_h

#include "test.h"


class TestSearchIncidentVertexArc : public Test
{
public:
    explicit TestSearchIncidentVertexArc();
    virtual ~TestSearchIncidentVertexArc();

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
    bool check_search_incident_vertex_edge();
    bool check_search_incident_vertex_arc();


private:
    //! Graph structure for modification
    sc_addr mGraphAddr_oriented;
    sc_addr mGraphAddr_not_oriented;


};

#endif // TEST_SEARCH_INCIDENT_VERTEX_ARC_H
