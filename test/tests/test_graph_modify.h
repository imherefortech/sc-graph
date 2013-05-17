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
    bool check_edge_creation();
    bool check_arc_creation();
    bool check_adjacency_in_not_oriented_graph();
    bool check_adjacency_in_oriented_graph();

private:
    //! Graph structure for modification
    sc_addr mGraphAddr_oriented;
    sc_addr mGraphAddr_not_oriented;
};

#endif // _test_graph_modify_h_
