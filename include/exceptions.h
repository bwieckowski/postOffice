//
// Created by Bartek on 12/12/2018.
//

#ifndef PROJEKT3_EXCEPTIONS_H
#define PROJEKT3_EXCEPTIONS_H


#include <stdexcept>


/**
 * Indicates a package with the same ID already exists, which should never happen.
 */
class PackageExistsException : std::exception {
public:
    PackageExistsException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string message;
};

/**
 * Thrown if characters other than 'C', 'T', 'G' or 'A' were encountered in the sequence.
 */
class IncorrectBiometricDataException : std::exception {
public:
    IncorrectBiometricDataException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string message;
};

/**
 * Thrown if the passed index is incorrect in this context.
 */
class IncorrectGateException : std::exception {
public:
    IncorrectGateException(const std::string& msg);
    const char* what() const noexcept override;
private:
    std::string message;
};

#endif //PROJEKT3_EXCEPTIONS_H