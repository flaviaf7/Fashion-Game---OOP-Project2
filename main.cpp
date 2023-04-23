/*

classes:
    Material -
    
    Item -
    
        ClothingItem - 
            Dress - dressLength, sleeveLength, neckline
            Pant - pantLength, pantStyle, waistType
            Jacket - jacketLength, jacketStyle, nr_buttons
                DressJacket -
        
        AccessoryItem - 
            Jewelry -
            Shoe - 
            Handbag - 

            
    FashionDesign -
*/

#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits>

using namespace std;



class Material{
protected:
    string name;
    float price;
public:

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

    friend istream& operator >>(istream& in, Material& obj){return obj.citire(in);}
    friend ostream& operator <<(ostream& out, const Material& obj){return obj.afisare(out);}

    virtual ~Material(){}

    string getName() const {return name;}
    float getPrice() const {return price;}
};


class Item{
protected:
    string name;
    string colour;
    vector <Material*> materials;
    float price;
public:
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

    friend istream& operator >> (istream& in, Item& obj){return obj.citire(in);}
    friend ostream& operator << (ostream& out, const Item& obj){return obj.afisare(out);}

    string getName() const {return this->name;}
    string getColour() const {return this->colour;}
    float getPrice() const {return this->price;}
    vector <Material*> getMaterials() const {return this->materials;}

    void setClothingName(string clothingName){this->name = clothingName;}
    void setColour(string colour){this->colour = colour;}
    void addMaterial(Material* material){this->materials.push_back(material);}

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
    ClothingItem():Item(){this->size = "";}

    ClothingItem(string name, string colour, vector <Material*> materials, string size):Item(name, colour, materials){
        this->size = size;
    }

    ClothingItem(const ClothingItem& obj):Item(obj){
        this->size = obj.size;
    }

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

    ClothingItem& operator = (const ClothingItem& obj){
        if (this != &obj){
            this->Item::operator=(obj);
            this->size = obj.size;
        }
        return *this;
    }

    string getSize() const {return this->size;}
    void setSize(string size) {this->size = size;}

    virtual ~ClothingItem(){}
};


class Dress : virtual public ClothingItem{
protected:
    string dressLength;
    string sleeveLength;
    string neckline;
public:

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

    Dress& operator = (const Dress& obj){
        if (this != &obj){
            ClothingItem::operator=(obj);
            this->dressLength = obj.dressLength;
            this->sleeveLength = obj.sleeveLength;
            this->neckline = obj.neckline;
        }
        return *this;
    }

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

    string getDressLength() const {return this->dressLength;}
    string getSleeveLength() const {return this->sleeveLength;}
    string getNeckline() const {return this->neckline;}

    void setDressLength(string dressLength){this->dressLength = dressLength;}
    void setSleeveLength(string sleeveLength){this->sleeveLength = sleeveLength;}
    void setNeckline(string neckline){this->neckline = neckline;}

    virtual ~Dress(){}
};


class Pants : public ClothingItem{
protected:
    string pantsLength;
    string pantsStyle;
    string waistType;
public:

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

    Pants& operator = (const Pants& obj){
        if (this!= &obj){
            ClothingItem::operator=(obj);
            this->pantsLength = obj.pantsLength;
            this->pantsStyle = obj.pantsStyle;
            this->waistType = obj.waistType;
        }
        return *this;
    }

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


    string getJacketLength() const {return this->jacketLength;}
    string getJacketStyle() const {return this->jacketStyle;}
    int getNrButtons() const {return this->nr_buttons;}

    void setJacketLength(string jacketLength){this->jacketLength = jacketLength;}
    void setJacketStyle(string jacketStyle){this->jacketStyle = jacketStyle;}
    void setNrButtons(int nr_buttons){this->nr_buttons = nr_buttons;}

    virtual ~Jacket(){}
};


class JacketDress : public Jacket, public Dress{
private:
    bool hasBelt;
public:
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

    JacketDress& operator=(const JacketDress& obj) {
        if (this != &obj){
            Jacket::operator=(obj);
            Dress::operator=(obj);
            this->hasBelt = obj.hasBelt;
        }
        return *this;
    }

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

