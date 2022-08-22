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
	BigInt operator+(BigInt& value) { return add(value); }

	// -------------------------- CONSTRUCTORS --------------------------

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

	BigInt(const BigInt& number) {
		val = number.val;
	}

	// -------------------------- OPERATIONS --------------------------
	BigInt add(BigInt& number) {
		// A + (-B) => A - B
		if (isPositive() && number.isNegative()) { return substract(number); }

		// -A + B => B - A
		else if (isNegative() && number.isPositive()) { return number.substract(*this->abs()); }

		// -A + -B => - (A + B)
		else if (isNegative() && number.isNegative()) {
			BigInt 
				tmpA = this->abs(), 
				tmpB = number.abs(), 
				res = tmpA + tmpB;

			return  res.negate();
		}

		std::string A = this->stringval(), B = number.stringval(), sum;

		if (A.length() < B.length()) { 
			switch_values(A, B);
		}

		int subres = 0, tmp = 0, counter = 0;
		std::size_t length_diff = A.length() - B.length();

		for (std::size_t i = A.length() - 1; i >= 0; i--) {
			int a = A[i] - '0';

			if (counter <= B.length() - 1) {
				int j = i - length_diff;
				int b = B[j] - '0';
				subres = (a + b) + tmp;
			}
			else {
				subres = a + tmp;
			}

			if (subres < 9 && i > 0) {
				tmp = std::to_string(subres)[0] - '0';
				subres = std::to_string(subres)[1] - '0';
			}
			else {
				tmp = 0;
			}
			sum = std::to_string(subres) + sum;
			counter++;
		}

	}

	BigInt abs() {
		if (isNegative()) { return BigInt(val.erase(0, 1)); }
		return BigInt(*this);
	}

	BigInt negate() {
		if (isPositive()) { return BigInt("-" + val); }
		return BigInt(*this);
	}

	// -------------------------- METHODS --------------------------
	bool isNegative() { return val[0] == '-'; }

	bool isPositive() { return !isNegative(); }

	int length() { return val.length(); }

	// -------------------------- GETTERS & SETTERS --------------------------
	std::string stringval() { return val; }

	void setVal(std::string new_value) {
		val = new_value;
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

	static void switch_values(std::string &A, std::string& B) {
		std::string tmp;

		tmp = A;
		A = B;
		B = tmp;
	}
};