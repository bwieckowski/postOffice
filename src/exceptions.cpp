//
// Created by Bartek on 12/12/2018.
//

#include <string>
#include "../include/exceptions.h"

PackageExistsException::PackageExistsException(const std::string &msg) : message(msg)
{
}

const char *PackageExistsException::what() const noexcept
{
    std::string mes= "[EXCEPTION] "+message;
    return mes.c_str();
}


IncorrectBiometricDataException::IncorrectBiometricDataException(const std::string &msg)
        : message(msg)
{
}

const char *IncorrectBiometricDataException::what() const noexcept
{
    return message.c_str();
}

IncorrectGateException::IncorrectGateException(const std::string &msg)
        : message(msg)
{
}

const char *IncorrectGateException::what() const noexcept
{
    return message.c_str();
}