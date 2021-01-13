#ifndef RABINKARP_H
#define RABINKARP_H

#include "utils.h"
#include <list>

#pragma once
class RabinKarp
{
public:
	RabinKarp();
	//function to find the pattern in the text once
	Position find_rk(const std::string&, const std::string&);
	//function to create a list of 
	std::list<Position> find_multi_rk(const std::string&, const std::string&);
	//function to calculate the hash value of the pattern
	Position hash_function1(const std::string&);

	Position hash_function2(const std::string&);
	

private:
	//length for pattern and text 
	Position pat_len;
	Position text_len;

	//hash value of the pattern and text
	int pat_hash;
	int text_hash;

	//table which holds the numeric value of each letter
	Position charSetTotal;

	//prime number where the higher it is, the lower the collision rate but more computation required.
	//will avoid integer overflow
	int collisionFactor;
	
};

#endif 
