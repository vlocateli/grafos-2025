#ifndef GRAPH_HPP
#define GRAPH_HPP 1
#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <forward_list>
//#define GRAPH_CHECK_DUPLICATE_EDGE 1

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
    private:
        std::vector<Vertex<T>> vertices_;
        size_t  num_vertices_;
        bool has_edge(T p, T q) const;
        void add_edge_to_vertex(Vertex<T> const& v, Edge<T> const& e);
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
#endif // GRAPH_HPP
