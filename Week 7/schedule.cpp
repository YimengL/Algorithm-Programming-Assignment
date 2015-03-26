/* Algorithm: Design and Analysis, Week 7 Programming Assignment, Q1 */
/* Author: Yimeng Li */
/* Date: 2015/Mar/25 Wed */

# include <iostream>
# include <string>
# include <fstream>
# include <vector>
# include <algorithm>

using namespace std;

struct job {
	int len;
	int weight;
};
vector<job> joblist;

void store_file(string);
void print_all(void);
bool my_compare(job, job);
long complete_time(void);

int main(int argc, char** argv) {
	store_file("jobs.txt");
	sort(joblist.begin(), joblist.end(), my_compare);
	long t = complete_time();
	cout << "Complete time: " << t << endl;
	return 0;
}

void store_file(string filename) {
	ifstream infile;
	infile.open(filename, ios::in);
	int sz;
	infile >> sz;
	joblist.resize(sz);
	int tmp_l, tmp_w;
	for (int i = 0; i < sz; ++i) {
		infile >> tmp_w >> tmp_l;
		joblist[i].weight = tmp_w;
		joblist[i].len = tmp_l;
	}
	infile.close();
}

void print_all(void) {
	for (int i = 0; i < joblist.size(); ++i)
		cout << joblist[i].weight << "  " << joblist[i].len << endl;
	cout << endl;
}

bool my_compare(job job1, job job2) {
	int diff1 = job1.weight - job1.len;
	int diff2 = job2.weight - job2.len;
	if (diff1 > diff2)
		return true;
	else if (diff1 < diff2)
		return false;
	else
		return (job1.weight > job2.weight);
}

long complete_time(void) {
	long t = 0;
	int start = 0;
	int finish;
	for (int i = 0; i < joblist.size(); ++i) {
		finish = start + joblist[i].len;
		t += finish * joblist[i].weight;
		start = finish;
	}
	return t;
}