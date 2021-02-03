#include "../include/inertial_flow_cutter.h"
#include <iostream>


ListGraph load_adj_list(std::vector<std::vector<int>> &adj)
{
    ListGraph graph;
    int n = 0;
    int m = 0;

    for (unsigned int i = 0; i < adj.size(); i++)
    {
        n++;
        for (unsigned int j = 0; j < adj[i].size(); j++)
        {
            m++;
        }
    }

    graph = ListGraph(n, m);
    int next_arc = 0;

    for (unsigned int i = 0; i < adj.size(); i++)
    {
        for (unsigned int j = 0; j < adj[i].size(); j++)
        {
            graph.head[next_arc] = i;
            graph.tail[next_arc] = adj[i][j];
            graph.arc_weight[next_arc] = 1;
            next_arc++;
        }
    }

    return graph;
}

ListGraph load_adj_list(std::vector<std::vector<int>> &adj, std::vector<int> &active)
{
    ListGraph graph;
    int n = 0;
    int m = 0;

    for (unsigned int i = 0; i < adj.size(); i++)
    {
        if (active[i] < 0)
        {
            n++;
            for (int neigh : adj[i])
            {
                if (active[neigh])
                    m++;
            }
        }
    }

    graph = ListGraph(n, m);
    int next_arc = 0;

    for (unsigned int i = 0; i < adj.size(); i++)
    {
        if (active[i] < 0) 
        {
            for (auto neigh : adj[i])
            {
                if (active[neigh] < 0)
                {
                    graph.head[next_arc] = i;
                    graph.tail[next_arc] = neigh;
                    graph.arc_weight[next_arc] = 1;
                    next_arc++;
                }
            }
        }
    }

    return graph;
}

void get_nd_separators_cutter(std::vector<std::vector<int>> &adj, double balance, std::vector<std::pair<int, std::vector<int>>> &separators, int max_levels)
{
    auto graph = load_adj_list(adj);

    auto sep_algo = my_kahip::ComputeSeparator(balance);
    cch_order::compute_nested_dissection_graph_order(std::move(graph.tail), std::move(graph.head),
                                                     std::move(graph.arc_weight), sep_algo, 0, separators, max_levels + 1);    
}

/*void get_nd_separators(std::vector<std::vector<int>> &adj, std::vector<int> &active, double balance, std::vector<std::pair<int, std::vector<int>>> &separators)
{
    auto graph = load_adj_list(adj, active);

    auto sep_algo = my_kahip::ComputeSeparator(balance);
    cch_order::compute_nested_dissection_graph_order(std::move(graph.tail), std::move(graph.head),
                                                     std::move(graph.arc_weight), sep_algo, 0, separators);    
}*/
