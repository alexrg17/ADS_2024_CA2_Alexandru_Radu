#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>
#include "BinaryTree/TreeMap.h"

// Struct to represent a row of retail data
struct RetailData {
    std::string date;
    std::string product;
    std::string category;
    int unitsSold;
    double pricePerUnit;
    double totalRevenue;
};

// Function to read data from the CSV file
std::vector<RetailData> readCSV(const std::string& filename) {
    std::vector<RetailData> data;
    std::ifstream file("/Users/alex/CLionProjects/ADS_2024_CA2_Alexandru_Radu/RetailSalesData.csv");

    if (!file.is_open()) {
        throw std::runtime_error("Error: Unable to open file. Check the filename and location.");
    }

    std::string line;
    std::getline(file, line); // Skip the header row
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        RetailData row;
        std::getline(ss, row.date, ',');
        std::getline(ss, row.product, ',');
        std::getline(ss, row.category, ',');
        ss >> row.unitsSold;
        ss.ignore(); // Ignore the comma
        ss >> row.pricePerUnit;
        ss.ignore(); // Ignore the comma
        ss >> row.totalRevenue;
        data.push_back(row);
    }

    return data;
}

// Function to display data in a table format
void displayData(const std::vector<RetailData>& data) {
    if (data.empty()) {
        std::cout << "No data to display.\n";
        return;
    }

    std::cout << std::left << std::setw(12) << "Date"
              << std::setw(15) << "Product"
              << std::setw(12) << "Category"
              << std::setw(12) << "Units Sold"
              << std::setw(15) << "Price/Unit"
              << std::setw(15) << "Total Revenue" << "\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto& row : data) {
        std::cout << std::left << std::setw(12) << row.date
                  << std::setw(15) << row.product
                  << std::setw(12) << row.category
                  << std::setw(12) << row.unitsSold
                  << std::setw(15) << row.pricePerUnit
                  << std::setw(15) << row.totalRevenue << "\n";
    }
}

// Function to create an index for a specified field
void createIndex(const std::vector<RetailData>& data, const std::string& field) {
    // Validate the field
    if (field != "Product" && field != "Category" && field != "Date") {
        std::cerr << "Error: Invalid field specified. Please choose Product, Category, or Date.\n";
        return;
    }

    TreeMap<std::string, int> index;

    for (const auto& row : data) {
        std::string key;

        // Determine the key based on the chosen field
        if (field == "Product") key = row.product;
        else if (field == "Category") key = row.category;
        else if (field == "Date") key = row.date;

        if (key.empty()) continue; // Skip empty keys

        // Add to the index or increment the count
        if (!index.containsKey(key)) {
            index.put(key, 1); // First occurrence
        } else {
            index.put(key, index.get(key) + 1); // Increment count
        }
    }

    // Display the index
    std::cout << "Index for field: " << field << "\n";
    for (const auto& key : index.keySet()) {
        std::cout << key << ": " << index.get(key) << " rows\n";
    }
}

// Function to filter data based on a user-specified value
void filterData(const std::vector<RetailData>& data, const std::string& field, const std::string& value) {
    std::vector<RetailData> filteredData;

    for (const auto& row : data) {
        if ((field == "Product" && row.product == value) ||
            (field == "Category" && row.category == value) ||
            (field == "Date" && row.date == value)) {
            filteredData.push_back(row);
        }
    }

    if (filteredData.empty()) {
        std::cout << "No matching rows found for " << field << " = " << value << ".\n";
    } else {
        displayData(filteredData);
    }
}

int main() {
    try {
        std::string filename = "RetailSalesData.csv";
        std::vector<RetailData> data = readCSV(filename);

        int choice;
        do {
            std::cout << "\nMenu:\n";
            std::cout << "1. View all data\n";
            std::cout << "2. Create an index\n";
            std::cout << "3. Filter data by a field\n";
            std::cout << "4. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            if (choice == 1) {
                displayData(data);
            } else if (choice == 2) {
                std::string field;
                std::cout << "Enter field to index (Product/Category/Date): ";
                std::cin >> field;
                createIndex(data, field);
            } else if (choice == 3) {
                std::string field, value;
                std::cout << "Enter field to filter by (Product/Category/Date): ";
                std::cin >> field;
                std::cout << "Enter value for " << field << ": ";
                std::cin >> value;
                filterData(data, field, value);
            } else if (choice != 4) {
                std::cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 4);

        std::cout << "Exiting program.\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}