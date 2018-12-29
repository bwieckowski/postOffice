//
// Created by Bartek on 12/12/2018.
//

#include <array>
#include<stdarg.h>
#include "../include/client.h"
#include "../include/exceptions.h"

Client::Client(const std::string & clientId ) {

    this->idNumber = clientId;
    this->priority = 0;
}

std::string Client::getIdNumber()
{
    return idNumber;
}
std::string Client::getFullName()
{
    return fullName;
}

int Client::getPriority() {
    return priority;
}

void Client::setFullName(const std::string& fullName)
{
    this->fullName = fullName;
}

void Client::updatePriority(int priority) {
    this->priority = priority;
}

void Client::newPackage(const std::string &packageId) {

    if( !packages.empty() ) {
        for (auto i = packages.begin(); i != packages.end(); i++) {
            if ((*i) == packageId)
                throw PackageExistsException("package with specified ID already exists.\n");
        }
        packages.push_back( packageId );
    }
    else
        packages.push_back( packageId );

}

void Client::packagesCollected() {
    packages.clear();
}

std::vector<std::string> Client::awaitingPackages() {
    return packages;
}

void Client::updateBiometricData(const std::string& biometricData) throw( IncorrectBiometricDataException ){

    if( isDNASequenceCorrect(biometricData) )
        this->biometricData = biometricData;
    else
        throw IncorrectBiometricDataException("Incorect DNA sequence\n");

}

bool Client::isDNASequenceCorrect(std::string DNA) {
    for (int i = 0; i < DNA.length(); ++i)
        if( DNA[i] != 'A' && DNA[i] != 'C' && DNA[i] != 'G' && DNA[i] != 'T'  )
            return false;
    return true;
}

const std::string& Client::getBiometricData(){
    return biometricData;
}


//void displayArray( int **array, int lenght1,int lenght2)
//{
//    for (int i = 0; i < lenght1; ++i) {
//        for (int j = 0; j < lenght2; ++j) {
//             printf( "%d \b ",array[i][j]);
//        }
//        std::cout<<std::endl;
//    }
//}


int maxofElements(int n_args, ...)
{
    va_list ap;

    va_start(ap, n_args);
    int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    va_end(ap);
    return max;
}

Client::~Client() {



}


bool Client::verifyBiometricData(const std::string& biometricData, double threshold) throw( IncorrectBiometricDataException ){


    if( !isDNASequenceCorrect( biometricData ) )
        throw IncorrectBiometricDataException( "Incorrect DNA Sequence\n" );

    int W1 = 2;

     int arrayLenghtOrginal = this->biometricData.length()+1;
     int arrayLenghtCompare = biometricData.length()+1;

    std::vector< std::vector<int> > traceMatrix( arrayLenghtOrginal, std::vector<int> (arrayLenghtCompare, 0));
    std::vector< std::vector<int> > substitutionMatrix( arrayLenghtOrginal, std::vector<int> (arrayLenghtCompare, 0));


    //Complite substitution Matrix
    for (int i = 0; i < arrayLenghtOrginal; ++i) {
        for (int j = 0; j < arrayLenghtCompare; ++j) {

            if( j == 0 || i == 0) {
                substitutionMatrix[i][j] = 0;
               // continue;
            }
            if( biometricData[i-1] == this->biometricData[j-1] )
                substitutionMatrix[i][j] = 3;
            else
                substitutionMatrix[i][j] = -3;
        }
    }



    for (int i = 0; i < arrayLenghtOrginal; ++i) {
        for (int j = 0; j < arrayLenghtCompare; ++j) {
           if( i == 0 || j == 0) {
               traceMatrix[i][j] = 0;
            //   continue;
           }

           int max = maxofElements(4, substitutionMatrix[i][j]+traceMatrix[i-1][j-1],
                                      traceMatrix[i-1][j]-W1,
                                      traceMatrix[i][j-1]-W1,
                                      0 );
           traceMatrix[i][j] =  max;
        }
    }
  //  displayArray( substitutionMatrix, arrayLenghtOrginal,arrayLenghtCompare);//,this->biometricData,biometricData);
  //  displayArray( traceMatrix, arrayLenghtOrginal, arrayLenghtCompare);//,this->biometricData,biometricData );

    int maxi = 0, maxj = 0, maxVal = traceMatrix[0][0];
    for (int i = 0; i < arrayLenghtOrginal; ++i) {
        for (int j = 0; j < arrayLenghtCompare; ++j) {
            if( traceMatrix[i][j] > maxVal )
            {
                maxi = i;
                maxj = j;
                maxVal = traceMatrix[i][j];
            }
        }
    }

  //  printf(" max val : %d \n",maxVal);

    int i= maxi, j = maxj, sum = 0, steps = 0 ;

    //Find Path
    while( traceMatrix[i][j] != 0 )
    {
        sum += traceMatrix[i][j];
        steps++;
        if(traceMatrix[i-1][j-1] == 0 )
        {
            i = i-1;
            j = j-1;
        } else if( traceMatrix[i-1][j-1] > traceMatrix[i-1][j])
        {
            i = i-1;
            j = j-1;
        } else{
            i = i - 1;
        }

  //      printf(" %d, ",traceMatrix[i][j]);
    }

    int shortersequence = this->biometricData.length();
    if( biometricData.length() < shortersequence )
        shortersequence = biometricData.length();

    return ((maxVal/shortersequence) > threshold);


}