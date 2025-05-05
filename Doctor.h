#pragma once
#include <iostream>
#include "Patient.h"



class Doctor{
private:
    Patient _patient;
public:
    Doctor(){
        _patient=Patient();
    }
    void SetPatient(Patient& pat){
        _patient=pat;
    }
    Patient GetPatient(){
        return _patient;
    }
    void AppendHealthScript(std::string h_s){

    }
    void AppendDrugs(std::string drugs){
        
    }
    void AppendAnamnesis(std::string anam){
        
    }

    void UpdatePatient(){


    }
};