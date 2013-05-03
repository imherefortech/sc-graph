#ifndef _test_graph_modify_h_
#define _test_graph_modify_h_

#include "test.h"

class TestGraphModify : public Test
{
public:
    explicit TestGraphModify();
    virtual ~TestGraphModify();

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
    bool check_vertex_creation();
    bool check_arc_creation();

private:
    //! Graph structure for modification
    sc_addr mGraphAddr;
};

#endif // _test_graph_modify_h_
