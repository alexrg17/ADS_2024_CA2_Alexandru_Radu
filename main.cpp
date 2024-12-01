#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include "BinaryTree/TreeMap.h"

// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> result;
    std::istringstream stream(line);
    std::string token;
    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}

// Function to print the contents of the TreeMap
void printTreeMap(const TreeMap<std::string, std::vector<std::string>>& data) {
    for (const auto& key : data.keySet()) {
        std::cout << "Category: " << key << std::endl;
        for (const auto& record : data.get(key)) {
            std::cout << "  " << record << std::endl;
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string filename = "RetailSalesData.csv";

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return 1;
    }

    // Create a TreeMap to organize data by category
    TreeMap<std::string, std::vector<std::string>> salesData;

    // Read the CSV file
    std::string line;
    bool isHeader = true;
    while (std::getline(file, line)) {
        if (isHeader) {
            isHeader = false; // Skip the header row
            continue;
        }

        // Split the line into fields
        auto fields = split(line, ',');

        // Check if the row has valid data
        if (fields.size() < 6) continue;

        // Extract the relevant fields
        std::string category = fields[2];
        std::string record = "Date: " + fields[0] + ", Product: " + fields[1] +
                             ", Units Sold: " + fields[3] + ", Price: $" + fields[4] +
                             ", Revenue: $" + fields[5];

        // Add the record to the TreeMap
        if (!salesData.containsKey(category)) {
            salesData.put(category, std::vector<std::string>());
        }
        salesData.get(category).push_back(record);
    }

    file.close();

    // Display the data
    std::cout << "Retail Sales Data by Category:\n";
    printTreeMap(salesData);

    return 0;
}