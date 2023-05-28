/*

classes:
    Material - name, price

    Item - name, colour, materials, price

        ClothingItem - +size
            Dress - +dressLength, sleeveLength, neckline
            Pant - +pantLength, pantStyle, waistType
            Jacket - +jacketLength, jacketStyle, nr_buttons
                DressJacket - Dress, Jacket + hasBelt

        AccessoryItem - +brand
            Jewelry - +gemstones
            Shoe - +style, heel
            Handbag - +style


    FashionDesign - name, clothing, accessory, price
*/

#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <map>
#include <list>
#include <set>
#include <algorithm>

using namespace std;


class InvalidInputException : public exception {
public:
    const char* what() const throw() {
        return "Invalid input. Please enter an integer.";
    }
};

class NotEnoughMoneyException : public exception {
public:
    const char* what() const throw() {
        return "Not enough money.";
    }
};

class Material{
protected:
    string name;
    float price;
public:

    //constructors
    Material(){
        name = "";
        price = 0;
    }

    Material(string name, float price){
        this->name = name;
        this->price = price;
    }

    Material(const Material& obj)
    {
        this->name = obj.name;
        this->price = obj.price;
    }

    //op =
    Material& operator=(const Material& obj)
    {
        if (this != &obj){
            this->name = obj.name;
            this->price = obj.price;
        }
        return *this;
    }

    istream& citire(istream& in){
        cout << "Name: ";
        in >> this->name;
        cout << "Price: ";
        in >> this->price;
        return in;
    }

    ostream& afisare(ostream& out) const{
        cout << "Name: " << this->name << endl;
        cout << "Price: " << this->price << endl;
        return out;
    }

    //op >>, <<
    friend istream& operator >>(istream& in, Material& obj){return obj.citire(in);}
    friend ostream& operator <<(ostream& out, const Material& obj){return obj.afisare(out);}

    //getters
    string getName() const {return name;}
    float getPrice() const {return price;}

    //destructor
    ~Material() {}
};


//abstract class
class Item{
protected:
    string name;
    string colour;
    vector <Material*> materials;
    float price;
public:

    //constructors
    Item(){
        this->name = "";
        this->colour = "";
        this->materials = {};
        this->price = 0;
    }

    Item(string name, string colour, vector <Material*> materials){
        this->name = name;
        this->colour = colour;
        for (auto material : materials) {
            this->materials.push_back(new Material(*material));
            this->price += material->getPrice();
        }
    }

    Item(const Item& obj){
        this->name = obj.name;
        this->colour = obj.colour;
        for (auto material : obj.materials) {
            this->materials.push_back(new Material(*material));
        }
        this->price = obj.price;
    }

    //op =
    Item& operator=(const Item& obj){
        if (this != &obj){
            this->name = obj.name;
            this->colour = obj.colour;
            for (auto material : obj.materials) {
                this->materials.push_back(new Material(*material));
            }
            this->price = obj.price;
        }
        return *this;
    }

    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0;

    //op >>, <<
    friend istream& operator >> (istream& in, Item& obj){return obj.citire(in);}
    friend ostream& operator << (ostream& out, const Item& obj){return obj.afisare(out);}

    //getters & setters
    string getName() const {return this->name;}
    string getColour() const {return this->colour;}
    float getPrice() const {return this->price;}
    vector <Material*> getMaterials() const {return this->materials;}

    void setClothingName(string clothingName){this->name = clothingName;}
    void setColour(string colour){this->colour = colour;}

    //function to add a new material to the item
    void addMaterial(Material* material){this->materials.push_back(material);}

    //function to get the number of materials in an item
    const int getNumMaterials() const {return this->materials.size();}

    //destructor
    virtual ~Item() {
        for (auto material : materials) {
            delete material;
        }
        materials.clear();
    }
};


class ClothingItem : public Item {
protected:
    string size;

public:

    //constructors
    ClothingItem():Item(){this->size = "";}

    ClothingItem(string name, string colour, vector <Material*> materials, string size):Item(name, colour, materials){
        this->size = size;
    }

    ClothingItem(const ClothingItem& obj):Item(obj){
        this->size = obj.size;
    }

    //read & write methods
    virtual istream& citire(istream& in){
        int aux, i;
        cout << "Nume: ";
        in >> this->name;
        cout << "Colour: ";
        in >> this->colour;

        if(!this->materials.empty()){
            this->materials.clear();
        }

        cout << endl << "1. Add material\n2. Stop adding material\n";
        while (cin >> aux && aux != 2){
            this->materials.push_back(new Material());
            in >> *(this->materials.back());
            this->price += this->materials[i++]->getPrice();
            cout << "1. Add material\n2. Stop adding material\n";
        }
        cout << "Size: ";
        in >> this->size;
        return in;
    }

    virtual ostream& afisare(ostream& out) const{
        out << "Nume: " << this->name << endl;
        out << "Colour: " << this->colour << endl;
        out << "Price: " << this->price << endl;
        out << "Materials:\n\n";
        for(int i=0; i<this->materials.size(); i++)
            out << *(this->materials[i]) << endl;
        cout << "Size: " << this->size << endl;
        return out;
    }

    //op =
    ClothingItem& operator = (const ClothingItem& obj){
        if (this != &obj){
            this->Item::operator=(obj);
            this->size = obj.size;
        }
        return *this;
    }

    //getter & setter
    string getSize() const {return this->size;}
    void setSize(string size) {this->size = size;}

    //destructor
    virtual ~ClothingItem(){}
};


