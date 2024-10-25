// Computer.h

#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <crow.h>
#include "Item.h"

class Computer : public Item {
public:
    // Constructors
    Computer();
    Computer(crow::json::rvalue readValueJson);

    // Getters and Setters
    std::string getModel() const { return model; }
    void setModel(const std::string& model);
    int getYear() const { return year; }
    void setYear(int year);
    std::string getBrand() const { return brand; }
    void setBrand(const std::string& brand);

    // JSON Serialization
    crow::json::wvalue convertToJson() const override;
    void updateFromJson(crow::json::rvalue readValueJson) override;

    // Conversion to Item
    Item toItem() const;

private:
    std::string model;
    int year;
    std::string brand;
};

#endif // COMPUTER_H
