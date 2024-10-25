#include "GenericAPI.h"
#include <stdexcept>
#include "Computer.h"
#include "Item.h"
#include "Note.h"
#include "Book.h"
#include "User.h"

using namespace std;
using namespace crow;

template<typename T>
map<string, T> GenericAPI<T>::resourceMap;

template<typename T>
response GenericAPI<T>::createResource(const request& req) {
    json::rvalue readValueJson = json::load(req.body);
    if (!readValueJson) {
        return response(400, "Invalid JSON");
    }
    
    T resource{readValueJson};
    resourceMap[resource.getId()] = resource;

    return response(201, resource.convertToJson().dump());
}

template<typename T>
response GenericAPI<T>::readResource(const string& id) {
    try {
        T resource = resourceMap.at(id);
        return response(resource.convertToJson().dump());
    } catch (out_of_range&) {
        return response(404, "Resource Not Found");
    }
}

template<typename T>
response GenericAPI<T>::readAllResources() {
    json::wvalue jsonWriteValue;
    int index = 0;
    for (const auto& keyValuePair : resourceMap) {
        jsonWriteValue[index++] = keyValuePair.second.convertToJson();
    }
    return response(jsonWriteValue.dump());
}

template<typename T>
response GenericAPI<T>::updateResource(const request& req, const string& id) {
    try {
        T resource = resourceMap.at(id);
        json::rvalue readValueJson = json::load(req.body);
        if (!readValueJson) {
            return response(400, "Invalid JSON");
        }

        resource.updateFromJson(readValueJson);
        resourceMap[id] = resource;

        return response(200, resource.convertToJson().dump());
    } catch (out_of_range&) {
        return response(404, "Resource Not Found");
    }
}

template<typename T>
response GenericAPI<T>::deleteResource(const string& id) {
    try {
        resourceMap.erase(id);
        return response(204);
    } catch (out_of_range&) {
        return response(404, "Resource Not Found");
    }
}

template class GenericAPI<Item>;
template class GenericAPI<Book>;
template class GenericAPI<Note>;
template class GenericAPI<Computer>;
template class GenericAPI<User>;
