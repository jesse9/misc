/*
 * record.cpp
 *
 *  Created on: 2015Äê1ÔÂ18ÈÕ
 *      Author: jesse
 */

#include "include/record.h"
#include "include/common.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

namespace shdb {

bool Date::operator<(const Date &other) const {
	return year < other.year || month < other.month || day < other.day;
}

bool Date::operator==(const Date &other) const {
	return year == other.year && month == other.month && day == other.day;
}

bool Date::operator!=(const Date &other) const {
	return !(*this == other);
}

bool Date::parse(const std::string &line, Date *date) {
	if (line.length() != StringLength || line[4] != '-' || line[7] != '-') {
		LOG << "Invalid date format: " << line << endl;
		return false;
	}
	for (int i = 0; i < StringLength; ++i) {
		if (line[i] != '-' && (line[i] > '9' || line[i] < '0')) {
			LOG << "Invalid date format: " << line << endl;
			return false;
		}
	}

	date->year = (line[0] - '0') * 1000 + (line[1] - '0') * 100
			+ (line[2] - '0') * 10 + (line[3] - '0');
	date->month = (line[5] - '0') * 10 + (line[6] - '0');
	date->day = (line[8] - '0') * 10 + (line[9] - '0');
	return true;
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
	os.fill('0');
	os.width(4);
	os << date.year << "-";
	os.width(2);
	os << (int)date.month << "-";
	os.width(2);
	os << (int)date.day;
	os.fill(' ');
	return os;
}

bool DayRecord::parse(const string &line, DayRecord *record) {
	stringstream ss(line);
	string column;

#define GET_COLUMN	do { \
	if (!getline(ss, column, ',')) { \
		LOG << "Invalid day record format: " << line << endl; \
		return false; \
	} \
} while(false)

	GET_COLUMN;
	if (!Date::parse(column, &record->date)) {
		LOG << "Invalid day record format: " << line << endl;
		return false;
	}
	GET_COLUMN;
	record->open_price = atof(column.c_str());
	GET_COLUMN;
	record->high_price = atof(column.c_str());
	GET_COLUMN;
	record->low_price = atof(column.c_str());
	GET_COLUMN;
	record->close_price = atof(column.c_str());
	GET_COLUMN;
	stringstream llss(column);
	llss >> record->volume;
	GET_COLUMN;
	record->adj_close_price = atof(column.c_str());
	return true;
}

std::ostream &operator<<(std::ostream &os, const DayRecord &record) {
	os << record.date << ",";
	os << record.open_price << ",";
	os << record.high_price << ",";
	os << record.low_price << ",";
	os << record.close_price << ",";
	os << record.volume << ",";
	os << record.adj_close_price;
	return os;
}

}  // namespace shdb

