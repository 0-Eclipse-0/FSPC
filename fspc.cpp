#include <iostream>
#include <iomanip>

using namespace std;

const string pn = "[FSPC] ";
const string er = "[ERR] ";
const int cost_mult = 3; // Default cost multiplier (Usually 3x in food industry)

void bad_inp(int type){
  switch(type)
  {
    case 1:
      cerr<<er<<"Invalid input..."<<endl;
      break;
    case 2:
      cerr<<er<<"Invalid input. Exiting..."<<endl;
      break;
    default:
      cerr<<er<<"Invalid input..."<<endl;
      break;
  }
}

class Product
{
  public:
    void EnterInfo();
    int DispPortSize()
    {
      return portion_size;
    }
    float GetPrice();
    int GetNumPort();
  private:
    int units;
    int unit_size;
    float case_cost;
    int portion_size;
};

void Product::EnterInfo()
{
  cout<<pn<<"Enter the number of units per case (i.e. bags): ";
  while((!(cin >> units)) | (units <= 0)){
    bad_inp(1);
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cout<<pn<<"Enter the number of units per case (i.e. bags): ";
  }

  cout<<pn<<"Enter the (per) unit size (in oz): ";
  while((!(cin >> unit_size)) | (unit_size <= 0)){
    bad_inp(1);
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cout<<pn<<"Enter the (per) unit size (in oz): ";
  }

  cout<<pn<<"Enter the cost per case: ";
  while((!(cin >> case_cost)) | (case_cost <= 0)){
    bad_inp(1);
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cout<<pn<<"Enter the cost per case: ";
  }

  cout<<pn<<"Enter the desired portion size (in oz): ";
  while((!(cin >> portion_size)) | (portion_size <= 0)){
    bad_inp(1);
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    cout<<pn<<"Enter the desired portion size (in oz): ";
  }
}

float Product::GetPrice()
{
  return case_cost/(units*unit_size)*portion_size*cost_mult;
}

int Product::GetNumPort()
{
  return (units*unit_size)/portion_size;
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
    cout<<"oz you should be charging ~$"<<setprecision(2)<<fixed<<NewProd.GetPrice();
    cout<<" per sale \nwith a total of ~"<<NewProd.GetNumPort();
    cout<<" available portions per case!"<<endl;

    cout<<pn<<"Would you like to calculate the price for another product? (Y/n): ";
    cin>>usr_chc;

    switch(usr_chc)
    {
      case 'Y': case 'y':
        break;
      case 'n': case 'N':
        continue_prog = 0;
        break;
      default:
        bad_inp(2);
        exit(3);
    };
  }

  return 0;
}
