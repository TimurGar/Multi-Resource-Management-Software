#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <crow.h>
#include "Item.h"

class Book : public Item {
private:
    int year;
    std::string subject;
    std::string author;
    std::string edition;

public:
    // Constructors
    Book(); // Default constructor
    Book(crow::json::rvalue readValueJson); // Constructor with JSON input

    // Accessor methods
    int getYear() const;
    std::string getSubject() const;
    std::string getAuthor() const;
    std::string getEdition() const;

    // Mutator methods
    void setYear(int newYear);
    void setSubject(const std::string& newSubject);
    void setAuthor(const std::string& newAuthor);
    void setEdition(const std::string& newEdition);

    // Override Item's serialization to JSON
    crow::json::wvalue convertToJson() const override;

    // Override Item's update from JSON
    void updateFromJson(crow::json::rvalue readValueJson) override;

    Item toItem() const;

};

#endif // BOOK_H
