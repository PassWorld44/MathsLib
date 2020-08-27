#pragma once

#include <string>
#include <cassert>
#include <stdexcept>
#include <limits>
#include <map>

class BigInt
//this is a unoptimised way to enlarge the capacity of a int.
//This use a std::string full of numbers
{
public:
	BigInt(int nbr, int base = 10, std::string baseExplained = "");
	//supports base 10, 2 and 16
	BigInt(std::string str, int base = 10, std::string baseExplained = "");

	int to_int() const;
	//use of stoi, see it for details
private:
	void init(std::string baseExplained);

	std::string m_nbr;
	int m_base;
	std::map<char, int> m_baseDetails;
};