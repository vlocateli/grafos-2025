#include "../include/parser/parser.hpp"
#include "../include/graph/graph.hpp"
int main ()
{
    Parser p("dummy.txt");
    p.parse_file();
    auto buff = p.buff();
    Graph<int> g;
    g.read_from(buff);
}
