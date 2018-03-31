#include <iostream>
#include "part_1/chapter_1/programs.h"

using namespace std;

int main()
{
	cout << "The Algorist" << endl;
	cout << "# Part One" << endl;

	{		
		cout << "## Chapter One" << endl
		<< "### The Lotto Psychic" << endl;
		part_one_chapter_one::lottoPsychic({ 15u, 6u, 6u, 4u });
	}
		

	return 0;
}