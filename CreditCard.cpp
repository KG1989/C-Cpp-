#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;
using std::endl;

class CreditCard 
{
public:
    //constructor
    CreditCard(const string &no, const string &nm, int lim, double bal=0);
    //accessors (getters) const because we are just accessing values, not using
    string getNumber() const { return number; }
    string getName() const { return name; }
    double getBalance() const { return balance; }
    int getLimit() const { return limit; }

    //member functions
    bool chargeIt(double price);
    void makePayment(double payment);

private:
    string number;
    string name;
    int limit;
    double balance;
};

void printInfo(CreditCard &cc);

int main()
{   
    CreditCard cc1("111 222 333 444", "Kyle Garland", 5000);
    CreditCard cc2("999 888 777 665", "Megan Malmgren", 7500);

    for (int i = 0; i < 10; i++)
    {
        cc1.chargeIt(double(i));
        cc2.chargeIt(2*i);
    }

    printInfo(cc1);
    printInfo(cc2);

    return 0;
}

CreditCard::CreditCard(const string &no, const string &nm, int lim, double bal)
{
    number = no;
    name = nm;
    balance = bal;
    limit = lim;
}

bool CreditCard::chargeIt(double price)
{
    //we can access balance because it is a class member
    if (price + balance > double(limit))
        return false; //charge did not go through, limit credit limit exceeded
    else
    {
        balance += price;
        return true;        //charge went through
    }
}

void CreditCard::makePayment(double payment)
{
    balance -= payment;
}

void printInfo(CreditCard &cc)
{
    cout << "Name:      " << cc.getName() << endl;
    cout << "Number:    " << cc.getNumber() << endl;
    cout << "Limit:     " << cc.getLimit() << endl;
    cout << "Balance:   " << cc.getBalance() << endl;
}

