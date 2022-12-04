#include "MyChrono.hpp"

// Constructors
MyChrono::MyChrono()
{
}

MyChrono::MyChrono(const MyChrono &copy)
{
	(void) copy;
}


// Destructor
MyChrono::~MyChrono()
{
}


// Operators
MyChrono & MyChrono::operator=(const MyChrono &assign)
{
	(void) assign;
	return *this;
}

int	MyChrono::time_diff(struct timeval *start, struct timeval *end)
{	
	return ((end->tv_sec - start->tv_sec)
		* 1000 + ((end->tv_usec - start->tv_usec) / 1000));
}

void	MyChrono::begin()
{
		gettimeofday(&_start, NULL);
}


void MyChrono::end()
{
	struct timeval now; 
	gettimeofday(&now, NULL);
	_time_spent = time_diff(&_start, &now);
}

void MyChrono::print_time(std::string const str) const
{
 std::cout << std::setw(20) << std::left << str;
 std::cout << _time_spent << " micro seconds" <<  std::endl;
}

