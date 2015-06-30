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

		bool endOfFile() const {
			return end;
		}

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
		bool end = false;
		int line_num = 0;
		string record_str_wo_date;

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

	for (f1.next(), f2.next(); !f1.endOfFile() || !f2.endOfFile(); ) {
		if (f1.endOfFile()) {
			f2.print();
			f2.next();
		} else if (f2.endOfFile()) {
			f1.print();
			f1.next();
		} else if (f1.record.date < f2.record.date) {
			f1.print();
			f1.next();
		} else {
			f2.print();
			f2.next();
		}
	}

	return 0;
}
