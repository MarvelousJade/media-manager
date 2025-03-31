#include "ui.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include "book.h"
#include "movie.h"
#include "tvShow.h"
#include "spellChecker.h"
#include "settings.h"

namespace seneca {
    UI::UI(Collection& collection) : m_collection(collection) {}

    void UI::run() {
        bool exit = false;
        char choice;

        // Initial load of media items
        loadMediaItems();

        while (!exit) {
            displayMenu();
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case '1':
                    displayCollection();
                    break;
                case '2':
                    searchByTitle();
                    break;
                case '3':
                    fixSpelling();
                    break;
                case '4':
                    sortCollection();
                    break;
                case '5':
                    analyzeShows();
                    break;
                case '6':
                    g_settings.m_tableView = !g_settings.m_tableView;
                    std::cout << "View mode changed to " << (g_settings.m_tableView ? "Table" : "Detailed") << std::endl;
                    break;
                case '7': {
                    std::cout << "Enter new summary width (current: " << g_settings.m_maxSummaryWidth << "): ";
                    short width;
                    std::cin >> width;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    g_settings.m_maxSummaryWidth = width;
                    std::cout << "Summary width updated to " << width << std::endl;
                    break;
                }
                case '0':
                    exit = true;
                    std::cout << "Thank you for using Media Manager!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }

            if (!exit) {
                std::cout << "\nPress Enter to continue...";
                std::cin.get();
                system("clear"); // Use "cls" for Windows
            }
        }
    }

    void UI::displayMenu() const {
        std::cout << "=============================================\n";
        std::cout << "        MULTIMEDIA MANAGEMENT SYSTEM        \n";
        std::cout << "=============================================\n";
        std::cout << "Collection: " << m_collection.name() << " (" << m_collection.size() << " items)\n";
        std::cout << "View Mode: " << (g_settings.m_tableView ? "Table" : "Detailed") << "\n";
        std::cout << "Summary Width: " << g_settings.m_maxSummaryWidth << "\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "1. Display all items\n";
        std::cout << "2. Search by title\n";
        std::cout << "3. Fix spelling in titles and summaries\n";
        std::cout << "4. Sort collection\n";
        std::cout << "5. Analyze TV Shows\n";
        std::cout << "6. Toggle view mode\n";
        std::cout << "7. Change summary width\n";
        std::cout << "0. Exit\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "Enter your choice: ";
    }

    void UI::loadMediaItems() {
        std::cout << "Loading media items...\n";
        
        try {
            // Callback function for item addition
            auto itemAddedObserver = [](const Collection& theCollection, const MediaItem& theItem) {
                std::cout << "Item \"" << theItem.getTitle() << "\" added!" << std::endl;
            };
            
            m_collection.setObserver(itemAddedObserver);
            
            // Load TV Shows
            std::cout << "Loading TV Shows...\n";
            
            // Example of loading data (in a real application, this would read files)
            TvShow* show1 = TvShow::createItem("1,Game of Thrones,2011,An epic fantasy series based on the novels by George R.R. Martin");
            TvShow* show2 = TvShow::createItem("2,Breaking Bad,2008,A high school chemistry teacher turned methamphetamine manufacturer");
            TvShow* show3 = TvShow::createItem("3,Stranger Things,2016,A sci-fi horror series set in the 1980s");
            
            m_collection += show1;
            m_collection += show2;
            m_collection += show3;
            
            // Add some episodes
            TvShow::addEpisode(m_collection, "1,1,1,1,2011-04-17,3600,Winter Is Coming,The Stark family receives a visit from the king");
            TvShow::addEpisode(m_collection, "1,2,1,2,2011-04-24,3540,The Kingsroad,The Lannisters plot against the Starks");
            TvShow::addEpisode(m_collection, "2,1,1,1,2008-01-20,3000,Pilot,Walter White receives a terminal diagnosis");
            
            // Load Movies
            std::cout << "Loading Movies...\n";
            Movie* movie1 = Movie::createItem("The Shawshank Redemption,1994,Two imprisoned men bond over a number of years");
            Movie* movie2 = Movie::createItem("The Godfather,1972,The aging patriarch of an organized crime dynasty");
            
            m_collection += movie1;
            m_collection += movie2;
            
            // Load Books
            std::cout << "Loading Books...\n";
            Book* book1 = Book::createItem("George Orwell,1984,UK,9.99,1949,A dystopian novel set in a totalitarian society");
            Book* book2 = Book::createItem("J.K. Rowling,Harry Potter and the Philosopher's Stone,UK,12.99,1997,The first book in the Harry Potter series");
            
            m_collection += book1;
            m_collection += book2;
            
            std::cout << "All media items loaded successfully!\n\n";
            
        } catch (const char* msg) {
            std::cerr << "Error: " << msg << std::endl;
        } catch (const std::string& msg) {
            std::cerr << "Error: " << msg << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown error occurred while loading media items." << std::endl;
        }
    }

