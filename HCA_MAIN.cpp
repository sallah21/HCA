
#include <iostream>
#include "Cluster.h"
#include <string>
#include <vector>
#include "Entity.h"
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <algorithm>
int main(int argc, char* argv[])
{
    std::string  file_name;
    std::ifstream read_file;
    std::ofstream save_file;
    std::vector<double> start_data;
    std::vector<Cluster> data;

    char sep;
    int  group_number;
    std::string line = "";

    if (argc == 0) {
        std::cout << "ALGORYTM HCA \n -f nazwapliku -k ilosc grup -s separator danych w pliku ";
    }
    for (int i = 0; i < argc; i++) { // Sprawdzanie parametrow wejsciowych
        
        if (!strcmp(argv[i], "-k")) {
            try {
                group_number = std::stoi(argv[i + 1]);
            }
            catch(const std::invalid_argument e){
                std::cout << "Group number error \n";
                return 0;
            }
            if (group_number <= 0) {
                std::cout << "Group number below 0\n";
                return 0;
            }
            std::cout << "Number of groups: " << argv[i + 1] << std::endl;
        }
        if (!strcmp(argv[i], "-f")) {
            file_name = argv[i + 1];
            std::cout<<"Filename: " << argv[i + 1] << std::endl;
        }
        if (!strcmp(argv[i], "-s")) {
            sep = *argv[i + 1];
            if (std::isblank(sep)) {
                std::cout << "Speparator error\n";
            }
            std::cout << "Separator: " << argv[i + 1] << std::endl;
        }
    }
    
  
    read_file.open(file_name); 
    if (read_file) {
        std::cout << "file was readen correctly\n";
   }
    else {
        std::cout << "file error \n";
        return 0;
    }

    int numbers_of_values = 0;
    while (std::getline(read_file, line,'\n')) { // Zczytywanie danych do pliku zgodnie z podanym w parametrach separatorem oraz zapisywanie do pliku
        std::stringstream ss(line);
        try {
            
            while (std::getline(ss, line,sep )) { 

                double value = std::stod(line);
               
                start_data.push_back(value);
            }
        
            Cluster d(start_data);
            data.push_back(d);
            start_data.clear();
        }
        catch (...) {
            std::cout << "Reading error. Check separator\n";
            return 0;
        }
    }

    read_file.close();
    std::cout <<"data size :" << data.size() << std::endl;

    if (group_number > data.size()) {
        std::cout << "Group number is bigger than data size" << std::endl;
        return 0;
    }
    data = UPGMA(group_number, data);
    // zapisywanie wynikow do pliku txt
    save_file.open("results.txt");
    int cd = 1;
    for (auto const& i : data) {
        save_file << "GROUP " << cd <<  std::endl;
        save_file << SerializeCluster(i) << std::endl; // serializacja zawarosci klastra 
        cd++;
    }
  save_file.close();
 }
