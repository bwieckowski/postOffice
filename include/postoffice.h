//
// Created by Bartek on 12/12/2018.
//

#ifndef PROJEKT3_POSTOFFICE_H
#define PROJEKT3_POSTOFFICE_H

#include "ipostoffice.h"
#include "client.h"
#include "queue"
#include "../include/exceptions.h"
#include <map>
using namespace std;

struct compareClientPriority{

    bool operator ()(   Client &cl1,   Client &cl2 )
    {
         return cl1.getPriority() < cl2.getPriority();
    }
};


class PostOffice : public IPostOffice
{
    public:
        PostOffice( unsigned );

        std::shared_ptr<IClient> getClient(const std::string& identificationNumber);

        void enqueueClient(const std::shared_ptr<IClient>& client);

        std::vector<std::string> getStatus();
        void gateReady(unsigned gateIndex) throw( IncorrectGateException );
        void collectPackages(unsigned gateIndex) throw( IncorrectGateException );

    private:
         bool validGate(  unsigned );
         unsigned gateCount;
         std::vector< std::shared_ptr<Client> > clients;
         std::map< int, Client > expectedClientsInGates;
         std::priority_queue<Client, vector<Client>, compareClientPriority> clientsQueue;
};


#endif //PROJEKT3_POSTOFFICE_H
