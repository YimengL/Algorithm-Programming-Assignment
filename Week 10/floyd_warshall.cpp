/* Algorithm: Design and Analysis, Week 10 Programming Assignment, Q1 */
/* Author: Yimeng Li */
/* Date: 2015/April/22 Wed */

# include <iostream>
# include <vector>
# include <string>
# include <climits>
# include <fstream>
# include <cmath>

using namespace std;

vector<vector<vector<int>>> dp;
int num_ver;
int global_min = INT_MAX;
const int INF = 10000000;

/* several functions' prototype */
void store_file(string);
void print_all(int);
void floyd_warshall(void);
/* **************************** */

int main(int argc, char** argv) {
	store_file("g3.txt");	
	floyd_warshall();

	cout << "Shortest shortest path: ";
	if (global_min == INF)
		cout << "NULL" << endl;
	else
		cout << global_min << endl;

	return 0;
}

void store_file(string filename) {
	int num_edge;

	ifstream infile;
	infile.open(filename, ios::in);
	infile >> num_ver >> num_edge;

	/* step 1 of Floyd-Warshall Algorithm: Base case */
	/* base case no.1: dp[0][s][e] = INF if edge(s, e) not exist */
	dp.resize(2, vector<vector<int>>(num_ver+1, vector<int>(num_ver+1, INF)));

	/* base case no.2: dp[k][s][e] = 0 if edge(s, e) exist */
	for (int i = 1; i <= num_ver; ++i) {
		dp[0][i][i] = 0;
	}

	/* base case no.3: dp[k][s][e]= w if edge(s, e) exist */
	int s, e, w;
	while(num_edge-- > 0) {
		infile >> s >> e >> w;
		dp[0][s][e] = w;
	}
//	print_all(0);		// for test
	infile.close();
}

/* just for test */
void print_all(int k) {
	for (int i = 1; i <= num_ver; ++i) {
		for (int j = 1; j <= num_ver; ++j) {
			if (dp[k%2][i][j] == INF)
				cout << "INF" << "\t";
			else
				cout << dp[k%2][i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void floyd_warshall(void) {
	// pseudocode of Floyd-Warshall algorithm:
	// For k = 1 to n
	//    For i = 1 to n
	//       For j = 1 to n
	//		    A[i][j][k] = min (A[i][j][k-1],						case 1
	//							   A[i][k][k-1] + A[k][j][k-1])		case 2
	for (int k = 1; k <= num_ver; ++k) {
		for (int i = 1; i <= num_ver; ++i) {
			for (int j = 1; j <= num_ver; ++j) {
				if (dp[(k-1)%2][i][k] != INF and dp[(k-1)%2][k][j] != INF 
					and dp[(k-1)%2][i][j] > (dp[(k-1)%2][i][k] + dp[(k-1)%2][k][j]))
					dp[k%2][i][j] = dp[(k-1)%2][i][k] + dp[(k-1)%2][k][j];
				else
					dp[k%2][i][j] = dp[(k-1)%2][i][j];
			}
		}
	}

	for (int i = 1; i <= num_ver; ++i) {
		for (int j = 1; j <= num_ver; ++j) {
			global_min = (dp[num_ver%2][i][j] < global_min) ? dp[num_ver%2][i][j] : global_min;
		}
	}

	// check if G has a negative cycle: Will have A[i][i][n] < 0 for at least one i at the end of algorithm
	for (int i = 1; i <= num_ver; ++i) {
		if (dp[num_ver%2][i][i] < 0) {
			global_min = INF;
			return;
		}
	}
}