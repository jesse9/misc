/*
 * record.h
 *
 *  Created on: 2015Äê1ÔÂ18ÈÕ
 *      Author: jesse
 */

#ifndef INCLUDE_RECORD_H_
#define INCLUDE_RECORD_H_

#include <ostream>
#include <string>

namespace shdb {

struct Date {
	static constexpr int StringLength =10;

	short int year = 0;
	char month = 0;
	char day = 0;

	bool operator==(const Date &other) const;
	bool operator!=(const Date &other) const;

	// Returns true if parsing is successful.
	static bool parse(const std::string &line, Date *date);
};

std::ostream &operator<<(std::ostream &os, const Date &date);

struct DayRecord {
	Date date;
	double open_price = 0;
	double high_price = 0;
	double low_price = 0;
	double close_price = 0;
	long long int volume = 0;
	double adj_close_price = 0;

	// Returns true if parsing is successful.
	static bool parse(const std::string &line, DayRecord *record);
};

std::ostream &operator<<(std::ostream &os, const DayRecord &record);

}  // namespace shdb

#endif /* INCLUDE_RECORD_H_ */
