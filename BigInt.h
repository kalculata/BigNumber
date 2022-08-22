#pragma once

#include <string>
#include <iostream>
#include <regex>

typedef BigInt bigint;

class BigInt {
private:
	std::string val;

public:
	BigInt() {
		val = "0";
	}
};