#ifndef _test_graph_gen_h_
#define _test_graph_gen_h_

#include "test.h"

class TestGraphGen : public Test
{
public:
    explicit TestGraphGen();
    virtual ~TestGraphGen();

    //! \copydoc Test::name
    const String& name() const;
    //! \copydoc Test::run
    bool run();
    //! \copydoc Test::prepare
    bool prepare();
    //! \copydoc Test::done
    void done();

private:
    bool check_empty_graph_generation();

};

#endif // _test_graph_gen_h_