class Dress : virtual public ClothingItem{
protected:
    string dressLength;
    string sleeveLength;
    string neckline;
public:

    //constructors
    Dress(): ClothingItem()
    {
        this->dressLength = "";
        this->sleeveLength = "";
        this->neckline = "";
    }

    Dress(string name, string colour, vector <Material*> materials, string size, string dressLength, string sleeveLength, string neckline):ClothingItem(name, colour, materials, size)
    {
        this->dressLength = dressLength;
        this->sleeveLength = sleeveLength;
        this->neckline = neckline;
    }

    Dress(const Dress& obj): ClothingItem(obj){
        this->dressLength = obj.dressLength;
        this->sleeveLength = obj.sleeveLength;
        this->neckline = obj.neckline;
    }

    //op =
    Dress& operator = (const Dress& obj){
        if (this != &obj){
            ClothingItem::operator=(obj);
            this->dressLength = obj.dressLength;
            this->sleeveLength = obj.sleeveLength;
            this->neckline = obj.neckline;
        }
        return *this;
    }

    //read & write methods
    virtual istream& citire(istream& in){
        ClothingItem::citire(in);
        cout << "Dress Length: ";
        in >> this->dressLength;
        cout << "Dress Sleeve Length: ";
        in >> this->sleeveLength;
        cout << "Dress Neckline: ";
        in >> this->neckline;
        return in;
    }

    virtual ostream& afisare(ostream& out) const{
        ClothingItem::afisare(out);
        out << "Dress Length: " << this->dressLength << endl;
        out << "Dress Sleeve Length: " << this->sleeveLength << endl;
        out << "Dress Neckline: " << this->neckline << endl;
        return out;
    }

    //getters & setters
    string getDressLength() const {return this->dressLength;}
    string getSleeveLength() const {return this->sleeveLength;}
    string getNeckline() const {return this->neckline;}

    void setDressLength(string dressLength){this->dressLength = dressLength;}
    void setSleeveLength(string sleeveLength){this->sleeveLength = sleeveLength;}
    void setNeckline(string neckline){this->neckline = neckline;}

    //destructor
    virtual ~Dress(){}
};


class Pants : public ClothingItem{
protected:
    string pantsLength;
    string pantsStyle;
    string waistType;
public:

    //constructors
    Pants():ClothingItem()
    {
        this->pantsLength = "";
        this->pantsStyle = "";
        this->waistType = "";
    }

    Pants(string clothingname, string colour, vector <Material*> materials, string size, string pantsLength, string pantsStyle, string waistType):ClothingItem(clothingname, colour, materials, size)
    {
        this->pantsLength = pantsLength;
        this->pantsStyle = pantsStyle;
        this->waistType = waistType;
    }

    Pants(const Pants& obj):ClothingItem(obj)
    {
        this->pantsLength = obj.pantsLength;
        this->pantsStyle = obj.pantsStyle;
        this->waistType = obj.waistType;
    }

    //op =
    Pants& operator = (const Pants& obj){
        if (this!= &obj){
            ClothingItem::operator=(obj);
            this->pantsLength = obj.pantsLength;
            this->pantsStyle = obj.pantsStyle;
            this->waistType = obj.waistType;
        }
        return *this;
    }

    //read & write methods
    istream& citire(istream& in){
        ClothingItem::citire(in);
        cout << "Pants Length: ";
        in >> this->pantsLength;
        cout << "Pants Style: ";
        in >> this->pantsStyle;
        cout << "Pants Waist Type: ";
        in >> this->waistType;
        return in;
    }

    ostream& afisare(ostream& out) const {
        ClothingItem::afisare(out);
        out << "Pants Length: " << this->pantsLength << endl;
        out << "Pants Style: " << this->pantsStyle << endl;
        out << "Pants Waist Type: " << this->waistType << endl;
        return out;
    }

    //getters & setters
    string getPantsLength() const {return this->pantsLength;}
    string getPantsStyle() const {return this->pantsStyle;}
    string getWaistType() const {return this->waistType;}

    void setPantsLength(string pantLength){this->pantsLength = pantLength;}
    void setPantsStyle(string pantStyle){this->pantsStyle = pantStyle;}
    void setWaistType(string waistType){this->waistType = waistType;}

    virtual ~Pants(){}
};


class Jacket : virtual public ClothingItem{
protected:
    string jacketLength;
    string jacketStyle;
    int nr_buttons;
public:

    //constructors
    Jacket():ClothingItem()
    {
        this->jacketLength = "";
        this->jacketStyle = "";
        this->nr_buttons = 0;
    }

    Jacket(string name, string colour, vector <Material*> materials, string size, string jacketLength, string jacketStyle, int nr_buttons):ClothingItem(name, colour, materials, size)
    {
        this->jacketLength = jacketLength;
        this->jacketStyle = jacketStyle;
        this->nr_buttons = nr_buttons;
    }

    Jacket(const Jacket& obj):ClothingItem(obj){
        this->jacketLength = obj.jacketLength;
        this->jacketStyle = obj.jacketStyle;
        this->nr_buttons = obj.nr_buttons;
    }

    //op =
    Jacket& operator = (const Jacket& obj)
    {
        if (this!= &obj){
            ClothingItem::operator = (obj);
            this->jacketLength = obj.jacketLength;
            this->jacketStyle = obj.jacketStyle;
            this->nr_buttons = obj.nr_buttons;
        }
        return *this;
    }

