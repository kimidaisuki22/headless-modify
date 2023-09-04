#pragma once
#include <cstdint>
#include <iostream>
template<typename T,typename U>
void print_elem_array(T && array, U&& print_function,std::string hint={}){
      for (uint32_t i = 0; i < array.size(); i++) {
        std::cout << hint << (!hint.empty() ? ": " :"") << i << std::endl;
        print_function(array[i]);
 
        std::cout << "-----------------------------" << std::endl;
    }
}