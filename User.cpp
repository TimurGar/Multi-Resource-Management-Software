#include "User.h"

using namespace std;
using namespace crow;



// Constructor with username
User::User(const std::string& name) : userName(name) {}

// Constructor with JSON input
User::User(json::rvalue readValueJson) {
    updateFromJson(readValueJson);
}

// Set username
void User::setUsername(const std::string& newUsername) {
    userName = newUsername;
}

// Add an item to the user's collection
void User::addItem(const Item& item) {
    items.push_back(item);


}

std::vector<std::string> User::getItemIds() const {
    std::vector<std::string> ids;
    for (const auto& item : items) { // 
        if (item.getUserId() == this->userName) { // Assuming userName is used as userID
            ids.push_back(item.getId());
        }
    }
    return ids;
}


// Serialize the User object to JSON
crow::json::wvalue User::convertToJson() const {
    json::wvalue writeJson;
    writeJson["userName"] = userName;
    return writeJson;
}

// Update from JSON
void User::updateFromJson(json::rvalue readValueJson) {
    userName = readValueJson["userName"].s();
}
