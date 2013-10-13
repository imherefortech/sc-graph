#ifndef TEST_CHECK_GRAPH_IS_REGULAR_H
#define TEST_CHECK_GRAPH_IS_REGULAR_H

#include "test.h"

class TestCheckGraphIsRegular : public Test
{
public:
    explicit TestCheckGraphIsRegular();
    virtual ~TestCheckGraphIsRegular();

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
   // bool check_graph_is_regular();
    bool check_graph_is_regular_not_or();
    bool check_graph_is_regular_or();

private:
    //! Graph structure for modification
    sc_addr mGraphAddrOrient;
    sc_addr mGraphAddrNotOrient;
};

#endif // TEST_CHECK_GRAPH_IS_REGULAR_H
