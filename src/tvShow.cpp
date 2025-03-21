#include <iomanip>
#include <sstream>
#include "tvShow.h"
#include "mediaItem.h"
#include "settings.h"
#include "book.h"

namespace seneca {
	using namespace std;
	TvShow::TvShow(const string& id, const std::string& title, const std::string& summary, unsigned short year) : MediaItem(title, summary, year), m_id(id) {}; 

	void TvShow::display(std::ostream& out) const
	  {
	    if (g_settings.m_tableView)
	    {
	      out << "S | ";
	      out << std::left << std::setfill('.');
	      out << std::setw(50) << this->getTitle() << " | ";
	      out << std::right << std::setfill(' ');
	      out << std::setw(2) << this->m_episodes.size() << " | ";
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
	      out << this->getTitle() << " [" << this->getYear() << "]\n";
	      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
	      while (pos < this->getSummary().size())
	      {
		out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
		pos += g_settings.m_maxSummaryWidth;
	      }
	      for (auto& item : m_episodes)
	      {
		out << std::setfill('0') << std::right;
		out << "    " << 'S' << std::setw(2) << item.m_season
		  << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
		if (item.m_title != "")
		  out << item.m_title << '\n';
		else
		  out << "Episode " << item.m_numberOverall << '\n';

		pos = 0;
		while (pos < item.m_summary.size())
		{
		  out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
		  pos += g_settings.m_maxSummaryWidth - 8;
		}
	      }
	      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
		<< std::setfill(' ') << '\n';
	    }
	  };

	TvShow* TvShow::createItem(const std::string& strShow) {
		if (strShow.empty() || strShow[0] == '#') throw "Not a valid Book.";

		vector<string> tvShowTokens;
		tvShowTokens = Book::split(strShow, ',');
		string id;
		string title, summary; 
		unsigned short year; 
		const int idxOfSummary = 3;

		id = tvShowTokens[0]; 
		title = tvShowTokens[1];
		stringstream ss(tvShowTokens[2]);
		ss >> year;


		for (int i = idxOfSummary; i < tvShowTokens.size(); i++) {
			if (i == idxOfSummary || i == tvShowTokens.size() - 1) {
				summary += tvShowTokens[i];
			} else {
				summary = summary + ", " + tvShowTokens[i];
			};
		}; 
		
		return new TvShow(id, title, summary, year);	
	};
	
	double TvShow::getEpisodeAverageLength() const {
		if (m_episodes.empty()) return 0.0;

		double totalSeconds = 0;

		for (auto& episode : m_episodes) {
			int seconds = episode.m_length.tm_hour * 3600 + episode.m_length.tm_min * 60 + episode.m_length.tm_sec; 
			totalSeconds += seconds ;
		};

		return totalSeconds / m_episodes.size();
	};

	list<string> TvShow::getLongEpisodes() const {
		list<string> longEpisodes;	
		int hour = 3600;	
		int lengthInSeconds = 0;
	
		for (auto& episode : m_episodes) {
			 lengthInSeconds = episode.m_length.tm_hour * 3600 + episode.m_length.tm_min * 60 + episode.m_length.tm_sec; 

			if (lengthInSeconds >= 3600)
				longEpisodes.push_back(episode.m_title);
		};
		
		return longEpisodes;
	};
} 

