// LipSQL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>



class Record {
public:
    std::string type;
    int id;  // Identifier for the Record
    bool isIdRecord;  // Flag to determine if Record is an ID Record or not
    int row;
    int column;
    int intValue;
    double doubleValue;

    Record(std::string t, int r, int c, int iVal = 0, double dVal = 0.0, bool idRec = false)
        : type(t), row(r), column(c), intValue(iVal), doubleValue(dVal), isIdRecord(idRec) {}
};

class Table {
public:
    std::vector<Record> records;

    std::vector<std::string> names;
    std::vector<std::string> data;
    int rows;
    int columns;
    int lastId;  // Last assigned ID

    Table(int r, int c) : rows(r), columns(c), lastId(0) {}
    int getLastId()  {
        return this->lastId;
    }
    void create_table(int nrows, int ncols, const std::vector<std::string>& names_of_columns, const std::vector<std::string>& types_of_columns) {
        rows = nrows;
        columns = ncols;
        names = names_of_columns;
        data = types_of_columns;
        // Note: You may want to initialize `records`, `records_int`, and `records_double` as well, based on the input values
    }

    void insert_data(std::vector<Record> row) {
        if (row.size() > columns) {
            throw std::logic_error("Number of records in the row does not match table's columns");
        }
        //std::cout << row.size() << std::endl;
        

         for (int i = 0; i < row.size(); ++i) {
             auto& record = row[i];

             if (record.column == 1) {  // First column is always "id"
                 record.isIdRecord = true;
                 record.id = this->lastId++;
                 
                 records.push_back(record);
             }
             else if (record.type == "int") {
                 record.id = NULL;
                 records.push_back(record);
             }
             else if (record.type == "double") {
                 record.id = NULL;
                 records.push_back(record);
             }
             else {
                 throw std::logic_error("Unsupported record type");
             }

         }

         
    }
    void getAllData() {
        for (const auto& record : records) {
            std::cout << "Type: " << record.type
                << ", ID: " << record.id
                << ", Row: " << record.row
                << ", Column: " << record.column
                << ", Int Value: " << record.intValue
                << ", Double Value: " << record.doubleValue
                << ", Is ID Record: " << (record.isIdRecord ? "true" : "false")
                << std::endl;

        }
    }


};

int main() {
    
    Table table(5, 5); // Create a table with 5 rows and 5 columns

    Record record("int", 1, 1, 1, 0, false);
    Record record1("double", 2, 1, 0, 2.2, false);
    Record record2("double", 3, 1, 0, 2.2, false);
    Record record3("double", 4, 1, 0, 2.2, false);
    std::vector<Record> records;
    std::vector<Record> records1;
    records.push_back(record);
    records1.push_back(record1);
    records1.push_back(record2);
    records1.push_back(record3);
    table.create_table(5, 5, { "id" , "c1" , "c2" , "c3" , "c4" }, { "int" , "double" ,"double ",  "double" ,"double " });
    // Use the getter function to retrieve the lastId
    
    // Assume that `records` is an already constructed vector of Records
    table.insert_data(records);
    table.insert_data(records1);
    table.getAllData();
    // Use the getter function to retrieve the lastId
    //int lastId = table.getLastId();
    //std::cout << "The last used ID is: " << lastId << std::endl;
    int exit;
    std::cin >>exit ;
    return 0;
}





