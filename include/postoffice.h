//
// Created by Bartek on 12/12/2018.
//

#ifndef PROJEKT3_POSTOFFICE_H
#define PROJEKT3_POSTOFFICE_H

#define SAVEFILE "clients.csv"

#include "ipostoffice.h"
#include "client.h"
#include "queue"
#include "../include/exceptions.h"
#include <map>


using namespace std;

struct compareClientPriority{

    bool operator ()(  Client cl1, Client cl2 )
    {
        return cl1.getPriority() < cl2.getPriority();
    }

    bool operator ()(   std::shared_ptr<Client> cl1, std::shared_ptr<Client> cl2 )
    {
         return cl1->getPriority() < cl2->getPriority();
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
        ~PostOffice();

    private:
         bool validGate(  unsigned );
         unsigned gateCount;
         void fillClients();
         std::vector< std::shared_ptr<Client> > clients;
         std::map< int, std::shared_ptr<Client> > expectedClientsInGates;
         void saveClientsToFile();
         std::priority_queue< std::shared_ptr<Client>, std::vector<std::shared_ptr<Client>>, compareClientPriority> clientsQueue;
};


#endif //PROJEKT3_POSTOFFICE_H
