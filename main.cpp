#include <iostream>
#include "file_operations.h"


int main(void){
    const std::string link = "employees_tracking.csv";
    const char separator = ';';
    add_data(link);
    get_data(link, separator);
    return 0;
}