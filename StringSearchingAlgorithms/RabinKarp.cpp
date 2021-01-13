#include "RabinKarp.h"
#include <iostream>

RabinKarp::RabinKarp()
{
	//get the total number of ASCII characters to calculate the hash funciton with
	charSetTotal = 256;

	//initialize variables
	pat_len = 0;
	text_len = 0;
	pat_hash = 0;
	text_hash = 0;
	collisionFactor = 101;
}

Position RabinKarp::hash_function1(const std::string& str)
{
	//variable to be used as the hash value placeholder
	Position hash = 0;

	//loop that calculates the hash value of the pattern
	for (Position i = pat_len - 1; i >= 0; i--)
	{
		hash = fmod((Position(str[i]) * pow(charSetTotal, i)), collisionFactor);
	}
	return hash;
}



std::list<Position> RabinKarp::find_multi_rk(const std::string& pattern, const std::string& text)
{
	//list of all the positions where the word is found 
	std::list<Position> positions;

	//set the pattern and text length
	pat_len = pattern.length();
	text_len = text.length();

	//calculate the hash value of the pattern 
	pat_hash = hash_function1(pattern);
	//calculate the hash value of the text with the pattern length
	text_hash = hash_function1(text);

	//loop for going through the text
	for (Position i = 0; i <= text_len - pat_len; ++i)
	{
		
		//if the hashes match then return
		if (pat_hash == text_hash)
		{
			//do addition check
			//check each letter at a time to make sure of match
			Position j;
			for (j = 0; j < pat_len; j++)
			{
				if (text[i + j] != pattern[j])
				{
					break; // Doesn't match here.

				}
			}
			if (j == pat_len) {
				positions.push_back(i) ; // Matched here. Add to list
			}
		}
		//if no match then continue with rolling hash
		else
		{
			//variable which holds the hash value of the first character in the text being compared
			Position fHash = (Position(text[i]) * (fmod(pow(charSetTotal, pat_len - 1), collisionFactor)));

			//remove the first letter value from the hash and add the next
			text_hash = (((text_hash - fHash) * charSetTotal) + text[i + pat_len]) % collisionFactor;

			//if the hash is a negative, convert to positive
			if (text_hash < 0)
			{
				text_hash = (text_hash + collisionFactor);
			}
		}

		//if the text reaches the end then return the positions list
		if (i == text_len - pat_len)
		{
			return positions;
		}
	}


	//not found
	return positions;
}
