#include <vector>
#include <string>
#include <optional>
#include <float.h>
#include <limits.h>
#include <iostream>
#include "Implementation.cpp";
#include <regex>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <cctype> // for std::isspace

using namespace std;



// Create some example tables
std::vector<Table> TABLES;





void printAllRecords(const Table& table) {
    std::cout << "All Records in the Table:\n";

    for (int i = 0; i < table.rows; ++i) {
        for (int j = 0; j < table.cols; ++j) {
            std::cout << "Type: " << table.records[i][j].type << " ";
            std::cout << "Row: " << table.records[i][j].row << " ";
            std::cout << "Col: " << table.records[i][j].col << " ";
            std::cout << "Value: ";

            if (table.records[i][j].type == "integer") {
                std::cout << table.records[i][j].intValue.value_or(0);
            }
            else if (table.records[i][j].type == "double") {
                std::cout << table.records[i][j].doubleValue.value_or(0.0);
            }
            else if (table.records[i][j].type == "string") {
                std::cout << table.records[i][j].stringValue.value_or("");
            }

            std::cout << "\t";
        }
        std::cout << "\n";
    }
}

int find_table(const std::string& tableName) {
    for (int i = 0; i < TABLES.size(); i++) {
        if (TABLES[i].table_name == tableName) {
            return i;
        }
    }
    return -1;
}

std::string define_accurate_name(const std::string& var) {
    std::string accurate_name;

    for (char c : var) {
        if (c != ' ' && c != ')' && c != '(' && c != '"') {
            accurate_name += c;
        }
    }

    return accurate_name;
}

// Helper function to trim leading and trailing whitespaces from a string
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    if (start != std::string::npos && end != std::string::npos) {
        return str.substr(start, end - start + 1);
    }

    return "";
}

// Helper function to split a string into a vector of substrings based on a delimiter
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

// Helper function to extract table name from a query
std::string extract_table_name(const std::string& query) {
    size_t start_pos = query.find("FROM ") + strlen("FROM ");
    size_t end_pos = query.find("(");

    return trim(query.substr(start_pos, end_pos - start_pos));
}

// Helper function to extract conditions from a SELECT_FROM query
std::vector<std::string> extract_conditions(const std::string& query) {
    size_t start_pos = query.find("(") + 1;
    size_t end_pos = query.find(")");

    std::string conditions_part = query.substr(start_pos, end_pos - start_pos);
    return split(conditions_part, ',');
}

// Helper function to extract selected columns from a SELECT_FROM query
std::vector<std::string> extract_selected_columns(const std::string& query) {
    size_t start_pos = query.find("SELECT_FROM ") + strlen("SELECT_FROM ");
    size_t end_pos = query.find("(");

    std::string selected_columns_part = query.substr(start_pos, end_pos - start_pos);
    return split(selected_columns_part, ',');
}

bool is_number(const std::string& str) {
    std::istringstream ss(str);
    double number;
    ss >> std::noskipws >> number;  // Try to read the string as a number

    // Check if the entire string was consumed and the conversion was successful
    return ss.eof() && !ss.fail();
}

// Create a new table and add it to the global vector
void create_table(const std::string& query) {
    // Sample query: "CREATE TABLE Customers (CustomerID int, score double);"

    // Extract table name, column names, and column types from the query
    size_t start_pos = query.find("CREATE TABLE ") + strlen("CREATE TABLE ");
    size_t end_pos = query.find("(");

    std::string table_name = query.substr(start_pos, end_pos - start_pos);
    table_name = define_accurate_name(table_name);

    // Extract column names and types
    start_pos = end_pos + 1;
    end_pos = query.find(");");

    std::string columns_part = query.substr(start_pos, end_pos - start_pos);
    std::vector<std::string> columns = split(columns_part, ',');

    std::vector<std::string> names_of_columns;
    std::vector<std::string> types_of_columns;

    for (const auto& column : columns) {
        std::vector<std::string> parts = split(column, ' ');
        names_of_columns.push_back(parts[0]);
        types_of_columns.push_back(parts[1]);
    }

    // Create a new table
    Table new_table(0, names_of_columns.size());
    new_table.table_name = table_name;
    new_table.create_table(new_table.rows, new_table.cols, names_of_columns, types_of_columns);

    // Add the new table to the global vector
    TABLES.push_back(new_table);

    std::cout << "Table '" << table_name << "' created successfully." << std::endl;
}

