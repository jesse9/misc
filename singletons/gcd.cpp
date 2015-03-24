/*
 * gcd.cpp
 *
 *  Created on: Mar 22, 2015 10:40:34 PM 
 *      Author: Xing
 */

#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) {
	if (a < b) {
		swap(a, b);
	}

	int c = a % b;
	while (c != 0) {
		a = b;
		b = c;
		c = a % b;
	}
	return b;
}


int lcm(int a, int b) {
    return a*b/gcd(a,b);
}


int recursive(int N, const vector<int> &jump, int start, int nums, int parial_lcm) {
    if (start >= jump.size()) {
        return 0;
    }
    int count = recursive(N, jump, start + 1, nums, parial_lcm);

    parial_lcm = lcm(parial_lcm, jump[start]);
    cout << nums << " [" << start << "]=" << jump[start] << " LCM " << parial_lcm << endl;
    if (nums % 2 == 0) {
        count += N / parial_lcm;
    } else {
        count -= N / parial_lcm;
    }

    count += recursive(N, jump, start + 1, nums + 1, parial_lcm);
    return count;
}
/*
 * Complete the function below.
 */
int countUneatenLeaves(int N, vector < int > A) {
    const vector<int> &jump = A;
    return N - recursive(N, jump, 0, 0, 1);
}

int main(int argc, char *argv[]) {
	vector<int> jump = { 2, 4, 5};
	cout << countUneatenLeaves(10, jump) << endl;
	return 0;
}