    //read & write methods
    virtual istream& citire(istream& in){
        ClothingItem::citire(in);
        cout << "Jacket Length: ";
        in >> this->jacketLength;
        cout << "Jacket Style: ";
        in >> this->jacketStyle;
        cout << "Number of buttons: ";
        in >> this->nr_buttons;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        ClothingItem::afisare(out);
        out << "Jacket Length: " << this->jacketLength << endl;
        out << "Jacket Style: " << this->jacketStyle << endl;
        out << "Number of buttons: " << this->nr_buttons << endl;
        return out;
    }

    //getters & setters
    string getJacketLength() const {return this->jacketLength;}
    string getJacketStyle() const {return this->jacketStyle;}
    int getNrButtons() const {return this->nr_buttons;}

    void setJacketLength(string jacketLength){this->jacketLength = jacketLength;}
    void setJacketStyle(string jacketStyle){this->jacketStyle = jacketStyle;}
    void setNrButtons(int nr_buttons){this->nr_buttons = nr_buttons;}

    //destructor
    virtual ~Jacket(){}
};


class JacketDress : public Jacket, public Dress{
private:
    bool hasBelt;
public:

    //constructors
    JacketDress() : Jacket(), Dress() {
        this->hasBelt = false;
    }

    JacketDress(string name, string colour, vector<Material*> materials, string size, string dressLength, string sleeveLength, string neckline, string jacketLength, string jacketStyle, int nr_buttons, bool hasBelt) :
            ClothingItem(name,colour,materials,size),
            Jacket(name, colour, materials, size, jacketLength, jacketStyle, nr_buttons),
            Dress(name, colour, materials, size, dressLength, sleeveLength, neckline){
        this->hasBelt = hasBelt;
    }

    JacketDress(const JacketDress& obj): ClothingItem(obj), Jacket(obj), Dress(obj){
        this->hasBelt = obj.hasBelt;
    }

    //op =
    JacketDress& operator=(const JacketDress& obj) {
        if (this != &obj){
            Jacket::operator=(obj);
            Dress::operator=(obj);
            this->hasBelt = obj.hasBelt;
        }
        return *this;
    }

    //read & write methods
    virtual istream& citire(istream& in){
        Jacket::citire(in);
        cout << "Dress Length: ";
        in >> this->dressLength;
        cout << "Dress Sleeve Length: ";
        in >> this->sleeveLength;
        cout << "Dress Neckline: ";
        in >> this->neckline;
        cout << "Has Belt[0/1]: ";
        in >> this->hasBelt;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        Jacket::afisare(out);
        out << "Dress Length: " << this->dressLength << endl;
        out << "Dress Sleeve Length: " << this->sleeveLength << endl;
        out << "Dress Neckline: " << this->neckline << endl;
        out << "Has Belt[0/1]: " << this->hasBelt << endl;
        return out;
    }

    //getter & setter
    bool getHasBelt() const { return this->hasBelt;}
    void setHasBelt(bool hasBelt) { this->hasBelt = hasBelt;}

    //destructor
    ~JacketDress() {}
};


class AccessoryItem: public Item{
protected:
    string brand;
public:

    //constructors
    AccessoryItem():Item(){this->brand = "";}

    AccessoryItem(string name, string colour, vector <Material*> materials, string brand):Item(name, colour, materials){
        this->brand = brand;
    }

    AccessoryItem(const AccessoryItem& obj) : Item(obj){
        this->brand = obj.brand;
    }

    //op =
    AccessoryItem& operator = (const AccessoryItem& obj)
    {
        if (this!= &obj){
            Item::operator=(obj);
            this->brand = obj.brand;
        }
        return *this;
    }

    //read & write methods
    virtual istream& citire(istream& in){
        int aux, i;
        cout << "Nume: ";
        in >> this->name;
        cout << "Colour: ";
        in >> this->colour;

        if(!this->materials.empty()){
            this->materials.clear();
        }

        cout << endl << "1. Add material\n2. Stop adding material\n";
        while (cin >> aux && aux != 2){
            this->materials.push_back(new Material());
            in >> *(this->materials.back());
            this->price += this->materials[i++]->getPrice();
            cout << "1. Add material\n2. Stop adding material\n";
        }
        cout << "Brand: ";
        in >> this->brand;
        return in;
    }

    virtual ostream& afisare(ostream& out)const {
        out << "Nume: " << this->name << endl;
        out << "Colour: " << this->colour << endl;
        out << "Price: " << this->price << endl;
        out << "Materials:\n\n";
        for(int i=0; i<this->materials.size(); i++)
            out << *(this->materials[i]) << endl;
        out << "Brand: " << this->brand << endl;
        return out;
    }

    //getter & setter
    string getBrand() const {return this->brand;}
    void setBrand(string brand){this->brand = brand;}

    //destructor
    virtual ~AccessoryItem() {}
};


class Handbag : public AccessoryItem{
protected:
    string style;
public:

    //constructors
    Handbag():AccessoryItem()
    {
        this->style = "";
    }

    Handbag(string name, string colour, vector <Material*> materials, string brand, string style):AccessoryItem(name, colour, materials, brand)
    {
        this->style = style;
    }

    Handbag(const Handbag& obj):AccessoryItem(obj){
        this->style = obj.style;
    }

    //op =
    Handbag& operator = (const Handbag& obj)
    {
        if (this!= &obj){
            AccessoryItem::operator = (obj);
            this->style = obj.style;
        }
        return *this;
    }

