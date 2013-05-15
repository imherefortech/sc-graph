#ifndef TEST_FIND_MIN_PATH_H
#define TEST_FIND_MIN_PATH_H

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
    bool check_find_conn_comp();

private:
    //! Graph structure for modification
    sc_addr mGraphAddr;
};

#endif // TEST_FIND_MIN_PATH_H
