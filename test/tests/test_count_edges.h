#ifndef TEST_COUNT_EDGES_H
#define TEST_COUNT_EDGES_H

#include "test.h"

class TestCountEdges : public Test
{
public:
    explicit TestCountEdges();
    virtual ~TestCountEdges();

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
    bool check_count_edges();

private:
    //! Graph structure for counting vertices
    sc_addr mGraphAddr;
};

#endif // TEST_COUNT_EDGES_H
