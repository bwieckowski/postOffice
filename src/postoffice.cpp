//
// Created by Bartek on 12/12/2018.
//
//#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iostream>
#include "../include/postoffice.h"

using namespace std;
PostOffice::PostOffice( unsigned gate_count )
{
    this->gateCount = gate_count;
    fillClients();
}

void PostOffice::fillClients()
{

    string linia;
    ifstream data(SAVEFILE);

    if( data.fail() )
        return;

        while (!data.eof()) {
            getline(data, linia, ',');
            if( !linia.empty()) {
                Client p(linia);
         //       cout << "ID: " << linia << endl;

                getline(data, linia, ',');
                p.setFullName(linia.c_str());
        //        cout << "IMIE: " << linia << endl;


                getline(data, linia, ',');
                p.updatePriority(atoi(linia.c_str()));
        //        std::cout << "PIORYTET: " << linia << endl;

                getline(data, linia, ',');
                if( !linia.empty())
                    p.updateBiometricData(linia);
        //        cout << "DNA: " << linia << endl;

                getline(data, linia, ',');
                int packagesAmount = atoi(linia.c_str());


                if (packagesAmount > 0)
                    for (int i = 0; i < packagesAmount; ++i) {
                        getline(data, linia, ',');
                        p.newPackage(linia.c_str());
                    }

                clients.push_back(std::make_shared<Client>(p));
            }
        }

        data.close();


}


std::shared_ptr<IClient> PostOffice::getClient(const std::string & identificationNumber){


    for (auto client : clients) {
        if (client->getIdNumber() == identificationNumber)
        {
            return client;
        }

    }


    auto ptr = make_shared<Client>( Client( identificationNumber ) );
    clients.push_back( ptr );
    return ptr;

}

void PostOffice::enqueueClient(const std::shared_ptr<IClient> &client) {

    if( client == nullptr)
        return;

    shared_ptr<Client> clientPtr2 = dynamic_pointer_cast<Client>(client);
    clientsQueue.push( clientPtr2 );

}


void PostOffice::gateReady(unsigned gateIndex) throw( IncorrectGateException )  {

    if( gateIndex > this->gateCount )
        throw IncorrectGateException("Inccorect gate Number to Large or to Small \n");

   if( clientsQueue.size() < 1 )
       return;

       auto client = clientsQueue.top();
       expectedClientsInGates[ gateIndex ] = client;
       clientsQueue.pop();


}

std::vector<std::string> PostOffice::getStatus() {

    std::vector<std::string> statusVector;

    for (int i = 0; i < gateCount; ++i) {

        auto it = expectedClientsInGates.find(i);
        if( it != expectedClientsInGates.end() )
            statusVector.push_back( expectedClientsInGates[i]->getFullName() );
        else
            statusVector.push_back( std::string() );
    }

    return statusVector;
}


 void PostOffice::collectPackages(unsigned gateIndex) throw( IncorrectGateException )
{

    auto gate = expectedClientsInGates.find( gateIndex );

    if( gateIndex > this->gateCount)
        throw IncorrectGateException( "There is no gate with this ID" );

    if( gate == expectedClientsInGates.end()  )
        throw IncorrectGateException( "There is nobody in the gate" );

    ( *gate ).second->packagesCollected();


 }

void PostOffice::saveClientsToFile()
{
    std::ofstream myfile;
    myfile.open(SAVEFILE);

    int sizeClients = clients.size();
    for (auto clientIter :  clients) {
        auto client = (*clientIter);

        string bioData = client.getBiometricData();

        myfile<<client.getIdNumber()<<","<<client.getFullName()<<","<<client.getPriority()<<","<<bioData<<","<<client.awaitingPackages().size()<<",";

        if( client.awaitingPackages().size() > 0)
            for (auto package : client.awaitingPackages() )
                myfile<<package<<",";

    }
    myfile.close();
}



 PostOffice::~PostOffice() {
         saveClientsToFile();

 }

