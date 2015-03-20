/*
 * lower_upper_bound.cpp
 *
 *  Created on: Mar 19, 2015 10:54:31 PM 
 *      Author: Xing
 */

#include <iostream>
#include <set>

using namespace std;

template<class SetType>
void PrintAll(const SetType &s) {
	bool first = true;
	for (auto it = s.begin(); it != s.end(); ++it) {
		if (!first) {
			cout << ", ";
		} else {
			first = false;
		}
		cout << *it;
	}
	cout << endl;
}

template<class SetType>
void PrintIt(const typename SetType::iterator &it, const SetType &s) {
	if (it == s.end()) {
		cout << "end";
	} else {
		cout << *it;
	}
}

template<class SetType>
void PrintLowerAndUpperBound(const int v, const SetType &s) {
	cout << "lower_bound(" << v << ")=";
	PrintIt(s.lower_bound(v), s);
	cout << ", ";
	cout << "upper_bound(" << v << ")=";
	PrintIt(s.upper_bound(v), s);
	cout << endl;
}

template<typename T>
struct GreaterThan {
	bool operator()(const T &a, const T &b) const {
		return a > b;
	}
};

int main(int argc, char *argv[]) {
	set<int> s = {2, 4, 6, 8};
	PrintAll(s);
	PrintLowerAndUpperBound(1, s);
	PrintLowerAndUpperBound(2, s);
	PrintLowerAndUpperBound(5, s);
	PrintLowerAndUpperBound(6, s);
	PrintLowerAndUpperBound(8, s);
	PrintLowerAndUpperBound(9, s);
	cout << endl;

	set<int, GreaterThan<int>> ss(s.begin(), s.end());
	PrintAll(ss);
	PrintLowerAndUpperBound(1, ss);
	PrintLowerAndUpperBound(2, ss);
	PrintLowerAndUpperBound(5, ss);
	PrintLowerAndUpperBound(6, ss);
	PrintLowerAndUpperBound(8, ss);
	PrintLowerAndUpperBound(9, ss);

	return 0;
}

