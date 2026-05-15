#pragma once

#include <string>
#include <vector>

class Book {
public:
    Book(const std::string& title, const std::string& author);

    const std::string& getTitle()  const;
    const std::string& getAuthor() const;

    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);

    void print() const;

private:
    std::string title;
    std::string author;
};


class Library {
public:
    explicit Library(const std::string& name);

    const std::string& getName() const;
    int                bookCount() const;

    void addBook(const std::string& title, const std::string& author);

    const std::vector<Book>& getBooks() const;

    const Book* searchBook(const std::string& title) const;

    void printAll() const;

private:
    std::string       name;
    std::vector<Book> books;
};