#pragma once
#include <iostream>
#include <fstream>
#include <string>

std::string read_file(std::string file_name){
    std::fstream file;
    file.open("../"+file_name, std::ios::in); 
    if(file.is_open()){
        std::string data, temp;
        while(getline(file, temp)){  
            data += temp;
        }
        file.close();
        return data;
   }
   throw std::invalid_argument("Error when trying to open file");
}