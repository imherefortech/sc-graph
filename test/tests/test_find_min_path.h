#ifndef TEST_FIND_MIN_PATH_H
#define TEST_FIND_MIN_PATH_H

#include "test.h"

class TestFindMinPath : public Test
{
public:
    explicit TestFindMinPath();
    virtual ~TestFindMinPath();

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
    bool check_find_min_path_not_or();
    bool check_find_min_path_or();

private:
    //! Graph structure for modification
    sc_addr mOrGraphAddr;
    sc_addr mNotOrGraphAddr;
};

#endif // TEST_FIND_MIN_PATH_H
