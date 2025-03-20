#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#include <string>
#include <array>
#include <vector>

namespace  seneca {
	class SpellChecker {
		std::array<std::string, 6> m_badWords;
		std::array<std::string, 6> m_goodWords;
		static std::vector<int> counter;
	public:	
		SpellChecker(const char* filename);		
		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;
	};
}

#endif
