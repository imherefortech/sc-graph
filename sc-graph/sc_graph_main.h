#ifndef _sc_graph_main_h_
#define _sc_graph_main_h_

#include "sc_graph_keynodes.h"
#include "sc_graph_generator.h"
#include "sc_graph_struct.h"
#include "sc_graph_find_conn_comp.h"


/*!
 * Initialize sc-graph library. Need to be called before library usage.
 * \attention sc_helper_initialize funciton must to be called before this one
 */
void sc_graph_initialize();

/*!
 * Shutdowns sc-graph library. Need to be called after library usage finished.
 */
void sc_graph_shutdown();

#endif // _sc_graph_main_h_
