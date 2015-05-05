/* Algorithm: Design and Analysis, Week 11 Programming Assignment, Q1 */
/* Author: Yimeng Li */
/* Date: 2015/May/04 Mon */

# include <iostream>
# include <string>
# include <vector>
# include <fstream>
# include <cmath>
# include <algorithm>
# include <climits>

using namespace std;

/* use Euclidean Distance */
struct e_pos {
	double x_axis;
	double y_axis;
};
vector<e_pos> vertice;
double global_min = INT_MAX;

void store_file(string);
void print_all(vector<e_pos>);
void opt2_tsp(vector<e_pos>);
double dist(vector<e_pos>, int, int);
double final_distance(vector<e_pos>);

int main(int argc, char** argv) {

	store_file("tsp.txt");
	cout << "Initial: " << final_distance(vertice) << endl;
	vector<e_pos> vertice_tmp = vertice;
	for (int i = 0; i < 1000; ++i) {
		random_shuffle(vertice_tmp.begin(), vertice_tmp.end());
		opt2_tsp(vertice_tmp);
//		print_all(vertice_tmp);
		cout << "min: " << global_min << endl;
	}
	return 0;
}

void store_file(string filename) {
	ifstream infile;
	infile.open(filename, ios::in);

	int num_of_ver;
	infile >> num_of_ver;
	vertice.resize(num_of_ver);
	double x_tmp, y_tmp;

	for (int i = 0; i < num_of_ver; ++i) {
		infile >> x_tmp >> y_tmp;
		vertice[i].x_axis = x_tmp;
		vertice[i].y_axis = y_tmp;
	}
	infile.close();
}

void print_all(vector<e_pos> vertice) {
	for (int i = 0; i < vertice.size(); ++i) {
		cout << vertice[i].x_axis << " -- " << vertice[i].y_axis << endl;
	}
	cout << endl;
}

void opt2_tsp(vector<e_pos> vertice_tmp) {
	double min_change;
	do {
		min_change = 0;
		int min_i = -1;
		int min_j = -1;
		for (int i = 0; i < vertice_tmp.size() - 3; ++i) {
			for (int j = i + 2; j < vertice_tmp.size() - 1; ++j) {
				double change = dist(vertice_tmp, i, j) + dist(vertice_tmp, i+1, j+1) 
				- dist(vertice_tmp, i, i+1) - dist(vertice_tmp, j, j+1);
				if (change - min_change < -0.0000000001) {
					min_change = change;
					min_i = i;
					min_j = j;
				}
			}
		}
		if (min_change < 0) {
			swap(vertice_tmp[min_i+1], vertice_tmp[min_j]);
		}
	} while (min_change < 0);
	double res = final_distance(vertice_tmp);
	if (res < global_min)
		global_min = res;
	cout << "Distance: " << res << " then ";
}

// calculate the distance between two positions
double dist(vector<e_pos> vertice_tmp, int i, int j) {
	return sqrt(pow(vertice_tmp[i].x_axis - vertice_tmp[j].x_axis, 2) + 
		pow(vertice_tmp[i].y_axis - vertice_tmp[j].y_axis, 2));
}

// calculate the final distance
double final_distance(vector<e_pos> vertice_tmp) {
	double res = 0;
	for (int i = 0; i < vertice_tmp.size()-1; ++i) {
		res += dist(vertice_tmp, i, i+1);
	}
	res += dist(vertice_tmp, 0, vertice_tmp.size()-1);
	return res;
}