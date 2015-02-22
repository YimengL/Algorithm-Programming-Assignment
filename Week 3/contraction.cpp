/* Algorithm: Design and Analysis, Week 3 Programming Assignment */
/* Author: Yimeng Li */
/* Date: 2015/Feb/21 Sat */

# include <iostream>
# include <vector>
# include <fstream>
# include <sstream>
# include <string>
# include <cstdlib>
# include <ctime>
# include <cmath>
# include <climits>
# include <unistd.h>

using namespace std;

const int TIMES = 5000;

/* function prototype */
void store_file(vector<vector<int> >&, string);
void print_adjacency_list(vector<vector<int> >&);
int contraction(vector<vector<int>>&);
void random_pick(vector<vector<int>>&, int&, int&);
void merge_vertex(vector<vector<int>>&, int&, int&);
void remove_loop(vector<vector<int>>&, int&, int&);

int main(int argc, char** argv) {

	vector<vector<int> > adjacency_list;
	/* store the elements in txt file into adjacency list */
	store_file(adjacency_list, "40.txt");
	vector<vector<int>> tmp = adjacency_list;
	print_adjacency_list(adjacency_list);
	srand((unsigned)time(NULL));

	/* karger contraction */
	int min_cut = INT_MAX;
	for (int i = 0; i < TIMES; ++i) {
		adjacency_list = tmp;
		int inter_val = contraction(adjacency_list);
		min_cut = min(inter_val, min_cut);
		cout << min_cut << ": " << i << endl;
	}
	cout << "min-cut: " << min_cut << endl;

	return 0;
}

/* store the txt file into adjacency list */
void store_file(vector<vector<int> >& adjacency_list, string filename) {
	ifstream infile;
	infile.open(filename, ios::in);
	string line;
	while (getline(infile, line)) {
		vector<int> tmp_list;
		istringstream istr(line);
		int tmp;
		while (istr >> tmp)
			tmp_list.push_back(tmp);
		adjacency_list.push_back(tmp_list);
	}
	infile.close();
}

/* print the adjacency list */
void print_adjacency_list(vector<vector<int> >& adjacency_list) {
	for(int i = 0; i < adjacency_list.size(); ++i) {
		for (int j = 0; j < adjacency_list[i].size(); ++j)
			cout << adjacency_list[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

/* karger contraction */
int contraction(vector<vector<int>>& adjacency_list) {
	while (adjacency_list.size() > 2) {
		int index_u = 0;
		int index_v = 0;
		random_pick(adjacency_list ,index_u, index_v);
		merge_vertex(adjacency_list, index_u, index_v);
		remove_loop(adjacency_list, index_u, index_v);
	}
	return adjacency_list[0].size() - 1;
}

/* random pick edge u-v */
void random_pick(vector<vector<int>>& adjacency_list, int& index_u, int& index_v) {
	
	index_u = rand() % adjacency_list.size();
	int tmp_v = (rand() % (adjacency_list[index_u].size() - 1)) + 1;
	for (int i = 0; i < adjacency_list.size(); ++i)
		if (adjacency_list[i][0] == adjacency_list[index_u][tmp_v]) {
			index_v = i;
			break;
		}
}

/* merge the u and v, keep u, delete v */
void merge_vertex(vector<vector<int>>& adjacency_list, int& index_u, int& index_v) {
	for (int i = 0; i < adjacency_list.size(); ++i) {
		if (i != index_v) {
			for (int j = 1; j < adjacency_list[i].size(); ++j) {
				if (adjacency_list[i][j] == adjacency_list[index_v][0])
					adjacency_list[i][j] = adjacency_list[index_u][0];
			}
		}
	}
	for (int i = 1; i < adjacency_list[index_v].size(); ++i)
		adjacency_list[index_u].push_back(adjacency_list[index_v][i]);
}

/* remove self-loop */
void remove_loop(vector<vector<int>>& adjacency_list, int& index_u, int& index_v) {
	for (int i = 1; i < adjacency_list[index_u].size(); ++i)
		if (adjacency_list[index_u][i] == adjacency_list[index_u][0]) {
			adjacency_list[index_u].erase(adjacency_list[index_u].begin() + i);
			--i;
		}
	adjacency_list.erase(adjacency_list.begin() + index_v);
}