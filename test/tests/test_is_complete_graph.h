#ifndef TEST_IS_COMPLETE_GRAPH_H
#define TEST_IS_COMPLETE_GRAPH_H

#include "test.h"

class TestIsCompleteGraph : public Test
{
public:
    explicit TestIsCompleteGraph();
    virtual ~TestIsCompleteGraph();

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
    bool check_is_complete_graph();


private:
    //! Graph structure for modification
    sc_addr mGraphAddr_oriented;
    sc_addr mGraphAddr_not_oriented;


};

#endif // TEST_IS_COMPLETE_GRAPH_H
