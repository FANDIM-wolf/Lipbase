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
    Record() { intValue = NULL; doubleValue = NULL; }
    Record(std::string type, int row, int col, std::optional<int> intValue, std::optional<double> doubleValue)
        : type(type), row(row), col(col), intValue(intValue), doubleValue(doubleValue) {}
};

class Conditon {
public:
    std::optional<int> value_integer;
    std::optional<double> value_double;
    
    

    
    
};

class Table {
    int rows;
    int cols;
    
public:
    std::vector<std::vector<Record>> records;

    Table(int rows, int cols) : rows(rows), cols(cols) {
        records.resize(rows, std::vector<Record>(cols, Record("", 0, 0, std::nullopt, std::nullopt)));
    }


    void create_table(int rows, int cols,
        const std::vector<std::string>& names_of_columns,
        const std::vector<std::string>& types_of_columns) {
        // Implementation depends on your specific requirements
    }

    void insert_data(Record record) {
        // Check if the specified row and column are within bounds
        if (record.row >= 0 && record.row < rows && record.col >= 0 && record.col < cols) {
            // If yes, insert data
            records[record.row][record.col] = record;
        }
        else {
            // If no, resize the table and then insert data
            // Note: This will only extend the table for new cols/rows. It won't shrink the table if row or col is less than current rows or cols.
            rows = std::max(rows, record.row + 1);
            cols = std::max(cols, record.col + 1);
            records.resize(rows);
            for (auto& r : records) {
                r.resize(cols);
            }
            records[record.row][record.col] = record;
        }
    }


    std::vector<Record> select_data(const std::vector<Conditon>& conditions) {
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

    std::vector<Record> update_data(const std::vector<Conditon>& conditions, const std::vector<Conditon>& updates) {
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

                    select_records.push_back(records[i][j]);
                }
            }
        }

        return select_records;
    }

    void delete_data(const std::vector<Conditon>& conditions) {
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

                // If row is not matched in some column, we can skip it right away
                if (!row_matched)
                    break;
            }
            if (!row_matched)  // If row is not matched after all conditions, it remains in new_records
                new_records.push_back(records[i]);
        }

        records = new_records;
        rows = records.size();
    }

};
