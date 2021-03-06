#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <algorithm>

using namespace std;


struct Book
{
    string author;
    string title;
    string genre;

    Book(string Author, string Title, string Genre)
    {
        author = Author;
        title = Title;
        genre = Genre;
    }

    Book()
    {

    }

};

class BookInventory
{
public:

    Book * book;
    int numberOfBooks = 0;
    int ID;

    BookInventory(Book * bok, int number, int id)
    {
        book = bok;
        numberOfBooks = number;
        ID = id;
    }
    BookInventory()
    {

    }
    void printInfo()
    {

        printf("Book: %s written by %s of genre %s has %d copies and has %d id number\n", book->title.c_str(),
               book->author.c_str(), book->genre.c_str(), numberOfBooks,ID);
    }
};

class Library
{
    vector <BookInventory*> books;
    static int nextId;

public:

    BookInventory *searchForBook(string title, string author, string genre)
    {
        for (auto const &value: books)
        {
            if(value->book->title == title && value->book->author == author && value->book->genre == genre)
            {
                return value;
            }
        }

        return NULL;
    }
    BookInventory *searchForBook(int id)
    {
        for (auto const &value: books)
        {
            if(value->ID == id)
                return value;
        }
        return NULL;
    }

    BookInventory *searchForBook(Book * book)
    {
        for (auto const &value: books)
        {
            if(value->book->title == book->title && value->book->author == book->author && value->book->genre == book->genre)
            {
                return value;
            }
        }

        return NULL;
    }
    void addBook(string author, string title, string genre)
    {

        if(searchForBook(title,author,genre)!=NULL)
        {
            searchForBook(title,author,genre)->numberOfBooks++;
            return;
        }

        BookInventory * temp = new BookInventory;
        Book * tBook = new Book;
        tBook->author = author;
        tBook->genre = genre;
        tBook->title = title;
        temp ->book = tBook;


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
    void saveToFile()
    {
        ofstream outputFile;
        ofstream idFile;
        idFile.open("id.txt");
        outputFile.open("books.txt");
        if(idFile && outputFile)
        {
            for (auto const &value: books)
            {
                outputFile << value->book->title << " " << value->book->author << " "<< value->book->genre << " " << value->ID << " "<< value->numberOfBooks << endl;
            }
            idFile << nextId;
            outputFile.close();
            idFile.close();
        }
        else
            return;
    }
    void readFromFile()
    {
        ifstream saveFile;
        ifstream idFile;
        saveFile.open("books.txt");
        idFile.open("id.txt");
        idFile >> nextId;
        if(saveFile && idFile)
        {
            string author;
            string title;
            string genre;
            int id;
            int quantity;
            while (saveFile >> title >> author >> genre >> id >> quantity)
            {
                books.push_back(new BookInventory(new Book(author, title, genre), quantity, id));
            }
            saveFile.close();
            idFile.close();
        }
        else
            return;
    }

    void deleteBook(string author, string title, string genre)
    {
        BookInventory *temp = searchForBook(title, author, genre);
        if(temp!=NULL)
        {
            if(temp->numberOfBooks>1)
                temp->numberOfBooks--;
            else
            {
                books.erase(remove(books.begin(), books.end(), temp),books.end());
            }
        }
        else
        {
            cout << "There is no such book" << endl;
            return;
        }
    }
    void deleteBook(int id)
    {
        BookInventory *temp = searchForBook(id);
        if(temp!=NULL)
        {
            if(temp->numberOfBooks>1)
                temp->numberOfBooks--;
            else
            {
                books.erase(remove(books.begin(), books.end(), temp),books.end());
            }
        }
        else
        {
            cout << "There is no such book" << endl;
            return;
        }
    }
    void deleteBook(Book * book)
    {
        BookInventory *temp = searchForBook(book);
        if(temp!=NULL)
        {
            if(temp->numberOfBooks>1)
                temp->numberOfBooks--;
            else
            {
                books.erase(remove(books.begin(), books.end(), temp),books.end());
            }
        }
        else
        {
            cout << "There is no such book" << endl;
            return;
        }
    }
    Book * getBookInfo()
    {
        string author;
        string title;
        string genre;
        cout << "If you want to add book please provide this information" << endl;
        cout << "Author name without spaces: ";
        cin >> author;
        cout << "Title without spaces: ";
        cin >> title;
        cout << "Genre without spaces: ";
        cin >> genre;
        return new Book(author,title,genre);
    }
    void userAddBook()
    {
        Book * temp = getBookInfo();
        addBook(temp->author, temp->title, temp->genre);
        cout << "Book added!" << endl;
    }
    void userSearchForBook()
    {
        Book * temp = getBookInfo();
        BookInventory * temp2 = searchForBook(temp);
        if(temp2!=NULL)
            temp2->printInfo();
        else
            cout << "There is no such book" << endl;
    }
    void userDeleteBook()
    {
        Book * temp = getBookInfo();
        deleteBook(temp);
    }
};

int Library::nextId = 0;

int main()
{

    Library testLib;
    testLib.readFromFile();


    cout << "Choose what you want to do: " << endl;
    cout << "Enter 1 if you want to add a book" << endl;
    cout << "2 if you are searching for book" << endl;
    cout << "3 if you want to delete book" << endl;
    cout << "4 if you want to list all books" << endl;
    cout << "5 if uou want to end the program" << endl;

    char ch;
    while(true)
    {
        ch = getchar();
        switch(ch)
        {
            case '1':
                testLib.userAddBook();
                break;
            case '2':
                testLib.userSearchForBook();
                break;
            case '3':
                testLib.userDeleteBook();
                break;
            case '4':
                testLib.listBooks();
                break;
            case '5':
                return 0;
            default:
                cout << "Please enter only 1,2,3 or 4";
                break;
        }
    }

    testLib.saveToFile();

    return 0;
}