// Insert data into a specific table
void insert_in_table(const std::string& query) {
    // Sample query: "INSERT INTO Customers (CustomerID, score) VALUES (0, 2.4);"

    // Extract table name, column names, and values from the query
    size_t start_pos = query.find("INSERT INTO ") + strlen("INSERT INTO ");
    size_t end_pos = query.find("(");

    std::string table_name = query.substr(start_pos, end_pos - start_pos);
    table_name = define_accurate_name(table_name);

    // Find the table by name
    int index_of_table = find_table(table_name);
    cout << index_of_table << endl;
    if (index_of_table != -1) {
        // Extract column names
        start_pos = end_pos + 1;
        end_pos = query.find(")");

        std::string columns_part = query.substr(start_pos, end_pos - start_pos);
        std::vector<std::string> columns = split(columns_part, ',');

        // Extract values
        start_pos = query.find("VALUES (") + strlen("VALUES (");
        end_pos = query.find(");");

        std::string values_part = query.substr(start_pos, end_pos - start_pos);
        std::vector<std::string> values = split(values_part, ',');

        // Create a Record with extracted values
        std::vector<Record> new_row;

        for (size_t i = 0; i < values.size(); i++) {
            trim(values[i]);
            if (values[i] == "NULL") {
                new_row.emplace_back("", 0, 0, std::nullopt, std::nullopt, std::nullopt);
            }
            else if (is_number(values[i])) {
                if (values[i].find('.') != std::string::npos) {
                    new_row.emplace_back("double", 0, i, std::nullopt, std::stod(values[i]), std::nullopt);
                }
                else {
                    new_row.emplace_back("integer", 0, i, std::stoi(values[i]), std::nullopt, std::nullopt);
                }
            }
            else {
                new_row.emplace_back("string", 0, i, std::nullopt, std::nullopt, values[i]);
            }
        }


        // Call the insert_data method with the new row for the specific table
        TABLES[index_of_table].insert_data(new_row);

        std::cout << "Data inserted into table '" << table_name << "' successfully." << std::endl;

        // Print all records in the updated table
        printAllRecords(TABLES[index_of_table]);
    }
    else {
        std::cerr << "Error: Table not found." << std::endl;
    }
}

// Helper function to print a row
void printRow(const std::vector<Record>& row) {
    for (const auto& record : row) {
        std::cout << "Type: " << record.type << ", Row: " << record.row
            << ", Col: " << record.col << ", Value: ";

        if (record.intValue) {
            std::cout << *record.intValue;
        }
        else if (record.doubleValue) {
            std::cout << *record.doubleValue;
        }
        else if (record.stringValue) {
            std::cout << *record.stringValue;
        }

        std::cout << "\t";
    }
    std::cout << std::endl;
}

void process_query(string query) {
    // Extract table name, conditions, and selected columns from the query
    std::string table_name = extract_table_name(query);
    std::vector<std::string> conditions_str = extract_conditions(query);
    std::vector<std::string> selected_columns_str = extract_selected_columns(query);

    // Find the table by name
    int index_of_table = find_table(table_name);

    if (index_of_table != -1) {
        // Convert conditions from strings to Condition objects
        std::vector<Condition> conditions;
        for (const auto& condition_str : conditions_str) {
            Condition condition;
            trim(condition_str);
            if (condition_str == "*") {
                condition.value_double = std::nullopt;
                condition.value_integer = std::nullopt;
                condition.value_string = std::nullopt;
                conditions.push_back(condition);
            }
            else {
                size_t equals_pos = condition_str.find('=');
                std::string column_name = condition_str.substr(0, equals_pos);
                std::string value_str = condition_str.substr(equals_pos + 1);

                trim(column_name);
                trim(value_str);

                if (is_number(value_str)) {
                    cout << "Number!" << endl;
                    if (value_str.find('.') != std::string::npos) {

                        condition.value_double = std::stod(value_str);
                        condition.value_string = std::nullopt;
                        condition.value_integer = std::nullopt;
                    }
                    else {
                        condition.value_integer = std::stoi(value_str);
                        condition.value_double = std::nullopt;
                        condition.value_string = std::nullopt;
                    }
                }
                else {
                    condition.value_double = std::nullopt;
                    condition.value_integer = std::nullopt;
                    condition.value_string = value_str;
                }

                conditions.push_back(condition);
            }
        }
        // Print all conditions
        std::cout << "Conditions: ";
        std::cout << conditions.size() << endl;
        for (const auto& condition : conditions) {
            if (condition.value_integer) {
                std::cout << "Int: " << *condition.value_integer << " ";
            }
            if (condition.value_double) {
                std::cout << "Double: " << *condition.value_double << " ";
            }
            if (condition.value_string) {
                std::cout << "String: " << *condition.value_string << " ";
            }
        }
        std::cout << std::endl;

        // Update the record using the conditions
        std::vector<Record> selected_records = TABLES[index_of_table].select_data(conditions);
        cout << "Selected :" << selected_records.size() << endl;
    }
    else {
        std::cerr << "Error: Table not found." << std::endl;
    }
}
