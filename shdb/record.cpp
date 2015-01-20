/*
 * record.cpp
 *
 *  Created on: 2015��1��18��
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

