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
    string note;

public:
    Meeting(const string& d, const string& t, const string& n)
        : Record(d), time(t), note(n) {}

    void display() const override {
        cout << "Meeting on " << date << " at " << time << " - " << note << endl;
    }
};

class PersonalFinanceManager {
private:
    double balance;
    vector<Transaction> transactions;
    vector<Meeting> meetings;

public:
    PersonalFinanceManager() : balance(0.0) {}

    void addIncome (double amount, const string& desc, const string& date) {
        balance += amount;
        transactions.emplace_back("Income", amount, desc, date);
        cout << "Income added successfully.\n";
    }

    void addExpense (double amount, const string& desc, const string& date) {
        if(amount > balance) {
            cout << "Error: Not enough balance.\n";
            return;
        }
        balance -= amount;
        transactions.emplace_back("Expense", amount, desc, date);
        cout << "Expense added successfully.\n";
    }

    void viewBalance() const {
        cout << "Current Balance: $" << balance << endl;
    }

    void viewTransactions() const {
        if(transactions.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        cout << "Transaction History:\n";
        for(const auto& t : transactions) {
            t.display();
        }
    }

    void scheduleMeeting(const string& date, const string& time, const string& note) {
        meetings.emplace_back(date, time, note);
        cout << "Meeting scheduled successfully.\n";
    }

    void viewMeetings() const {
        if(meetings.empty()) {
            cout << "No meetings scheduled.\n";
            return;
        }
        cout << "Scheduled Meetings:\n";
        for(const auto& m : meetings) {
            m.display();
        }
    }

    double calculateProfitAndLoss (const map<string, pair<double, double>>& summary) const {
        double totalIncome = 0;
        double totalExpense = 0;

        for(const auto& entry : summary) {
            totalIncome += entry.second.first;
            totalExpense += entry.second.second;
        }

        return totalIncome - totalExpense;
    }

    void generateDailyReport() const {
        if(transactions.empty()) {
            cout << "No transactions available for report.\n";
            return;
        }

        map<string, pair<double, double>> dailySummary;
        map<string, double> dailyBalance;
        double runningBalance = 0;

        for(const auto& t : transactions) {
            string date = t.getDate();
            string type = t.getType();
            double amount = t.getAmount();

            if(type == "Income") {
                dailySummary[date].first += amount;
                runningBalance += amount;
            } else if (type == "Expense") {
                dailySummary[date].second += amount;
                runningBalance -= amount;
            }

            dailyBalance[date] = runningBalance;
        }

        cout << "\n--- Daily Report ---\n";
        for(const auto& entry : dailySummary) {
            const string& date = entry.first;
            double income = entry.second.first;
            double expense = entry.second.second;
            double endBalance = dailyBalance[date];

            cout << "Date: " << date << "\n";
            cout << "  Income: $" << income << "\n";
            cout << "  Expenses: $" << expense << "\n";
            cout << "  Balance at end of day: $" << endBalance << "\n";

            double profitOrLoss = income - expense;
            if(profitOrLoss >= 0) {
                cout << "  Profit for the day: $" << profitOrLoss << endl;
            } else {
                cout << "  Loss for the day: $" << -profitOrLoss << endl;
            }
            cout << "-------------------------\n";
        }
    }

    void generateMonthlyReport() const {
        if(transactions.empty()) {
            cout << "No transactions available for monthly report.\n";
            return;
        }

        map<string, pair<double, double>> monthlySummary;
        map<string, double> monthlyEndBalance;
        double runningBalance = 0;

        for(const auto& t : transactions) {
            string month = t.getDate().substr(0, 7);
            string type = t.getType();
            double amount = t.getAmount();

            if(type == "Income") {
                monthlySummary[month].first += amount;
                runningBalance += amount;
            } else if(type == "Expense") {
                monthlySummary[month].second += amount;
                runningBalance -= amount;
            }

            monthlyEndBalance[month] = runningBalance;
        }

        cout << "\n--- Monthly Report ---\n";
        for(const auto& entry : monthlySummary) {
            const string& month = entry.first;
            double income = entry.second.first;
            double expense = entry.second.second;
            double balance = monthlyEndBalance[month];

            cout << "Month: " << month << "\n";
            cout << "  Total Income: $" << income << "\n";
            cout << "  Total Expenses: $" << expense << "\n";
            cout << "  End-of-Month Balance: $" << balance << "\n";

            double profitOrLoss = income - expense;
            if(profitOrLoss >= 0) {
                cout << "  Profit for the month: $" << profitOrLoss << endl;
            } else {
                cout << "  Loss for the month: $" << -profitOrLoss << endl;
            }
            cout << "-------------------------------\n";
        }
    }
};

int main() {
    string password;
    cout << "Enter password to access Personal Finance Manager: ";
    getline(cin, password);

    if(password != "1234") {
        cout << "Access Denied. Incorrect password.\n";
        return 1;
    }

    PersonalFinanceManager pfm;
    int choice;
    double amount;
    string desc, date, time, note;

    do {
        cout << "\n--- Personal Finance Manager ---\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Balance\n";
        cout << "4. View Transactions\n";
        cout << "5. Schedule a Meeting\n";
        cout << "6. View Scheduled Meetings\n";
        cout << "7. Generate Daily Report\n";
        cout << "8. Generate Monthly Report\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                cout << "Enter amount: ";
                cin >> amount;
                cin.ignore();
                cout << "Enter description: ";
                getline(cin, desc);
                pfm.addIncome(amount, desc, date);
                break;

            case 2:
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                cout << "Enter amount: ";
                cin >> amount;
                cin.ignore();
                cout << "Enter description: ";
                getline(cin, desc);
                pfm.addExpense(amount, desc, date);
                break;

            case 3:
                pfm.viewBalance();
                break;

            case 4:
                pfm.viewTransactions();
                break;

            case 5:
                cout << "Enter date (YYYY-MM-DD): ";
                getline(cin, date);
                cout << "Enter time (HH:MM): ";
                getline(cin, time);
                cout << "Enter meeting note: ";
                getline(cin, note);
                pfm.scheduleMeeting(date, time, note);
                break;

            case 6:
                pfm.viewMeetings();
                break;

            case 7:
                pfm.generateDailyReport();
                break;

            case 8:
                pfm.generateMonthlyReport();
                break;

            case 0:
                cout << "Exiting... Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
