# Multimedia Management System

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

A comprehensive C++ application for managing and organizing collections of multimedia content including books, movies, and TV shows. The system provides robust data management capabilities with support for metadata, search, sorting, and analysis.

## Features

- **Unified Media Management**: Organize books, movies, and TV shows in a centralized collection
- **Detailed Information**: Store and display comprehensive metadata for each media type
- **Episode Tracking**: Manage TV show episodes with season and episode details
- **Content Analysis**: Calculate statistics like average episode length and identify long episodes
- **Spell Checking**: Built-in spell checker to correct common errors in titles and descriptions
- **Flexible Display Options**: Toggle between table and detailed views
- **Sorting Capabilities**: Organize media items by title, year, or other properties
- **User-Friendly Interface**: Intuitive command-line interface for easy navigation

## Architecture

The application is built using modern C++17 and follows object-oriented design principles:

```
┌─────────────┐     ┌───────────┐
│ Collection  │────>│ MediaItem │<───────────┐
└─────────────┘     └───────────┘            │
                         ▲                   │
                         │                   │
         ┌───────────────┼───────────────┐   │
         │               │               │   │
   ┌─────────┐    ┌────────────┐    ┌─────────┐
   │  Book   │    │   Movie    │    │ TvShow  │
   └─────────┘    └────────────┘    └─────────┘
                                         │
                                    ┌─────────┐
                                    │TvEpisode│
                                    └─────────┘
```

- **MediaItem**: Abstract base class for all media types
- **Book**: Stores information about books including author, country, and price
- **Movie**: Manages movie data with title, year, and summary
- **TvShow**: Tracks TV show information along with episodes
- **Collection**: Container class that manages and organizes media items
- **SpellChecker**: Utility class for correcting misspelled words in text
- **Settings**: Configuration options for display formatting

## Requirements

- C++17 compatible compiler
- Standard Template Library (STL)
- CMake 3.12 or higher (for building)

## Building the Project

```bash
# Clone the repository
git clone https://github.com/your-username/multimedia-management.git
cd multimedia-management

# Create build directory
mkdir build
cd build

# Generate build files and compile
cmake ..
make

# Run the application
./media_manager
```

## Usage

When you start the application, you'll be presented with a menu-driven interface:

```
=============================================
        MULTIMEDIA MANAGEMENT SYSTEM        
=============================================
Collection: Personal Media Library (7 items)
View Mode: Table
Summary Width: 80
---------------------------------------------
1. Display all items
2. Search by title
3. Fix spelling in titles and summaries
4. Sort collection
5. Analyze TV Shows
6. Toggle view mode
7. Change summary width
0. Exit
---------------------------------------------
Enter your choice:
```

From here you can:
- View all media items in the collection
- Search for items by title
- Fix spelling errors in titles and descriptions
- Sort the collection by different criteria
- Analyze TV shows to get episode statistics
- Customize display settings

## Data Files

The system supports loading data from CSV files:

- `books.csv`: Book data in format `AUTHOR,TITLE,COUNTRY,PRICE,YEAR,SUMMARY`
- `movies.csv`: Movie data in format `TITLE,YEAR,SUMMARY`
- `tvShows.csv`: TV show data in format `ID,TITLE,YEAR,SUMMARY`
- `episodes.csv`: Episode data in format `ID,EPISODE_NUMBER,SEASON_NUMBER,EPISODE_IN_SEASON,AIR_DATE,LENGTH,TITLE,SUMMARY`
- `words.txt`: Dictionary for spell checking, format `BAD_WORD GOOD_WORD`

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by modern digital media management systems
- Built using modern C++ programming techniques and STL algorithms