    //read & write methods
    istream& citire(istream& in){
        AccessoryItem::citire(in);
        cout << "Style: ";
        in >> this->style;
        return in;
    }

    ostream& afisare(ostream& out) const {
        AccessoryItem::afisare(out);
        out << "Style: " << this->style;
        return out;
    }

    //getter & setter
    string getStyle() const {return this->style;}
    void setStyle(string style){this->style = style;}

    //destructor
    virtual ~Handbag(){}
};


class Jewelry : public AccessoryItem{
protected:
    string gemstones;
public:

    //constructors
    Jewelry() : AccessoryItem()
    {
        this->gemstones = "";
    }

    Jewelry(string name, string colour, vector <Material*> materials, string brand, string gemstones) : AccessoryItem(name, colour, materials, brand)
    {
        this->gemstones = gemstones;
    }

    Jewelry(const Jewelry& obj):AccessoryItem(obj)
    {
        this->gemstones = obj.gemstones;
    }

    //op =
    Jewelry& operator = (const Jewelry& obj)
    {
        if (this!= &obj){
            AccessoryItem::operator = (obj);
            this->gemstones = obj.gemstones;
        }
        return *this;
    }

    //read & write methods
    istream& citire(istream& in){
        AccessoryItem::citire(in);
        cout << "Gemstones: ";
        in >> this->gemstones;
        return in;
    }

    ostream& afisare(ostream& out) const {
        AccessoryItem::afisare(out);
        out << "Gemstones: " << this->gemstones << endl;
        return out;
    }

    //getter & setter
    string getGemstones() const {return this->gemstones;}
    void setGemstones(string gemstones){this->gemstones = gemstones;}

};


class Shoe : public AccessoryItem {
protected:
    string style;
    string heel;
public:

    //constructors
    Shoe() : AccessoryItem()
    {
        this->style = "";
        this->heel = "";
    }

    Shoe(string name, string colour, vector <Material*> materials, string brand, string style, string heel) : AccessoryItem(name, colour, materials, brand)
    {
        this->style = style;
        this->heel = heel;
    }

    Shoe(const Shoe& obj):AccessoryItem(obj)
    {
        this->style = obj.style;
        this->heel = obj.heel;
    }

    //op =
    Shoe& operator = (const Shoe& obj)
    {
        if (this!= &obj){
            AccessoryItem::operator = (obj);
            this->style = obj.style;
            this->heel = obj.heel;
        }
        return *this;
    }

    //read & write methods
    istream& citire(istream& in){
        AccessoryItem::citire(in);
        cout << "Style: ";
        in >> this->style;
        cout << "Heel: ";
        in >> this->heel;
        return in;
    }

    ostream& afisare(ostream& out) const {
        AccessoryItem::afisare(out);
        out << "Style: " << this->style << endl;
        out << "Heel: " << this->heel << endl;
        return out;
    }

    //getters & setters
    string getStyle() const {return this->style;}
    string getHeel() const {return this->heel;}

    void setStyle(string style){this->style = style;}
    void setHeel(string heel){this->heel = heel;}

};


class FashionDesign {
private:
    string name;
    ClothingItem* clothing;
    AccessoryItem* accessory;
    float price;
public:

    //constructors
    FashionDesign(){
        this->name = "";
        this->clothing = new ClothingItem();
        this->accessory = new AccessoryItem();
        this->price = 0;
    }

    FashionDesign(string name, ClothingItem* clothing, AccessoryItem* accessory){
        this->name = name;
        this->clothing = clothing;
        this->accessory = accessory;
        this->price = clothing->getPrice() + accessory->getPrice();
    }

    FashionDesign(ClothingItem* clothing, AccessoryItem* accessory){
        this->name = "";
        this->clothing = clothing;
        this->accessory = accessory;
        this->price = clothing->getPrice() + accessory->getPrice();

    }

    FashionDesign(const FashionDesign& obj){
        this->name = obj.name;
        this->clothing = obj.clothing;
        this->accessory = obj.accessory;
        this->price = obj.price;
    }

    //op =
    FashionDesign& operator =(const FashionDesign& obj){
        if (this != &obj){
            this->name = obj.name;
            this->clothing = obj.clothing;
            this->accessory = obj.accessory;
            this->price = obj.price;
        }
        return *this;
    }

    //read & write methods
    istream& citire(istream& in){
        cout << "Design Name: ";
        in >> this->name;
        cout << "Item of Clothing: ";
        clothing->citire(in);
        cout << "Accessory Item: ";
        accessory->citire(in);
        this->price = clothing->getPrice() + accessory->getPrice();
        return in;
    }

    ostream& afisare(ostream& out) const {
        out << "Design Name: " << this->name << endl;
        out << "Item of Clothing:\n";
        clothing->afisare(out);
        out << "Accessory Item:\n";
        accessory->afisare(out);
        out << "Price: " << this->price << endl;
        return out;
    }

    //op >>, <<
    friend istream& operator >> (istream& in, FashionDesign& obj){return obj.citire(in);}
    friend ostream& operator << (ostream& out, const FashionDesign& obj){return obj.afisare(out);}

    //getters & setters
    string getName() const {return this->name;}
    ClothingItem* getClothing() const {return this->clothing;}
    AccessoryItem* getAccessory() const {return this->accessory;}
    float getPrice() const {return this->price;}

    void setName(string name) {this->name = name;}
    void setClothing(ClothingItem* clothing) {
        this->clothing = clothing;
        this->price = clothing->getPrice() + accessory->getPrice();
    }
    void setAccessory(AccessoryItem* accessory) {
        this->accessory = accessory;
        this->price = clothing->getPrice() + accessory->getPrice();
    }

