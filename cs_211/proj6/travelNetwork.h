/**
 *  @brief TravelNetwork header file
 *
 *  @author Ammar Subei
*/

#include <string>

#include "airport.h"

using std::string;

class TravelNetwork
{
  private:
    MyList<Airport> airports;
    MyList<string> filenames;

  public:
    /**
     *  @brief Default constructor
    */
    TravelNetwork();

    /**
     *  @brief Initialize airports
    */
    void initAirports();

    /**
     *  @brief Initialize airports
     *  @param int initial number of airports
    */
    void initAirports(const int numAirports);

    /**
     *  @brief Loop to process commands
     *  @param FILE input file
    */
    void processCommandLoop (FILE* inFile);

    /**
     *  @brief Prints out available commands
    */
    void showCommands();

    /**
     *  @brief Performs the travel command
    */
    void doTravel();

    /**
     *  @brief Performs the resize command
    */
    void doResize();

    /**
     *  @brief Performs the insert command
    */
    void doInsert();

    /**
     *  @brief Performs the delete command
    */
    void doDelete();

    /**
     *  @brief Performs the list command
    */
    void doList();

    /**
     *  @brief Performs the file command
    */
    void doFile();
};
