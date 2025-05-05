#pragma once
#include "Patient.h"
#include <iostream>
#include "QueueList.h"
#include "DataBaseWorker.h"



class PatientController{
private:
    QueueList<Patient> _patients;
    DataBaseWorker _dbController;




public:
    PatientController(){}
    Patient Next(){
        Patient tmp=_patients.Front();
        _patients.Pop();
        return tmp;
    }

    void UpdatePatient(Patient& pat){
        _patients.Push(pat);

    }


};