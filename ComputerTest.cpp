#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include <string>
#include "Item.h"
#include "Computer.h"

using namespace std;  
using namespace crow;  


TEST_CASE("Testing Computer Class") 
{
    // Testing Computer constructor
    SUBCASE("Testing the Computer Constructor") 
    {
        // Create a new Computer class from json.
        Computer testComputer(json::load(R"({"brand":"Microsoft","year":2019,"userID":"Steven","id":"2","name":"Used PC","price":1400.0,"location":"Moore","model":"Chome Book"})"));

        // Check that the constructor properly loaded the values.
        CHECK(testComputer.getId() == "2");
        CHECK(testComputer.getUserId() == "Steven");
        CHECK(testComputer.getName() == "Used PC");
        CHECK(testComputer.getPrice() == 1400.0f);
        CHECK(testComputer.getLocation() == "Moore");
        CHECK(testComputer.getBrand() == "Microsoft");
        CHECK(testComputer.getYear() == 2019);
        CHECK(testComputer.getModel() == "Chome Book");
            
    }

    // Testing convertToJson method
    SUBCASE("Testing the convertToJson Method") 
    {
        // Create a new Computer class from json.
        Computer testComputer(json::load(R"({"brand":"Microsoft","year":2019,"userID":"Steven","id":"2","name":"Used PC","price":1400.0,"location":"Moore","model":"Chome Book"})"));

        // Convert the Computer class to json using the convertToJson method.
        json::wvalue jsonOutput = testComputer.convertToJson();

        // Convert back to a json read value for testing.
        json::rvalue jsonReadValue = json::load(jsonOutput.dump());

        // Check the values.
        CHECK(jsonReadValue["brand"].s() == "Microsoft");
        CHECK(jsonReadValue["year"].i() == 2019);
        CHECK(jsonReadValue["userID"].s() == "Steven");
        CHECK(jsonReadValue["id"].s() == "2");
        CHECK(jsonReadValue["name"].s() == "Used PC");
        CHECK(jsonReadValue["price"].d() == 1400.0f);
        CHECK(jsonReadValue["location"].s() == "Moore");
        CHECK(jsonReadValue["model"].s() == "Chome Book");
    }

    // Testing updateFromJson method
    SUBCASE("Testing updateFromJson Method") 
    {
        // Create a new Computer class from json.
        Computer testComputer(json::load(R"({"brand":"Microsoft","year":2019,"userID":"Steven","id":"2","name":"Used PC","price":1400.0,"location":"Moore","model":"Chome Book"})"));

        // Create the update json.
        json::rvalue updateJson = json::load(R"({"brand":"Apple","year":2020,"userID":"Steven","id":"2","name":"New laptop","price":1000.0,"location":"THC","model":"Air"})");

        // Update the Computer with the updateFromJson method. 
        testComputer.updateFromJson(updateJson);

        // Check the updated values.
        CHECK(testComputer.getId() == "2");
        CHECK(testComputer.getUserId() == "Steven");
        CHECK(testComputer.getName() == "New laptop");
        CHECK(testComputer.getPrice() == 1000.0f);
        CHECK(testComputer.getLocation() == "THC");
        CHECK(testComputer.getBrand() == "Apple");
        CHECK(testComputer.getYear() == 2020);
        CHECK(testComputer.getModel() == "Air");
    }
}