/*
Example 3: Library Management System
*/

#include <iostream>
using namespace std;

class Book {
public:
    string title,author,ISBN;
    int availableCopies;

    Book(string t,string a,string i,int c) {
        title=t;
        author=a;
        ISBN=i;
        availableCopies=c;
    }

    void issue() {
        if(availableCopies>0){availableCopies--;cout<<"Book issued successfully!\n";}
        else cout<<"Book not available!\n";
    }

    void returnBook() {
        availableCopies++;
        cout<<"Book returned successfully!\n";
    }

    void display() {
        cout<<"Title: "<<title<<", Author: "<<author<<", ISBN: "<<ISBN<<", Copies: "<<availableCopies<<endl;
    }
};

class Library {
private:
    Book** books;
    int size;
    int capacity;

    void resize(int newCapacity) {
        Book** newBooks=new Book*[newCapacity];
        for(int i=0;i<size;i++)newBooks[i]=books[i];
        delete[] books;
        books=newBooks;
        capacity=newCapacity;
    }

public:
    Library():size(0),capacity(2){books=new Book*[capacity];}

    ~Library(){
        for(int i=0;i<size;i++)delete books[i];
        delete[] books;
    }

    void addBook(string title,string author,string ISBN,int copies) {
        if(size==capacity)resize(capacity*2);
        books[size]=new Book(title,author,ISBN,copies);
        size++;
    }

    void issueBook(string title) {
        for(int i=0;i<size;i++)if(books[i]->title==title){books[i]->issue();return;}
        cout<<"Book not found!\n";
    }

    void returnBook(string title) {
        for(int i=0;i<size;i++)if(books[i]->title==title){books[i]->returnBook();return;}
        cout<<"Book not found!\n";
    }

    void search(string query) {
        for(int i=0;i<size;i++)if(books[i]->title==query||books[i]->author==query){books[i]->display();return;}
        cout<<"Book not found!\n";
    }

    void displayAll() {
        if(size==0){cout<<"No books in the library!\n";return;}
        for(int i=0;i<size;i++)books[i]->display();
    }
};

int main() {
    Library lib;
    lib.addBook("C++ Basics","Bjarne Stroustrup","123456",5);
    lib.addBook("Data Structures","Robert Lafore","789012",3);
    lib.displayAll();

    lib.issueBook("C++ Basics");
    lib.returnBook("C++ Basics");
    lib.search("Robert Lafore");

    return 0;
}

