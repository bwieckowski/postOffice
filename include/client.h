//
// Created by Bartek on 12/12/2018.
//

#ifndef PROJEKT3_CLIENT_H
#define PROJEKT3_CLIENT_H

#include "iclient.h"
#include <vector>
#include "exceptions.h"

#define SAVEFILE "clients.csv"

class Client : public IClient
{

public:

    Client( const std::string&  = "" );

     std::string getIdNumber();
     std::string getFullName();
     int getPriority();

     void setFullName(const std::string& fullName);

     void updatePriority(int priority);

     const std::string& getBiometricData();
     void updateBiometricData(const std::string& biometricData) throw( IncorrectBiometricDataException );
     bool verifyBiometricData(const std::string& biometricData, double threshold) throw( IncorrectBiometricDataException );
     void newPackage(const std::string& packageId);
     std::vector<std::string> awaitingPackages();
     void packagesCollected();

    ~Client();

private:
    std::string idNumber;
    std::string fullName;
    int priority;
    std::vector<std::string> packages;
    std::string biometricData;

    bool isDNASequenceCorrect( std::string DNA );

};





#endif //PROJEKT3_CLIENT_H


