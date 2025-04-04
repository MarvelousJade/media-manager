#include <stdexcept>
#include <string>
#include <algorithm>
#include "collection.h"

namespace seneca {
	using namespace std;

	Collection::Collection(const std::string& name) : m_name(name), m_observer(nullptr) {};

	const std::string& Collection::name() const { return m_name; };

	size_t Collection::size() const { return m_mediaItems.size(); };

	void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) { m_observer = observer; };

	Collection& Collection::operator+=(MediaItem* item) {
		for (auto& m_item : m_mediaItems) {
			if ( item->getTitle() == m_item->getTitle()) {
				delete item;
				return *this;
			};
		};

		m_mediaItems.push_back(item);	
		if (m_observer != nullptr) m_observer(*this, *item);

		return *this;
	};

	MediaItem* Collection::operator[](size_t idx) const {
		if (idx < 0 || idx >= m_mediaItems.size()) 
			throw out_of_range("Bad index " + to_string(idx) + ". " + "Collection has " + to_string(m_mediaItems.size()) + "items."); 	

		return m_mediaItems[idx];
	};

	MediaItem* Collection::operator[](const std::string& title) const {
		auto it = find_if(m_mediaItems.begin(), m_mediaItems.end(), [&title](const MediaItem* item ) -> bool {
			return item->getTitle() == title; 
		});	
		
		return (it != m_mediaItems.end() ? *it : nullptr );
	};

	void Collection::removeQuotes() {
		for_each(m_mediaItems.begin(), m_mediaItems.end(), [](MediaItem* item) {
			string title = item->getTitle();
			string summary = item->getSummary();
			if (!title.empty() && title.front() == '"' && title.back() == '"' ) {
				title = title.substr(1, title.size() - 2); 
				item->setTitle(title);
			};

			if (!summary.empty() && summary.front() == '"' && summary.back() == '"' ) {
				summary = summary.substr(1, summary.size() - 2); 
				item->setSummary(summary);
			};
	
			if (!summary.empty() && summary.back() == '"' ) {
				summary = summary.substr(0, summary.size() - 1); 
				item->setSummary(summary);
			};		
		});	
	};

	void Collection::sort(const std::string& field) {	
		if (field == "title") {
			std::sort(m_mediaItems.begin(), m_mediaItems.end(), [](MediaItem* a, MediaItem* b) {
				return a->getTitle() < b->getTitle();
			});
		} else if (field == "year") {
			std::sort(m_mediaItems.begin(), m_mediaItems.end(), [](MediaItem* a, MediaItem* b) {
				return a->getYear() < b->getYear();
			});
		} else {
			throw invalid_argument("Unknow filed name: " + field);
		};
	};

	ostream& operator<<(ostream& os, const Collection& collection) {
		for (size_t i = 0; i < collection.size(); i++) {
			collection[i]->display(os);
		};

		return os;
	};
	
	Collection::~Collection() {
		for (auto& item: m_mediaItems) {
			delete item;
		};	
	};
}
	