    bool getHasBelt() const { return this->hasBelt;}
    void setHasBelt(bool hasBelt) { this->hasBelt = hasBelt;}

};

class AccessoryItem: public Item{
protected:
    string brand;
public:

    AccessoryItem():Item(){this->brand = "";}

    AccessoryItem(string name, string colour, vector <Material*> materials, string brand):Item(name, colour, materials){
        this->brand = brand;
    }

    AccessoryItem(const AccessoryItem& obj) : Item(obj){
        this->brand = obj.brand;
    }

    AccessoryItem& operator = (const AccessoryItem& obj)
    {
        if (this!= &obj){
            Item::operator=(obj);
            this->brand = obj.brand;
        }
        return *this;
    }

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


    string getBrand() const {return this->brand;}
    void setBrand(string brand){this->brand = brand;}

    virtual ~AccessoryItem() {}
};


class Handbag : public AccessoryItem{
protected:
    string style;
public:

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

    Handbag& operator = (const Handbag& obj)
    {
        if (this!= &obj){
            AccessoryItem::operator = (obj);
            this->style = obj.style;
        }
        return *this;
    }

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

    string getStyle() const {return this->style;}
    void setStyle(string style){this->style = style;}

    virtual ~Handbag(){}
};


class Jewelry : public AccessoryItem{
protected:
    string gemstones;
public:

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

    Jewelry& operator = (const Jewelry& obj)
    {
        if (this!= &obj){
            AccessoryItem::operator = (obj);
            this->gemstones = obj.gemstones;
        }
        return *this;
    }

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

    string getGemstones() const {return this->gemstones;}
    void setGemstones(string gemstones){this->gemstones = gemstones;}

};


class Shoe : public AccessoryItem {
protected:
    string style;
    string heel;
public:

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

    Shoe& operator = (const Shoe& obj)
    {
        if (this!= &obj){
            AccessoryItem::operator = (obj);
            this->style = obj.style;
            this->heel = obj.heel;
        }
        return *this;
    }

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

    FashionDesign& operator =(const FashionDesign& obj){
        if (this != &obj){
            this->name = obj.name;
            this->clothing = obj.clothing;
            this->accessory = obj.accessory;
            this->price = obj.price;
        }
        return *this;
    }

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

    friend istream& operator >> (istream& in, FashionDesign& obj){return obj.citire(in);}
    friend ostream& operator << (ostream& out, const FashionDesign& obj){return obj.afisare(out);}

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

    ~FashionDesign(){}

};

void verifyChoice(int& choice){
    while(!(cin >> choice)){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer: ";
        }
}

void createLine(char ch){
    cout << string(80, ch) << endl;
}

