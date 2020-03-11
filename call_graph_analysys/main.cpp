#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <iostream>
#include <random>

int main() {
	boost::adjacency_list<> g;
	std::mt19937 rng{ 42 };

	generate_random_graph(g, 10, 20, rng);

	for (auto vd : boost::make_iterator_range(adjacent_vertices(5, g)))
	{
		std::cout << "vertex " << vd << " is an out-edge of vertex 5\n";
	}
}