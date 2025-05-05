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
    Patient(){
        _surname="";
        _name="";
        _patronymic="";
        _gender=Gender::Female;
    }
    Patient(std::string surname,std::string name, std::string patronymic, Gender gender,std::vector<Visit> history ){
        _surname=surname;
        _name=name;
        _patronymic=patronymic;
        _gender=gender;
        _history=history;
    }
    std::string ToString(){
        std::string res="";
        res+=_surname+"|";
        res+=_name+"|";
        res+=_patronymic+"|";
        if(_gender==Gender::Male)
            res+="Male|";
        if(_gender==Gender::Female)
            res+="Female|";
        
        for(size_t i=0;i<_history.size();i++){
            res+="{"+_history[i].ToString()+"}";
            if(i!=_history.size()-1)
                res+=", ";

        }

        return res;
        
    }

    static Patient Deserialize(std::string str){
        Patient p;
        std::istringstream ss(str);

        
        std::getline(ss, p._surname, '|');
        std::getline(ss, p._name, '|');
        std::getline(ss, p._patronymic, '|');

        std::string gender;
        std::getline(ss, gender, '|');
        if (gender == "Male")
            p._gender = Gender::Male;
        else if (gender == "Female")
            p._gender = Gender::Female;
        else
            throw "Invalid gender";

        std::string history_visit;
        while (std::getline(ss, history_visit, ',')){
            if(history_visit.back()=='}')
                history_visit.pop_back();
            if(history_visit.front()=='{')
                history_visit.erase(0,1);
            if(history_visit.front()==' ')
                history_visit.erase(0,2);

            p._history.push_back(Visit::Deserialize(history_visit));
        }
        return p;

    }


};