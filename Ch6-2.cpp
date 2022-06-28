#include <cstdio>
#include <map>
#include <vector>

struct Account {

    virtual ~Account() = default;

    virtual void withdraw(const double amount) = 0;

    virtual void deposit(const double amount) = 0;

    virtual void checkBalance() = 0;
};

struct CheckingAccount : Account {
    CheckingAccount(double amount) : balance{ amount } {}

    void withdraw(const double amount) override {
        balance -= amount;
    }

    void deposit(const double amount) override {
        balance += amount;
    }

    void checkBalance() override {
        printf("Your balance is %lf\n", balance);
    }

    double balance;
};

struct SavingAccount : Account {
    SavingAccount(double amount) : balance{ amount } {}

    void withdraw(const double amount) override {
        balance -= amount;
    }

    void deposit(const double amount) override {
        balance += amount;
    }

    void checkBalance() override {
        printf("Your balance is %lf\n", balance);
    }

    double balance;
};

template <class T>
struct Bank {

    void make_transfer(T& from, T& to, double amount) {
        from.withdraw(amount);
        to.deposit(amount);
    }

};


template<typename T>
struct Foobar
{
    Foobar() {
        printf("Constructing primary class\n");
    }
};

template<>
struct Foobar<int>
{
    Foobar() {
        printf("Constructing int specialized class\n");
    }
};

int main() {

    int x = 10;
    x <<= 2;
    printf("%i\n", x);

    Foobar<long> f1;
    Foobar<int> f2;
    Foobar<char> f3;

    CheckingAccount ca{ 45 };
    CheckingAccount cb{ 700 };
    SavingAccount sa{ 145 };
    SavingAccount sb{ 2700 };
    ca.checkBalance();
    cb.checkBalance();
    sa.checkBalance();
    sb.checkBalance();

    Bank<Account> bank{};

    bank.make_transfer(ca, cb, 10);
    bank.make_transfer(sa, sb, 10);
    bank.make_transfer(ca, sa, 200);
    bank.make_transfer(sb, sa, 15),
        ca.checkBalance();
    cb.checkBalance();
    sa.checkBalance();
    sb.checkBalance();
}
