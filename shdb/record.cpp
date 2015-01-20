/*
 * record.cpp
 *
 *  Created on: 2015Äê1ÔÂ18ÈÕ
 *      Author: jesse
 */

#include "include/record.h"

namespace shdb {

bool verify_all_definitions() {
	if (!Date::DefinitionValid()) {
		return false;
	}

	if (!Price::DefinitionValid()) {
		return false;
	}

	if (!DayRecord::DefinitionValid()) {
		return false;
	}
	return true;
}

}  // namespace shdb

