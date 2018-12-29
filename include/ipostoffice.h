//
// Created by Bartek on 12/12/2018.
//

#ifndef PROJEKT3_IPOSTOFFICE_H
#define PROJEKT3_IPOSTOFFICE_H

#include <memory>
#include <vector>
#include "iclient.h"


/**
 * @brief The IPostOffice interface exposes methods for managing our Post Office instance.
 */
class IPostOffice
{
public:
    /**
     * @brief create Creates an instance of default implementation of this interface.
     * @param gate_count Number of available client gates in the office building.
     * @return Shared pointer to instance of default implementation of this interface.
     */
    static std::shared_ptr<IPostOffice> create(unsigned gate_count);

    virtual ~IPostOffice() = default;

    /**
     * @brief getClient Retrieves a IClient object for the given ID.
     * @param identificationNumber Unique ID of the client (on his identity document).
     * @return Shared pointer to the retrieved instance of IClient.
     *
     * Creates a new instance for a new client or loads data (e.g. from file) and returns
     * filled object for saved clients. Client instances MUST be persisted after they are
     * no longer used.
     */
    virtual std::shared_ptr<IClient> getClient(const std::string& identificationNumber) = 0;

    /**
     * @brief enqueueClient Add the specified client to the waiting queue.
     * @param client Client that is to be added to the queue.
     */
    virtual void enqueueClient(const std::shared_ptr<IClient>& client) = 0;

    /**
     * @brief getStatus Retrieves status of each gate.
     * @return Vector of clients' full names (or empty strings) that each gate expects.
     */
    virtual std::vector<std::string> getStatus() = 0;

    /**
     * @brief gateReady Indicates that the pointed gate is ready to accept the next client.
     * @param gateIndex Gate's index.
     * @throws IncorrectGateException Thrown if nonexistent gate index is passed.
     */
    virtual void gateReady(unsigned gateIndex) = 0;

    /**
     * @brief retrievePackages Shortcut for calling packagesRetrieved() on client that is handled by specified gate.
     * @param gateIndex Gate's index.
     * @throws IncorrectGateException Thrown if nonexistent gate index is passed or no client is being served in this gate.
     */
    virtual void collectPackages(unsigned gateIndex) = 0;
};


#endif //PROJEKT3_IPOSTOFFICE_H
