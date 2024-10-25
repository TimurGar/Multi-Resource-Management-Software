    #include "Book.h"

    using namespace std;
    using namespace crow;

    // Default constructor
    Book::Book() : Item(), year(0), subject(""), author(""), edition("") {}

    // Constructor with JSON input
    Book::Book(json::rvalue readValueJson) : Item(readValueJson) {
        updateFromJson(readValueJson);
    }

    // Accessor methods
    int Book::getYear() const {
        return year;
    }

    std::string Book::getSubject() const {
        return subject;
    }

    std::string Book::getAuthor() const {
        return author;
    }

    std::string Book::getEdition() const {
        return edition;
    }

    // Mutator methods
    void Book::setYear(int newYear) {
        year = newYear;
    }

    void Book::setSubject(const std::string& newSubject) {
        subject = newSubject;
    }

    void Book::setAuthor(const std::string& newAuthor) {
        author = newAuthor;
    }

    void Book::setEdition(const std::string& newEdition) {
        edition = newEdition;
    }

    // Serialize the Book object to JSON
    crow::json::wvalue Book::convertToJson() const{
        json::wvalue writeJson = Item::convertToJson(); // Call base class method

        writeJson["year"] = year;
        writeJson["subject"] = subject;
        writeJson["author"] = author;
        writeJson["edition"] = edition;

        return writeJson;
    }

    // Update from JSON
    void Book::updateFromJson(json::rvalue readValueJson) {
        Item::updateFromJson(readValueJson); // Call base class method

        year = readValueJson["year"].i();
        subject = readValueJson["subject"].s();
        author = readValueJson["author"].s();
        edition = readValueJson["edition"].s();
    }

    Item Book::toItem() const {
        Item item;
        item.setId(getId());
        item.setName(getName());
        item.setPrice(getPrice());
        item.setLocation(getLocation());
        item.setUserId(getUserId());
        return item;
    }