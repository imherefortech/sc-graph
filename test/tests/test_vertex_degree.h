#ifndef TEST_VERTEX_DEGREE_H
#define TEST_VERTEX_DEGREE_H

#include "test.h"

class TestVertexDegree : public Test
{
public:
    explicit TestVertexDegree();
    virtual ~TestVertexDegree();

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
    bool check_vertex_degree_in_oriented_graph();
    bool check_vertex_degree_in_not_oriented_graph();

private:
    //! Not oriented test graph
    sc_addr not_oriented_graph;
    //! Oriented test graph
    sc_addr oriented_graph;
    //! Vertex for degree calculation
};

#endif // TEST_VERTEX_DEGREE_H
