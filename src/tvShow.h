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
		std::string getId() const;

		template<typename Collection_t>
		static void addEpisode(Collection_t& col, const std::string& strEpisode) {
			if (strEpisode.empty() || strEpisode[0] == '#') throw "Not a valid episode.";

			std::vector<std::string> episodeTokens;
			episodeTokens = Book::split(strEpisode, ',');
			std::string id;
			tm length;
			unsigned short numberOverall, season, numberInSeason;
			std::string airDate, title, summary; 
			const int idxOfSummary = 7;
			TvShow* tvShow = nullptr;

			id = episodeTokens[0]; 
			numberOverall = stoi(episodeTokens[1]);

			if (episodeTokens[2].empty()) {
				season = 1;
			} else {
				season = stoi(episodeTokens[2]);
			}

			numberInSeason = stoi(episodeTokens[3]);

			airDate = episodeTokens[4];

			std::istringstream timeStream(episodeTokens[5]);
			timeStream >> std::get_time(&length, "%H:%M:%S"); 

			title = episodeTokens[6];

			// Concatenate summary with comma in between
			for (size_t i = idxOfSummary; i < episodeTokens.size(); i++) {
				if (i == idxOfSummary) {
					summary += episodeTokens[i];
				} else {
					summary = summary + ", " + episodeTokens[i];
				};
			};
			
			for (size_t i = 0; i < col.size(); i++) {
				tvShow = dynamic_cast<TvShow*>(col[i]);

				if (tvShow->getId() == id) 
					tvShow->m_episodes.push_back({tvShow, numberOverall, season, numberInSeason, airDate, length, title, summary});
			};
		};

		double getEpisodeAverageLength() const;
		std::list<std::string> getLongEpisodes() const;
	}; 
}

#endif
