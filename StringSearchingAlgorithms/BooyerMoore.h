#ifndef BOYERMOORE_H
#define BOYERMOORE_H

#include "utils.h";

class BooyerMoore
{
public:
	Position find_bm(const std::string&, const std::string&);
	std::list<Position> find_bm_multi(const std::string&, const std::string&);

private:
	//length for pattern and text 
	Position pat_len;
	Position text_len;

	//lookup table 
	Position skip[256];
};

#endif

