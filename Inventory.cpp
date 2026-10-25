#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Item
{
    int partnumber;
    string description;
    int quantity;

    Item(int pn, string d, int q)
    {
        partnumber = pn;
        description = d;
        quantity = q;
    }
};

int find(vector<Item>& Inventory, int partnumber)
{
    int end = Inventory.size();
    end = end-1;
    int start = 0;
    while(start<=end)
    {
        int mid = (start + end)/2;
        if(Inventory[mid].partnumber==partnumber)
        {
            return mid;
        }
        else if(Inventory[mid].partnumber>partnumber)
        {
            end = mid-1;
        }
        else if(Inventory[mid].partnumber<partnumber)
        {
            start = mid+1;
        }
    }
    return -1;
}

void add(vector<Item>& Inventory, Item& newItem)
{
    if(find(Inventory, newItem.partnumber) != -1)
    {
        for(int i = 0; i<Inventory.size(); i++)
        {
            if(Inventory[i].partnumber == newItem.partnumber)
            {
                Inventory[i].quantity += newItem.quantity;
                break;
            }
        }
    }
    else
    {
        int size = Inventory.size();
        for(int i = size-1; i>=0; i--)
        {
            if(newItem.partnumber > Inventory[i].partnumber)
            {
                Inventory.insert(Inventory.begin() + i+1, newItem);
                return;
            }
        }
        Inventory.insert(Inventory.begin(), newItem);
    }
}

void show(vector<Item>& Inventory, int partnumber)
{
    for(int i = 0; i<Inventory.size(); i++)
    {
        if (Inventory[i].partnumber == partnumber)
        {
            cout<<"Item Partnumber: "<<Inventory[i].partnumber<<endl;
            cout<<"Item Description: "<<Inventory[i].description<<endl;
            cout<<"Item Quantity: "<<Inventory[i].quantity<<endl;
            return;
        }
    }
    cout<<"No Item Information"<<endl;
}

void remove(vector<Item>& Inventory, int partnumber, int quantity)
{
    for(int i = 0; i<Inventory.size(); i++)
    {
        if(Inventory[i].partnumber == partnumber)
        {
            if(Inventory[i].quantity > quantity)
            {
                Inventory[i].quantity -= quantity;
                cout<<"Remove "<<quantity<<" of "<<Inventory[i].description<<". Now remain "<<Inventory[i].quantity<<endl;
            }
            else
            {
                string d = Inventory[i].description;
                Inventory.erase(Inventory.begin() + i);
                cout<<"Remove all of "<<d<<endl;
            }
            return;
        }
    }
    cout << "Item not found." << endl;
}

void list(vector<Item>& Inventory)
{
    for(int i = 0; i<Inventory.size(); i++)
    {
        cout<<Inventory[i].partnumber<<", "<<Inventory[i].description<<", "<<Inventory[i].quantity<<endl;
    }
}

int main()
{
    vector<Item> Inventory;
    Inventory.push_back(Item(12, "Apple", 20));
    Inventory.push_back(Item(14, "Banana", 15));
    Inventory.push_back(Item(42, "Fries", 30));
    Inventory.push_back(Item(57, "Washer", 10));
    Inventory.push_back(Item(100, "Pencil", 50));


    cout << "Expected to get 0, got " << find(Inventory, 12) << endl;
    cout << "Expected to get 2, got "<< find(Inventory, 42) << endl;
    cout << "Expected to get 4, got "<< find(Inventory, 100) << endl;
    cout << "Expected to get -1, got "<< find(Inventory, 1) << endl;
    vector<Item> Inventory2;
    cout << "Expected to get -1, got "<< find(Inventory2, 57) << endl;
    vector<Item> Inventory3;
    Inventory3.push_back(Item(190, "Cake", 12));
    cout << "Expected to get 0, got "<< find(Inventory3, 190) << endl;
    cout << " " <<endl;

    Item item1(12, "Apple", 5);
    add(Inventory, item1);
    cout << "Expected quantity 25, got "<< Inventory[0].quantity << endl;
    cout << "Expected size 5, got "<< Inventory.size() << endl;
    Item item2(5, "Cake", 12);
    add(Inventory, item2);
    cout << "Expected first part is number 5, got "<< Inventory[0].partnumber << endl;
    Item item3(30, "Milk", 8);
    add(Inventory, item3);
    cout << "Expected part number 30 at index 3, got "<< Inventory[3].partnumber << endl;
    Item item4(200, "Eraser", 10);
    add(Inventory, item4);
    cout << "Expected last part number 200, got "<< Inventory[Inventory.size()-1].partnumber << endl;
    Item item5(50, "Bread", 6);
    add(Inventory2, item5);
    cout << "Expected size 1, got "<< Inventory2.size() << endl;
    cout << "Expected first part number 50, got "<< Inventory2[0].partnumber << endl;
    cout << " " <<endl;


    vector<Item> showInventory;
    showInventory.push_back(Item(12, "Apple", 20));
    showInventory.push_back(Item(14, "Banana", 15));
    showInventory.push_back(Item(42, "Fries", 30));

    cout << "Expected to get 12, Apple, 20" << endl;
    show(showInventory, 12);
    cout << "Expected to get 14, Banana, 15" << endl;
    show(showInventory, 14);
    cout << "Expected to get 42, Fries, 30" << endl;
    show(showInventory, 42);
    cout << "Expected to get no item information" << endl;
    show(showInventory, 99);
    vector<Item> emptyShowInventory;
    cout << "Expected to get no item information" << endl;
    show(emptyShowInventory, 12);
    cout << " " <<endl;


    remove(Inventory, 12, 5);
    cout << "Expected quantity 20, got "<< Inventory[find(Inventory, 12)].quantity << endl;
    remove(Inventory, 12, 20);
    cout << "Expected -1, got " << find(Inventory, 12) << endl;
    remove(Inventory, 5, 100);
    cout << "Expected -1, got " << find(Inventory, 5) << endl;
    remove(Inventory, 999, 1);
    cout << "Expected: Item not found." << endl;
    vector<Item> Inventory4;
    remove(Inventory4, 12, 1);
    cout << "Expected: Item not found." << endl;
    cout << " " <<endl;


    vector<Item> listInventory;
    cout << "Expected no output" << endl;
    list(listInventory);
    listInventory.push_back(Item(12, "Apple", 20));
    cout << "Expected 12, Apple, 20" << endl;
    list(listInventory);
    listInventory.push_back(Item(14, "Banana", 15));
    cout << "Expected Apple and Banana" << endl;
    list(listInventory);
    listInventory.push_back(Item(42, "Fries", 0));
    cout << "Expected Apple, Banana, and Fries with quantity 0" << endl;
    list(listInventory);
    listInventory.push_back(Item(57, "Blue Pencil", 10));
    cout << "Test 5: Expected all four items, including Blue Pencil" << endl;
    list(listInventory);
}