    //destructor
    ~FashionDesign(){}

};


class User {
private:
    double budget;
    set<FashionDesign*> purchasedDesigns;                      // set for storing purchased fashion designs
    map<FashionDesign*, double> soldItems;                      // map for storing sold items
    list<FashionDesign*> wishlist;                              // list for storing the wishlist

public:
    User(double initialBudget) : budget(initialBudget) {}

    double getBudget() const {
        return budget;
    }

    set<FashionDesign*> getPurchasedDesigns() const {
        return purchasedDesigns;
    }

    map<FashionDesign*, double> getSoldItems() const {
        return soldItems;
    }

    void purchaseFashionDesign(FashionDesign* design) {
        //check if the user can afford the purchase
        double totalPrice = design->getPrice();
        try{ 
            if (totalPrice > budget) {
                throw NotEnoughMoneyException();
            }
        }
        catch (const exception& e){
            cout << e.what() << endl;
            return;
        }

        //make the purchase
        budget -= totalPrice;
        purchasedDesigns.insert(design);

        cout << "Fashion design purchased successfully." << endl;
        system("pause");
    }

    void sellItem() {
        displayPurchasedDesigns();
        int index;
        cout << "\nEnter the index of the item you want to sell: ";
        // put this in a try catch so if the user gives an char* it works:
        try {
            cin >> index;
        } catch (InvalidInputException& e) {
            cout << e.what() << endl;
            return;
        }

        if (index < 1 || index > purchasedDesigns.size()) {
            cout << "Invalid index." << endl;
            return;
        }


        //remove the item from the purchased designs
        auto it = purchasedDesigns.begin();
        advance(it, index - 1);
        FashionDesign* design = *it;
        purchasedDesigns.erase(it);

        //add the sold item and the money made to the sold items map
        double salePrice = design->getPrice() * 1.2; // 20% profit
        soldItems.insert({ design, salePrice });

        //also remove the item from the wishlist if it is there
        for (auto it = wishlist.begin(); it != wishlist.end(); ++it) {
            if (*it == design) {
                wishlist.erase(it);
                break;
            }
        }



        //increase the budget with the sale price
        budget += salePrice;

        cout << "Item sold successfully. Money earned: " << salePrice << endl;
        system("pause");
    }

    void displayPurchasedDesigns() const {
        system("cls");
        cout << string(80, '~') << endl;
        cout << "Budget: " << budget << endl;
        cout << string(80, '~') << endl;
        cout << "Purchased Fashion Designs:" << endl;

        int i = 1;
        for (const auto& design : purchasedDesigns) {
            cout << i++ << ". " << design->getName() << " - " << design->getPrice() << " dollars" << endl;
        }
        cout << string(80, '~') << endl;
        system("pause");
    }

    void displaySoldItems() const {
        system("cls");
        cout << string(80, '~') << endl;
        cout << "Budget: " << budget << endl;
        cout << string(80, '~') << endl;
        cout << "Sold Items:" << endl;
        int i = 1;
        for (const auto& item : soldItems) {
            cout << i++ << ". " << item.first->getName() << " - " << item.second << " dollars" << endl;
        }
        cout << string(80, '~') << endl;
        system("pause");
    }

    void addToWishlist(FashionDesign* design) {
        system("cls");
        cout << string(80, '~') << endl;

        // Check if the design is already in the wishlist
        if (find(wishlist.begin(), wishlist.end(), design) != wishlist.end()) {
            cout << "This fashion design is already in your wishlist." << endl;
            return;
        }

        // Add the design to the wishlist
        wishlist.push_back(design);
        cout << "Fashion design added to wishlist." << endl;
        system("pause");
    }

    void removeFromWishlist() {
        system("cls");
        cout << string(80, '~') << endl;
        displayWishlist();
        int index;
        cout << "Enter the index of the design you want to remove from the wishlist: ";
        try{
            cin >> index;
        } catch (InvalidInputException& e) {
            cout << e.what() << endl;
            return;
        }

        if (index < 1 || index > wishlist.size()) {
            cout << "Invalid index." << endl;
            return;
        }

        //remove the design from the wishlist
        auto it = wishlist.begin();
        advance(it, index - 1);
        FashionDesign* design = *it;
        wishlist.erase(it);

        cout << "Fashion design removed from wishlist." << endl;
        system("pause");
    }

    void displayWishlist() const {
        system("cls");
        cout << string(80, '~') << endl;
        cout << "Wishlist:" << endl;
        int i = 1;
        for (const auto& design : wishlist) {
            cout << i++ << ". " << design->getName() << ", Price: " << design->getPrice() << endl;
        }
        cout << string(80, '~') << endl;
        system("pause");
    }

};


class Menu{
private:
    static Menu *meniu;
    static int cnt;
    const User* user = new User(1000);

    vector<ClothingItem*> clothingItems;
    vector<Material*> materials;
    vector<AccessoryItem*> accessoryItems;

    static void addCnt(){
        ++cnt;
    }

    static void delCnt(){
        --cnt;
    }


    Menu();
    Menu(const Menu&);
    Menu& operator=(const Menu&);

    ~Menu(){}

    void createLine(char ch){
        cout << string(80, ch) << endl;
    }

    void CRUD() {
        createLine('~');
        cout << "1. Add Item\n2. Delete Item\n3. Modify Item\n4. View Item\n5. Exit\n";
        createLine('~');
    }