void CRUD() {
    createLine('~');
    cout << "1. Add Item\n2. Delete Item\n3. Modify Item\n4. View Item\n";
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

void playGame(vector<Item*>& clothingItems, vector<Item*>& accessoryItems) {

    const int NUM_LEVELS = 3;
    float totalStars = 0;
    int level = 1;
    int cityidx = 0;
    string cities[] = {"New York", "Paris", "Tokyo"};
    bool playAgain = true;


    while (playAgain) {
        createLine('~');
        cout << "Welcome to " << cities[cityidx] << endl;
        level = 1;
        totalStars = 0;

        while (level <= NUM_LEVELS) {

            int clothingChoice, accessoryChoice;
            createLine('~');
            cout << "Level " << level << ":" << endl;
            showLists(clothingItems, accessoryItems);
            cout << endl;
            cout << "Choose a ClothingItem (1-" << clothingItems.size() << "): ";
            verifyChoice(clothingChoice);

            cout << "Choose an AccessoryItem (1-" << accessoryItems.size() << "): ";
            verifyChoice(accessoryChoice);

            if (clothingChoice < 1 || clothingChoice > clothingItems.size() || accessoryChoice < 1 || accessoryChoice > accessoryItems.size() ) {
                cout << "The choice has to be between 1 - " << clothingItems.size() << " for the Clothing Item and 1 - " << accessoryItems.size() << " for the Accessory Item. Please choose again." << endl;
                system("cls");
                continue;
            }

            Item* clothing_item = clothingItems[clothingChoice - 1];
            Item* accessory_item = accessoryItems[accessoryChoice - 1];
            FashionDesign* fashion_design = new FashionDesign(dynamic_cast<ClothingItem*>(clothing_item) , dynamic_cast<AccessoryItem*>(accessory_item));
            string fashion_design_name;
            cout << "Choose a design name: ";
            cin >> fashion_design_name;
            fashion_design->setName(fashion_design_name);


            int level_Stars, totalPrice = fashion_design->getPrice();
            if (totalPrice <= 50) {
                level_Stars = 1;
            } else if (totalPrice <= 100) {
                level_Stars = 2;
            } else if (totalPrice <= 150) {
                level_Stars = 3;
            } else if (totalPrice <= 200) {
                level_Stars = 4;
            } else {
                level_Stars = 5;
            }
            totalStars += level_Stars;

            cout << "You earned " << level_Stars << " stars for this outfit. Total stars: " << totalStars << endl;
            system("pause");
            system("cls");
            level++;
            delete fashion_design;
        }

        system("cls");
        float averageStars = totalStars / NUM_LEVELS;
        cout << "Congratulations, you have finished the game with an average of " << averageStars << " stars!" << endl;

        char choice;
        cout << "Do you want to continue playing? (y/n): ";
        cin >> choice;

        if (choice == 'n' || choice == 'N') {
            playAgain = false;
        } else if (choice == 'y' || choice == 'Y') {
            cityidx++;
            if (cityidx >= sizeof(cities)/sizeof(cities[0])){
                cout << "You have finished all cities. Game Over!" << endl;
                break;
            }
        } else {
            cout << "Invalid choice. Game Over!" << endl;
            playAgain = false;
        }
        system("pause");
        system("cls");
    }
}


void addItem(vector <Item*>& items, int choice){
    char itemType;
    Item* item;
    if(choice == 1){
        createLine('~');
        cout << "Enter the type of clothing item you want to add:\n1 for dress\n2 for jacket\n3 for pants\n4 for jacket dress\n";
        cin >> itemType;
        createLine('~');
        switch (itemType) {
            case '1':
                item = new Dress;
                break;
            case '2':
                item = new Jacket;
                break;
            case '3':
                item = new Pants;
                break;
            case '4':
                item = new JacketDress;
                break;
            default:
                cout << "Invalid input. Item not added." << endl;
                return;
        }
    }else if (choice == 2){
        createLine('~');
        cout << "Enter the type of accessory item you want to add:\n1 for Jewelry\n2 for Handbag\n3 for Shoe\n";
        cin >> itemType;
        createLine('~');
        switch (itemType) {
            case '1':
                item = new Jewelry;
                break;
            case '2':
                item = new Handbag;
                break;
            case '3':
                item = new Shoe;
                break;
            default:
                cout << "Invalid input. Item not added." << endl;
                return;
        }
    }

    cout << "Enter the details of the new item: \n";
    cin >> *item;
    createLine('~');
    items.push_back(item);

    system("cls");
    createLine('~');
    cout << "Item added successfully!\n";
    createLine('~');
    system("pause");
}


void deleteItem(vector <Item*>& items, int choice){
    int index;
    if(items.empty()){
        cout << "No items found." << endl;
        return;
    }
    if(choice == 1){
        createLine('~');
        cout << "Clothing List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            ClothingItem* clothingItem = dynamic_cast<ClothingItem*>(items[i]);
            if(clothingItem){
                cout << i + 1 << ". " << items[i]->getName() << endl;
            }
        }
    }else if (choice == 2){
        createLine('~');
        cout << "Accessory List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            AccessoryItem* accessoryItem = dynamic_cast<AccessoryItem*>(items[i]);
            if(accessoryItem){
                cout << i + 1 << ". " << items[i]->getName() << endl;
            }
        }
    }

    cout << "Enter the number of the item to delete: ";
    while (!(cin >> index) || index < 1 || index > items.size()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 1 and " << items.size() << ": ";
    }

    delete items[index-1];
    items.erase(items.begin()+index-1);

    system("cls");
    createLine('~');
    cout << "Item deleted successfully!\n";
    createLine('~');
    system("pause");
}

