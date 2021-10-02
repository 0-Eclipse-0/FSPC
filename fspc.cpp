#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using std::string;

const string pn = "[FSPC] ";
const string er = "[ERR] ";
const int cost_mult = 3; // Default cost multiplier (Usually 3x in food industry)

class Product
{
  public:
    void EnterInfo();
    int DispPortSize()
    {
      return portion_size;
    }
    float GetPrice();
  private:
    int units;
    int unit_size;
    float case_cost;
    int portion_size;
};

void Product::EnterInfo()
{
  cout<<pn<<"Enter number of units per case: ";
  cin>>units;
  cout<<pn<<"Enter unit size (in oz): ";
  cin>>unit_size;
  cout<<pn<<"Enter case cost: ";
  cin>>case_cost;
  cout<<pn<<"Enter desired portion size (in oz): ";
  cin>>portion_size;
}

float Product::GetPrice()

  return case_cost/(units*unit_size)*portion_size*cost_mult;
}

void cls()
{
  cout<<"\033[2J\033[1;1H";
}

void welcome_msg()
{
  cout<<"[Food Service Price Calculator]"<<endl;
}

void startup(){
  cls();
  welcome_msg();
}

int main(){
  Product NewProd;
  bool continue_prog = 1;
  char usr_chc;
  startup();

  while(continue_prog){
    NewProd.EnterInfo();
    cout<<pn<<"For a portion size of "<<NewProd.DispPortSize();
    cout<<"oz you should be charging ~$"<<setprecision(2)<<fixed<<NewProd.GetPrice()<<endl;

    cout<<pn<<"Would you like to calculate the price for another product? (Y/n): ";
    cin>>usr_chc;

    switch(usr_chc)
    {
      case 'Y' | 'y':
        break;
      case 'n' | 'N':
        continue_prog = 0;
        break;
      default:
        cerr<<er<<"Invalid input. Exiting..."<<endl;
        exit(3);
    };
  }

  return 0;
}
