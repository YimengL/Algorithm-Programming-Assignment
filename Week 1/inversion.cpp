/* Algorithm: Design and Analysis, Week 1 Programming Assignment */
/* Author: Yimeng Li */
/* Date: 2015/Jan/24 */

# include <iostream>
# include <fstream>
# include <vector>

using namespace std;

/* prototype */
long sort(vector<int>&, int, int);
long merge(vector<int>&, int, int, int);

int main(int argc, char** argv) {

	/* copy the file to inversion vector */
	vector<int> inversion;
	ifstream infile;
	infile.open("test6.txt", ios::in);
	int temp;
	long cnt = 0;
	while (infile >> temp) {
		inversion.push_back(temp);
	}
	infile.close();

	cnt = sort(inversion, 0, inversion.size()-1);
	cout << "number of inversions: " << cnt << endl;

	return 0;
}

long sort(vector<int>& vec, int low, int high) {
	vector<int> aux(vec);
	if (high <= low)
		return 0;
	int mid = low + (high - low) / 2;
	long x = sort(vec, low, mid);
	long y = sort(vec, mid+1, high);
	long z = merge(vec, low, mid, high);
	return (x + y + z);
}

long merge(vector<int>& vec, int low, int mid, int high) {
	long cnt = 0;
	int i = low;
	int j = mid + 1;
	vector<int> aux(vec);
	for (int k = low; k <= high; ++k) {
		if (i > mid)
			vec[k] = aux[j++];
		else if (j > high)
			vec[k] = aux[i++];
		else if (aux[i] < aux[j])
			vec[k] = aux[i++];
		else {
			vec[k] = aux[j++];
			cnt += (mid - i + 1);
		}
	}
	return cnt;
} 