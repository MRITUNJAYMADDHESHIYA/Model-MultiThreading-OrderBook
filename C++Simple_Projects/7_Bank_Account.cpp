#include<iostream>
#include<vector>
using namespace std;

//store account details
class BankAccount{
    private:
        string accountHolder;
        int    accountNumber;
        double balance;
    public:
        //constructor
        BankAccount(string name, int accNum, double initialBalance){
            accountHolder = name;
            accountNumber = accNum;
            balance = initialBalance;
        }

        //Deposit Money
        void deposit(double amount){
            if(amount > 0){
                balance += amount;
                cout<<"Deposited: $"<<amount<<endl;
            }else{
                cout<<"Invalid deposit amount!"<<endl;
            }
        }

        //withdraw money
        void withdraw(double amount){
            if(amount > 0 && amount <= balance){
                balance -= amount;
                cout<<"Withdrew: $"<<amount<<endl;
            }else{
                cout<<"Invalid withdrawal amount or insufficient funds!"<<endl;
            }
        }

        //Display account details
        void display(){
            cout<<"\nAccount Holder: "<<accountHolder<<endl;
            cout<<"Account Number: "<<accountNumber<<endl;
            cout<<"Balance: $"<<balance<<endl;
        }

        //Get account number
        int getAccountNumber(){
            return accountNumber;
        }
};

int main(){
    vector<BankAccount> accounts;

    while(true){
        
        cout<<"Bank Account Management System"<<endl;
        cout<<"-------------------------------"<<endl;
        cout<<"1. Create Account"<<endl;
        cout<<"2. Deposit Money"<<endl;
        cout<<"3. Withdraw Money"<<endl;
        cout<<"4. Check Balance"<<endl;
        cout<<"5. Exit"<<endl;

        int choice;
        cout<<"Enter your choice: ";
        cin>>choice;   

        if(choice == 1){
            string name;
            int accNum;
            double initialBalance;
            cout<<"Enter Account Holder Name: ";    
            cin.ignore();
            getline(cin, name);
            cout<<"Enter Account Number: ";
            cin>>accNum;
            cout<<"Enter Initial Balance: $";
            cin>>initialBalance;
            accounts.push_back(BankAccount(name, accNum, initialBalance));
            cout<<"Account created successfully!\n"<<endl;
        }else if(choice == 2){
            int accNum;
            double amount;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            bool found = false;

            for(auto &acc : accounts){
                if(acc.getAccountNumber() == accNum){
                    cout<<"Enter Deposit Amount: $";
                    cin>>amount;
                    acc.deposit(amount);
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"Account not found!"<<endl;
            }
        }else if(choice == 3){
            int accNum;
            double amount;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            bool found = false;

            for(auto &acc : accounts){
                if(acc.getAccountNumber() == accNum){
                    cout<<"Enter Withdrawal Amount: $";
                    cin>>amount;
                    acc.withdraw(amount);
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"Account not found!"<<endl;
            }
        }else if(choice == 4){
            int accNum;
            cout<<"Enter Account Number: ";
            cin>>accNum;
            bool found = false;
            for(auto &acc : accounts){
                if(acc.getAccountNumber() == accNum){
                    acc.display();
                    found = true;
                    break;
                }
            }
            if(!found){
                cout<<"Account not found!"<<endl;
            }
        }else if(choice == 5){
            cout<<"Exiting the system. Goodbye!"<<endl;
            break;
        }else{
            cout<<"Invalid choice! Please try again."<<endl;
        }
        cout<<endl; //for better readability
    }
    return 0;
}   