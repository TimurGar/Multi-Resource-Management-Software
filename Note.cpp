#include "Note.h"

using namespace std;
using namespace crow;

// Default constructor
Note::Note() : Item(), subject(""), department(""), class_(""), creator("") {}

// Constructor with JSON input
Note::Note(json::rvalue readValueJson) : Item(readValueJson) {
    updateFromJson(readValueJson);
}

// Accessor methods
std::string Note::getSubject() const {
    return subject;
}

std::string Note::getDepartment() const {
    return department;
}

std::string Note::getClass() const {
    return class_;
}

std::string Note::getCreator() const {
    return creator;
}

// Mutator methods
void Note::setSubject(const std::string& newSubject) {
    subject = newSubject;
}

void Note::setDepartment(const std::string& newDepartment) {
    department = newDepartment;
}

void Note::setClass(const std::string& newClass) {
    class_ = newClass;
}

void Note::setCreator(const std::string& newCreator) {
    creator = newCreator;
}

// Serialize the Note object to JSON
crow::json::wvalue Note::convertToJson() const {
    json::wvalue writeJson = Item::convertToJson(); // Call base class method

    writeJson["subject"] = subject;
    writeJson["department"] = department;
    writeJson["class"] = class_;
    writeJson["creator"] = creator;

    return writeJson;
}

// Update from JSON
void Note::updateFromJson(json::rvalue readValueJson) {
    Item::updateFromJson(readValueJson); // Call base class method

    subject = readValueJson["subject"].s();
    department = readValueJson["department"].s();
    class_ = readValueJson["class"].s();
    creator = readValueJson["creator"].s();
}

Item Note::toItem() const {
    Item item;
    item.setId(getId());
    item.setName(getName());
    item.setPrice(getPrice());
    item.setLocation(getLocation());
    item.setUserId(getUserId()); 
    return item;
}