    void showLists(vector<Item*>& clothingItems, vector<Item*>& accessoryItems) {

        cout << "Clothing List:" << endl;
        if (clothingItems.empty()){
            cout << "No clothing items found." << endl;
        } else {
            for (int i = 0; i < clothingItems.size(); i++) {
                cout << i + 1 << ". " << clothingItems[i]->getName() << " - " << clothingItems[i]->getPrice() << " dollars" << endl;
            }
        }

        cout << "Accessory List:" << endl;
        if (accessoryItems.empty()){
            cout << "No accessory items found." << endl;
        } else {
            for (int i = 0; i < accessoryItems.size(); i++) {
                cout << i + 1 << ". " << accessoryItems[i]->getName() << " - " << accessoryItems[i]->getPrice() << " dollars" << endl;
            }
        }
    }

    void displayOptions(User& user){
        while(true){
            system("cls");
            createLine('~');
            cout << "1. Shop\n2. Sell Item\n3. Display Purchased Designs\n4. Display Sold Items\n5. Add to Wishlist\n6. Remove from wishlist\n7. Display Wishlist\n8. Exit\n";
            createLine('~');
            int choice;
            cout << "Enter your choice (1-8): ";
            verifyChoice(choice);
            switch (choice) {
                case 1:
                    shop(user);
                    break;
                case 2:
                    user.sellItem();
                    break;
                case 3:
                    user.displayPurchasedDesigns();
                    break;
                case 4:
                    user.displaySoldItems();
                    break;
                case 5:
                    addWishlist(user);
                    break;
                case 6:
                    user.removeFromWishlist();
                    break;
                case 7:
                    user.displayWishlist();
                    break;
                case 8:
                    return;
                default:
                    createLine('~');
                    cout << "Invalid choice. Please try again." << endl;
                    createLine('~');
                    system("pause");
                    break;
            }
        }
    }

    void displayShop(){
        cout << "Available Clothing Items:" << endl;
        for (int i = 0; i < clothingItems.size(); i++) {
            cout << i + 1 << ". " << clothingItems[i]->getName() << ", Price: " << clothingItems[i]->getPrice() << endl;
        }
        cout << endl;

        cout << "Available Accessory Items:" << endl;
        for (int i = 0; i < accessoryItems.size(); i++) {
            cout << i + 1 << ". " << accessoryItems[i]->getName() << ", Price: " << accessoryItems[i]->getPrice() << endl;
        }
        cout << endl;
    }

    void addWishlist(User& user){
        system("cls");
        cout << string(80, '~') << endl;
        cout << "Budget: " << user.getBudget() << endl;
        cout << string(80, '~') << endl;
        //display available clothing items and accessory items to the user using index numbers
        displayShop();
        //allow the user to choose a clothing item and an accessory item
        int clothingChoice, accessoryChoice;
        cout << "Choose a clothing item (enter the corresponding number): ";
        cin >> clothingChoice;
        cout << "Choose an accessory item (enter the corresponding number): ";
        cin >> accessoryChoice;

        //validate the user's choices
        if (clothingChoice < 0 || clothingChoice >= clothingItems.size() || accessoryChoice < 0 ||
            accessoryChoice >= accessoryItems.size()) {
            cout << "Invalid choices. Please try again." << endl;
            return;
        }

        //get the chosen clothing item and accessory item
        ClothingItem* chosenClothingItem = clothingItems[clothingChoice-1];
        AccessoryItem* chosenAccessoryItem = accessoryItems[accessoryChoice-1];

        //choose a name for the design
        cout << "Enter a name for the design: ";
        string name;
        cin >> name;

        //create a fashion design with the chosen clothing item and accessory item
        FashionDesign* design = new FashionDesign(name, chosenClothingItem, chosenAccessoryItem);

        //purchase the fashion design
        user.addToWishlist(design);
    }


    void shop(User& user) {
        system("cls");
        cout << string(80, '~') << endl;
        cout << "Budget: " << user.getBudget() << endl;
        cout << string(80, '~') << endl;
        //display available clothing items and accessory items to the user using index numbers
        displayShop();
        //allow the user to choose a clothing item and an accessory item
        int clothingChoice, accessoryChoice;
        //put this in a try catch block to catch invalid input exceptions and display a message to the user


        while (true) {
            try {
                cout << "Choose a clothing item (enter the corresponding number): ";
                cin >> clothingChoice;
                if (clothingChoice < 1 || clothingChoice > clothingItems.size()) {
                    throw out_of_range("Invalid input. Please enter a number between 1 and " + to_string(clothingItems.size()));
                }
                cout << "Choose an accessory item (enter the corresponding number): ";
                cin >> accessoryChoice;
                if (accessoryChoice < 1 || accessoryChoice > accessoryItems.size()){
                    throw out_of_range("Invalid input. Please enter a number between 1 and " + to_string(accessoryItems.size()));
                }
                break;
            } catch (const exception& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << ": ";
            }
        }



        //get the chosen clothing item and accessory item
        ClothingItem* chosenClothingItem = clothingItems[clothingChoice-1];
        AccessoryItem* chosenAccessoryItem = accessoryItems[accessoryChoice-1];

        //choose a name for the design
        cout << "Enter a name for the design: ";
        string name;
        cin >> name;

        //create a fashion design with the chosen clothing item and accessory item
        FashionDesign* design = new FashionDesign(name, chosenClothingItem, chosenAccessoryItem);

        //purchase the fashion design and remove it from the shop
        user.purchaseFashionDesign(design);
        clothingItems.erase(clothingItems.begin() + clothingChoice - 1);
        accessoryItems.erase(accessoryItems.begin() + accessoryChoice - 1);
    }

