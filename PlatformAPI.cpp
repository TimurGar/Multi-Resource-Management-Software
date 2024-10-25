#include <crow.h>
#include <map>
#include <csignal>
#include <string>
#include "User.h"
#include "Item.h"
#include "Computer.h"
#include "Book.h"
#include "Note.h"
#include "GenericAPI.h"
#include "persistence.h"

using namespace std;
using namespace crow;
extern std::map<std::string, Item> itemsMap;


map<string, User> usersMap = loadFromFile<User>("users.json");
map<string, Item> itemsMap = loadFromFile<Item>("items.json");
map<string, Computer> computersMap = loadFromFile<Computer>("computers.json");
map<string, Book> booksMap = loadFromFile<Book>("books.json");
map<string, Note> notesMap = loadFromFile<Note>("notes.json");
template<>
crow::response GenericAPI<Computer>::createResource(const crow::request& req) {
    auto jsonValue = crow::json::load(req.body);
    if (!jsonValue) {
        return crow::response(400, "Invalid JSON");
    }

    Computer newComputer(jsonValue);
    computersMap[newComputer.getId()] = newComputer;
    itemsMap[newComputer.getId()] = newComputer.toItem();
    GenericAPI<Item>::resourceMap = itemsMap;
    GenericAPI<Computer>::resourceMap = computersMap;

    // Optionally save to file immediately
    saveToFile<Computer>(computersMap, "computers.json");
    saveToFile<Item>(itemsMap, "items.json");

    return crow::response(200, "Computer added");
}

template<>
crow::response GenericAPI<Note>::createResource(const crow::request& req) {
    auto jsonValue = crow::json::load(req.body);
    if (!jsonValue) {
        return crow::response(400, "Invalid JSON");
    }

    Note newNote(jsonValue);
    notesMap[newNote.getId()] = newNote;
    itemsMap[newNote.getId()] = newNote.toItem(); // Update itemsMap with Item representation
    GenericAPI<Item>::resourceMap = itemsMap;
    GenericAPI<Note>::resourceMap = notesMap;

    saveToFile<Note>(notesMap, "notes.json");
    saveToFile<Item>(itemsMap, "items.json");

    return crow::response(200, "Note added");
}

template<>
crow::response GenericAPI<Book>::createResource(const crow::request& req) {
    auto jsonValue = crow::json::load(req.body);
    if (!jsonValue) {
        return crow::response(400, "Invalid JSON");
    }

    Book newBook(jsonValue);
    booksMap[newBook.getId()] = newBook;
    itemsMap[newBook.getId()] = newBook.toItem(); // Update itemsMap with Item representation

    GenericAPI<Item>::resourceMap = itemsMap;
    GenericAPI<Book>::resourceMap = booksMap;

    saveToFile<Book>(booksMap, "books.json");
    saveToFile<Item>(itemsMap, "items.json");

    return crow::response(200, "Book added");
}

