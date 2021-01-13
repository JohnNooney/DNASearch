#include <cassert>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <chrono>

#include "BooyerMoore.h";
#include "RabinKarp.h";
#include "utils.h";
using namespace std;

using std::cout;
using std::endl;
using std::list;
using std::ofstream;
using std::string;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

// Define the alias "the_clock" for the clock type we're going to use.
// (You can change this to make the code below use a different clock.)
typedef std::chrono::steady_clock the_clock;

//create csv file to upload data to
ofstream my_file("data_comparison.csv");

//randomly generate a text to use for string searching 
string createText(int textLength)
{
	//array of the characters used to build the text
	string charSet[7] = { "g", "c", "a", "t" };
	string text;

	//loop that adds a random letter each iteration
	for (int i = 0; i < textLength; i++)
	{
		//random number generator to select a random character out of the char set
		int charSelect = rand() % 7;
		//add random letter the text
		text += charSet[charSelect];
	}

	return text;
}

void bmTestSuite(string pat, string text, int cycle)
{
	//create booyer moore object
	BooyerMoore bmSearch = BooyerMoore();

	//variables to hold the averages
	auto avgTime = 0;

	//cycle through through the search to find average 
	for (int i = 0; i < cycle; i++)
	{
		// Start timing
		the_clock::time_point start = the_clock::now();
		std::list<Position> pos = bmSearch.find_bm_multi(pat, text);
		// Stop timing
		the_clock::time_point end = the_clock::now();
		// Compute the difference between the two times in milliseconds
		auto time_taken = duration_cast<milliseconds>(end - start).count();

		Position c = 0;
		for (int n : pos)
		{
			c++;
		}

		//get the total times
		avgTime = avgTime + time_taken;
	}

	//find average of total times
	avgTime = avgTime / cycle;
	cout << "Average Time: " << avgTime << " ms";
	cout << " For: " << pat << "\n";

	//upload to csv file the pattern size along with the average time 
	int patSize = pat.size();
	my_file << patSize << ", " << avgTime;
}

void rkTestSuite(string pat, string text, int cycle)
{
	//create rabin karp object
	RabinKarp rkSearch = RabinKarp();

	//variables to hold the averages
	auto avgTime = 0;

	//cycle through through the search to find average 
	for (int i = 0; i < cycle; i++)
	{
		// Start timing
		the_clock::time_point start = the_clock::now();
		std::list<Position> pos = rkSearch.find_multi_rk(pat, text);
		// Stop timing
		the_clock::time_point end = the_clock::now();
		// Compute the difference between the two times in milliseconds
		auto time_taken = duration_cast<milliseconds>(end - start).count();

		Position c = 0;
		for (int n : pos)
		{
			c++;
		}

		//get the total times
		avgTime = avgTime + time_taken;
	}

	//find average of total times
	avgTime = avgTime / cycle;
	cout << "Average Time: " << avgTime << " ms";
	cout << " For: " << pat << "\n";

	//display in 2 columns for reading to file
	int patSize = pat.size();
	my_file << patSize << ", " << avgTime;
}

int main(int argc, char* argv[]) 
{
	bool flag = true;
	while (flag)
	{
		//variables used for test suites
		int length; //dont exceed 1,000,000,000
		int patternCycle;
		string ogPattern;
		string pattern;
		string input;
		bool increase = false;

		//prompt user
		cout << "Please enter a length of DNA sequence to generate (recommended: 1,000,000): ";
		cin >> length;
		cout << "Please enter a dna sequence to search for (letters: g,c,a,t): ";
		cin >> ogPattern;
		cout << "How many times would you like the algorithms repeate for an average? (recommended: 10): ";
		cin >> patternCycle;
		cout << "Would you like to increase the length of your pattern on each repition? <y> <n>: ";
		cin >> input;
		cout << "\n";

		if (input == "y")
		{
			increase = true;
		}

		pattern = ogPattern;

		string text = createText(length);
		cout << length << " character Text generated \n";

		//test the booyer moore method with different pattern lengths
		cout << "Boyer-Moore: \n";
		for (int i = 0; i < patternCycle; i++)
		{
			bmTestSuite(pattern, text, patternCycle);

			//increment pattern for next repetition
			if (increase)
			{
				pattern = pattern + "g";
			}
		}

		//reset pattern to search for rabin karp
		if (increase)
		{
			pattern = ogPattern;
		}

		cout << "\n";

		//test the rabin karp method with different pattern lengths
		cout << "Rabin-Karp: \n";
		for (int i = 0; i < patternCycle; i++)
		{
			rkTestSuite(pattern, text, patternCycle);

			//increment pattern for next repetition
			if (increase)
			{
				pattern = pattern + "g";
			}
		}


		cout << "\n*****************************************\n";

		string input2;
		cout << "Would you like to try again?  <y> <n>: ";
		cin >> input2;
		if (input2 == "n")
		{
			flag = false;
		}
	}
	

	return 0;
}