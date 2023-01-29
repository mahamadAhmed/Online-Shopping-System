//this program about Online Shopping System
//Using classes and arrays, the team will develop a set of functions for an online 
//shopping system.

#include <iostream>
#include<cstdlib>
using namespace std;
class Item
{
private:
	int quantity, price;
	static int ID;
	string name;

public:
	//Constructors(default, parameterized, and copy)
	Item();
	Item(int quant, int pri, string nam);
	Item(const Item& opj);

	//Setters& Getters
	static void set_id() { ID++; }
	void set_quantity(int qunt) { quantity = qunt; }
	void set_price(int pri) { price = pri; }
	void set_name(string nam) { name = nam; }
	static int get_id() { return ID; }

	int get_quantity() { return quantity; }
	int get_price() { return price; }
	string get_name() { return name; }

	//Operator overloading for the ==, +=,-=, >> and << operators
	bool operator == (string n);
	friend istream& operator >> (istream& input, Item& odpj);
	friend ostream& operator<<(ostream& output, Item& opj);
	Item operator += (Item& opj);
	Item operator -= (int qunt);
	~Item();
};
int Item::ID = 1;

Item::Item()
{
	quantity = 0, price = 0;
	name = "";
}

Item::Item(int quant, int pri, string nam)
{

	quantity = quant;
	price = pri;
	name = nam;
}

Item::Item(const Item& opj)
{
	name = opj.name;
	price = opj.price;
	quantity = opj.quantity;

}

bool Item::operator==(string n)
{
	return (name == n);
}

Item Item::operator+=(Item& opj)
{
	quantity = quantity + opj.quantity;
	return *this;
}

Item Item::operator-=(int qunt)
{
	quantity = quantity - qunt;
	return *this;
}

Item::~Item()
{
}
istream& operator>>(istream& input, Item& d)
{

	input >> d.name;
	input >> d.price;
	input >> d.quantity;
	return input;
}

ostream& operator<<(ostream& output, Item& b)
{

	output << "name : " << b.name << endl;
	output << "quantity : " << b.quantity << endl;
	output << "price : " << b.price << endl;

	return output;
}


//////////////////////////////////////////////////////////

class Seller
{
private:
	Item* items;
	string  name, email;
	int maxItems;
public:
	int count = 0;
	//Setters& Getters
	void set_name(string n) { name = n; }
	void set_email(string n) { email = n; }
	void set_maxItems(int n) { maxItems = n; }
	string get_Name() { return name; }
	string get_email() { return email; }
	int get_maxItems() { return maxItems; }
	//Constructor (parameterized)
	Seller() {
		items = new Item[maxItems];
	}
	Seller(string nam, string mail, int maxItems);

	//Operator overloading for the >> and << operators
	friend istream& operator >> (istream& input, Seller& opj);
	friend ostream& operator << (ostream& output, Seller& opj);
	//Add An Item
	void Add_Item(Item& opj);
	//function return boolean
	bool there_place() { return (maxItems == (Item::get_id()) - 1 ? false : true); }
	//Sell An Item
	void Sell_Item(string nam, int qunt);
	//function return boolean if item found
	bool item_found(string nam);
	//function Print Items
	void print_items();
	//Find an Item by ID
	Item find_by_id(int id);
	//Destructor
	~Seller();

};

Seller::Seller(string nam, string mail, int maxItem)
{
	name = nam;
	email = mail;
	maxItems = maxItem;
	items = new Item[maxItem];
}

istream& operator>>(istream& input, Seller& opj)
{
	input >> opj.name;
	input >> opj.email;
	return input;
}

ostream& operator<<(ostream& output, Seller& opj)
{
	output << "name : " << opj.name << endl;
	output << "Email : " << opj.email << endl;
	return output;
}

bool Seller::item_found(string nam)
{
	bool found = false;
	for (size_t i = 0; i < maxItems; i++)
	{
		if (items[i] == nam)
		{
			count = i;
			found = true;
		}
	}
	return found;
}

void Seller::Add_Item(Item& opj)
{

	int cont = 0;
	bool itemexists = false;
	for (int i = 0; i < maxItems; i++)
	{
		if (opj == items[i].get_name()) { itemexists = true; cont = i; }
	}
	if (itemexists)
	{
		items[cont] += opj;
	}
	else if (there_place())
	{
		items[Item::get_id() - 1] = opj;
		Item::set_id();
	}
	else
	{
		cout << "fail! there's no empty place \n";
	}
}

void Seller::Sell_Item(string nam, int qunt)
{
	if (item_found(nam))
	{
		if (qunt <= items[count].get_quantity())
		{
			items[count] -= qunt;
		}
		else
		{
			cout << "There is only {" << items[count].get_quantity() << "} left for this item" << endl;
		}
	}
	else
	{
		cout << "Item not found\n";
	}
}

void Seller::print_items()
{
	for (size_t i = 0; i < maxItems; i++)
	{
		cout << "Item " << i + 1 << endl;
		cout << items[i];
	}
}

Item Seller::find_by_id(int id)
{
	if (id <= Item::get_id() - 1) {
		cout << items[id - 1];
		return items[id - 1];
	}
	else
	{
		cout << " not found Item with this id\n";
	}
}
Seller::~Seller()
{
	delete[] items;
}


int main()
{
	int maxNumberOfItems;
	string selname, selmail;
	cout << "Please  input your name and email \n";
	cin >> selname >> selmail;
	cout << "Please  input your max number of Items\n";
	cin >> maxNumberOfItems;
	Seller sel(selname, selmail, maxNumberOfItems);

	Item* it;
	it = new Item[maxNumberOfItems];
	while (true)

	{
		cout << "choose from which have the following options: \n";
		cout << "1. Print My Info.\n"
			<< "2. Add An Item.\n"
			<< "3. Sell An Item.\n"
			<< "4. Print Items.\n"
			<< "5. Find an Item by ID\n"
			<< "6. Exit\n";

		int choose = 0, qunt = 0, id = 0, pri = 0;
		string nam = "";
		cin >> choose;
		switch (choose)
		{
		case 1:
			cout << sel;
			break;
		case 2:
			if (choose == 2) {
				cout << "Enter  name and a price and quantity \n";
				cin >> it[Item::get_id() - 1];
				sel.Add_Item(it[Item::get_id() - 1]);
			}
			break;
		case 3:
			cout << "Enter name and quantity\n";
			cin >> nam;
			cin >> qunt;
			sel.Sell_Item(nam, qunt);
			break;
		case 4:
			sel.print_items();
			break;
		case 5:
			cout << "Enter id\n";
			cin >> id;
			sel.find_by_id(id);
		case 6:
			break;
		default:
			cout << "Enter number between 1 - 6 \n";
			break;
		}
		if (choose == 6)
		{
			exit(EXIT_FAILURE);
		}
	}
	delete it;
	return 0;
}
