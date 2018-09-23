#include <iostream>
#include <vector>


using namespace std;


struct Book
{
    string author;
    string title;
    string genre;
};

struct BookInventory
{
    Book book;
    int numberOfBooks;
    int ID;
};

class Library
{
    vector <BookInventory> books;
    static int nextId;

public:


};

int Library::nextId = 0;

int main()
{



    return 0;
}