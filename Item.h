// Item.h

#ifndef ITEM_H
#define ITEM_H

#include <crow.h>
#include <string>
#include <vector>

class Item {
public:
    // Constructors
    Item();
    Item(crow::json::rvalue readValueJson);

    // Getters and Setters
    std::string getId() const { return id; }
    void setId(const std::string& newId) { id = newId; }
    std::string getUserId() const { return userID; }
    void setUserId(const std::string& newUserId) { userID = newUserId; }
    float getPrice() const { return price; }
    void setPrice(float newPrice) { price = newPrice; }
    std::string getLocation() const { return location; }
    void setLocation(const std::string& newLocation) { location = newLocation; }
    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    // JSON Serialization
    virtual crow::json::wvalue convertToJson() const;
    virtual void updateFromJson(crow::json::rvalue readValueJson);

protected:
    std::string id;
    std::string userID;  // New member
    float price;
    std::string location;
    std::string name;
};

#endif // ITEM_H
