// LipSQL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include "implementation.cpp";
#include <regex>


int main() {
    

    // Create a table with 2 rows and 3 columns
    // Creating a table with 5 rows and 3 columns
    Table t(5, 3);

    // Inserting data into the table row-by-row
    // The data is completely made-up and may not make sense in a real world application.

    // For row 0
    t.insert_data(Record("integer", 0, 0, 0, std::nullopt));  // ID = 0
    t.insert_data(Record("integer", 0, 1, 25, std::nullopt));  // Age = 25
    t.insert_data(Record("double", 0, 2, std::nullopt, 92.5));  // Score = 92.5
    // For row 1
    t.insert_data(Record("integer", 1, 0, 1, std::nullopt));  // ID = 1
    t.insert_data(Record("integer", 1, 1, 24, std::nullopt));  // Age = 25
    t.insert_data(Record("double", 1, 2, std::nullopt, 92.1));  // Score = 92.5
    // For row 2
    t.insert_data(Record("integer", 2, 0, 2, std::nullopt));  // ID = 2
    t.insert_data(Record("integer", 2, 1, 25, std::nullopt));  // Age = 25
    t.insert_data(Record("double", 2, 2, std::nullopt, 92.5));  // Score = 92.5
   

    // For row 3
    t.insert_data(Record("integer", 3, 0, 3, std::nullopt));  // ID = 3
    t.insert_data(Record("integer", 3, 1, 0, std::nullopt));  // Age = 25
    t.insert_data(Record("double", 3, 2, std::nullopt, 92.1));  // Score = 92.5
    // Similar data for row 1 and row 2 can be inserted here (not shown)...

    // Creating conditions
    Conditon con1; con1.value_integer = NULL;  // Condition on Id
    Conditon con2; con2.value_integer = 25;  // Condition on Age
    Conditon con3; con3.value_double = NULL;  // Condition on Score
    std::vector<Conditon> conditions = { con1 , con2 , con3 };

    // Selecting data from the table based on conditions
    std::vector<Record> selected_records = t.select_data(conditions);

    // Print selected data
    for (const auto& record : selected_records) {
        if (record.intValue.has_value()) {
            std::cout << "Row: " << record.row << ", Col: " << record.col << ", Value: " << record.intValue.value() << std::endl;
        }
        else if (record.doubleValue.has_value()) {
            std::cout << "Row: " << record.row << ", Col: " << record.col << ", Value: " << record.doubleValue.value() << std::endl;
        }
    }

    std::cout << "updating" << std::endl;
    // Updating data from the table based on conditions
    Conditon up1; up1.value_integer = 12;  // Condition on Id
    Conditon up2; up2.value_integer = 21;  // Condition on Age
    Conditon up3; up3.value_double = 46;  // Condition on Score
    std::vector<Conditon> updates = { up1 , up2 , up3 };

    std::vector<Record> updated_records = t.update_data(conditions , updates);
    
    // Print selected data
    for (const auto& record : updated_records) {
        if (record.intValue.has_value()) {
            std::cout << "Row: " << record.row << ", Col: " << record.col << ", Value: " << record.intValue.value() << std::endl;
            
        }
        else if (record.doubleValue.has_value()) {
            
            std::cout << "Row: " << record.row << ", Col: " << record.col << ", Value: " << record.doubleValue.value() << std::endl;
        }
    }
    return 0;
}





