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

	bool operator<(const Date &other) const;
	bool operator==(const Date &other) const;
	bool operator!=(const Date &other) const;

	// Returns true if parsing is successful.
	static bool parse(const std::string &line, Date *date);
};

std::ostream &operator<<(std::ostream &os, const Date &date);

struct CompactDayRecord;

struct DayRecord {
	Date date;
	int open_price_k = 0;
	int high_price_k = 0;
	int low_price_k = 0;
	int close_price_k = 0;
	long long int volume = 0;
	int adj_close_price_k = 0;

	void compact(CompactDayRecord *compact_record) const;

	// Returns true if parsing is successful.
	static bool parse(const std::string &line, DayRecord *record);
};

std::ostream &operator<<(std::ostream &os, const DayRecord &record);

struct CompactDayRecord {
	unsigned long long year : 11;
	unsigned long long month : 4;
	unsigned long long day : 5;
	unsigned long long open_price_k : 21;
	unsigned long long high_price_k : 21;

	unsigned long long reserved1 : 2;

	unsigned long long low_price_k : 21;
	unsigned long long close_price_k : 21;
	unsigned long long adj_close_price_k : 21;

	unsigned long long reserved2 : 1;

	unsigned long long volume : 43;

	unsigned long long reserved3 : 21;

	void decompress(DayRecord *record) const;
} __attribute__ ((aligned (8)));

}  // namespace shdb

#endif /* INCLUDE_RECORD_H_ */
