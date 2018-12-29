//
// Created by Bartek on 12/12/2018.
//
//#include <iostream>
#include "../include/postoffice.h"


PostOffice::PostOffice( unsigned gate_count )
{
    this->gateCount = gate_count;
}

std::shared_ptr<IClient> PostOffice::getClient(const std::string & identificationNumber){


    for (auto client : clients)
        if(client->getIdNumber() == identificationNumber)
            return  client;

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


//   auto awaitingPackages = ( *gate ).second->awaitingPackages();
//   for( auto package : awaitingPackages )
//       cout<< package <<endl;


 }