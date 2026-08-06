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

public:
    Transaction(const string& t, double a, const string& d, const string& dt)
        : Record(dt), type(t), amount(a), description(d) {}

    void display() const override {
        cout << type << " - $" << amount << " : " << description << " on " << date << endl;
    }

    string getType() const { return type; }
    double getAmount() const { return amount; }
};

class Meeting : public Record {
private:
    string time;
