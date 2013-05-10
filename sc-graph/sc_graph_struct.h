#ifndef _sc_graph_struct_h_
#define _sc_graph_struct_h_

#include "sc_graph_prerequest.h"

/* File contains functions to work with graph structure.
 */

/*! Create new node in specified graph structure
 * \param graph sc-addr of graph structure to append new node in
 * \param vertex Pointer to sc-addr that will contain addr of created vertex
 *
 * \return If node created succesffully, then return SC_RESULT_OK; otherwise return any error code
 */
sc_result sc_graph_create_vertex(sc_addr graph, sc_addr *vertex);

/*! Create new arc in specified graph. Between two vertecies.
 * \param graph sc-addr of graph structure to append new arc in
 * \param v1 Element where arc will be started
 * \param v2 Element where arc will be ended
 * \param arc Pointer to sc-addr that will contain addr of created arc
 * \return If arc created, then return SC_RESULT_OK; otherwise return
 * error code
 * \note \p v1 and \p v2 must be a verticies of the \p graph structure
 */
sc_result sc_graph_create_arc(sc_addr graph, sc_addr v1, sc_addr v2, sc_addr *arc);



/*! Checks if the specified \p vertex exist in the \p graph
 * \param graph sc-addr of graph structure to check if \p vetrex exist
 * \param vertex sc-addr of vertex to check
 *
 * \return If \p vertex exist in the \p graph, then return SC_RESULT_OK; otherwise return error code
 */
sc_result sc_graph_check_vertex(sc_addr graph, sc_addr vertex);

/*! Checks if the specified \p arc exist in the \p graph
 * \param graph sc-addr of graph structure to check if \p arc exist
 * \param arc sc-addr of arc to check
 *
 * \return If \p arc exist in the \p graph, then return SC_RESULT_OK; otherwise return error code
 */
sc_result sc_graph_check_arc(sc_addr graph, sc_addr arc);

/*! Checks if the specified \p element exist in the \p graph. Element can be an a vertex or arc
 * \param graph sc-addr of graph structure to check if \p element exist
 * \param element sc-addr of element to check
 *
 * \return If \p element exist in the \p graph, then return SC_RESULT_OK; otherwise return error code
 */
sc_result sc_graph_check_element(sc_addr graph, sc_addr element);

/*! Check if two graph elements connected with any arc
 * \param graph sc-addr of graph structure for check
 * \param v1 Element where checked arc starts
 * \param v2 Element where checked arc ends
 * \return If arc between \p v1 and \p v2 exist, then return SC_RESULT_OK; otherwise return error code
 */
sc_result sc_graph_check_elements_adjacency(sc_addr graph, sc_addr v1, sc_addr v2);

/*! Count number of vertices in specified graph
 * \param graph sc-addr of graph structure
 * \return return the number of vertices if \p graph is correct; otherwise return -1
 */
int sc_graph_count_vertices(sc_addr graph);

#endif // _sc_graph_struct_h_
