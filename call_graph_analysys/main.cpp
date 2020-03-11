#include<iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include <libs/graph/src/read_graphviz_new.cpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include<map>
#include<vector>

using namespace boost;
using namespace std;

struct DotVertex {

	std::string label;

};

struct DotEdge {
	std::string label;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, DotVertex, DotEdge> graph_t;
//typedef boost::graph_traits<graph_t>::vertex_descriptor DotVertex;
typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_t;




int main() {
	vector <string> func_vec{ "{adpcm_main}","{upzero}", "{quantl}", "{encode}","{decode}" };

	for (int i = 3; i < 100; i++) {
		graph_t graphviz;
		boost::dynamic_properties dp(boost::ignore_other_properties);

		//	dp.property("node_id", boost::get(&DotVertex::name, graphviz));
		dp.property("label", boost::get(&DotVertex::label, graphviz));
		//dp.property("peripheries", boost::get(&DotVertex::peripheries, graphviz));
		dp.property("label", boost::get(&DotEdge::label, graphviz));
		std::ifstream dot("O:/total_new_apdcm/total_new_solution" + to_string(i) +"/callgraph.dot");
	



		bool status = boost::read_graphviz(dot, graphviz, dp);
		if (status)
			cout << 255;

		map <string, vector<string>> graph_map;
		string file_path_name = "O:/total_new_apdcm/total_new_solution" + to_string(i) + "/call_graph_detail.gph";
		cout << file_path_name << endl;
		std::ofstream outfile(file_path_name);

		for (auto v : make_iterator_range(vertices(graphviz))) {
			string parent_name = graphviz[v].label;

			if (std::find(func_vec.begin(), func_vec.end(), parent_name) != func_vec.end()) {
			//	std::cout << "Element found" << endl;

				vector <string> child_vec;
				for (auto w : make_iterator_range(adjacent_vertices(v, graphviz))) {

					string child_name = graphviz[w].label;

					if (std::find(func_vec.begin(), func_vec.end(), child_name) != func_vec.end()) {
						child_vec.push_back(child_name);
					}


				}

				graph_map.emplace(parent_name, child_vec);
				child_vec.clear();

			}
		}

		for (auto& x : graph_map) {

		//	cout << x.first << "-> ";

			outfile << "garph " << x.first << "-> ";

			for (int i = 0; i < x.second.size(); i++) {
				//cout << x.second[i] << ",";
				outfile << x.second[i] << ",";
				
			}
		//	cout << endl;
			outfile << endl;

		}

		outfile.close();
		graph_map.clear();
	}

	system("pause");
	return 0;

}
