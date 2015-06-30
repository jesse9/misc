/*
 * record.cpp
 *
 *  Created on: 2015Äê1ÔÂ18ÈÕ
 *      Author: jesse
 */

#include "include/record.h"
#include "include/common.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace shdb {

bool Date::operator==(const Date &other) const {
	return year == other.year && month == other.month && day == other.day;
}

bool Date::operator!=(const Date &other) const {
	return !(*this == other);
}

bool Date::parse(const std::string &line, Date *date) {
	if (line.length() != 10 || line[4] != '-' || line[7] != '-') {
		LOG << "Invalid date format: " << line << endl;
		return false;
	}
	for (int i = 0; i < 10; ++i) {
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

bool DayRecord::operator==(const DayRecord &other) const {
	return date == other.date &&
			open_price == other.open_price &&
			high_price == other.high_price &&
			low_price == other.low_price &&
			close_price == other.close_price &&
			volume == other.volume &&
			adj_close_price == other.adj_close_price;
}

bool DayRecord::operator!=(const DayRecord &other) const {
	return !(*this == other);
}

bool DayRecord::parse(const string &line, DayRecord *record) {
	stringstream ss(line);
	string column;
	if (!getline(ss, column, ',')) {
		LOG << "Invalid day record format: " << line << endl;
		return false;
	}
	if (!Date::parse(column, &record->date)) {
		LOG << "Invalid day record format: " << line << endl;
		return false;
	}

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

