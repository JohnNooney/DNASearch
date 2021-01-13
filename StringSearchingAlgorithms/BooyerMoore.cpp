#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <list>

#include "BooyerMoore.h";

Position BooyerMoore::find_bm(const std::string& pat, const std::string& text)
{
	//set the lengths of the text and pattern
	pat_len = pat.size();
	text_len = text.size();

	//fill up the table (with which letters can be skipped over)
	for (Position i = 0; i < 256; ++i)
		skip[i] = pat_len; // Not in the pattern.
	//for each element in the pattern, holds how many spaces you can skip when a character is seen
	for (int i = 0; i < pat_len; ++i)
		skip[Position(pat[i])] = (pat_len - 1) - i;

	for (Position i = 0; i < text_len - pat_len; ++i)
	{
		//show_context(text, i);

		//create variable in which the letter being compared is entered into the lookup table
		Position s = skip[Position(text[i + pat_len - 1])];
		//if the letter being compared is not the last charachter in the pattern
		if (s != 0) {
			i += s - 1; // Skip forwards.
			continue;
		}

		else
		{
			Position j;
			for (j = 0; j < pat_len; j++)
			{
				if (text[i + j] != pat[j])
				{
					break; // Doesn't match here.

				}
			}
			if (j == pat_len) {
				return i; // Matched here.
			}
		}

	}
	return -1; // Not found.
}

std::list<Position> BooyerMoore::find_bm_multi(const std::string& pat, const std::string& text)
{
	pat_len = pat.size();
	text_len = text.size();

	//fill up the table (with which letters can be skipped over)
	for (Position i = 0; i < 256; ++i)
		skip[i] = pat_len; // Not in the pattern.
	//for each element in the pattern, holds how many spaces you can skip when a character is seen
	for (Position i = 0; i < pat_len; ++i)
		skip[Position(pat[i])] = (pat_len - 1) - i;

	//list of the postions of which the word is found
	std::list<Position> positions;

	for (Position i = 0; i < text_len - pat_len; ++i)
	{
		//show_context(text, i);

		//create variable in which the letter being compared is entered into the lookup table
		Position s = skip[Position(text[i + pat_len - 1])];
		//if the letter being compared is not the last charachter in the pattern
		if (s != 0) {
			i += s - 1; // Skip forward
			continue;
		}

		else
		{
			Position j;
			for (j = 0; j < pat_len; j++)
			{
				if (text[i + j] != pat[j])
				{
					break; // Doesn't match here.

				}
			}
			if (j == pat_len)
			{
				//add found pattern match to list
				positions.push_back(i);
			}
		}

	}

	return positions;
}
