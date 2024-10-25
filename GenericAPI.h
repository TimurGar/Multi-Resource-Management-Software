#ifndef GENERIC_API_H
#define GENERIC_API_H

#include <crow.h>
#include <map>
#include <string>
#include "Computer.h" // Include the Computer header

template<typename T> 
class GenericAPI {
public:
    static std::map<std::string, T> resourceMap;
    static crow::response createResource(const crow::request& req);
    static crow::response readResource(const std::string& id); 
    static crow::response readAllResources();
    static crow::response updateResource(const crow::request& req, const std::string& id);
    static crow::response deleteResource(const std::string& id); 
};

// Declare the specialization for the Computer class
template<>
crow::response GenericAPI<Computer>::createResource(const crow::request& req);

#endif // GENERIC_API_H
