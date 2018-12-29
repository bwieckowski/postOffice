//
// Created by Bartek on 12/12/2018.
//

#include <iostream>
#include "../include/postoffice.h"


PostOffice::PostOffice( unsigned gate_count )
{
    this->gateCount = gate_count;
}

std::shared_ptr<IClient> PostOffice::getClient(const std::string & identificationNumber){


    for (auto client : clients)
    {
        cout<<"finding: "<< client.getIdNumber()<<" "<<client.getFullName()<<endl;
        if(client.getIdNumber() == identificationNumber) //find the correct pointer to image in the vector
            return make_shared<Client>( client ); //return the Image
    }

    auto newClient = Client( identificationNumber );
    clients.push_back( newClient );
    auto ptr = make_shared<Client>( clients.back() );
    cout<<" client created "<<ptr->getIdNumber()<<endl;
        ptr->setFullName("Jan Kowalski");
    return ptr;

}

void PostOffice::enqueueClient(const std::shared_ptr<IClient> &client) {

    shared_ptr<Client> clientPtr2 = dynamic_pointer_cast<Client>(client);
    clientsQueue.push( *clientPtr2 );

}

bool PostOffice::validGate( unsigned gateIndex )
{
    return  !(( -1 < gateIndex) && ( gateIndex > this->gateCount ));
}


void PostOffice::gateReady(unsigned gateIndex) throw( IncorrectGateException )  {

    if( !validGate( gateIndex ) )
        throw IncorrectGateException(" Inccorect gate Number to Large or to Small \n");

   auto clients = clientsQueue.top();

    expectedClientsInGates[ gateIndex ] = clients;
    clientsQueue.pop();

}

std::vector<std::string> PostOffice::getStatus() {

    std::vector<std::string> statusVector;

    for (int i = 0; i < gateCount; ++i) {

        auto it = expectedClientsInGates.find(i);
        if( it != expectedClientsInGates.end() )
            statusVector.push_back( expectedClientsInGates[i].getFullName() );
        else
            statusVector.push_back( std::string() );
    }

    return statusVector;
}


 void PostOffice::collectPackages(unsigned gateIndex) throw( IncorrectGateException )
{

    auto gate = expectedClientsInGates.find( gateIndex );

    if( gate == expectedClientsInGates.end()  )
        throw IncorrectGateException( " there is nobody in the gate" );

   auto it =  ( *gate ).second.awaitingPackages().begin();
   for( ; it != ( *gate ).second.awaitingPackages().end(); it++ )
       cout<<(*it)<<endl;

    ( *gate ).second.packagesCollected();
    
}