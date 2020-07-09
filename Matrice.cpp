#include "Matrice.h"

Matrice::Matrice(std::size_t dimX, std::size_t dimY)
    : m_dimX{dimX}, m_dimY{dimY}, m_tab{dimX * dimY, 0}
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

int& Matrice::operator()(const std::size_t x, const std::size_t y)
{
    assert(x < m_dimX && "La coordonée x ne peut pas dépasser la taille du tableau");
    assert(y < m_dimY && "La coordonée y ne peut pas dépasser la taille du tableau");
    assert(x >= 0 && "La coordonée x ne peut pas être en dessous de 0");
    assert(y >= 0 && "La coordonée y ne peut pas être en dessous de 0");

	assert(x * y < m_tab.size() && "La coordonée y ne peut pas dépasser la taille du tableau");

    return m_tab.at(x * m_dimY + y);
}

const int Matrice::operator()(std::size_t x, std::size_t y) const
{
    assert(x < m_dimX && "La coordonée x ne peut pas dépasser la taille du tableau");
    assert(y < m_dimY && "La coordonée y ne peut pas dépasser la taille du tableau");
    assert(x >= 0 && "La coordonée x ne peut pas être en dessous de 0");
    assert(y >= 0 && "La coordonée y ne peut pas être en dessous de 0");

	assert(x * y < m_tab.size() && "La coordonée y ne peut pas dépasser la taille du tableau");

    return m_tab.at(x * m_dimY + y);
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
		for(int j = 0; i < mat.m_dimY; j++)
		{
			int val = 0;
			for(int k = 0; k < m_dimY; k++)
			{
				val += m_tab[m_dimX * i + k] * mat.m_tab[mat.m_dimX * k + j];
			}

			result.m_tab[i * m_dimX + j] = val;
		}
	}

	return *this;
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