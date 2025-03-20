#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include <list>
#include <vector>
#include <stdexcept>
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
	  unsigned int m_length{};
	  std::string m_title{};
	  std::string m_summary{};
	};

	class TvShow : public MediaItem {
		int m_id;
		std::vector<TvEpisode> m_episodes;
		TvShow(int id, const std::string& title, const std::string& summary, unsigned short year); 
	public:
		void display(std::ostream& out) const override;	
		static TvShow* createItem(const std::string& strEpisode);

		template<typename Collection_t>
		static void addEpisode(Collection_t& col, const std::string& strEpisode) {
			if (strEpisode.empty() || strEpisode[0] == '#') throw std::invalid_argument("Not a valid Book.");

			std::vector<std::string> tvShowTokens;
			tvShowTokens = Book::split(strEpisode, ',');
			int id;
			unsigned int length;
			unsigned short numberOverall, season, numberInSeason;
			std::string airDate, title, summary; 

			id = stoi(tvShowTokens[0]); 
			numberOverall = stoi(tvShowTokens[1]);
			season = stoi(tvShowTokens[2]);
			numberInSeason = stoi(tvShowTokens[3]);
			airDate = tvShowTokens[4];
			length = stoi(tvShowTokens[5]);
			title = tvShowTokens[6];
			summary = tvShowTokens[7];
		};
		double getEpisodeAverageLength() const;
		std::list<std::string> getLongEpisodes() const;
	}; 
}

#endif
