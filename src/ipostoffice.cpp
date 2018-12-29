//
// Created by Bartek on 12/12/2018.
//

#include "../include/ipostoffice.h"
#include "../include/postoffice.h"


std::shared_ptr<IPostOffice> IPostOffice::create(unsigned gate_count) {

    std::shared_ptr<IPostOffice> myOffice( new PostOffice(gate_count) );
    return myOffice;

}