    template <typename T>
    void addItem(vector<T*>& items, int choice) {
        createLine('~');
        cout << "Enter the details of the item: \n";

        T* item = nullptr;
        try {
            if (choice == 1) {
                int clothingChoice;
                cout << "1. Dress\n2. Pants\n3. Jacket\n4. DressJacket\n";
                cout << "Enter your choice: ";
                cin >> clothingChoice;

                if (clothingChoice == 1) {
                    item = dynamic_cast<T*>(new Dress());
                } else if (clothingChoice == 2) {
                    item = dynamic_cast<T*>(new Pants());
                } else if (clothingChoice == 3) {
                    item = dynamic_cast<T*>(new Jacket());
                } else if (clothingChoice == 4) {
                    item = dynamic_cast<T*>(new JacketDress());
                } else {
                    throw out_of_range("Invalid clothing item choice.");
                }
            } else if (choice == 2) {
                int accessoryChoice;
                cout << "1. Jewelry\n2. Shoe\n3. Handbag\n";
                cout << "Enter your choice: ";
                cin >> accessoryChoice;

                if (accessoryChoice == 1) {
                    item = dynamic_cast<T*>(new Jewelry());
                } else if (accessoryChoice == 2) {
                    item = dynamic_cast<T*>(new Shoe());
                } else if (accessoryChoice == 3) {
                    item = dynamic_cast<T*>(new Handbag());
                } else {
                    throw out_of_range("Invalid accessory item choice.");
                }
            } else {
                throw out_of_range("Invalid item choice.");
            }

            if (item != nullptr) {
                cin >> *item;
                items.push_back(item);
                createLine('~');
                cout << "Item successfully added!\n";
            } else {
                throw runtime_error("Error: Failed to create item.\n");
            }
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }

        createLine('~');
        system("pause");
    }

    template<typename T>
    void deleteItem(vector<T*>& items){
        int index;
        createLine('~');
        if(items.empty()){
            cout << "No items found." << endl;
            createLine('~');
            return;
        }
        cout << "Item List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i]->getName() << endl;
        }
        createLine('~');
        cout << "Enter the number of the item to delete: ";
        while (true) {
            try {
                cin >> index;
                if (index < 1 || index > items.size()) {
                    throw out_of_range("Invalid input. Please enter a number between 1 and " + to_string(items.size()));
                }
                break;
            } catch (const exception& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << ": ";
            }
        }

        system("cls");
        createLine('~');
        cout << "Item details:\n";
        cout << *items[index - 1] << endl;
        createLine('~');
        cout << "Are you sure you want to delete this item? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            delete items[index - 1];
            items.erase(items.begin() + index - 1);
            createLine('~');
            cout << "Item successfully deleted!\n";
            createLine('~');
        } else {
            createLine('~');
            cout << "Item not deleted!\n";
            createLine('~');
        }
        system("pause");
    }

    template<typename T>
    void modifyItem(vector<T*>& items){
        int index;
        createLine('~');
        if(items.empty()){
            cout << "No items found." << endl;
            createLine('~');
            return;
        }
        cout << "Item List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i]->getName() << endl;
        }
        createLine('~');
        cout << "Enter the number of the item to modify: ";
        while (true) {
            try {
                cin >> index;
                if (index < 1 || index > items.size()) {
                    throw out_of_range("Invalid input. Please enter a number between 1 and " + to_string(items.size()));
                }
                break;
            } catch (const exception& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << ": ";
            }
        }

        system("cls");
        createLine('~');
        cout << "Item details:\n";
        cout << *items[index - 1] << endl;
        createLine('~');
        cout << "Enter the new details of the item: \n";
        cin >> *items[index - 1];
        createLine('~');
        cout << "Item successfully modified!\n";
        createLine('~');
        system("pause");

    }

    template<typename T>
    void viewItem(vector<T*>& items) {
        int index;
        createLine('~');

        if (items.empty()) {
            cout << "No items found." << endl;
            createLine('~');
            return;
        }

        cout << "Item List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            cout << i + 1 << ". " << items[i]->getName() << endl;
        }

        createLine('~');
        cout << "Enter the number of the item to view: ";
        while (true) {
            try {
                cin >> index;
                if (index < 1 || index > items.size()) {
                    throw out_of_range("Invalid input. Please enter a number between 1 and " + to_string(items.size()));
                }
                system("cls");
                createLine('~');
                cout << "Item details:\n";
                cout << *items[index - 1] << endl;
                createLine('~');
                system("pause");
                break;
            } catch (const exception& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << e.what() << ": ";
            }
        }
    }


    void verifyChoice(int& choice){
        while(!(cin >> choice)){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw InvalidInputException();
            }
    }

    void modifyItems(vector<ClothingItem*>& clothingItems, vector<AccessoryItem*>& accessoryItems) {
        while(true){
            system("cls");
            CRUD();
            int choice;
            cout << "Enter your choice (1-5): ";
            verifyChoice(choice);
            system("cls");
            switch(choice) {
                case 1:
                    createLine('~');
                    cout << "1. Add Clothing Item\n2. Add Accessory Item\n";
                    createLine('~');
                    cout << "Enter your choice (1-2): ";
                    verifyChoice(choice);
                    if (choice == 1) addItem(clothingItems,choice);
                    else addItem(accessoryItems,choice);
                    break;
                case 2:
                    createLine('~');
                    cout << "1. Delete Clothing Item\n2. Delete Accessory Item\n";
                    createLine('~');
                    cout << "Enter your choice (1-2): ";
                    verifyChoice(choice);
                    if (choice == 1) deleteItem(clothingItems);
                    else deleteItem(accessoryItems);
                    break;
                case 3:
                    createLine('~');
                    cout << "1. Modify Clothing Item\n2. Modify Accessory Item\n";
                    createLine('~');
                    cout << "Enter your choice (1-2): ";
                    verifyChoice(choice);
                    if (choice == 1) modifyItem(clothingItems);
                    else modifyItem(accessoryItems);
                    break;
                case 4:
                    createLine('~');
                    cout << "1. View Clothing Item\n2. View Accessory Item\n";
                    createLine('~');
                    cout << "Enter your choice (1-2): ";
                    verifyChoice(choice);
                    if (choice == 1) viewItem(clothingItems);
                    else viewItem(accessoryItems);
                    break;
                case 5:
                    return;
                default:
                    createLine('~');
                    cout << "Invalid choice. Please enter a number from 1 to 4." << endl;
                    createLine('~');
                    system("pause");
                    break;
            }
        }
    }