void modifyItem(vector<Item*>& items, int choice){
    int index;
    createLine('~');
    if(items.empty()){
        cout << "No items found." << endl;
        createLine('~');
        return;
    }
    if(choice == 1){
        cout << "Clothing List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            ClothingItem* clothingItem = dynamic_cast<ClothingItem*>(items[i]);
            if(clothingItem){
                cout << i + 1 << ". " << items[i]->getName() << endl;
            }
        }
    }else if (choice == 2){
        cout << "Accessory List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            AccessoryItem* accessoryItem = dynamic_cast<AccessoryItem*>(items[i]);
            if(accessoryItem){
                cout << i + 1 << ". " << items[i]->getName() << endl;
            }
        }
    }
    createLine('~');
    cout << "Enter the number of the item to modify: ";
    while (!(cin >> index) || index < 1 || index > items.size()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 1 and " << items.size() << ": ";
    }

    system("cls");
    createLine('~');
    cout << "Enter the new details of the item: \n";
    Item* item = items[index-1];
    JacketDress* jdItem = dynamic_cast<JacketDress*>(item);
    if (jdItem) {
        cin >> *jdItem;
    } else {
        cin >> *item;
    }    
    createLine('~');
    cout << "Item successfully modified.\n";
    createLine('~');
    system("pause");
}

void viewItem(vector<Item*>& items, int choice) {
    int index;
    createLine('~');
    if(items.empty()){
        cout << "No items found." << endl;
        createLine('~');
        return;
    }
    if(choice == 1){
        cout << "Clothing List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            ClothingItem* clothingItem = dynamic_cast<ClothingItem*>(items[i]);
            if(clothingItem){
                cout << i + 1 << ". " << items[i]->getName() << endl;
            }
        }
    }else if (choice == 2){
        cout << "Accessory List:" << endl;
        for (int i = 0; i < items.size(); i++) {
            AccessoryItem* accessoryItem = dynamic_cast<AccessoryItem*>(items[i]);
            if(accessoryItem){
                cout << i + 1 << ". " << items[i]->getName() << endl;
            }
        }
    }
    createLine('~');
    cout << "Enter the number of the item to view details: ";
    while (!(cin >> index) || index < 1 || index > items.size()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number between 1 and " << items.size() << ": ";
    }

    system("cls");
    createLine('~');
    cout << *(items[index-1]);
    createLine('~');
    system("pause");
}

void modifyItems(vector<Item*>& clothingItems, vector<Item*>& accessoryItems) {
    while (true) {
        system("cls");
        createLine('~');
        cout << "Which items would you like to modify?" << endl;
        cout << "1. Clothing items\n2. Accessory items\n3. Return to main menu" << endl;
        createLine('~');

        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                system("cls");
                createLine('~');
                cout << "Clothing items:" << endl;
                for (const auto& item : clothingItems) {
                    cout << item->getName() << " - $" << item->getPrice() << endl;
                }
                createLine('~');
                CRUD();
                int choice1;
                verifyChoice(choice1);
                switch (choice1) {
                    case 1:
                        system("cls");
                        addItem(clothingItems, choice);
                        break;
                    case 2:
                        system("cls");
                        deleteItem(clothingItems, choice);
                        break;
                    case 3:
                        system("cls");
                        modifyItem(clothingItems, choice);
                        break;
                    case 4:
                        system("cls");
                        viewItem(clothingItems, choice);
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                        break;
                }
                break;
            case 2:
                system("cls");
                createLine('~');
                cout << "Accessory items:" << endl;
                for (const auto& item : accessoryItems) {
                    cout << item->getName() << " - $" << item->getPrice() << endl;
                }
                createLine('~');
                CRUD();
                int choice2;
                verifyChoice(choice2);
                switch (choice2) {
                    case 1:
                        system("cls");
                        addItem(accessoryItems, choice);
                        break;
                    case 2:
                        system("cls");
                        deleteItem(accessoryItems, choice);
                        break;
                    case 3:
                        system("cls");
                        modifyItem(accessoryItems, choice);
                        break;
                    case 4:
                        system("cls");
                        viewItem(accessoryItems, choice);
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                        break;
                }
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice." << endl;
                break;
        }
    }
}

