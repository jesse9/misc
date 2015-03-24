/*
 * GoodPoints.cpp
 *
 *  Created on: Mar 22, 2015 5:27:23 PM 
 *      Author: Xing
 */

#include <iostream>
#include <vector>

using namespace std;

static void DownStream(int start_point,
		vector<pair<int, vector<int> *>> &points) {
	const int up = points[start_point].first;
	points[start_point].first = 0;
	auto *downs = points[start_point].second;
	points[start_point].second = NULL;

	if (downs != NULL) {
		for (const int down : *downs) {
			DownStream(down, points);
		}
		delete downs;
	}
}

static void DownAndUpStream(int start_point,
		vector<pair<int, vector<int> *>> &points) {
	const int up = points[start_point].first;
	points[start_point].first = 0;
	auto *downs = points[start_point].second;
	points[start_point].second = NULL;

	if (up > 0) {
		DownAndUpStream(up, points);
	}

	if (downs != NULL) {
		for (const int down : *downs) {
			DownAndUpStream(down, points);
		}
		delete downs;
	}
}

int main(int argc, char *argv[]) {
	const vector<int> next = {0, 5, 5, 5, 5, 5};

	vector<pair<int, vector<int> *>> points(next.size());
	for (int i = 0; i < points.size(); ++i) {
		points[i].first = 0;
		points[i].second = new vector<int>;
	}

	for (int i = 1; i < next.size(); ++i) {
		const int target = next[i];
		points[i].first = target;
		points[target].second->push_back(i);
	}

	DownStream(1, points);

	int count = 0;
	for (int i = 2; i < next.size(); ++i) {
		if (points[i].second != NULL) {
			DownAndUpStream(i, points);
			++count;
		}
	}

	for (int i = 0; i < points.size(); ++i) {
		if (points[i].second != NULL) {
			delete points[i].second;
		}
	}

	cout << count << endl;

	return 0;
}


