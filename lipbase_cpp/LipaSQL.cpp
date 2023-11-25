// TestLipaSQL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <string>
#include <optional>
#include <float.h>
#include <limits.h>
#include <iostream>

using namespace std;

class Record {
public:
    std::string type;
    int row;
    int col;
    std::optional<int> intValue;
    std::optional<double> doubleValue;
    std::optional<std::string> stringValue;  // New field for string value
    Record() : intValue(std::nullopt), doubleValue(std::nullopt), stringValue(std::nullopt) {}
    Record(std::string type, int row, int col, std::optional<int> intValue, std::optional<double> doubleValue, std::optional<std::string> stringValue)
        : type(type), row(row), col(col), intValue(intValue), doubleValue(doubleValue), stringValue(stringValue) {}
};


class Condition {
public:
    std::optional<int> value_integer;
    std::optional<double> value_double;
    std::optional<std::string> value_string;  // New field for string value


};

class Table {


public:
    std::vector<std::vector<Record>> records;
    int rows;
    int cols;
    string table_name;
    std::vector<string> names;
    std::vector<string> types_of_values;
    int counter = 0;
    Table(int rows, int cols) : rows(rows), cols(cols) {
        records.resize(rows, std::vector<Record>(cols, Record("", 0, 0, std::nullopt, std::nullopt, std::nullopt)));
    }



    void create_table(int rows, int cols,
        const std::vector<std::string>& names_of_columns,
        const std::vector<std::string>& types_of_columns) {
        // Implementation depends on your specific requirements
    }

    void insert_data(const std::vector<Record>& new_row) {
        cout << new_row.size() << endl;
        // Check if the new row has the same number of columns as the table
        if (new_row.size() == cols) {
            // Add the new row to the records vector
            records.push_back(new_row);
            rows++;  // Increment the number of rows
        }
        else {
            std::cerr << "Error: The number of columns in the new row does not match the table." << std::endl;
        }

    }

    std::vector<Record> select_data(const std::vector<Condition>& conditions) {
        std::vector<Record> select_records;

        // Iterate over records
        for (int i = 0; i < rows; i++) {
            bool row_matched = true; // Indicates whether the current row matches all conditions
            for (int j = 0; j < cols; j++) {
                // Condition check for integers
                if (conditions[j].value_integer && records[i][j].intValue != conditions[j].value_integer) {
                    if (conditions[j].value_integer != NULL) {
                        row_matched = false;
                    }
                }
                // Condition check for doubles
                if (conditions[j].value_double && records[i][j].doubleValue != conditions[j].value_double) {
                    if (conditions[j].value_double != NULL) {
                        row_matched = false;
                    }
                }
                // Condition check for doubles
                if (conditions[j].value_string && records[i][j].stringValue != conditions[j].value_string) {
                    if (conditions[j].value_string != std::nullopt) {
                        row_matched = false;
                    }
                }
                // If row is not matched in some column, we can skip it right away
                if (!row_matched) {
                    break;
                }
            }
            if (row_matched)  // If row is still matched after all conditions, push back all records in the row to select_records
                select_records.insert(select_records.end(), records[i].begin(), records[i].end());
        }

        return select_records;
    }

    std::vector<Record> update_data(const std::vector<Condition>& conditions, const std::vector<Condition>& updates) {
        std::vector<Record> select_records;

        // Iterate over records
        for (int i = 0; i < rows; i++) {
            bool row_matched = true; // Indicates whether the current row matches all conditions
            for (int j = 0; j < cols; j++) {
                // Condition check for integers
                if (conditions[j].value_integer && records[i][j].intValue != conditions[j].value_integer) {

                    if (conditions[j].value_integer != NULL) {
                        row_matched = false;
                    }
                }
                // Condition check for doubles
                if (conditions[j].value_double && records[i][j].doubleValue != conditions[j].value_double) {
                    if (conditions[j].value_double != NULL) {
                        row_matched = false;
                    }
                }

                // Condition check for string
                if (conditions[j].value_string && records[i][j].stringValue != conditions[j].value_string) {
                    if (conditions[j].value_string != std::nullopt) {
                        row_matched = false;
                    }
                }
                // If row is not matched in some column, we can skip it right away
                if (!row_matched) {
                    break;
                }
            }

            if (row_matched)  // If row is still matched after checking all conditions
            {
                for (int j = 0; j < cols; j++) {
                    // Updating record if needed
                    if (records[i][j].type == "integer" && updates[j].value_integer) {
                        records[i][j].intValue = updates[j].value_integer;
                    }
                    else if (records[i][j].type == "double" && updates[j].value_double) {
                        records[i][j].doubleValue = updates[j].value_double;
                    }
                    else if (records[i][j].type == "string" && updates[j].value_string) {
                        records[i][j].stringValue = updates[j].value_string;
                    }
                    select_records.push_back(records[i][j]);
                }
            }
        }

        return select_records;
    }

