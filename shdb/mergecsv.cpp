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

	ifstream csv1(argv[1]), csv2(argv[2]);
	if (!csv1.is_open()) {
		LOG << "Cannot open file: " << argv[1] << endl;
		return -1;
	}
	if (!csv2.is_open()) {
		LOG << "Cannot open file: " << argv[2] << endl;
		return -1;
	}

	int line_num1 = 0, line_num2 = 0;
	for (bool csv1_end = false, csv2_end = false; !csv1_end || !csv2_end;) {
		string line;
		DayRecord record1, record2;
		string record_wo_date1, record_wo_date2;
		bool has_record1 = false, has_record2 = false;
		if (!csv1_end) {
			if (getline(csv1, line)) {
				++line_num1;
				if (!DayRecord::parse(line, &record1)) {
					LOG << "Invalid day record at " << argv[1] << ":"
							<< line_num1 << ": " << line << endl;
				} else {
					has_record1 = true;
					record_wo_date1 = line.substr(Date::StringLength + 1);
				}
			} else {
				csv1_end = true;
			}
		}
		if (!csv2_end) {
			if (getline(csv2, line)) {
				++line_num2;
				if (!DayRecord::parse(line, &record2)) {
					LOG << "Invalid day record at " << argv[2] << ":"
							<< line_num2 << ": " << line << endl;
				} else {
					has_record2 = true;
					record_wo_date2 = line.substr(Date::StringLength + 1);
				}
			} else {
				csv2_end = true;
			}
		}

		if (has_record1 && has_record2) {
			if (record1.date == record2.date) {
				if (record_wo_date1 != record_wo_date2) {
					LOG << "Conflict records: " << argv[1] << ":" << line_num1
							<< ": " << record1.date << "," << record_wo_date1
							<< " v.s. " << argv[2] << ":" << line_num2 << ": "
							<< record2.date << "," << record_wo_date2 << endl;
					return -1;
				} else {
					cout << record1.date << "," << record_wo_date1 << endl;
				}
			}
		} else if (has_record1) {
			cout << record1.date << "," << record_wo_date1 << endl;
		} else if (has_record2) {
			cout << record2.date << "," << record_wo_date2 << endl;
		}
	}

	return 0;
}
