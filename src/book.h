#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "mediaItem.h"
#include <string>
#include <vector>

namespace seneca 
{
	class Book : public MediaItem 
	{
		std::string m_author;
		std::string m_country;
		double m_price;
		Book(const std::string& author, const std::string& title, const std::string& country, const std::string& summary, unsigned short year, double price);
		std::vector<std::string> split(const std::string s, char delimiter);
	public:
		void display(std::ostream& out) const override;	
		Book* createItem(const std::string& strBook);	
	};
}

#endif
