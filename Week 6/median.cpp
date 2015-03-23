/* Algorithm: Design and Analysis, Week 6 Programming Assignment, Q2 */
/* Author: Yimeng Li */
/* Date: 2015/Mar/23 Mon */

# include <iostream>
# include <vector>
# include <fstream>
# include <string>
# include <functional>
# include <queue>
# include <algorithm>

using namespace std;

void store_file(string);			/* prototype */
int median_maintain(void);

const int MOD = 10000;
vector<int> input_stream;

int main(int argc, char** argv) {
	store_file("Median.txt");
	int sum = median_maintain();
	cout << "result: " << sum << endl;
}

void store_file(string filename) {
	ifstream infile;
	infile.open(filename, ios::in);
	int tmp;
	int cnt = 0;
	int i = 0;
	while (infile >> tmp)
		input_stream.push_back(tmp);
	infile.close();
}

int median_maintain(void) {
	priority_queue<int, vector<int>, greater<int>> min_heap;
	priority_queue<int> max_heap;
	int cnt = 0;
	
	/* for the first two elements, add smaller to max_heap on the left, and bigger
	 * one to the min_heap on the right */
	max_heap.push(min(input_stream[0], input_stream[1]));
	cnt += input_stream[0];
	min_heap.push(max(input_stream[0], input_stream[1]));
	cnt += max_heap.top();

	for (int i = 2; i < input_stream.size(); ++i) {
		/* step 1: add next item to one of the heaps: if next item is smaller than 
		 * max_heap root, add it to max_heap, else add it to min_heap */
		if (input_stream[i] < max_heap.top())
			max_heap.push(input_stream[i]);
		else
			min_heap.push(input_stream[i]);

		/* step 2: balance the heaps(after this step, heaps will be either balanced
		 * or one of them will contains one more item): if number of elements in one
		 * of the heaps is greater than other more than one, remove the root element
		 * from the one containing more elements and add to the other one */
		if (min_heap.size() > max_heap.size() and min_heap.size() - max_heap.size() > 1) {
			int tmp = min_heap.top();
			min_heap.pop();
			max_heap.push(tmp);
		}
		else if (max_heap.size() > min_heap.size() and max_heap.size() - min_heap.size() > 1) {
			int tmp = max_heap.top();
			max_heap.pop();
			min_heap.push(tmp);
		}

		/* if heaps contain even elements: median is max_heap's root, else median is
		 * root of heap with more elements */
		int val;
		if (i % 2)
			cnt += + max_heap.top();
		else {
			if (max_heap.size() > min_heap.size())
				cnt += + max_heap.top();
			else
				cnt += min_heap.top(); 
		}
		cnt %= MOD;
	}
	return cnt;
}