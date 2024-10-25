// Computer.cpp

#include "Computer.h"

using namespace std;
using namespace crow;

// Default constructor
Computer::Computer() : Item(), model(""), year(0), brand("") {}

// Constructor with JSON input
Computer::Computer(json::rvalue readValueJson) : Item(readValueJson) {
    updateFromJson(readValueJson);
}

// Accessor and Mutator methods for model, year, and brand
// ...

// Serialize the Computer object to JSON
crow::json::wvalue Computer::convertToJson() const {
    json::wvalue writeJson = Item::convertToJson();
    writeJson["model"] = model;
    writeJson["year"] = year;
    writeJson["brand"] = brand;
    return writeJson;
}

// Update from JSON
void Computer::updateFromJson(json::rvalue readValueJson) {
    Item::updateFromJson(readValueJson);
    model = readValueJson["model"].s();
    year = readValueJson["year"].i();
    brand = readValueJson["brand"].s();
}

// Conversion to Item
Item Computer::toItem() const {
    Item item;
    item.setId(getId());
    item.setName(getName());
    item.setPrice(getPrice());
    item.setLocation(getLocation());
    item.setUserId(getUserId());

    return item;
}
