// LipSQL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <string>
#include <optional>
#include <iostream>

#include "Functions.h";


using namespace std;



int main() {
    // Example usage
       
    //Load_tables();
    // Save the tables to a file
    //saveTables(TABLES, "tables.dat");
    
    bool PROMOTION_TO_RUN_CODE = true;
    std::string command;
    while (PROMOTION_TO_RUN_CODE) {
        std::cout << "LipaQL>>";
        std::getline(std::cin, command);
        string query = command;
        string command_from_line, statement;
        string spaces;
        bool command_executed = false;
        int status_of_last_element, type_of_last_elment, result;


        for (int i = 0; i <= query.size(); i++) {



            if (int(query[i]) == 32) {
                spaces += query[i];
            }


            command_from_line += query[i];
            //define_accurate_name_of_command(command_from_line);
            //cout << command_from_line << endl;

            //cout<<"test2"<<query[i]<<i<<endl;
            if (command_from_line == spaces + "CREATE" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {

                create_table(query);
                command_from_line = "";

            }
            if (command_from_line == spaces + "SHOW" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {

                //Show_tables();
                cout << "sHOW" << endl;
                command_from_line = "";


            }
            if (command_from_line == spaces + "INSERT" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {

                insert_in_table(query);
                
                command_from_line = "";


            }
            if (command_from_line == spaces + "SELECT_FROM" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {

                //Select_table(query);
                //select_data_from_table(command_from_line);
                process_query(query);
                command_from_line = "";

            }
            if (command_from_line == spaces + "LOAD_TABLES" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {

                // Load the tables from the file
                
                //Load_tables();
                command_from_line = "";

            }
            if (command_from_line == spaces + "exit" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {

                
                command_from_line = "";
                PROMOTION_TO_RUN_CODE = false;

            }



        }
    }
    

    return 0;
   
    
  
   
}





