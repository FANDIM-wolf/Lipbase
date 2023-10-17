// LipSQL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>
#include "implementation.cpp";
#include <regex>


int main() {
    /*


    //grab arguments  from string "CREATE TABLE rows = 5 columns = 5 WITH id(int) , c1(double) ,  c2(double) , c3(double) , c4(double) ;"  and save this data in some variables  "

    std::string str = "CREATE TABLE rows = 5 columns = 5 WITH id(int) , c1(double) , c2(double) , c3(double) , c4(double) , c5(double) ;";
    int rows, columns;
    std::vector<std::pair<std::string, std::string>> fields;

    std::regex e1("rows = (\\d+)");
    std::regex e2("columns = (\\d+)");
    std::regex e3("(\\w+)\\((\\w+)\\)");

    std::smatch match;
    if (std::regex_search(str, match, e1)) {
        rows = std::stoi(match.str(1));
    }
    if (std::regex_search(str, match, e2)) {
        columns = std::stoi(match.str(1));
    }

    auto words_begin = std::sregex_iterator(str.begin(), str.end(), e3);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        fields.push_back(std::make_pair(match.str(1), match.str(2)));
    }

    std::cout << "Rows: " << rows << ", Columns: " << columns << std::endl;
    for (const auto& field : fields) {
        std::cout << "Column name: " << field.first << ", Type: " << field.second << std::endl;
    }

    */

    // Create a table with 2 rows and 3 columns
    // Creating a table with 3 rows and 3 columns
    Table t(3, 3);

    // Inserting data into the table row-by-row
    // The data is completely made-up and may not make sense in a real world application.

    // For row 0
    t.insert_data(Record("integer", 0, 0, 1, std::nullopt));  // ID = 1
    t.insert_data(Record("integer", 0, 1, 25, std::nullopt));  // Age = 25
    t.insert_data(Record("double", 0, 2, std::nullopt, 92.5));  // Score = 92.5
    // For row 1
    t.insert_data(Record("integer", 1, 0, 1, std::nullopt));  // ID = 1
    t.insert_data(Record("integer", 1, 1, 25, std::nullopt));  // Age = 25
    t.insert_data(Record("double", 1, 2, std::nullopt, 92.1));  // Score = 92.5


    // Similar data for row 1 and row 2 can be inserted here (not shown)...

    // Creating conditions
    Conditon con1; con1.value_integer = 1;  // Condition on Id
    Conditon con2; con2.value_integer = 25;  // Condition on Age
    Conditon con3; con3.value_double = 92.5;  // Condition on Score
    std::vector<Conditon> conditions = { con1, con2, con3 };

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

    return 0;
}





