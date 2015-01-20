/*
 * record.h
 *
 *  Created on: 2015Äê1ÔÂ18ÈÕ
 *      Author: jesse
 */

#ifndef INCLUDE_RECORD_H_
#define INCLUDE_RECORD_H_

namespace shdb {

// Class T must have a static field size_in_bytes defined.
template<class T>
class VerifySize {
public:
	static bool DefinitionValid() {
		return sizeof(T) == T::size_in_bytes;
	}
};

class Date : public VerifySize<Date> {
public:
	static constexpr unsigned size_in_bytes = 4;

	int year : 16;
	int month : 8;
	int day : 8;
};

class Price : public VerifySize<Price> {
public:
	static constexpr unsigned size_in_bytes = 4;

	int price_times_10k;
};

class DayRecord : public VerifySize<DayRecord> {
public:
	static constexpr unsigned size_in_bytes = 32;

	Date date;
	Price open, close, adj_close, high, low;
	long long volume;
};

extern bool verify_all_definitions();

}  // namespace shdb

#endif /* INCLUDE_RECORD_H_ */
