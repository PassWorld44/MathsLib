#pragma once

#include <string>
#include <cassert>
#include <stdexcept>
#include <limits>
#include <map>
#include <algorithm>
#include <iostream>

#include "MyMaths.h"

class BigInt
//this is a unoptimised way to enlarge the capacity of a int.
//This use a std::string full of numbers
{
public:
	BigInt(int nbr, int base = 10, std::string baseExplained = "");
	//supports base 10, 2 and 16
	BigInt(std::string str, int base = 10, std::string baseExplained = "");

	BigInt& operator+=(const BigInt other);

	int to_int() const;

	std::string getString() const;
private:
	void init(std::string baseExplained);

	char coressspondingChar(int val);

	std::string m_nbr;
	int m_base;
	std::map<char, int> m_baseDetails;
};