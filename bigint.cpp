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

	if(baseExplained.empty())
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

BigInt& BigInt::operator+=(const BigInt other)
{
	assert(m_base == other.m_base && "can't add two diffrenets bases");
	int sizeO = other.m_nbr.size();
	int sizeS = m_nbr.size();

	auto itO = other.m_nbr.crbegin();
	auto itS = m_nbr.rbegin();

	int retenue = 0;

	while(itO != other.m_nbr.crend() && itS != m_nbr.rend())
	{
		int nbr = other.m_baseDetails.at(*itO) +m_baseDetails.at(*itS) + retenue;

		retenue = nbr / m_base;
		nbr %= m_base;

		*itS = coressspondingChar(nbr);

		itO++;
		itS++;
	};

	if(itO == other.m_nbr.crend() && itS == m_nbr.rend())
	{
		return *this;
	}
	else if(itO == other.m_nbr.crend()) //we reach the end 
	//of the other string but not the this.m_string
	{
		std::string result {itS, m_nbr.rend()};
		reverse(result.begin(), result.end());
		//we initiate it with a reverse iterator
		reverse(m_nbr.rbegin(), itS);
		//the actual m_nbr is trash so i can save the reversed thing that are already computed
		result.append(m_nbr.rbegin(), itS);

		m_nbr = result;
	}

	return *this;
}

char BigInt::coressspondingChar(int val)
{
	auto it = std::find_if(m_baseDetails.cbegin(), m_baseDetails.cend(), 
	[val](std::pair<char, int> truc) -> bool
	{
		return truc.second == val;
	});

	return it->first;
}

int BigInt::to_int() const //TODO a refaire
{
	int nbr = 0;
	int i = 0;
	std::for_each(m_nbr.crbegin(), m_nbr.crend(), 
	[&](char carac)  {
		nbr += m_baseDetails.at(carac) * pow(m_base, i);
		i++;
	});
	std::cout << nbr << std::endl;
	return nbr;
}

std::string BigInt::getString() const
{
	return m_nbr;
}

BigInt operator+(BigInt a, const BigInt&  b)
{
	a += b;
	return a;
}

std::ostream& operator<<(std::ostream& sortie, BigInt a)
{
	sortie << a.getString();
	return sortie;
}