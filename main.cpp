#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>

using namespace std;


struct Book
{
    string author;
    string title;
    string genre;
};

struct BookInventory
{
    Book * book;
    int numberOfBooks = 0;
    int ID;
};

class Library
{
    vector <BookInventory*> books;
    static int nextId;

public:

    void addBook(string author, string title, string genre)
    {
        BookInventory * temp = new BookInventory;
        Book * tBook = new Book;
        tBook->author = author;
        tBook->genre = genre;
        tBook->title = title;
        temp ->book = tBook;
        for (auto const &value: books)
            if(value->book->title == tBook->title && value->book->author == tBook->author && value->book->genre == tBook->genre)
            {
                value->numberOfBooks++;
                return;
            }

            temp->ID = nextId;
            nextId++;
            temp->numberOfBooks++;
        books.push_back(temp);
    }
    void listBooks()
    {
        for (auto const &value: books)
            printf("Book: %s written by %s of genre %s has %d copies and has %d id number\n", value->book->title.c_str(),
                   value->book->author.c_str(), value->book->genre.c_str(), value->numberOfBooks, value->ID);
    }

};

int Library::nextId = 0;

int main()
{
    Library testLib;
    testLib.addBook("Damian", "Super", "Fantasy");
    testLib.listBooks();


    return 0;
}