#ifndef TEST_FIND_CONN_COMP_H
#define TEST_FIND_CONN_COMP_H

#include "test.h"

class TestFindConnComp : public Test
{
public:
    explicit TestFindConnComp();
    virtual ~TestFindConnComp();

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
    bool check_find_conn_comp_not_or();
    bool check_find_conn_comp_or();

private:
    //! Graph structure for modification
    sc_addr mOrGraphAddr;
    sc_addr mNotOrGraphAddr;
};
#endif // TEST_FIND_CONN_COMP_H
