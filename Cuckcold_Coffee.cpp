#include <iostream>

using namespace std;

class user
{
    string uname, passwd;
    public:
        void new_user(string u, string p);
        string verify(string x, string y);
        string get_uname()
        {
            return uname;
        }
};

void user::new_user(string u, string p)
{
    uname = u;
    passwd = p;
}

string user::verify(string x, string y)
{
    return (x==uname && y==passwd) ? "true" : "false";
}


class balance
{
    double bal1;
public:
    void set_balance(double b);
    double get_balance();
};

void balance::set_balance(double b)
{
    bal1 = b;

}
double balance::get_balance()
{
    return bal1;
}


string rtrim(const string& str) {
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return (end == string::npos) ? "" : str.substr(0, end + 1);
}


int main()
{
    int num=1;
    user newuser[100];
    balance user1[100];
    string uname, pass;


    // admin
    newuser[0].new_user("admin","admin");
    user1[0].set_balance(1000);


    cout<<"Hello user, Welcome to Cuppa Coffee online Services."<<endl;
    int z;
    repeat:
        cout<<"1. New User.\n2. Existing user.\n3. Exit."<<endl<<"Input choice: ";
        cin>>z;
        cin.ignore();
        if(z==1)
        {
            cout<<"Username: ";
            getline(cin,uname);
            uname=rtrim(uname);

            cout<<"Password: ";
            getline(cin,pass);
            pass=rtrim(pass);
            goto new_user;
        }
        if(z==2)
        {
            cout<<"Username: ";
            getline(cin,uname);
            uname=rtrim(uname);

            cout<<"Password: ";
            getline(cin,pass);
            pass=rtrim(pass);
            goto existing_user;
        }
        if(z==3)
        {
            exit(0);
        }

retry:
    cout<<"Username: ";
    getline(cin,uname);
    uname=rtrim(uname);

    cout<<"Password: ";
    getline(cin,pass);
    pass=rtrim(pass);
    goto existing_user;

new_user:
    newuser[num].new_user(uname, pass);
    cout<<"Initial deposit: $ ";
    int b;
    cin>>b;
    user1[num].set_balance(b);
    cout<<"User created successfully."<<endl;
    num++;
    goto repeat;

existing_user:
    int index;
    for (int i=0;i<=num;i++)
    {
        if (newuser[i].get_uname()==uname)
        {
            index=i;
            break;
        }
        if (i==num && newuser[i].get_uname()!=uname)
        {
            cout<<"User not found. Please try again."<<endl;
            goto retry;
        }
    }

    if (newuser[index].verify(uname, pass)=="true")
    {
        cout<<"Logged in successfully."<<endl;
        cout<<"Welcome "<<uname<<endl;
        cout<<"Balance: $"<<user1[index].get_balance()<<endl;
        do_something:
            cout<<"What would you like to do:\n1. Deposit/Withdraw Funds.\n2. Buy a Coffee.\n3. Exit"<<endl<<"Input choice: ";
            int r,coffee=20;
            cin>>r;
            if (r==1)
            {
                cout<<"1. Deposit"<<endl<<"2. Withdraw"<<endl<<"3. View Balance."<<endl<<"Input choice: ";
                cin>>r;
                int a;
                if (r==1)
                {
                    cout<<"Enter amount: $ ";
                    cin>>a;
                    user1[index].set_balance(user1[index].get_balance()+a);
                    cout<<"Remaining balance: $ "<<  user1[index].get_balance()<<endl;
                    goto do_something;
                }
                else if (r==2)
                {
                    below:
                        cout<<"Enter amount: $ ";
                        cin>>a;
                    if (a>user1[index].get_balance())
                    {
                        cout<<"Please enter the amount below $ "<<user1[index].get_balance()<<endl;
                        goto below;
                    }
                    user1[index].set_balance(user1[index].get_balance()-a);
                    cout<<"Remaining balance: $ "<<user1[index].get_balance()<<endl;
                    goto do_something;
                }
                else if (r==3)
                {
                    cout<<"Current Balance: $ "<<user1[index].get_balance()<<endl;
                    goto do_something;
                }
            }
            if (r==2)
            {
                cout<<"Cost of Coffee: $ "<<coffee<<endl;
                cout<<"Current balance: $ "<<user1[index].get_balance()<<endl;
                if (user1[index].get_balance()<coffee)
                {
                    cout<<"Sorry you can't buy a Coffee at the moment."<<endl<<"Please add funds to proceed."<<endl;
                    goto do_something;
                }
                else
                {
                    cout<<"Enter the qty of Coffee: ";
                    int q;
                    cin>>q;
                    if (user1[index].get_balance()<coffee*q)
                    {
                        cout<<"You don't have enough balance to purchase "<<q<<" coffee. Please add funds."<<endl;
                        goto do_something;
                    }
                    else
                    {
                        int previous_bal=user1[index].get_balance();
                        cout<<"Thank you for your Purchase."<<endl;
                        user1[index].set_balance(user1[index].get_balance()-q*coffee);
                        cout<<"Updated balance: $ "<<previous_bal<<" - $ "<<q*coffee<<" = $ "<<user1[index].get_balance()<<endl;
                        goto do_something;
                    }

                }
            }
            if (r==3)
            {
                goto repeat;
            }
    }
    else if (newuser[index].verify(uname, pass)=="false")
    {
        cout<<"Please enter correct credentials."<<endl;
        goto repeat;
    }


    return 0;
}
