#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <crow.h>
#include "Item.h"

class Note : public Item {
private:
    std::string subject;
    std::string department;
    std::string class_;
    std::string creator;

public:
    // Constructors
    Note(); // Default constructor
    Note(crow::json::rvalue readValueJson); // Constructor with JSON input

    // Accessor methods
    std::string getSubject() const;
    std::string getDepartment() const;
    std::string getClass() const;
    std::string getCreator() const;

    // Mutator methods
    void setSubject(const std::string& newSubject);
    void setDepartment(const std::string& newDepartment);
    void setClass(const std::string& newClass);
    void setCreator(const std::string& newCreator);

    // Override Item's serialization to JSON
    crow::json::wvalue convertToJson() const override;

    // Override Item's update from JSON
    void updateFromJson(crow::json::rvalue readValueJson) override;
    
    Item toItem() const;

};

#endif // NOTE_H
