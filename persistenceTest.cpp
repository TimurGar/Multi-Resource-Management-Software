#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <crow.h>
#include <doctest.h>
#include "Item.h"
#include "persistence.h"

using namespace std;
using namespace crow;


TEST_CASE("Saving to a file and loading from a file.") 
{
    // Load a resources to read.
    map<string, Item> itemsMap;
    itemsMap["1"] = Item{json::load(R"({"location":"THC","price":800.0,"name":"laptop","id":"1","userID":"1"})")};
    itemsMap["2"] = Item{json::load(R"({"location":"THC","price":700.0,"name":"laptop","id":"2","userID":"2"})")};
    itemsMap["3"] = Item{json::load(R"({"location":"Moore","price":600.0,"name":"laptop","id":"3","userID":"3"})")};
    itemsMap["4"] = Item{json::load(R"({"location":"Moore","price":500.0,"name":"laptop","id":"4","userID":"4"})")};

    // Perform the action
    saveToFile<Item>(itemsMap, "persistenceTest.json");
    map<string, Item> itemsMapLoaded = loadFromFile<Item>("persistenceTest.json");

    // Check the results
    CHECK(itemsMap.size() == itemsMapLoaded.size()); // Ensure saved and loaded map are the same size.
    
    // First Item
    CHECK(itemsMap.at("1").getId() == itemsMapLoaded.at("1").getId()); // Validate the resource content
    CHECK(itemsMap.at("1").getUserId() == itemsMapLoaded.at("1").getUserId()); // Validate the resource content
    CHECK(itemsMap.at("1").getName() == itemsMapLoaded.at("1").getName()); // Validate the resource content
    CHECK(itemsMap.at("1").getPrice() == itemsMapLoaded.at("1").getPrice()); // Validate the resource content
    CHECK(itemsMap.at("1").getLocation() == itemsMapLoaded.at("1").getLocation()); // Validate the resource content
    
    // Secon Item
    CHECK(itemsMap.at("2").getId() == itemsMapLoaded.at("2").getId()); // Validate the resource content
    CHECK(itemsMap.at("2").getUserId() == itemsMapLoaded.at("2").getUserId()); // Validate the resource content
    CHECK(itemsMap.at("2").getName() == itemsMapLoaded.at("2").getName()); // Validate the resource content
    CHECK(itemsMap.at("2").getPrice() == itemsMapLoaded.at("2").getPrice()); // Validate the resource content
    CHECK(itemsMap.at("2").getLocation() == itemsMapLoaded.at("2").getLocation()); // Validate the resource content

    // Third Item
    CHECK(itemsMap.at("3").getId() == itemsMapLoaded.at("3").getId()); // Validate the resource content
    CHECK(itemsMap.at("3").getUserId() == itemsMapLoaded.at("3").getUserId()); // Validate the resource content
    CHECK(itemsMap.at("3").getName() == itemsMapLoaded.at("3").getName()); // Validate the resource content
    CHECK(itemsMap.at("3").getPrice() == itemsMapLoaded.at("3").getPrice()); // Validate the resource content
    CHECK(itemsMap.at("3").getLocation() == itemsMapLoaded.at("3").getLocation()); // Validate the resource content

    // Fourht Item
    CHECK(itemsMap.at("4").getId() == itemsMapLoaded.at("4").getId()); // Validate the resource content
    CHECK(itemsMap.at("4").getUserId() == itemsMapLoaded.at("4").getUserId()); // Validate the resource content
    CHECK(itemsMap.at("4").getName() == itemsMapLoaded.at("4").getName()); // Validate the resource content
    CHECK(itemsMap.at("4").getPrice() == itemsMapLoaded.at("4").getPrice()); // Validate the resource content
    CHECK(itemsMap.at("4").getLocation() == itemsMapLoaded.at("4").getLocation()); // Validate the resource content
}