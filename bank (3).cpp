#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
//bank system 
using namespace std;
class bank {
private:
	int acno;
	char name[50];
	int dep;
	char type;
public:
	void create();
	void show() const;
	void modify();
	void add(int );
	 void withdraw(int );
	void report ()const ;
	int retacno()const;
	char rettype()const;
	int retdep() const;
};
void bank::create()
{
	cout << "enter account number " << "\n";
	cin >> acno;
	cout << "enter your name " << "\n";
	cin.ignore();
	cin.getline(name, 50);
	cout << "please select the account type (S/C) " << "\n";
	cin >> type;
	type = toupper(type);
	cout << "enter the amount (>=500 for saving  and >=1000 for current " << "\n";
	cin >> dep;
	cout << "\n";
	cout << "account created " << "\n";
}
void bank::show() const 
{
	cout << "\n account number : " << acno<<"\n";
	cout << "account holders name : " << name << "\n";

	cout << "  account  type  :  " << type << "\n";
	cout << "amount is : " << dep;
}
void bank::modify()
{
	cout << "the account number is : " << acno;
	cout << "modify name : " << "\n";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\n";
	cout << "modify type : " << "\n";
	cin >> type;
	type = toupper(type);
	cout << "\n";
	cout << "modify amount : ";
	cin >> dep;
}
void bank::add(int x)
{
	dep = dep + x;
}
void bank::withdraw(int x)
{
	dep = dep - x;
}
int  bank::retacno()const {
	return acno;
}
char bank::rettype()const {
	return type;
}
int bank::retdep()const {
	return dep;
}
void bank::report()const {                                        //we can also use friend function 
	cout << acno << setw(10) << name << setw(10) << type << setw(10) << dep<<"\n";
}
void write();
void modify(int);
void deleteac(int );
void withdraw_dep(int ,int );
void intro();
//function to write file
void write()
{
	bank b;
	ofstream off;
	off.open("account.dat", ios::binary | ios::app);
	b.create();
	off.write(reinterpret_cast<char*>(&b), sizeof(bank));
	off.close();

}
//function to read a specific
void disply_min(int x)
{
	bank b;
	ifstream inn;
	inn.open("account.dat", ios::binary);
	bool flag = false;
	if (!inn)
	{
		cout << "file not found " << "\n";
		return;

	}
	cout << "\n      BANK DETAILS    " << "\n";
	while (inn.read(reinterpret_cast<char*>(&b), sizeof(bank)))
	{
		if (b.retacno() == x)
		{
			b.show();
			flag = true;
		}
	}
	inn.close();
	if (flag == false)
	{
		cout << "\n   account not found " << "\n";
	}
}
//fucttion to modify acc
void modify(int num)
{
	bool found = false;
	bank b;
	fstream fin;
	fin.open("account.dat", ios::binary | ios::in | ios::out);
	if (!fin)
	{
		cout << "file not found ";
		return;
	}
	while (!fin.eof() && found == false)
	{
		fin.read(reinterpret_cast<char*>(&b), sizeof(bank));
		if (b.retacno() == num)
		{
			b.show();
			cout << "\n";
			cout << "enter the new details " << "\n";
			b.modify();
			int pos = (-1) * static_cast<int>(sizeof(bank));
			fin.seekp(pos, ios::cur);
			fin.write("account.dat", ios::binary | ios::in | ios::out);
			cout << "\n   RECORD UPDATED \n";
			found = true;

		}
	}
	fin.close();
	if (found == false)
	{
		cout << " no record found " << "\n";
	}
}
void deleteac(int n)
{
	bank b;
	ifstream in;
	ofstream  on;
	in.open("account.dat", ios::binary);
	if (!in)
	{
		cout << "file not found " << "\n";
		return;
	}
	on.open("temp.dat", ios::binary);
	in.seekg(0, ios::beg);
	while (in.read(reinterpret_cast<char*>(&b), sizeof(bank)))
	{
		if (b.retacno() != n)
		{
			on.write(reinterpret_cast<char*>(&b), sizeof(bank));
		}
	}
	in.close();
	on.close();
	remove("account.dat");
	rename("temp.dat", "account.dat");
	cout << "\n  ACOUNT DELETED   \n";
}
void dislay_all()
{
	bank b;
	ifstream in;
	in.open("account.dat", ios::binary);
	if (!in)
	{
		cout << "file not found " << "\n";
		return;
	}
	cout << "-----ACCOUNT   HOLDER    LIST  " << "\n";
	cout << "=============================================" << "\n";
	cout << "ACNO.         NAME        TYPE  BALANCE   ";
	cout << "===========================================" << "\n";
	while (in.read(reinterpret_cast<char*>(&b), sizeof(bank)))
	{
		b.report();

	}
	in.close();
}
void withdraw_dep(int x, int option)
{
	bank b;
	int amt;
	bool flag = false;
	fstream fin;
	fin.open("account.dat", ios::binary | ios::in | ios::out);
	if (!fin)
	{
		cout << "file not found  " << "\n";
		return;

	}
	while (!fin.eof() && flag == false)
	{
		fin.read(reinterpret_cast<char*>(&b), sizeof(bank));
		if (b.retacno() == x)
		{
			b.show();
			if (option == 1)
			{
				cout << "\n\n\t TO DEPOSIT ACCOUNT \n";
				cout << "enter aamount to be deposited " << "\n";
				cin >> amt;
				b.add(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\t TO WITHDRAW  ACCOUNT \n";
				cout << "enter aamount to be withdrawed " << "\n";
				cin >> amt;
				int bal = b.retdep() - amt;
				if ((bal < 500 && b.rettype() == 'S') || (bal < 1000 && b.rettype() == 'C'))
					cout << "   insufficient balance " << "\n";
				else
					b.withdraw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(bank));
			fin.seekp(pos, ios::cur);
			fin.write(reinterpret_cast<char*>(&b), sizeof(bank));
			cout << "\n   RECORD UPDATED \n";
			flag = true;
		}
	}
	fin.close();
	if (flag == false)
	{
		cout << " \n record not found " << "\n";
	}
}
void intro()
{
	cout << "\n\n\t	BANK  ";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\t    SYSTEM";
	cout << "\n\n\t  MADE BY :TAIMOOR   " << "\n";
	system("pause");
}
int main()
{
	int num;
	char ch;
	intro();
	do {

		system("cls");
		cout << "\n\t\t          MAIN MENU             " << "\n" << "\n";
		cout << "\t\t     1)NEW ACCOUNT       " << "\n" << "\n";
		cout << "\t\t     2)DEPOSIT  AMOUNT   " << "\n" << "\n";
		cout << "\t\t     3)WITHDRAW AMOUNT   " << "\n" << "\n";
		cout << "\t\t     4)BALANCE INQUIRY   " << "\n" << "\n";
		cout << "\t\t     5)ALLACCOUNTSLIST   " << "\n" << "\n";
		cout << "\t\t     6)CLOSE   ACCOUNT   " << "\n" << "\n";
		cout << "\t\t     7)MODIFY  ACCOUNT   " << "\n" << "\n";
		cout << "\t\t     8)CLOSE   ACCOUNT   " << "\n" << "\n";
		cout << "select an option :" << "\n";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write();
			break;
		case '2':
			cout << "enter account number : " << "\n";
			cin >> num;
			withdraw_dep(num, 1);
			break;
		case '3':
			cout << "enter account number : " << "\n";
			cin >> num;
			withdraw_dep(num, 2);
			break;
		case '4':
			cout << "enter account number : " << "\n";
			cin >> num;
			disply_min(num);
			break;
		case '5':
			dislay_all();
			break;
		case '6':
			cout << "enter account number : " << "\n";
			cin >> num;
			deleteac(num);
			break;
		case '7':
			cout << "enter account number : " << "\n";
			cin >> num;
			modify(num);
			break;

		case '8':
			cout << "\n";
			cout << "thanks for using bank management system  " << "\n";
			break;
		default:
			cout << "\a";
		}
		cin.ignore();
		system("pause");
	} while (ch != 8);
		return 0;
}
