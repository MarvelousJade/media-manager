#include "book.h"
#include "settings.h"
#include "mediaItem.h"
#include <iomanip>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace seneca 
{
	vector<string> Book::split(const string s, char delimiter) 
	{
		vector<string> tokens;	
		istringstream tokenstream(s);
		string token;
		while (getline(tokenstream, token, delimiter))
		{
			if (!token.empty()) {
				MediaItem::trim(token);
				tokens.push_back(token);
			}
		};
		return tokens;
	};	

	void Book::split(std::string& s) {
		MediaItem::trim(s);
	};

	Book::Book(const std::string& author, const std::string& title, const std::string& country, const std::string& summary, unsigned short year, double price) : MediaItem(title, summary, year), m_author(author), m_country(country), m_price(price) {};

	void Book::display(std::ostream& out) const
	{
		if (g_settings.m_tableView)
		{
		  out << "B | ";
		  out << std::left << std::setfill('.');
		  out << std::setw(50) << this->getTitle() << " | ";
		  out << std::right << std::setfill(' ');
		  out << std::setw(2) << this->m_country << " | ";
		  out << std::setw(4) << this->getYear() << " | ";
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
		  out << this->getTitle() << " [" << this->getYear() << "] [";
		  out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
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

	Book* Book::createItem(const std::string& strBook) {
		if (strBook.empty() || strBook[0] == '#') throw "Not a valid Book.";

		vector<string> bookTokens;
		bookTokens = Book::split(strBook, ',');
		string author, title, country, summary; 
		unsigned short year; 
		double price;

		author = bookTokens[0]; 
		title = bookTokens[1];
		country = bookTokens[2]; 
		price = stod(bookTokens[3]);
		stringstream ss(bookTokens[4]);
		ss >> year;
		summary = bookTokens[5];
		
		return new Book(author, title, country, summary, year, price);	
	};
}

