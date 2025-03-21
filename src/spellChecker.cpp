#include <cstddef>
#include <iomanip>
#include <ios>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "spellChecker.h"
#include "book.h"

namespace seneca {
	using namespace std;

	std::vector<int> SpellChecker::counter(6, 0);

	SpellChecker::SpellChecker(const char* filename) {
		ifstream file(filename);
		if(!file) throw "Bad file name!";	

		string line;	
		size_t idx = 0;

		while(getline(file, line)) {
			stringstream ss(line);	
			string badWord, goodWord;
			getline(ss, badWord, ' ');
			getline(ss, goodWord);

			Book::split(badWord);
			Book::split(goodWord);

			m_badWords[idx] = badWord;
			m_goodWords[idx] = goodWord;

			idx++;

			if (idx >= m_badWords.size()) break;
		};

	};		

	void SpellChecker::operator()(std::string& text) {
		SpellChecker::counter.resize(m_badWords.size(), 0);

		for(size_t i = 0; i < m_badWords.size(); i++) {
			size_t pos = text.find(m_badWords[i]);
			while(pos != string::npos) {
				text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
				SpellChecker::counter[i]++;
				pos = text.find(m_badWords[i], pos+ m_goodWords[i].length());
			};
		};
	};

	void SpellChecker::showStatistics(std::ostream& out) const {
		out <<	"Spellchecker Statistics" << endl;

		for(int i = 0; i < SpellChecker::counter.size(); i++ ) {
			out << left << setw(15) << m_badWords[i] << ": " << SpellChecker::counter[i] << " replacements" << endl;
		};
	};
}
