#include "lib.hpp"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

Book::Book(const std::string& title, const std::string& author)
    : title(title), author(author)
{
    if (title.empty())  throw std::invalid_argument("Title cannot be empty");
    if (author.empty()) throw std::invalid_argument("Author cannot be empty");
}

const std::string& Book::getTitle()  const { return title; }
const std::string& Book::getAuthor() const { return author; }

void Book::setTitle(const std::string& t) {
    if (t.empty()) throw std::invalid_argument("Title cannot be empty");
    title = t;
}

void Book::setAuthor(const std::string& a) {
    if (a.empty()) throw std::invalid_argument("Author cannot be empty");
    author = a;
}

void Book::print() const {
    std::cout << "  " << std::left
              << std::setw(35) << title
              << " — " << author << "\n";
}

Library::Library(const std::string& name) : name(name) {
    if (name.empty()) throw std::invalid_argument("Library name cannot be empty");
}

const std::string& Library::getName()    const { return name; }
int                Library::bookCount()  const { return (int)books.size(); }

void Library::addBook(const std::string& title, const std::string& author) {
    books.emplace_back(title, author);
}

const std::vector<Book>& Library::getBooks() const {
    return books;
}

const Book* Library::searchBook(const std::string& title) const {
    auto it = std::find_if(books.begin(), books.end(),
        [&title](const Book& b) { return b.getTitle() == title; });
    return it != books.end() ? &(*it) : nullptr;
}

void Library::printAll() const {
    std::cout << "=== Library: " << name
              << " (" << books.size() << " books) ===\n";
    for (const auto& b : books)
        b.print();
}

int main() {
    Library lib("City Public Library");

    lib.addBook("The Great Gatsby",        "F. Scott Fitzgerald");
    lib.addBook("To Kill a Mockingbird",   "Harper Lee");
    lib.addBook("1984",                    "George Orwell");
    lib.addBook("Pride and Prejudice",     "Jane Austen");
    lib.addBook("The Catcher in the Rye",  "J.D. Salinger");
    lib.addBook("Brave New World",         "Aldous Huxley");

    lib.printAll();

    std::cout << "\n=== Search by title ===\n";

    const std::string query = "1984";
    const Book* found = lib.searchBook(query);
    if (found)
        std::cout << "Found: \"" << found->getTitle()
                  << "\" by " << found->getAuthor() << "\n";
    else
        std::cout << "Book \"" << query << "\" not found.\n";

    const std::string missing = "Don Quixote";
    const Book* notFound = lib.searchBook(missing);
    if (!notFound)
        std::cout << "Book \"" << missing << "\" not found.\n";

    std::cout << "\n=== All books via getBooks() ===\n";
    for (const auto& b : lib.getBooks())
        b.print();

    return 0;
}