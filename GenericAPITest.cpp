// Q: Should we test for book, note, and user?

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include "User.h"
#include "Item.h"
#include "Item.h"
#include "Book.h"
#include "Note.h"
#include "GenericAPI.h"
#include "persistence.h"

using namespace std;
using namespace crow;

// map<string, User> usersMap;
map<string, Item> itemsMap;
// map<string, Item> itemsMap;
// map<string, Book> booksMap;
// map<string, Note> notesMap;

TEST_CASE("Creating a new Item resource") 
{
    // Setup resource map to be empty before the test
    GenericAPI<Item>::resourceMap.clear();

    // Setup request object
    request req;
    req.body = R"({"location":"THC","price":800.0,"name":"laptop","id":"1","userID":"1"})"; 

    // Perform the action
    response res = GenericAPI<Item>::createResource(req);

    // Check the results
    CHECK(res.code == 201); // Check that the response code is 201 Created
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Item>::resourceMap.size() == 1); // Ensure the resource was added to the map
    CHECK(GenericAPI<Item>::resourceMap.at("1").getId() == "1"); // Validate the resource content
    CHECK(GenericAPI<Item>::resourceMap.at("1").getUserId() == "1"); // Validate the resource content
    CHECK(GenericAPI<Item>::resourceMap.at("1").getName() == "laptop"); // Validate the resource content
    CHECK(GenericAPI<Item>::resourceMap.at("1").getPrice() == 800.0f); // Validate the resource content
    CHECK(GenericAPI<Item>::resourceMap.at("1").getLocation() == "THC"); // Validate the resource content
}

TEST_CASE("Reading an Item resource") 
{
    // Load a resource to read.
    itemsMap["1"] = Item{json::load(R"({"location":"THC","price":800.0,"name":"laptop","id":"1","userID":"1"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Item>::resourceMap = itemsMap;

    // Perform the action
    response res = GenericAPI<Item>::readResource("1");

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == itemsMap["1"].convertToJson().dump()); // Validate the reponse body
    CHECK(GenericAPI<Item>::resourceMap.size() == 1); // Ensure that no resources were added or removed from the map
}

TEST_CASE("Reading all Item resources") 
{
    // Load resources to read.
    itemsMap["1"] = Item{json::load(R"({"location":"THC","price":800.0,"name":"laptop","id":"1","userID":"1"})")};
    itemsMap["2"] = Item{json::load(R"({"location":"THC","price":700.0,"name":"laptop","id":"2","userID":"2"})")};
    itemsMap["3"] = Item{json::load(R"({"location":"Moore","price":600.0,"name":"laptop","id":"3","userID":"3"})")};
    itemsMap["4"] = Item{json::load(R"({"location":"Moore","price":500.0,"name":"laptop","id":"4","userID":"4"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Item>::resourceMap = itemsMap;

    // Perform the action
    response res = GenericAPI<Item>::readAllResources();

    // Create the expected reponse body
    string expectedResponseBody = R"([{"location":"THC","price":800.0,"name":"laptop","id":"1","userID":"1"},{"userID":"2","id":"2","name":"laptop","price":700.0,"location":"THC"},{"location":"Moore","price":600.0,"name":"laptop","id":"3","userID":"3"},{"location":"Moore","price":500.0,"name":"laptop","id":"4","userID":"4"}])";

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == expectedResponseBody); // Validate the reponse body
    CHECK(GenericAPI<Item>::resourceMap.size() == 4); // Ensure that no resources were added or removed from the map
}


TEST_CASE("Updating a Item resource") 
{
    // Load resources to update.
    itemsMap["1"] = Item{json::load(R"({"location":"THC","price":800.0,"name":"laptop","id":"1","userID":"1"})")};
    itemsMap["2"] = Item{json::load(R"({"location":"THC","price":700.0,"name":"laptop","id":"2","userID":"2"})")};
    itemsMap["3"] = Item{json::load(R"({"location":"Moore","price":600.0,"name":"laptop","id":"3","userID":"3"})")};
    itemsMap["4"] = Item{json::load(R"({"location":"Moore","price":500.0,"name":"laptop","id":"4","userID":"4"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Item>::resourceMap = itemsMap;

    // Setup request object
    request req;
    req.body = R"({"location":"Jepson","price":800.0,"name":"Newlaptop","id":"1","userID":"1"})"; 

    // Setup a response object
    response res;

    // Perform the action
    res = GenericAPI<Item>::updateResource(req, "1");

    // Check the results
    CHECK(res.code == 200); // Check that the response code is 200 Ok
    CHECK(res.body == req.body); // Validate the reponse body
    CHECK(GenericAPI<Item>::resourceMap.size() == 4); // Ensure no resource was added or removed from the map
    CHECK(GenericAPI<Item>::resourceMap.at("1").getId() == "1"); // Validate the resource content
    CHECK(GenericAPI<Item>::resourceMap.at("1").getUserId() == "1"); // Validate the resource content
    CHECK(GenericAPI<Item>::resourceMap.at("1").getName() == "Newlaptop"); // Validate the resource content
    CHECK(GenericAPI<Item>::resourceMap.at("1").getPrice() == 800.0f); // Validate the resource content
    CHECK(GenericAPI<Item>::resourceMap.at("1").getLocation() == "Jepson"); // Validate the resource content
}


TEST_CASE("Deleting a Item resource") 
{
    // Load a resources to update.
    itemsMap["1"] = Item{json::load(R"({"location":"THC","price":800.0,"name":"laptop","id":"1","userID":"1"})")};
    itemsMap["2"] = Item{json::load(R"({"location":"THC","price":700.0,"name":"laptop","id":"2","userID":"2"})")};
    itemsMap["3"] = Item{json::load(R"({"location":"Moore","price":600.0,"name":"laptop","id":"3","userID":"3"})")};
    itemsMap["4"] = Item{json::load(R"({"location":"Moore","price":500.0,"name":"laptop","id":"4","userID":"4"})")};

    // Setup resource map to be empty before the test
    GenericAPI<Item>::resourceMap = itemsMap;

    // Perform the action
    response res = GenericAPI<Item>::deleteResource("4");

    // Check the results
    CHECK(res.code == 204); // Check that the response code is 204 No Content
    CHECK(res.body == ""); // Validate the reponse body
    CHECK(GenericAPI<Item>::resourceMap.size() == 3); // Ensure one resource was removed from the map
}