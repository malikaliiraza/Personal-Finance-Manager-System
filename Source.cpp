#include <iostream>
#include <vector>
//#include <string>
#include <map>

using namespace std;

class Record {
protected:
    string date;

public:
    Record(const string& d) : date(d) {}
    virtual void display() const = 0; 
    string getDate() const { return date; }
    virtual ~Record() {} 
};
class Transaction : public Record {
private:
    string type;
    double amount;
    string description;



};
