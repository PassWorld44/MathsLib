#include "Matrice.h"

Matrice::Matrice(std::size_t dimX, std::size_t dimY)
    : m_dimX{dimX}, m_dimY{dimY}, 
	m_tab{static_cast<int>(dimX * dimY), 0}
{
	m_tab.reserve(dimX * dimY);
	for(int i = 0; i < dimX * dimY; i++)
	{
		m_tab.push_back(0);
	}
}

std::size_t Matrice::nb_lignes() const
{
    return m_dimX;
}

std::size_t Matrice::nb_colonnes() const
{
    return m_dimY;
}

Matrice Matrice::transpose()
//just rotate the matrice
{
	Matrice res{m_dimY, m_dimX};
	for(int i = 0; i < m_dimX; i++)
	{
		for(int j = 0; j < m_dimY; j++)
		{
			res(j, i) = operator()(i, j);
		}
	}
	return res;
}

std::size_t Matrice::offset(std::size_t ligne, std::size_t collone) const noexcept
{
	assert(ligne < m_dimX && "La coordonée x ne peut pas dépasser la taille du tableau");
    assert(collone < m_dimY && "La coordonée y ne peut pas dépasser la taille du tableau");
    assert(ligne >= 0 && "La coordonée x ne peut pas être en dessous de 0");
    assert(collone >= 0 && "La coordonée y ne peut pas être en dessous de 0");

	assert(ligne * collone < m_tab.size() && "La coordonée y ne peut pas dépasser la taille du tableau");

	return ligne * m_dimY + collone;
}

int& Matrice::operator()(const std::size_t x, const std::size_t y)
{
    return m_tab.at(offset(x, y));
}

const int Matrice::operator()(std::size_t x, std::size_t y) const
{
    return m_tab.at(offset(x, y));
}

Matrice& Matrice::operator+=(const Matrice& mat)
{    
    assert(mat.m_dimX == m_dimX && "Les dimentions d'une matrice doivent être les memes pour l'addition");
    assert(mat.m_dimY == m_dimY && "Les dimentions d'une matrice doivent être les memes pour l'addition");
    
    auto it2{mat.m_tab.begin()};
    for(auto it{m_tab.begin()}; it != m_tab.end() || it2 != mat.m_tab.end(); it++)
    {
        *it += *it2;
        
        it2++;
    }

	return *this;
}

Matrice& Matrice::operator*=(int scal)
{
    for(auto it{m_tab.begin()}; it != m_tab.end(); it++)
    {
        *it *= scal;
    }

	return *this;
}

Matrice& Matrice::operator*=(const Matrice& mat)
{
	assert(m_dimY == mat.m_dimX && "les tailles des matrices données ne peuvent marcher.");

	Matrice result {m_dimX, mat.m_dimY};

	for(int i = 0; i < m_dimX; i++)
	{
		for(int j = 0; j< mat.m_dimY; j++)
		{
			int val = 0;
			for(int k = 0; k < m_dimY; k++)
			{
				val += m_tab.at(m_dimY * i + k) * mat.m_tab.at(mat.m_dimY * k + j);
			}
			result.m_tab.at(i * m_dimX + j) = val;
		}
	}

	*this = result;

	return *this;
}

std::ostream& Matrice::print(std::ostream& stream)
{
	for(int i = 0; i < m_dimX; i++)
	{
		for(int j = 0; j < m_dimY; j++)
		{
			stream << operator()(i, j) << ' ';
		}
		stream << std::endl;
	}

	return stream;
}

Matrice operator+(Matrice lhs, const Matrice& rhs)
{
    lhs += rhs;
    return lhs;
}

Matrice operator*(Matrice lhs, int rhs)
{
	return lhs *= rhs;
}

Matrice operator*(int lhs, Matrice rhs)
{
	return rhs *= lhs; //cause this operation is commutative
}

Matrice operator*(Matrice lhs, const Matrice& rhs)
{
	return lhs *= rhs;
}

std::ostream& operator<<(std::ostream& stream, Matrice mat)
{
	return mat.print(stream);
}