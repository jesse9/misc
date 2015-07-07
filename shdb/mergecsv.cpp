/*
 * csv2bin.cpp
 *
 *  Created on: 2015Äê1ÔÂ19ÈÕ
 *      Author: jesse
 */

#include "include/record.h"
#include "include/common.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace shdb;

int main(int argc, char *argv[]) {
	if (argc < 3) {
		LOG << "Usage: " << argv[0] << " csv1 csv2" << endl;
		return -1;
	}

	struct {
		string filename;
		ifstream csv;
		DayRecord record;
		string record_str_wo_date;
		int line_num = 0;
		bool end = false;

		void next() {
			while (!end) {
				if (tryRead()) {
					break;
				}
			}
		}

		void print() {
			cout << record.date << "," << record_str_wo_date << endl;
		}

	private:

		bool tryRead() {
			if (end) {
				return false;
			}
			string line;
			if (getline(csv, line)) {
				++line_num;
				if (!DayRecord::parse(line, &record)) {
					LOG << "Invalid day record at " << filename << ":"
							<< line_num << ": " << line << endl;
				} else {
					record_str_wo_date = line.substr(Date::StringLength + 1);
					return true;
				}
			} else {
				end = true;
			}
			return false;
		}
	} f1, f2;
	f1.filename = argv[1];
	f1.csv.open(argv[1]);
	if (!f1.csv.is_open()) {
		LOG << "Cannot open file: " << argv[1] << endl;
		return -1;
	}
	f2.filename = argv[2];
	f2.csv.open(argv[2]);
	if (!f2.csv.is_open()) {
		LOG << "Cannot open file: " << argv[2] << endl;
		return -1;
	}

	int num_f1 = 0, num_f2 = 0, num_overlap = 0, merge_total = 0;
	for (f1.next(), f2.next(); !f1.end || !f2.end; ) {
		if (f1.end) {
			f2.print();
			f2.next();
			++num_f2;
		} else if (f2.end) {
			f1.print();
			f1.next();
			++num_f1;
		} else if (f2.record.date < f1.record.date) {
			f1.print();
			f1.next();
			++num_f1;
		} else if (f1.record.date < f2.record.date) {
			f2.print();
			f2.next();
			++num_f2;
		} else {
			if (f1.record_str_wo_date != f2.record_str_wo_date) {
				LOG << "Conflict: " << f1.filename << ":" << f1.line_num << ": "
						<< f1.record.date << "," << f1.record_str_wo_date
						<< " v.s. " << f2.filename << ":" << f2.line_num << ": "
						<< f2.record.date << "," << f2.record_str_wo_date
						<< endl;
				return -1;
			}
			f1.print();
			f1.next();
			f2.next();
			++num_f1;
			++num_f2;
			++num_overlap;
		}
		++merge_total;
	}

	f1.csv.close();
	f2.csv.close();

	LOG << num_f1 << " from " << f1.filename << ", " << num_f2 << " from "
			<< f2.filename << ", " << num_overlap << " overlap, total "
			<< merge_total << " after merge." << endl;

	return 0;
}
