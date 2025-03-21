#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <ostream>
#include <string>
#include <vector>
#include "mediaItem.h"

namespace seneca {
	class Collection {
		std::string m_name;
		std::vector<MediaItem*> m_mediaItems;		
		void (*m_observer)(const Collection&, const MediaItem&);
	public:
		Collection(const std::string& name);
		const std::string& name() const;
		size_t size() const;
		void setObserver(void (*observer)(const Collection&, const MediaItem&));
		Collection& operator+=(MediaItem* item);
		MediaItem* operator[](size_t idx) const;
		MediaItem* operator[](const std::string& title) const;
		void removeQuotes();
		void sort(const std::string& field);
		~Collection();
	};
	std::ostream& operator<<(std::ostream& os, const Collection& collection);
}

#endif

