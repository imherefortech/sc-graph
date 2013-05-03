#ifndef _sc_graph_generator_h_
#define _sc_graph_generator_h_

#include "sc_graph_prerequest.h"

// File contains generators for graph structures


/*! Generates empty graph structure in sc-memory
 * @param graph Pointer to sc-addr that will contains generated graph structure
 * @return If graph structure created, then return SC_TRUE; otherwise returns SC_FALSE
 */
sc_bool sc_graph_generate_empty(sc_addr *graph);

#endif // _sc_graph_generator_h_
