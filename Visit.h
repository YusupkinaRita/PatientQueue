#pragma once
#include <iostream>
#include <vector>
#include <sstream>



class Visit{
private:
    std::string _anamnesis;
    std::vector<std::string> _health_script;
    std::vector<std::string> _drugs;

public:
    Visit(){
        _anamnesis="";
    }
    std::string ToString(){
        std::string res="";
        res+=_anamnesis+"|";
        for(size_t i=0;i<_health_script.size();i++){
            res+=_health_script[i];
            if(i!=_health_script.size()-1)
                res+=", ";
            
        }
        res+="|";
        for(size_t i=0;i<_drugs.size();i++){
            res+=_drugs[i];
            if(i!=_drugs.size()-1)
                res+=", ";
            
        }

        return res;

    }
    static Visit Deserialize(std::string str){
        Visit v;
        std::istringstream ss(str);
        std::string anamnesisPart, healthScriptPart, drugsPart;

        std::getline(ss, anamnesisPart, '|');
        std::getline(ss, healthScriptPart, '|');
        std::getline(ss, drugsPart);
        
        v._anamnesis=anamnesisPart;

        std::istringstream hsStream(healthScriptPart);
        std::string each_hs;
        while (std::getline(hsStream, each_hs, ',')) {
            if (!each_hs.empty() && each_hs[0] == ' ')
                each_hs.erase(0,1); 
            v._health_script.push_back(each_hs);
        }


        std::istringstream drugStream(drugsPart);
        std::string each_drug;
        while (std::getline(drugStream, each_drug, ',')) {
            if (!each_drug.empty() && each_drug[0] == ' ') 
                each_drug.erase(0, 1);
            v._drugs.push_back(each_drug);
        }

        return v;


    }
    


};