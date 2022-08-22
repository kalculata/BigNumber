#pragma once

#include <string>
#include <iostream>
#include <regex>

typedef BigInt bigint;

class BigNumberException: public std::exception {
private:
	std::string message;
public:
	BigNumberException(std::string msg): message(msg) {}
	
	std::string what() {
		return message;
	}
};

class BigInt {
private:
	std::string val;

public:
	BigInt() {
		val = "0";
	}

	BigInt(std::string value) {
		val = validate(value);
	}

	BigInt(const char* value) {
		val = validate(value);
	}

	BigInt(int value) {
		val = std::to_string(value);
	}
private:
	std::string validate(std::string value) {
		if(std::regex_match(value, std::regex("[-\+]?[0-9]+"))) {
			if (val[0] == '+') {
				return value.erase(0, 1);
			}
			return value;
		}
		else {
			throw BigNumberException("Invalid number");
		}
	}
};