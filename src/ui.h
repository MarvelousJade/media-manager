#ifndef SENECA_UI_H
#define SENECA_UI_H

#include <string>
#include "collection.h"

namespace seneca {
    class UI {
        Collection& m_collection;
        
        // Private helper methods
        void displayMenu() const;
        void loadMediaItems();
        void displayCollection() const;
        void searchByTitle() const;
        void fixSpelling();
        void sortCollection();
        void analyzeShows() const;
        
    public:
        UI(Collection& collection);
        void run();
    };
}

#endif
