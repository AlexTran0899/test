//-----------------------------------------------------
// Example code to read from fixed length records (random access file
// Author:  Susan Gauch
// Last updated:  Jan. 20, 2022
//-----------------------------------------------------

#include <iostream>
#include <fstream>
#include <PassengerInfo.h>

using namespace std;

class DB {
private:
    std::fstream Din;


public:
    int num_records;
    const static int RECORD_SIZE = 100;

    DB();

    ~DB();

    void writeRecord();

    void parseData(string line);

    void createDB(const string inFilename);

    void open(string filename);


    void close();

    bool readRecord(const int RecordNum, string &status, PassengerInfo &data);

    bool binarySearch(const int Id, PassengerInfo& foundPassenger);
};
