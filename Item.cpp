// Item.cpp

#include "Item.h"

using namespace std;
using namespace crow;

// Default constructor
Item::Item() : id(""), userID("-1"), price(0.0), location(""), name("") {}

// Constructor with JSON input
Item::Item(json::rvalue readValueJson) {
    updateFromJson(readValueJson);
}

// Convert to JSON
json::wvalue Item::convertToJson() const {
    json::wvalue writeJson;
    writeJson["id"] = id;
    writeJson["userID"] = userID;
    writeJson["name"] = name;
    writeJson["price"] = price;
    writeJson["location"] = location;
    return writeJson;
}

// Update from JSON
void Item::updateFromJson(json::rvalue readValueJson) {
    id = readValueJson["id"].s();
    userID = readValueJson["userID"].s();
    name = readValueJson["name"].s();
    price = readValueJson["price"].d();
    location = readValueJson["location"].s();
}