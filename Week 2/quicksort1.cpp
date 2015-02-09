/* Algorithm: Design and Analysis, Week 2 Programming Assignment, Q1 */
/* Author: Yimeng Li */
/* Date: 2015/Feb/08 Sun */

# include <iostream>
# include <fstream>
# include <vector>

using namespace std;

/* prototype of the two functions in quicksort */
long sort(vector<int>&, int, int);
int partition(vector<int>&, int, int);

int main(int argc, char** argv) {

	vector<int> num;

	/* store the elements in txt file into num vector */
	ifstream infile;
	infile.open("QuickSort.txt", ios::in);
	int tmp;
	while (infile >> tmp)
		num.push_back(tmp);
	infile.close();

	/* start sorting */
	long cnt = 0;
	cnt = sort(num, 0, num.size()-1);

	for (int i = 0; i < num.size(); ++i)
		cout << num[i] << endl;
	cout << cnt << endl;

	return 0;
}

long sort(vector<int>& num, int low, int high) {
	if (high <= low)
		return 0;
	int pivot = partition(num, low, high);
	int tmp1 = sort(num, low, pivot-1);
	int tmp2 = sort(num, pivot+1, high);
	return (tmp1 + tmp2 + (high - low));
}

int partition(vector<int>& num, int low, int high) {
	int pivot = num[low];
	int i = low + 1;
	int j;
	for (j = low + 1; j <= high; ++j) {
		if (num[j] < pivot) {
			swap(num[j], num[i]);
			++i;
		}
		/* else, do nothing */
	}
	swap(num[low], num[i-1]);
	return (i - 1);
}