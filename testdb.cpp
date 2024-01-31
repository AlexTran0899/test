#include "DB.h"
#include <iomanip>

using namespace std;


int main(int argc, char const *argv[]) {

    DB db;

    db.createDB("input");
    db.open("input.data");

    cout << "\n------------- Testing readRecord ------------\n";

    // Reads record 0
    // Then prints the values of the 5 fields to the screen with the name of the
    // field and the values read from the record, i.e.,
    // id: 00003 experience: 3 married: no wages: 1.344461678 industry:
    // Business_and_Repair_Service
    int recordNum = 0;
    int id = 0;
    string status;
    PassengerInfo p;

    if (db.readRecord(recordNum, status, p)){
        p.print();
    } else {
        cout << "Could not get record " << recordNum << ".\n\n";
    }


    // Reads record 9 (last record)
    recordNum = db.num_records -1;
    if (db.readRecord(recordNum,status,p)){
        p.print();
    }

    else
        cout << "Could not get record " << recordNum << ".\n\n";

    cout << "\n------------- Testing binarySearch ------------\n";

//     Find record with id 42 (should not be found)
    int Id = 10;
    cout << "Looking for Id: " << Id << endl;
    bool found = db.binarySearch(Id, p);
    if (found) p.print();
    else cout << "Record " << Id << " not found.\n\n";

// Find record with id 00000 (the first one in the file)
    Id = 2;
    cout << "Looking for Id: " << Id << endl;
    // update the value of recordnum if found, populate the fields
    found = db.binarySearch(Id, p);
    if (found) p.print();
    else cout << "Record " << Id << " not found.\n\n";

//    // Find record with id 00015 (the last one in the file)
//    Id = "00015";
//    cout << "Looking for Id: " << Id << endl;
//    found = db.binarySearch(Id, recordNum, Experience, Married, Wage, Industry);
//    if (found)
//        cout << "recordNum: " << recordNum << ", Id: " << Id
//             << ", Experience: " << Experience << ", Married: " << Married
//             << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
//    else
//        cout << "Record " << Id << " not found.\n\n";
//
//    // Find record with id 00006 (somewhere in the middle)
//    Id = "00006";
//    cout << "Looking for Id: " << Id << endl;
//    found = db.binarySearch(Id, recordNum, Experience, Married, Wage, Industry);
//    if (found)
//        cout << "recordNum: " << recordNum << ", Id: " << Id
//             << ", Experience: " << Experience << ", Married: " << Married
//             << ", Wage: " << Wage << ", Industry:" << Industry << "\n\n";
//    else
//        cout << "Record " << Id << " not found.\n\n";

    // Close database
    db.close();

    return 0;
}
