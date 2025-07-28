#include <algorithm>

#include <boost/graph/adjacency_list.hpp>

#include <cyber/solve.hpp>
#include <cyber/term.hpp>

namespace {

struct vertex_info {
    position_type position;
};

struct edge_info {
    std::size_t dimension;
};

struct search_info {
    bool skip;
    search_info(bool skip = false) : skip(skip) {}
};

using Graph = boost::adjacency_list<
    boost::vecS, boost::vecS,
    boost::directedS,
    boost::property<boost::vertex_index_t, vertex_info>,
    boost::property<boost::edge_index_t, edge_info>
>;
using Traits = boost::graph_traits<Graph>;

using vertex_index_type = boost::property_map<Graph, boost::vertex_index_t>::type;
using edge_index_type = boost::property_map<Graph, boost::edge_index_t>::type;
using search_index_type = boost::property_map<Graph, boost::vertex_index_t>::type;

using vertex_props_type = boost::vector_property_map<vertex_info, vertex_index_type>;
using edge_props_type = boost::vector_property_map<edge_info, edge_index_type>;
using search_props_type = boost::vector_property_map<search_info, vertex_index_type>;

void traverse(
    const Graph & graph,
    const matrix_type & matrix,
    const std::vector<std::vector<unsigned char>> & sequences,
    vertex_props_type & vertex_props,
    edge_props_type & edge_props,
    search_props_type & search_props,
    Traits::vertex_descriptor src_vertex_descriptor,
    edge_info src_edge_info,
    buffer_length_type distance,
    score_type & high_score,
    std::vector<Traits::vertex_descriptor> & path,
    std::vector<Traits::vertex_descriptor> & result
) {
    path.push_back(src_vertex_descriptor);
    put(search_props, src_vertex_descriptor, search_info{true});
    score_type score = 0;

    for (auto sequence = sequences.begin(); sequence != sequences.end(); ++sequence) {
        if (std::search(path.begin(), path.end(), sequence->begin(), sequence->end(),
            [&matrix,&vertex_props](Traits::vertex_descriptor vertex, unsigned char rhs){
                return matrix(get(vertex_props, vertex).position) == rhs;
            }
        ) != path.end()) {
            score += (1 << (std::distance(sequences.begin(), sequence)));
        }
    }
    if (score && (score > high_score || (score == high_score && path.size() < result.size()))) {
        high_score = score;
        result = path;
    }
    if (distance) {
        const auto edges = out_edges(src_vertex_descriptor, graph);
        for (auto edge = edges.first; edge != edges.second; ++edge) {
            const edge_info dst_edge_info = get(boost::edge_index_t(), graph, *edge);
            const Traits::vertex_descriptor dst_vertex_descriptor = target(*edge, graph);
            if (dst_edge_info.dimension != src_edge_info.dimension && !get(search_props, dst_vertex_descriptor).skip) {
                traverse(
                    graph, matrix, sequences,
                    vertex_props, edge_props, search_props,
                    dst_vertex_descriptor, dst_edge_info,
                    distance - 1,
                    high_score,
                    path, result
                );
            }
        }
    }
    put(search_props, src_vertex_descriptor, search_info{false});
    path.pop_back();
}

} // namespace

solved_type solve(
    const matrix_type & matrix,
    const sequences_type & sequences,
    const buffer_length_type buffer
) {
    Graph graph(matrix.shape()[0] * matrix.shape()[1]);

    vertex_index_type vertex_index(get(boost::vertex_index, graph));
    vertex_props_type vertex_props(num_vertices(graph), vertex_index);

    edge_index_type edge_index(get(boost::edge_index, graph));
    edge_props_type edge_props(num_edges(graph), edge_index);

    search_index_type search_index(get(boost::vertex_index, graph));
    search_props_type search_props(num_vertices(graph), search_index);

    // Store vertex values
    for (std::size_t r = 0; r < matrix.shape()[0]; ++r) {
        for (std::size_t c = 0; c < matrix.shape()[1]; ++c) {
            // NOTE: For whatever insane reason, multi_array::index uses SIGNED indices.
            vertex_info info{{static_cast<position_type::value_type>(r), static_cast<position_type::value_type>(c)}};
            put(vertex_props, Traits::vertex_descriptor{r * matrix.shape()[1] + c}, info);
        }
    }

    // Store horizontal edge directions
    for (std::size_t r = 0; r < matrix.shape()[0]; ++r) {
        for (std::size_t c_a = 0; c_a < matrix.shape()[1]; ++c_a) {
            for (std::size_t c_b = 0; c_b < matrix.shape()[1]; ++c_b) {
                if (c_a != c_b) {
                    add_edge(
                        Traits::vertex_descriptor{r * matrix.shape()[1] + c_a},
                        Traits::vertex_descriptor{r * matrix.shape()[1] + c_b},
                        boost::property<boost::edge_index_t, edge_info>(edge_info{0}),
                        graph
                    );
                }
            }
        }
    }

    // Store vertical edge directions
    for (std::size_t c = 0; c < matrix.shape()[1]; ++c) {
        for (std::size_t r_a = 0; r_a < matrix.shape()[0]; ++r_a) {
            for (std::size_t r_b = 0; r_b < matrix.shape()[0]; ++r_b) {
                if (r_a != r_b) {
                    add_edge(
                        Traits::vertex_descriptor{r_a * matrix.shape()[1] + c},
                        Traits::vertex_descriptor{r_b * matrix.shape()[1] + c},
                        boost::property<boost::edge_index_t, edge_info>(edge_info{1}),
                        graph
                    );
                }
            }
        }
    }

    std::vector<Traits::vertex_descriptor> result;
    std::vector<Traits::vertex_descriptor> path;
    score_type high_score = 0;
    for (std::size_t c = 0; c < matrix.shape()[1]; ++c) {
        const Traits::vertex_descriptor vertex{c};
        traverse(
            graph, matrix, sequences,
            vertex_props, edge_props, search_props,
            vertex, edge_info{0},
            buffer - 1,
            high_score,
            path, result
        );
    }

    return solved_type {
        [&matrix,&vertex_props,&result](){
            path_type path;
            std::transform(result.begin(), result.end(), std::back_insert_iterator(path), [&matrix,&vertex_props](const Traits::vertex_descriptor & vertex){
                return get(vertex_props, vertex).position;
            });
            return path;
        }(),
        high_score
    };
}
