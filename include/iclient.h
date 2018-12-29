//
// Created by Bartek on 12/12/2018.
//

#ifndef PROJEKT3_ICLIENT_H
#define PROJEKT3_ICLIENT_H

#include <string>

/**
 * @brief The IClient interface encapsulates client behavior.
 */
class IClient
{
public:
    virtual ~IClient() = default;

    /**
     * @brief getIdNumber Getter for client's identification number.
     * @return Unique ID of the client (on his identity document).
     */
    virtual std::string getIdNumber() = 0;

    /**
     * @brief getFullName Getter for client's name.
     * @return First name, middle names (optionally) and last name as a single string.
     */
    virtual std::string getFullName() = 0;

    /**
     * @brief setFullName Setter for client's name.
     * @param fullName First name, middle names (optionally) and last name as a single string.
     */
    virtual void setFullName(const std::string& fullName) = 0;

    /**
     * @brief getPriority Getter for client's priority for service.
     * @return Client's priority, the higher it is the client is more likely to be served faster.
     *
     * By default should be initialized to 0.
     */
    virtual int getPriority() = 0;

    /**
     * @brief updatePriority Setter for client's priority for service.
     * @param priority Client's priority, the higher it is the client is more likely to be served faster.
     */
    virtual void updatePriority(int priority) = 0;

    /**
     * @brief getBiometricData Getter for client's biometric sequence data.
     * @return Client's genetic sequence stored as a string.
     */
    virtual const std::string& getBiometricData() = 0;

    /**
     * @brief updateBiometricData Setter for client's biometric sequence data.
     * @param biometricData Client's genetic sequence stored as a string.
     * @throws IncorrectBiometricDataException Thrown if the passed sequence contains illegal DNA sequence characters.
     */
    virtual void updateBiometricData(const std::string& biometricData) = 0;

    /**
     * @brief verifyBiometricData Verifies the passed sequence's similarity to the previosly stored one.
     * @param biometricData Sequence to be veriefied for similarity.
     * @param threshold If the normalized score is higher than the threshold,
     * @return True if sequences are considered to originate from the same individual, false otherwise.
     * @throws IncorrectBiometricDataException Thrown if the argument sequence contains illegal DNA sequence characters.
     *
     * By default should implement following behavior:
     * Aligment score should be computed as in Smith-Waterman[1] algorithm
     *  with following parameters:
     * // Substitution matrix:
     * // +3 if a_i == b_j
     * // -3 if a_i != b_j
     * // Gap penalty:
     * // W_k == W_1
     * // W_1 == 2
     * After finding the maximum alignment score, we compute the normalized
     * score by dividing the maximum score by the length of the shorter sequence.
     * The sequence is "verified" if this score is higher than the threshold.
     *
     * [1]: https://en.wikipedia.org/wiki/Smith-Waterman_algorithm
     */
    virtual bool verifyBiometricData(const std::string& biometricData, double threshold) = 0;

    /**
     * @brief newPackage Adds a new package for the client.
     * @param packageId String that uniquely identifies the new package.
     * @throws PackageExistsException Thrown if package with specified ID already exists.
     */
    virtual void newPackage(const std::string& packageId) = 0;

    /**
     * @brief awaitingPackages Returns a collection of package IDs that are waiting for the client.
     * @return Vector of package IDs.
     */
    virtual std::vector<std::string> awaitingPackages() = 0;

    /**
     * @brief packagesRetrieved Indicates that the packages has been retrieved and clears all client's packages.
     */
    virtual void packagesCollected() = 0;
};


#endif //PROJEKT3_ICLIENT_H
