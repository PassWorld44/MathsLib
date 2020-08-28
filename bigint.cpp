#include "bigint.h"

BigInt::BigInt(int nbr, int base, std::string baseExplained)
	: m_nbr( std::to_string(nbr) ), m_base(base)
{
	init(baseExplained);
}

BigInt::BigInt(std::string str, int base, std::string baseExplained)
	: m_nbr(str), m_base(base)
{
	init(baseExplained);
}

void BigInt::init(std::string baseExplained)
{
	if(!baseExplained.empty())
	{
		switch(m_base)
		{
		case 2:
			baseExplained = "01";
			break;
		case 10:
			baseExplained = "0123456789";
			break;
		case 16:
			baseExplained = "0123456789abcdef";
			break;
		default:
			throw std::runtime_error("you have to define the caracters whitch define the base");
			break;
		}
	}
	int i = 0;
	for(char carac : baseExplained)
	{
		auto r = m_baseDetails.emplace(carac, i);
		if(!r.second)
		{
			throw std::runtime_error("there can't be two of the same caracters into the same base");
		}
		i++;
	}
}

int BigInt::to_int() const //TODO a refaire
{
	
}
