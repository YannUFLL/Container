
#include <vector>
#include <iostream>

class SousClasse
{
	int _a;
	
	SousClasse(int a): _a(a) {};
}

class MaClasse : private SousClasse
{
	MaClasse(): SousClasse()
};

int main()
{
	struct std {};
	std::cout << "test";
}
