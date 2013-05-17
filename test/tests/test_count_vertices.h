#ifndef TEST_COUNT_VERTICES_H
#define TEST_COUNT_VERTICES_H

#include "test.h"

class TestCountVertices : public Test
{
public:
    explicit TestCountVertices();
    virtual ~TestCountVertices();

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
    bool check_count_vertices();

private:
    //! Graph structure for counting vertices
    sc_addr mGraphAddr;
};

#endif // TEST_COUNT_VERTICES_H
