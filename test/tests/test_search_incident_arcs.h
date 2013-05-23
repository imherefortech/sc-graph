#ifndef _TEST_SEARCH_INCIDENT_ARCS_h
#define _TEST_SEARCH_INCIDENT_ARCS_h

#include "test.h"


class TestSearchIncidentArcs : public Test
{
public:
    explicit TestSearchIncidentArcs();
    virtual ~TestSearchIncidentArcs();

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
    bool check_search_incident_edges();
    bool check_search_incident_arcs();


private:
    //! Graph structure for modification
    sc_addr mOrGraphAddr;
    sc_addr mNotOrGraphAddr;


};

#endif // TEST_SEARCH_INCIDENT_ARCS_H
