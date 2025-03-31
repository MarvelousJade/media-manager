#include <iostream>
#include "collection.h"
#include "ui.h"

int main(int argc, char* argv[]) {
    std::cout << "Multimedia Management System\n";
    std::cout << "----------------------------\n";
    
    try {
        // Create a new collection
        seneca::Collection mediaLibrary("Personal Media Library");
        
        // Create and run the user interface
        seneca::UI interface(mediaLibrary);
        interface.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const char* msg) {
        std::cerr << "Error: " << msg << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown error occurred." << std::endl;
        return 3;
    }
    
    return 0;
}
