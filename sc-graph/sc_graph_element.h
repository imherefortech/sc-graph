#ifndef SC_GRAPH_FIND_CONN_COMP_H
#define SC_GRAPH_FIND_CONN_COMP_H

#include "sc_graph_prerequest.h"
#include "sc_graph_types.h"

/* File contains functions to work with graph elements
 */
/*! Find connective components of the specified graph
 * \param graph sc-addr of graph structure to search connective components
 * \param sc_addr of a set of connective components; connective compoment is a set of vertices
 * \return if connective components were found, return SC_RESULT_OK; otherwise return any error code
 */
sc_result sc_graph_find_conn_comp(sc_addr graph, sc_addr *conn_comp_set);



/*! Find incident arc vertexes of the specified graph
 * \param graph sc-addr of graph structure to work with
 * \param arc sc-addr of arc to search incedent vertexes
 * \param listVertex list of incident vertexes
 * \return if vertexes were found, return SC_RESULT_OK; otherwise return any error code
 */
sc_result search_incident_vertexes(sc_addr graph, sc_addr arc, sc_addr_list **listVertex);



#endif // SC_GRAPH_FIND_CONN_COMP_H