public:
    static Menu* getInstance(){
        if(!meniu)
            meniu = new Menu();

        addCnt();

        return meniu;
    }

    void deletevectors(){
        for (auto item : clothingItems) {
            if (item != NULL) {
                delete item;
                item = NULL;
            }
        }

        for (auto item : accessoryItems) {
            if (item != NULL) {
                delete item;
                item = NULL;
            }
        }

        for (auto material : materials) {
            if (material != NULL){
                delete material;
                material = NULL;
            }
        }
    }

    static void delInstance(){
        delCnt();
        if((cnt == 0) && (meniu)){
            meniu->deletevectors();
            delete meniu;
            meniu = NULL;
        }
    }

    void start(User& user) {
        try{
            while(true){
                system("cls");
                createLine('~');
                cout << "1. Buy designs\n2. Modify Items\n3. Exit\n";
                createLine('~');
                int choice;
                cout << "Enter your choice (1-3): ";
                verifyChoice(choice);
                system("cls");
                switch(choice) {
                    case 1:
                        displayOptions(user);
                        break;
                    case 2:
                        modifyItems(clothingItems, accessoryItems);
                        break;
                    case 3:
                        return;
                    default:
                        createLine('~');
                        cout << "Invalid choice. Please enter a number from 1 to 3." << endl;
                        createLine('~');
                        system("pause");
                        break;
                }
            }
        }
        catch(InvalidInputException& e){
            cout << endl << e.what() << endl;
        }
        catch(const exception& e){
            cout << e.what() << endl;
        }
    }
};


Menu::Menu(){
    Material* cotton = new Material("Cotton", 20.5);
    Material* silk = new Material("Silk", 50.4);
    Material* polyester = new Material("Polyester", 15.6);
    Material* denim = new Material("Denim", 30.7);
    Material* spandex = new Material("Spandex", 10.9);
    Material* leather = new Material("Leather", 100.1);
    Material* silver = new Material("Silver", 60.56);
    Material* diamond = new Material("Diamond", 200.7);
    Material* pearl = new Material("Pearl", 100.3);

    materials.push_back(silk);
    materials.push_back(polyester);
    materials.push_back(cotton);
    materials.push_back(denim);
    materials.push_back(spandex);
    materials.push_back(silver);
    materials.push_back(leather);
    materials.push_back(diamond);
    materials.push_back(pearl);

    clothingItems.push_back(new Dress("Summer dress", "Blue", {silk}, "S", "Short", "Sleeveless", "V-neck"));
    clothingItems.push_back(new Dress("Black Dress", "black", {silk, polyester}, "S", "Short", "Long-sleeved", "V-neck"));
    clothingItems.push_back(new Pants("Jeans", "Blue", {denim, cotton}, "M", "Long", "Slim-fit", "Low-rise"));
    clothingItems.push_back(new Pants("Khakis", "Beige", {cotton, spandex}, "M", "Long", "Straight", "Mid-waist"));
    clothingItems.push_back(new Jacket("Leather jacket", "Black", {leather}, "L", "Short", "Biker", 4));
    clothingItems.push_back(new JacketDress("Jacket Dress", "Green", {silk, leather}, "S", "Long", "Sleeveless", "Round-neck", "Mid-waist", "Bomber", 3, true));

    accessoryItems.push_back(new Handbag("Tote bag", "Red", {leather}, "Prada", "Tote"));
    accessoryItems.push_back(new Handbag("Clutch", "Black", {leather}, "Gucci", "Handheld"));
    accessoryItems.push_back(new Jewelry("Diamond earrings", "Silver", {silver, diamond}, "Swarovski", "Diamonds"));
    accessoryItems.push_back(new Jewelry("Pearl Necklace", "Cream", {silver, pearl}, "Swarovski", "Pearls"));
    accessoryItems.push_back(new Shoe("High heels", "Black", {leather}, "Christian Louboutin", "Pump", "Stiletto"));
    accessoryItems.push_back(new Shoe("Sneakers", "White & Blue", {leather}, "Adidas", "casual", "low"));
}

Menu* Menu::meniu=NULL;
int Menu::cnt=0;

int main(){
    Menu* menu = menu->getInstance();
    User user(1000);
    menu->start(user);
    return 0;
}
