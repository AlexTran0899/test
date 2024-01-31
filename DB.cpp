#include "DB.h"
#include "PassengerInfo.h"
#include <sstream>

DB::DB()
{
    num_records = 0;
}

DB::~DB() {}

void DB::open(string filename)
{
    Din.open(filename.c_str(), fstream::in | fstream::out | fstream::app);
}

void DB::close()
{
    Din.close();
}

bool DB::readRecord(const int RecordNum, string &status, PassengerInfo &data)
{
    bool found = false;
    stringstream output;

    if ((0 <= RecordNum) && (RecordNum <= num_records))
    {
        Din.seekg(RecordNum * 100, ios::beg);

        string line;

        if (getline(Din, line)) {
            stringstream ss(line);
            PassengerInfo p;

            p.marshal(ss);
            data = p;
            found = true;
        } else {
            status = "Failed to read record.";
        }
    }
    else
    {
        status = "Record " + to_string(RecordNum) + " out of range.";
    }

    return found;
}

bool DB::binarySearch(const int Id, PassengerInfo& foundPassenger)
{
    int Low = 0;
    int High = num_records - 1;
    bool found = false;

    while (!found && High >= Low)
    {
        int middle = (Low + High) / 2;
        string status;
        PassengerInfo p;

        if (readRecord(middle, status, p))
        {
            if (p.getPassengerId() == Id)
            {
                foundPassenger = p;
                found = true;
            }
            else if (p.getPassengerId() < Id)
                Low = middle + 1;
            else
                High = middle - 1;
        }
        else
        {
            return false; // Error reading record
        }
    }
    return found;
}

void DB::createDB(const string inFilename) {
    ifstream Din;
    ofstream Dout;
    ofstream ConfigOut;

    string line = "";

    Din.open(inFilename + ".csv");
    Dout.open(inFilename + ".data");

    while (!Din.eof()) {
        getline(Din, line);
        PassengerInfo passenger =  PassengerInfo::parseData(line);
        passenger.unmarshal(Dout);
        DB::num_records += 1;
    }
    Din.close();
    Dout.close();
}
