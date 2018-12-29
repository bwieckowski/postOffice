//
// Created by Bartek on 13/12/2018.
//

#ifndef PROJEKT3_TESTS_H
#define PROJEKT3_TESTS_H

#include "client.h"
#include "postoffice.h"
#include "exceptions.h"


class Test
{
public:
    void doTests();
    static void clientIntrodue();
    void clientEnqueueStructur();
    void uniqueClientTest();

    void defaultTest();
};


#endif //PROJEKT3_TESTS_H
