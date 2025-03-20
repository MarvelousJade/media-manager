#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <list>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "mediaItem.h"
#include "book.h"

namespace seneca {
	class TvShow;
	
	struct TvEpisode {
	  const TvShow* m_show{};
	  unsigned short m_numberOverall{};
	  unsigned short m_season{};
	  unsigned short m_numberInSeason{};
	  std::string m_airDate{};
	  std::tm m_length{};
	  std::string m_title{};
	  std::string m_summary{};
	};

	class TvShow : public MediaItem {
		std::string m_id;
		std::vector<TvEpisode> m_episodes;
		TvShow(const std::string& id, const std::string& title, const std::string& summary, unsigned short year); 
	public:
		void display(std::ostream& out) const override;	
		static TvShow* createItem(const std::string& strEpisode);

		template<typename Collection_t>
		static void addEpisode(Collection_t& col, const std::string& strEpisode) {
			if (strEpisode.empty() || strEpisode[0] == '#') throw "Not a valid Book.";

			std::vector<std::string> tvShowTokens;
			tvShowTokens = Book::split(strEpisode, ',');
			std::string id;
			tm length;
			unsigned short numberOverall, season, numberInSeason;
			std::string airDate, title, summary; 

			id = tvShowTokens[0]; 
			numberOverall = stoi(tvShowTokens[1]);

			if (tvShowTokens[2].empty()) {
				season = 1;
			} else {
				season = stoi(tvShowTokens[2]);
			}

			numberInSeason = stoi(tvShowTokens[3]);

			airDate = tvShowTokens[4];

			std::istringstream timeStream(tvShowTokens[5]);
			timeStream >> std::get_time(&length, "%H:%M:%S"); 

			title = tvShowTokens[6];
			summary = tvShowTokens[7];
		};

		double getEpisodeAverageLength() const;
		std::list<std::string> getLongEpisodes() const;
	}; 
}

#endif
