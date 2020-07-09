#include <vector>
#include <cassert>
#include <iostream>

//#include <cstddef> //for the std::size_t

class Matrice
{
private:
    std::vector<int> m_tab;
    std::size_t m_dimX;
    std::size_t m_dimY;
    
public:
    Matrice(std::size_t dimX, std::size_t dimY);
	Matrice(const Matrice& mat) = default;
	Matrice& operator=(const Matrice& mat) = default;
    
    std::size_t nb_lignes() const;
    std::size_t nb_colonnes() const;
    
    int& operator()(std::size_t x, std::size_t y);
    const int operator()(std::size_t x, std::size_t y) const;
    Matrice& operator+=(const Matrice& mat);
	Matrice& operator*=(int scal);
	Matrice& operator*=(const Matrice& mat);
};

Matrice operator+(Matrice lhs, const Matrice& rhs);
Matrice operator*(Matrice lhs, int rhs);
Matrice operator*(int lhs, Matrice rhs);
Matrice operator*(Matrice lhs, const Matrice& rhs);