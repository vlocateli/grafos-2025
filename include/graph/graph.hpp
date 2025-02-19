#ifndef GRAPH_HPP
#define GRAPH_HPP 1
#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <forward_list>
#include <sstream>
#include <array>
//#define GRAPH_CHECK_DUPLICATE_EDGE 1
#define DEBUG 1
#ifdef DEBUG
#define DBG(x) std::cerr << #x << ": " << x << '\n';
#endif // DEBUG
template<typename T>
struct Edge{
    T target_id_;
};
template<typename T>
struct Vertex{
    T id_;
    std::forward_list<Edge<T>> edge_list_;
};
template<typename T>
class Graph{
    public:
        Graph();
        Graph(size_t order);
        void add_edge(T const& p, T const& q);
        ~Graph() = default;
        friend inline std::ostream& operator<<(std::ostream& stream, Graph const& g)
        {
            if (!g.num_vertices_) {
                stream << "Null-Graph\n";
                return stream;
            }
            for (const auto& vertex : g.vertices_) {
                stream << "Vertex " << vertex.id_ << " is connected to: ";
                for (auto edge : vertex.edge_list_) {
                    stream << edge.target_id_ << " ";
                }
                stream << '\n';
            }
            return stream;
        }
        void read_from(std::vector<std::string> const& buff);
    private:
        std::vector<Vertex<T>> vertices_;
        size_t  num_vertices_;
        size_t  num_edges_;
        bool has_edge(T p, T q) const;
        void add_edge_to_vertex(Vertex<T> const& v, Edge<T> const& e);
        size_t graph_type_;

};
template <typename T>
Graph<T>::Graph()
    :
        num_vertices_{0}

{
}
template<typename T>
Graph<T>::Graph(size_t order)
    :
        num_vertices_{order}
{
    vertices_.reserve(order);
}
// TODO:
//      1) Check if p and q are equal; so it's a loop.
template<typename T>
void Graph<T>::add_edge(T const& p, T const& q)
{
#ifdef GRAPH_CHECK_DUPLICATE_EDGE
    if (!has_edge(p, q)) {
        auto v1 = Vertex<T>{p, {}};
        v1.edge_list_.emplace_front(Edge<T>{q});
        num_vertices_++;
        vertices_.push_back(v1);
    }
#else 
    auto v1 = Vertex<T>{p, {}};
    v1.edge_list_.emplace_front(Edge<T>{q});
    num_vertices_++;
    vertices_.push_back(v1);
    num_vertices_++;
#endif // GRAPH_CHECK_DUPLICATE_EDGE
    if (p == q) {
        num_vertices_ += 2;
        return;
    }
    num_vertices_++;
}
template<typename T>
bool Graph<T>::has_edge(T p, T q) const
{
    for (auto vert : vertices_) {
        if (vert.id_ == p) {
            for (auto edge : vert.edge_list_) {
                if (edge.target_id_ == q) {
                    return true;
                }
            }
        }
    }
    return false;
}
template<typename T>
void Graph<T>::add_edge_to_vertex(Vertex<T> const& p, Edge<T> const& q)
{
    assert(0 && "Unimplemented");
}

template<typename T>
void Graph<T>::read_from(std::vector<std::string> const& buff)
{
   std::stringstream ss;
   std::vector<size_t> graph_info;
   size_t info;
   for (const auto& line : buff) {       
       ss << line;
       ss >> info;
       graph_info.push_back(info);
   }
   graph_type_ = graph_info.at(0);
   num_vertices_ = graph_info.at(1);
   num_edges_ = graph_info.at(num_vertices_ + 2);
   DBG(graph_type_);
   DBG(num_vertices_);
   DBG(num_edges_);
}
#endif // GRAPH_HPP
