#include <vector>
#include <string>
#include <optional>
#include <float.h>
#include <limits.h>
#include <iostream>
#include <iostream>
#include <sstream>
#include <cctype>

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
                    if (conditions[j].value_integer != std::nullopt) {
                        row_matched = false;
                    }
                }
                // Condition check for doubles
                if (conditions[j].value_double && records[i][j].doubleValue != conditions[j].value_double) {
                    if (conditions[j].value_double != std::nullopt) {
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

                    if (conditions[j].value_integer != std::nullopt) {
                        row_matched = false;
                    }
                }
                // Condition check for doubles
                if (conditions[j].value_double && records[i][j].doubleValue != conditions[j].value_double) {
                    if (conditions[j].value_double != std::nullopt) {
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

