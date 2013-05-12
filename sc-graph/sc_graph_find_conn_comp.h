#ifndef SC_GRAPH_FIND_CONN_COMP_H
#define SC_GRAPH_FIND_CONN_COMP_H

#include "sc_graph_prerequest.h"

/* File contains functions needed for connective components search
 */
/*! Find connective components of the specified graph
 * \param graph sc-addr of graph structure to search connective components
 *
 * \return sc_addr of a set of connective components; connective compoment is a set of vertices
 */
sc_addr sc_graph_find_conn_comp(sc_addr graph);

/*! Deep first search to build a connective component
 * \param starting vertex of a search
 * \param set of not checked vertices
 * \param connective component that is being built by this search
 * \param graph sc-addr of graph structure to search connective components
 *
 */
void deep_first_search(sc_addr curr_vertex, sc_addr not_checked_vertices,
                       sc_addr curr_conn_comp, sc_addr graph);

#endif // SC_GRAPH_FIND_CONN_COMP_H
