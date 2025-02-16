#include "../include/graph.hpp"

int main ()
{
    Graph<int> g;
    g.add_edge(1,2);
    g.add_edge(2,3);
    g.add_edge(1,3);
    g.add_edge(1,1);
    std::cout << g;
}
