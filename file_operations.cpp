#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <sstream> 
#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>
#include "file_operations.h"

namespace {
class date{
    public:
    int year, month, day;
    friend std::ostream& operator<< (std::ostream &out, const date &date);
    friend bool operator== (const date &date_1, const date &date_2);
};
std::ostream& operator<< (std::ostream &out, const date &date){
    const char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    out<<date.year<<" "<<months[date.month];
    return out;
}
bool operator== (const date &date_1, const date &date_2){
    return (date_1.year == date_2.year && date_1.month == date_2.month);
}

date convert_data(const std::string str){

    const char separator = '-';
    std::vector<std::string> outputArray;
    std::stringstream streamData(str);
    std::string val;
    while (std::getline(streamData, val, separator)) {
        outputArray.push_back(val);
    }
    date date_;
    date_.year = std::stoi(outputArray[0]);
    date_.month = std::stoi(outputArray[1]);
    date_.day = std::stoi(outputArray[2]);
    return date_;

}

class Employee: public date{
    public:
    std::string Name, email, department, position, project, task;
    date date;
    int hours;
};
}

void add_data(const std::string link){
    int temp_char;
    std::fstream file_var;
    file_var.open(link, std::ios::out | std::ios::app);
    std::cout<<"Enter data in line:"<<std::endl;
    while((temp_char = getchar()) != EOF){
        file_var<<(char)temp_char;
    }
    file_var.close();
}

void get_data(const std::string link, const char separator){
    auto start = std::chrono::steady_clock::now();
    std::vector<Employee> worker;
    std::fstream file_var;
    Employee emp;
    std::string var, var_data, space; 
    file_var.open(link, std::ios::in);
    std::cout<<"Info out:"<<std::endl;
    while (file_var.good())
    {    
        getline(file_var,emp.Name, separator);
        getline(file_var,emp.email, separator);
        getline(file_var,emp.department, separator);
        getline(file_var,emp.position, separator);
        getline(file_var,emp.project, separator);
        getline(file_var,emp.task, separator);
        getline(file_var,var_data, separator);
        getline(file_var,var, '\n');
        if(var == ""){
            break;
        }
        getline(file_var,space, ' ');
        if(space == " "){
            break;
        }
        emp.date = convert_data(var_data);
        emp.hours = std::stoi(var);    
        if(worker.empty()){
            worker.push_back(emp);
        }
        else{
            bool push_work = true;
            for(int i=0; i<worker.size(); i++){
                if(worker[i].date == emp.date && worker[i].position == emp.position && worker[i].email == emp.email){
                    worker[i].hours += emp.hours;
                    push_work = false;
                    break;
                }
            }
            if(push_work){
            worker.push_back(emp);
            }
        }
    }
    file_var.close();
    for(int i=0; i<worker.size(); i++){
        std::cout<<worker[i].Name<<" "<<worker[i].email<<"  "<< worker[i].date <<"  ";
        std::cout<<worker[i].hours<<std::endl;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
}
