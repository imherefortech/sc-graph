#ifndef TEST_CHECK_GRAPH_IS_CUBIC_H
#define TEST_CHECK_GRAPH_IS_CUBIC_H

#include "test.h"

class TestCheckGraphIsCubic : public Test
{
public:
    explicit TestCheckGraphIsCubic();
    virtual ~TestCheckGraphIsCubic();

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
    bool check_graph_is_cubic_not_or();
    bool check_graph_is_cubic_or();

private:
    //! Graph structure for modification
    sc_addr mGraphAddrOrient;
    sc_addr mGraphAddrNotOrient;
};

#endif // TEST_CHECK_GRAPH_IS_CUBIC_H
