#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <ios>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "spellChecker.h"

namespace seneca {
	using namespace std;

	std::vector<int> SpellChecker::counter(6, 0);

	SpellChecker::SpellChecker(const char* filename) {
		ifstream file(filename);
		if(!filename) throw "Bad file name!";	

		string line;	
		const string whitespace = "\t\n\r";

		while(getline(file, line)) {
			stringstream ss(line);	
			string badWord, goodWord;
			size_t counter = 0;
			getline(ss, badWord, ' ');
			getline(ss, goodWord);
			m_badWords[counter] = badWord;	
			m_goodWords[counter] = goodWord;
			counter++;
		};

	};		

	void SpellChecker::operator()(std::string& text) {
		for(size_t i = 0; i < m_badWords.size(); i++) {
			size_t pos = text.find(m_badWords[i]);
			text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
			counter[i]++;
			pos = text.find(m_badWords[i], pos+ m_goodWords[i].length());
		};
	};

	void SpellChecker::showStatistics(std::ostream& out) const {
		for(int i = 0; i < counter.size(); i++ ) {
			out << right << setw(15) << m_badWords[i] << ": " << counter[i] << " replacements" << endl;
		};
	};
}
