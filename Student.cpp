#include <iostream>
#include "Student.h"

using namespace std;

// TODO: Task 1.1
Student::Student(int sid,
                 const string& name,
                 const string& major,
                 bool isLocal,
                 int ECANum,
                 int travelFastest,
                 int travelCheapest,
                 bool isFirstApplication): sid(sid), 
                                        name(name), 
                                        major(major),
                                        isLocal(isLocal),
                                        ECANum(ECANum),
                                        travelFastest(travelFastest),
                                        travelCheapest(travelCheapest),
                                        isFirstApplication(isFirstApplication),
                                        status(QUEUEING)
                                        {
                                            if(isLocal){
                                                totalHallPoints = (travelFastest + travelCheapest)/4 + ECANum*5 + (isFirstApplication? 5 : 0);
                                            }
                                            else{
                                                totalHallPoints = 15 + (isFirstApplication? 20 : 0) + ECANum*5;
                                            }
                                        }

// TODO: Task 1.2
bool Student::operator==(int sid) const {
    if(this->getSid() == sid){
        return true;
    }
    return false;
}
