#ifndef SC_GRAPH_FIND_CONN_COMP_H
#define SC_GRAPH_FIND_CONN_COMP_H

#include "sc_graph_prerequest.h"
#include "sc_graph_types.h"

/* File contains functions to work with graph elements
 */
/*! Find connective components of the specified graph
 * \param graph sc-addr of graph structure to search connective components
 * \param sc_addr of a list of connective components; connective compoment is a graph
 * \return if connective components were found, return SC_RESULT_OK; otherwise return any error code
 */
sc_result sc_graph_find_conn_comp(sc_addr graph, sc_addr_list **conn_comp_set);

/*! Calculates the \p vertex degree of the \p graph
 * \param graph sc-addr of the graph structure which contains the vertex
 * \param vertex sc-addr of the vertex the dergeee of which needs calculating
 * \param result pointer to int that will contain the degree
 * \return If degree was found, return SC_RESULT_OK; otherwise returns any error code
 */
sc_result sc_graph_vertex_degree(const sc_addr graph, const sc_addr vertex, int *result);



/*! Find incident arc vertexes of the specified graph
 * \param graph sc-addr of graph structure to work with
 * \param arc sc-addr of arc to search incedent vertexes
 * \param listVertex list of incident vertexes
 * \return if vertexes were found, return SC_RESULT_OK; otherwise return any error code
 */
sc_result search_incident_vertexes(sc_addr graph, sc_addr arc, sc_addr_list **listVertex);



/*! Find incident vertex arcs of the specified graph
 * \param graph sc-addr of graph structure to work with
 * \param vertex sc-addr of vertex to search incident arcs
 * \param listArc list of incident arcs
 * \return if arcs were found, return SC_RESULT_OK; otherwise return any error code
 */

sc_result search_incident_vertex_arc(sc_addr graph, sc_addr vertex, sc_addr_list **listArc);


#endif // SC_GRAPH_FIND_CONN_COMP_H