int main() {
    // Create GenericAPIs to use in the CROW_ROUTES
    GenericAPI<User>::resourceMap = usersMap;
    GenericAPI<Item>::resourceMap = itemsMap;
    GenericAPI<Computer>::resourceMap = computersMap;
    GenericAPI<Book>::resourceMap = booksMap;
    GenericAPI<Note>::resourceMap = notesMap;
    // Setup the simple web service
    crow::SimpleApp app;

    // Define user routes
    CROW_ROUTE(app, "/api/users").methods("POST"_method)(GenericAPI<User>::createResource);
    CROW_ROUTE(app, "/api/users").methods("GET"_method)(GenericAPI<User>::readAllResources);
    CROW_ROUTE(app, "/api/users/<string>/items").methods("GET"_method)([](const std::string& userID) {
        // Create JSON response
        crow::json::wvalue jsonResponse;

        size_t index = 0;
        for (const auto& [itemID, item] : itemsMap) {
            if (item.getUserId() == userID) {
                jsonResponse[index++] = item.convertToJson();
            }
        }

        return crow::response(jsonResponse);
    });

    
    // Define item routes
    CROW_ROUTE(app, "/api/items/computers").methods("GET"_method)([]() {
        json::wvalue jsonResponse;
        int index = 0;
        for (const auto& kv : computersMap) {
            jsonResponse[index++] = kv.second.convertToJson();
        }
        return crow::response(jsonResponse.dump());
    });
    CROW_ROUTE(app, "/api/items/computers").methods("POST"_method)(GenericAPI<Computer>::createResource);
    CROW_ROUTE(app, "/api/items/computers/<string>").methods("PUT"_method)([](const crow::request& req, string id) {
        auto jsonValue = crow::json::load(req.body);
        if (!jsonValue) {
            return crow::response(400, "Invalid JSON");
        }

        if (computersMap.find(id) == computersMap.end()) {
            return crow::response(404, "Computer not found");
        }

        Computer updatedComputer(jsonValue);
        computersMap[id] = updatedComputer;
        itemsMap[id] = updatedComputer.toItem();
        GenericAPI<Item>::resourceMap = itemsMap;
        GenericAPI<Computer>::resourceMap = computersMap;

        saveToFile<Computer>(computersMap, "computers.json");
        saveToFile<Item>(itemsMap, "items.json");

        return crow::response(200, "Computer updated");
    });

    CROW_ROUTE(app, "/api/items/computers/<string>").methods("DELETE"_method)([](string id) {
        if (computersMap.find(id) == computersMap.end()) {
            return crow::response(404, "Computer not found");
        }

        computersMap.erase(id);
        itemsMap.erase(id);
        GenericAPI<Item>::resourceMap = itemsMap;
        GenericAPI<Computer>::resourceMap = computersMap;

        saveToFile<Computer>(computersMap, "computers.json");
        saveToFile<Item>(itemsMap, "items.json");

        return crow::response(200, "Computer deleted");
    });

    CROW_ROUTE(app, "/api/items/books").methods("GET"_method)([]() {
        json::wvalue jsonResponse;
        int index = 0;
        for (const auto& kv : booksMap) {
            jsonResponse[index++] = kv.second.convertToJson();
        }
        return crow::response(jsonResponse.dump());
    });

    CROW_ROUTE(app, "/api/items/books").methods("POST"_method)(GenericAPI<Book>::createResource);
    CROW_ROUTE(app, "/api/items/books/<string>").methods("PUT"_method)([](const crow::request& req, string id) {
        auto jsonValue = crow::json::load(req.body);
        if (!jsonValue) {
            return crow::response(400, "Invalid JSON");
        }

        if (booksMap.find(id) == booksMap.end()) {
            return crow::response(404, "Book not found");
        }

        Book updatedBook(jsonValue);
        booksMap[id] = updatedBook;
        itemsMap[id] = updatedBook.toItem();
        GenericAPI<Item>::resourceMap = itemsMap;
        GenericAPI<Book>::resourceMap = booksMap;

        saveToFile<Book>(booksMap, "books.json");
        saveToFile<Item>(itemsMap, "items.json");

        return crow::response(200, "Book updated");
    });

    CROW_ROUTE(app, "/api/items/books/<string>").methods("DELETE"_method)([](string id) {
        if (booksMap.find(id) == booksMap.end()) {
            return crow::response(404, "Book not found");
        }

        booksMap.erase(id);
        itemsMap.erase(id);
        GenericAPI<Item>::resourceMap = itemsMap;
        GenericAPI<Book>::resourceMap = booksMap;

        saveToFile<Book>(booksMap, "books.json");
        saveToFile<Item>(itemsMap, "items.json");

        return crow::response(200, "Book deleted");
    });

    CROW_ROUTE(app, "/api/items/notes").methods("GET"_method)([]() {
    json::wvalue jsonResponse;
    int index = 0;
    for (const auto& kv : notesMap) {
        jsonResponse[index++] = kv.second.convertToJson();
    }
    return crow::response(jsonResponse.dump());
    });


    CROW_ROUTE(app, "/api/items/notes").methods("POST"_method)(GenericAPI<Note>::createResource);
    CROW_ROUTE(app, "/api/items/notes/<string>").methods("PUT"_method)([](const crow::request& req, string id) {
        auto jsonValue = crow::json::load(req.body);
        if (!jsonValue) {
            return crow::response(400, "Invalid JSON");
        }

        if (notesMap.find(id) == notesMap.end()) {
            return crow::response(404, "Note not found");
        }

        Note updatedNote(jsonValue);
        notesMap[id] = updatedNote;
        itemsMap[id] = updatedNote.toItem();
        GenericAPI<Item>::resourceMap = itemsMap;
        GenericAPI<Note>::resourceMap = notesMap;

        saveToFile<Note>(notesMap, "notes.json");
        saveToFile<Item>(itemsMap, "items.json");

        return crow::response(200, "Note updated");
    });

    CROW_ROUTE(app, "/api/items/notes/<string>").methods("DELETE"_method)([](string id) {
        if (notesMap.find(id) == notesMap.end()) {
            return crow::response(404, "Note not found");
        }

        notesMap.erase(id);
        itemsMap.erase(id);
        GenericAPI<Item>::resourceMap = itemsMap;
        GenericAPI<Note>::resourceMap = notesMap;

        saveToFile<Note>(notesMap, "notes.json");
        saveToFile<Item>(itemsMap, "items.json");

        return crow::response(200, "Note deleted");
    });


    // Run the web service app
    app.port(15081).multithreaded().run();

    // Optionally save on shutdown
    saveToFile<User>(GenericAPI<User>::resourceMap, "users.json");
    saveToFile<Computer>(GenericAPI<Computer>::resourceMap, "computers.json");
    saveToFile<Book>(GenericAPI<Book>::resourceMap, "books.json");
    saveToFile<Note>(GenericAPI<Note>::resourceMap, "notes.json");


    // Saving computers, books, notes to items.json
    saveToFile<Computer>(GenericAPI<Computer>::resourceMap, "items.json");
    saveToFile<Book>(GenericAPI<Book>::resourceMap, "items.json");
    saveToFile<Note>(GenericAPI<Note>::resourceMap, "items.json");
}