    void delete_data(const std::vector<Condition>& conditions) {
        std::vector<std::vector<Record>> new_records;

        // Iterate over records
        for (int i = 0; i < rows; i++) {
            bool row_matched = true; // Indicates whether the current row matches all conditions
            for (int j = 0; j < cols; j++) {
                // Condition check for integers
                if (conditions[j].value_integer && records[i][j].intValue != conditions[j].value_integer)
                    row_matched = false;

                // Condition check for doubles
                if (conditions[j].value_double && records[i][j].doubleValue != conditions[j].value_double)
                    row_matched = false;

                // Condition check for strings
                if (conditions[j].value_string && records[i][j].stringValue != conditions[j].value_string)
                    row_matched = false;

                // If row is not matched in some column, we can skip it right away
                if (!row_matched) {
                    new_records.push_back(records[i]);
                }
            }
            if (row_matched)  // If row is not matched after all conditions, it remains in new_records
                new_records.push_back(records[i]);
        }

        records = new_records;
        rows = records.size();
    }
    // Function to count all existing records
    int count_records() {
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (records[i][j].type != "") {  // Assuming type is not empty for a valid record
                    count++;
                }
            }
        }
        return count;
    }

};

int main()
{
    // Create a Table object with sample data
    Table table(4, 3);
    Record record = Record("integer", 1, 0, 1, std::nullopt, std::nullopt);
    Record record1 = Record("string", 1, 1, std::nullopt, std::nullopt, "Jhon");
    Record record2 = Record("string", 1, 2, std::nullopt, 24.3, std::nullopt);
    vector<Record> row;
    row.push_back(record);
    row.push_back(record1);
    row.push_back(record2);
    // Add sample data to the table
    table.insert_data(row);
    Record record3 = Record("integer", 2, 0, 2, std::nullopt, std::nullopt);
    Record record4 = Record("string", 2, 1, std::nullopt, std::nullopt, "Lisa");
    Record record5 = Record("string", 2, 2, std::nullopt, 24.3, std::nullopt);
    vector<Record> row1;
    row1.push_back(record3);
    row1.push_back(record4);
    row1.push_back(record5);
    table.insert_data(row1);
    // Define conditions for updating the record
    Condition idCondition;
    idCondition.value_double = NULL;
    idCondition.value_integer = NULL;
    idCondition.value_string = std::nullopt;
    Condition nameCondition;
    nameCondition.value_double = NULL;
    nameCondition.value_integer = NULL;
    nameCondition.value_string = std::nullopt;
    Condition scoreCondition;
    scoreCondition.value_double = 24.3;
    scoreCondition.value_integer = NULL;
    scoreCondition.value_string = std::nullopt;
    Condition idCondition1;
    idCondition1.value_double = NULL;
    idCondition1.value_integer = NULL;
    idCondition1.value_string = std::nullopt;
    Condition nameCondition1;
    nameCondition1.value_double = NULL;
    nameCondition1.value_integer = NULL;
    nameCondition1.value_string = std::nullopt;
    Condition scoreCondition1;
    scoreCondition1.value_double = 43.3;
    scoreCondition1.value_integer = NULL;
    scoreCondition1.value_string = std::nullopt;


    // Update the record using the conditions
    //table.update_data({ idCondition, nameCondition, scoreCondition }, { idCondition1, nameCondition1, scoreCondition1 });
   
    // Print the updated table
    std::vector<Record> selected_records  =  table.select_data({ idCondition, nameCondition, scoreCondition });
    cout << selected_records.size() << endl;
    
    // Print the selected records
  // Print the selected records
    for (const auto& row : selected_records) {
        if (row.intValue.has_value()) {
            std::cout << "Row: " << row.intValue.value()  << std::endl;
        }
        if (row.doubleValue.has_value()) {
            std::cout << "Row: " << row.doubleValue.value() << std::endl;
        }
        if (row.stringValue.has_value()) {
            std::cout << "Row: " << row.stringValue.value() << std::endl;
        }
       
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
