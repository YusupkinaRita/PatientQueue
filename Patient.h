#include <iostream>
#include "Visit.h"
#include <vector>

#pragma once

enum Gender{Male, Female};

class Patient{
private:
    std::string _surname;
    std::string _name;
    std::string _patronymic;
    Gender _gender;
    std::vector<Visit> _history;


public:
    Patient(std::string surname,std::string name, std::string patronymic, Gender gender,std::vector<Visit> history ){
        _surname=surname;
        _name=name;
        _patronymic=patronymic;
        _gender=gender;
        _history=history;
    }
    std::string ToString(){
        
    }


};