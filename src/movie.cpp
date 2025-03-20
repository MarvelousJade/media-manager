#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include "movie.h"
#include "mediaItem.h"
#include "settings.h"
#include "book.h"

namespace seneca {
	using namespace std;

	Movie::Movie(const std::string& title, const std::string& summary, unsigned short year)
		: MediaItem(title, summary, year) {};

	void Movie::display(std::ostream& out) const
	  {
	    if (g_settings.m_tableView)
	    {
	      out << "M | ";
	      out << std::left << std::setfill('.');
	      out << std::setw(50) << this->getTitle() << " | ";
	      out << std::right << std::setfill(' ');
	      out << std::setw(9) << this->getYear() << " | ";
	      out << std::left;
	      if (g_settings.m_maxSummaryWidth > -1)
	      {
		if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
		  out << this->getSummary();
		else
		  out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
	      }
	      else
		out << this->getSummary();
	      out << std::endl;
	    }
	    else
	    {
	      size_t pos = 0;
	      out << this->getTitle() << " [" << this->getYear() << "]\n";
	      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
	      while (pos < this->getSummary().size())
	      {
		out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
		pos += g_settings.m_maxSummaryWidth;
	      }
	      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
		<< std::setfill(' ') << '\n';
	    }
	  };
	
	Movie* Movie::createItem(const std::string& strMovie) {
		if (strMovie.empty() || strMovie[0] == '#') throw "Not a valid movie.";

		vector<string> movieTokens;
		movieTokens = Book::split(strMovie, ',');
		string author, title, country, summary; 
		unsigned short year; 

		title = movieTokens[0];
		year = stoi(movieTokens[1]);
		summary = movieTokens[2];
		
		return new Movie(title, summary, year);	
	};

}
