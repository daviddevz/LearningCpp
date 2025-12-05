#include <iostream>
#include <limits>
#include <string>
#include <vector>



//Library
class Library {
public:
    //Default constructor that sets Book array to empty array.
    Library() : bookArray(0){};

    void addBook(){
        Book bk;

        std::cout <<"What is the book's title? ";
        std::getline(std::cin, bk.title);

        std::cout <<"What is the author's name (First Last)? ";
        std::getline(std::cin, bk.author);

        std::cout <<"What year was the book published (Integer)? ";
        std::cin >> bk.pubYear;

        if (std::cin.fail()){
            std::cerr <<"Error reading year. Please enter a valid integer" <<std::endl;
            
            do {
                std::cout <<"What year was the book published (Integer)? ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cin >> bk.pubYear;
            } while(std::cin.fail());
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout <<"What is the book's genre ";
        std::getline(std::cin, bk.genre);

        bookArray.push_back(bk);
    }

private:
    //Book structure
    struct Book{
        std::string title, author, genre;
        int pubYear;
    };

    std::vector<Book> bookArray;
};

int main(){
    Library lib;
    lib.addBook();

    return 0;
}