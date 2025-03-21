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
		for (auto& m_item : m_mediaItems) {
			if(m_item->getTitle() == title) return m_item;
		};		
		
		return nullptr;
	};

	void Collection::removeQuotes() {
		for (auto& m_item : m_mediaItems) {
			string title = m_item->getTitle();
			string summary = m_item->getSummary();

			if (title.size() >= 2) {
				if (title.front() == '"' && title.back() == '"') {
					string newTitle = title.substr(1, title.size() - 2); 
					m_item->setTitle(newTitle);
				};
			};
			
			if (summary.size() >= 2) {
				if (summary.front() == '"' && summary.back() == '"') {
					string newSummary = summary.substr(1, summary.size() - 2); 
					m_item->setSummary(newSummary);
				};
			};
		};
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
		for (int i = 0; i < collection.size(); i++) {
			collection[i]->display(os);
		};

		return os;
	};
}
	
