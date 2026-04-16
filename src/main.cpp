#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

vector<Product> products;

void loadProducts() {

    ifstream file("data/products.csv");
    string line;

    getline(file, line);

    while(getline(file, line)) {

        stringstream ss(line);
        string value;
        Product p;

        getline(ss,value,',');
        p.id = stoi(value);

        getline(ss,value,',');
        p.name = value;

        getline(ss,value,',');
        p.quantity = stoi(value);

        getline(ss,value,',');
        p.price = stod(value);

        products.push_back(p);
    }
}

void saveProducts() {

    ofstream file("data/products.csv");

    file<<"id,name,quantity,price\n";

    for(auto &p:products){

        file<<p.id<<","
            <<p.name<<","
            <<p.quantity<<","
            <<p.price<<"\n";
    }
}

void showProducts(){

    cout<<"\nProducts\n";

    for(auto &p:products){

        cout<<p.id<<" "
            <<p.name<<" "
            <<p.quantity<<" "
            <<p.price<<endl;
    }
}

void addProduct(){

    Product p;

    cout<<"Enter ID: ";
    cin>>p.id;

    cout<<"Enter Name: ";
    cin>>p.name;

    cout<<"Enter Quantity: ";
    cin>>p.quantity;

    cout<<"Enter Price: ";
    cin>>p.price;

    products.push_back(p);
}

void purchaseProduct(){

    int id,qty;

    cout<<"Enter Product ID: ";
    cin>>id;

    cout<<"Enter Quantity: ";
    cin>>qty;

    for(auto &p:products){

        if(p.id==id && p.quantity>=qty){

            p.quantity-=qty;

            ofstream file("data/purchase_history.csv",ios::app);
            file<<p.id<<","<<p.name<<","<<qty<<"\n";

            cout<<"Purchase successful\n";
            return;
        }
    }

    cout<<"Product not available\n";
}
 void deleteProduct(){
     int id;
     cout<<"Enter Product ID to delete: ";
     cin>>id;
    
     for(auto it = products.begin(); it != products.end(); ++it){
         if(it->id == id){
             cout<<"Deleting product: "<<it->name<<endl;
             products.erase(it);
             cout<<"Product deleted successfully\n";
             return;
         }
     }
     cout<<"Product not found\n";
}

int main(){

    loadProducts();

    int choice;

    while(true){

        cout<<"\n1 View Products\n";
        cout<<"2 Add Product\n";
        cout<<"3 Delete Product\n";
	cout<<"4 Delete Product\n";
        cout<<"5 Exit\n";

        cin>>choice;

        if(choice==1) showProducts();
        else if(choice==2) addProduct();
        else if(choice==3) purchaseProduct();
	else if(choice==4) deleteProduct();
        else if(choice==5){
            saveProducts();
            break;
        }
    }
}
