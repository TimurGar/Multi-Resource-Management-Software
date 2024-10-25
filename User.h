#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <crow.h>
#include "Item.h" 

class User {
private:
    std::string userName;
    std::vector<Item> items;


public:
    // Constructors
    User() = default; // Default constructor
    User(const std::string& name); // Constructor with username
    User(crow::json::rvalue readValueJson); // Constructor with JSON input

    // Getters
    std::string getUsername() const { return userName; }
    std::string getId() const { return userName; } // If userName is the unique identifier
    std::vector<std::string> getItemIds() const;

    // Setters
    void setUsername(const std::string& newUsername);
    void addItem(const Item& item);

    // JSON serialization
    crow::json::wvalue convertToJson() const;

    // JSON deserialization
    void updateFromJson(crow::json::rvalue readValueJson);
};

#endif // USER_H
