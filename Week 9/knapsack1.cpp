# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <cmath>

using namespace std;

struct item {
	int value;
	int weight;
};
vector<item> items;
int k_size;		/* knapsack_size */
int num;		/* number of items */

void store_file(string);
void print_all(void);
int knapsack(void);

int main(int argc, char** argv) {
	store_file("knapsack_big.txt");
	print_all();
//	cout << "Result: " << knapsack() << endl;
	return 0;
}

void store_file(string filename) {
	ifstream infile;
	infile.open(filename, ios::in);
	infile >> k_size >> num;
	int i = 0;
	int v, w;
	while (i < num) {
		infile >> v >> w;
		item tmp = {v, w};
		items.push_back(tmp);
		++i;
	}
	infile.close();
}

void print_all(void) {
	for (int i = 0; i < items.size(); ++i)
		cout << items[i].value << " " << items[i].weight << endl;
}

int knapsack(void) {
	vector<vector<int>> dp(num + 1, vector<int>(k_size + 1, 0));
	for (int i = 1; i <= num; ++i) {
		if (i%10000 == 0)
			cout << i << endl;
		for (int x = 0; x <= k_size; ++x) {
			int case1 = dp[i-1][x];
			int case2 = 0;
			if (items[i].weight <= x)
				case2 = dp[i-1][x-items[i].weight] + items[i].value;
			dp[i][x] = max(case1, case2);
		}
	}
	return dp[num][k_size];
}