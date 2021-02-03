#ifndef INERTIAL_FLOW_CUTTER_H
#define INERTIAL_FLOW_CUTTER_H


#include "../src/min_fill_in.h"
#include "../src/list_graph.h"

#include <vector>

#ifdef USE_KAHIP
#include "../src/my_kahip.h"
#endif


ListGraph load_adj_list(std::vector<std::vector<int>> &adj);
ListGraph load_adj_list(std::vector<std::vector<int>> &adj, std::vector<int> &active);

void get_nd_separators_cutter(std::vector<std::vector<int>> &adj, double balance, std::vector<std::pair<int, std::vector<int>>> &separators, int max_levels = 1000000);
//void get_nd_separators(std::vector<std::vector<int>> &adj, std::vector<int> &active, double balance, std::vector<std::pair<int, std::vector<int>>> &separators);

#endif
