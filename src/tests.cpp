//
// Created by Bartek on 13/12/2018.
//

#include <iostream>
#include "../include/tests.h"

using namespace std;

void testSign()
{
    cout<<"[TEST] ";
}




void Test::doTests() {
    clientIntrodue();
    clientEnqueueStructur();

}


void Test::biologyIdentyficationTest()
{
    auto post_office = IPostOffice::create(3);
    auto client0 = post_office->getClient("96052791812");
    client0->setFullName("Jan Kowalski");
    client0->updatePriority(10);
    cout<< client0->getFullName()<<endl;

    auto client1 = post_office->getClient("69100839677");
    client1->setFullName("Adam Nowak");
    client1->updatePriority(1);
    cout<< client1->getFullName()<<endl;

}



void displayArray( std::vector<string> array, int lenght1)
{
    int j = 0;
    for (auto i = array.begin(); i !=array.end(); ++i,j++) {
           cout<<j<<". "<<(*i)<<endl;
        }
        std::cout<<std::endl;
}

void Test::uniqueClientTest()
{
    auto post_office = IPostOffice::create(3);

    auto client0 = post_office->getClient("96052791812");
    client0->setFullName("Jan Kowalski");
    client0->updatePriority(10);
    cout<< client0->getFullName()<<endl;

    auto client1 = post_office->getClient("69100839677");
    client1->setFullName("Adam Nowak");
    client1->updatePriority(1);
    cout<< client1->getFullName()<<endl;

    auto clientTmp = post_office->getClient("69100839677");

    cout<< clientTmp->getFullName()<<endl;
}

void Test::gateTest()
{
    auto post_office = IPostOffice::create(5);

    auto client0 = post_office->getClient("96052791812");
    client0->setFullName("Jan Kowalski");

  //  post_office->enqueueClient(client0);

    try {
        post_office->gateReady(3);
    } catch( IncorrectGateException  &gateExct)
    {
        cout<<gateExct.what();
    }



}


void Test::defaultTest()
{
    auto post_office = IPostOffice::create(5);

    auto client0 = post_office->getClient("96052791812");
    client0->setFullName("Jan Kowalski");
    auto client1 = post_office->getClient("69100839677");
    client1->setFullName("Adam Nowak");
    client1->updatePriority(1);

    post_office->enqueueClient(client0);
    post_office->enqueueClient(client1);

    post_office->gateReady(3);
    auto status = post_office->getStatus();
    assert(status[3] == "Adam Nowak");

    post_office->gateReady(3);
    status = post_office->getStatus();
    assert(status[3] == "Jan Kowalski");
}

void Test::clientIntrodue() {

    testSign();
    auto post_office = IPostOffice::create(5);

    auto client0 = post_office->getClient("96052791812");
    client0->setFullName("Jan Kowalski");

    try {
        client0->newPackage("00x29301asdhasd");
        client0->newPackage("21312312");
        client0->newPackage("21312312");
    } catch ( PackageExistsException &excption )
    {
        cout<<"Exception: "<<endl;
        cout<<excption.what();

    }

    cout<<"Waiting packages:"<<endl;
    for( auto package : client0->awaitingPackages())
        cout<<package<<endl;

    post_office->gateReady(2);
    post_office->enqueueClient( client0 );

    try{
        post_office->gateReady(6);
    }catch( IncorrectGateException &gateException)
    {
        cout<<gateException.what();
        post_office->gateReady(1);
    }



    cout<<"Waiting Clients:"<<endl;
    for( auto client : post_office->getStatus())
        cout<<client<<endl;


    try {
        post_office->collectPackages(7);
    }catch( IncorrectGateException &ext)
    {
        cout<<ext.what()<<endl;
    }


    try {
        post_office->collectPackages(4);
    }catch( IncorrectGateException &ext)
    {
        cout<<ext.what()<<endl;
    }


    try {
        cout<<"packages out"<<endl;
        post_office->collectPackages(1);
    }catch( IncorrectGateException &ext)
    {
        cout<<ext.what()<<endl;
    }





}

void Test::clientEnqueueStructur()
{
    priority_queue<Client, vector<Client>, compareClientPriority> clientsQueue;


    auto clientPtr = make_shared<Client>( Client( "837129831" ) );

    shared_ptr<IClient> iclientPtr = clientPtr;
    shared_ptr<Client> clientPtr2 = dynamic_pointer_cast<Client>(iclientPtr);

    clientsQueue.push( *clientPtr2 );

    shared_ptr<Client> clinet = make_shared<Client>(clientsQueue.top());
    cout<< clinet->getPriority()<<endl;
    clientsQueue.pop();
}