void start(vector <Item*>& clothingItems, vector <Item*>& accessoryItems) {
    while(true){
        system("cls");
        createLine('~');
        cout << "Welcome to the Fashion Game!" << endl;
        createLine('~');
        cout << "1. Play Game" << endl;
        cout << "2. Add/Modify/Delete Items" << endl;
        cout << "3. Quit" << endl;
        createLine('~');

        int choice;
        cout << "Enter your choice (1-3): ";
        verifyChoice(choice);
        system("cls");
        switch(choice) {
            case 1:
                playGame(clothingItems, accessoryItems);
                break;
            case 2:
                modifyItems(clothingItems, accessoryItems);
                break;
            case 3:
                createLine('~');
                cout << "Thanks for playing!" << endl;
                createLine('~');
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

int main()
{

    Material* cotton = new Material("Cotton", 20.5);
    Material* silk = new Material("Silk", 50.4);
    Material* polyester = new Material("Polyester", 15.6);
    Material* denim = new Material("Denim", 30.7);
    Material* spandex = new Material("Spandex", 10.9);
    Material* leather = new Material("Leather", 100.1);
    Material* silver = new Material("Silver", 60.56);
    Material* diamond = new Material("Diamond", 200.7);
    Material* pearl = new Material("Pearl", 100.3);

    vector<Material*> materials;
    materials.push_back(silk);
    materials.push_back(polyester);
    materials.push_back(cotton);
    materials.push_back(denim);
    materials.push_back(spandex);
    materials.push_back(silver);
    materials.push_back(leather);
    materials.push_back(diamond);
    materials.push_back(pearl);

    vector<Item*> clothingItems;
    clothingItems.push_back(new Dress("Summer dress", "Blue", {silk}, "S", "Short", "Sleeveless", "V-neck"));
    clothingItems.push_back(new Dress("Black Dress", "black", {silk, polyester}, "S", "Short", "Long-sleeved", "V-neck"));
    clothingItems.push_back(new Pants("Jeans", "Blue", {denim, cotton}, "M", "Long", "Slim-fit", "Low-rise"));
    clothingItems.push_back(new Pants("Khakis", "Beige", {cotton, spandex}, "M", "Long", "Straight", "Mid-waist"));
    clothingItems.push_back(new Jacket("Leather jacket", "Black", {leather}, "L", "Short", "Biker", 4));
    clothingItems.push_back(new JacketDress("Jacket Dress", "Green", {silk, leather}, "S", "Long", "Sleeveless", "Round-neck", "Mid-waist", "Bomber", 3, true));

    vector<Item*> accessoryItems;
    accessoryItems.push_back(new Handbag("Tote bag", "Red", {leather}, "Prada", "Tote"));
    accessoryItems.push_back(new Handbag("Clutch", "Black", {leather}, "Gucci", "Handheld"));
    accessoryItems.push_back(new Jewelry("Diamond earrings", "Silver", {silver, diamond}, "Swarovski", "Diamonds"));
    accessoryItems.push_back(new Jewelry("Pearl Necklace", "Cream", {silver, pearl}, "Swarovski", "Pearls"));
    accessoryItems.push_back(new Shoe("High heels", "Black", {leather}, "Christian Louboutin", "Pump", "Stiletto"));
    accessoryItems.push_back(new Shoe("Sneakers", "White & Blue", {leather}, "Adidas", "casual", "low"));


    start(clothingItems, accessoryItems);



    //dezalocari
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

    return 0;
}