    void UI::displayCollection() const {
        if (m_collection.size() == 0) {
            std::cout << "The collection is empty." << std::endl;
            return;
        }
        
        std::cout << "=============================================\n";
        std::cout << "           COLLECTION CONTENTS              \n";
        std::cout << "=============================================\n";
        
        std::cout << m_collection;
    }

    void UI::searchByTitle() const {
        std::cout << "Enter title to search for: ";
        std::string title;
        std::getline(std::cin, title);
        
        MediaItem* item = m_collection[title];
        
        if (item) {
            std::cout << "\nItem found:\n";
            std::cout << "---------------------------------------------\n";
            std::cout << *item;
        } else {
            std::cout << "No item with title \"" << title << "\" found in the collection." << std::endl;
        }
    }

    void UI::fixSpelling() {
        try {
            // Create a spell checker with custom misspelled words
            // In a real application, this would use a proper dictionary file
            SpellChecker sp("words.txt");
            
            std::cout << "Before spell check:" << std::endl;
            sp.showStatistics(std::cout);
            
            // Fix spelling in all items
            for (size_t i = 0; i < m_collection.size(); ++i) {
                m_collection[i]->fixSpelling(sp);
            }
            
            std::cout << "\nAfter spell check:" << std::endl;
            sp.showStatistics(std::cout);
            
            std::cout << "\nSpelling has been fixed in all titles and summaries." << std::endl;
            
        } catch (const char* msg) {
            std::cerr << "Error during spell checking: " << msg << std::endl;
        }
    }

    void UI::sortCollection() {
        std::cout << "Sort by:\n";
        std::cout << "1. Title\n";
        std::cout << "2. Year\n";
        std::cout << "Enter your choice: ";
        
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case '1':
                m_collection.sort("title");
                std::cout << "Collection sorted by title." << std::endl;
                break;
            case '2':
                m_collection.sort("year");
                std::cout << "Collection sorted by year." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Collection remains unsorted." << std::endl;
        }
    }

    void UI::analyzeShows() const {
        std::cout << "TV Show Analysis\n";
        std::cout << "---------------------------------------------\n";
        
        bool found = false;
        for (size_t i = 0; i < m_collection.size(); ++i) {
            TvShow* show = dynamic_cast<TvShow*>(m_collection[i]);
            if (show) {
                found = true;
                std::cout << "Show: " << show->getTitle() << std::endl;
                std::cout << "Average episode length: " 
                          << static_cast<int>(show->getEpisodeAverageLength() / 60) 
                          << " minutes" << std::endl;
                
                auto longEpisodes = show->getLongEpisodes();
                if (!longEpisodes.empty()) {
                    std::cout << "Episodes that are at least 60 minutes long:" << std::endl;
                    for (const auto& title : longEpisodes) {
                        std::cout << "- " << (title.empty() ? "[Untitled]" : title) << std::endl;
                    }
                } else {
                    std::cout << "No episodes are 60 minutes or longer." << std::endl;
                }
                std::cout << "---------------------------------------------\n";
            }
        }
        
        if (!found) {
            std::cout << "No TV shows found in the collection." << std::endl;
        }
    }
}
