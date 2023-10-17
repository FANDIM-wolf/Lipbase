#include <vector>
#include <string>
#include <optional>
#include <float.h>
#include <limits.h>

class Record {
public:
    std::string type;
    int row;
    int col;
    std::optional<int> intValue;
    std::optional<double> doubleValue;
    Record(){}
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
        for (int i = 0; i < rows; i++) {
            bool flag = true;
            for (int j = 0; j < cols; j++) {
                // If condition exists and doesn't match the record, set flag to false and break
                if ((conditions[j].value_integer && records[i][j].intValue != conditions[j].value_integer.value())
                    || (conditions[j].value_double && records[i][j].doubleValue != conditions[j].value_double.value())) {
                    flag = false;
                    break;
                }
            }
            if (flag)  // If flag is still true after all conditions, push back all records in the row to select_records
                select_records.insert(select_records.end(), records[i].begin(), records[i].end());
        }
        return select_records;
    }
};
