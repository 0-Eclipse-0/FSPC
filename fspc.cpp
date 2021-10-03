#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const string pn = "[FSPC] ";
const string er = "[ERR] ";

// bool sonic_mode = 0;
// if(sonic_mode)
// {
//   const int cost_mult = 9;
// }else{
//   const int cost_mult = 3;
// }

const int cost_mult = 3; // Default cost multiplier (Usually 3x in food industry)

void bad_inp(int type){
  switch(type)
  {
    case 1:
      cerr<<er<<"Invalid input..."<<endl;
      break;
    case 2:
      cerr<<er<<"Invalid input. Exiting..."<<endl;
      exit(3);
      break;
    default:
      cerr<<er<<"Invalid input..."<<endl;
      break;
  }
}

class Product
{
  public:
    void EnterInfo(bool out_2_file);
    int DispPortSize()
    {
      return portion_size;
    }
    float GetPrice();
    int GetNumPort();
    void OutFileText(char filename[50]);
  private:
    int units;
    int unit_size;
    float case_cost;
    int portion_size;
    char prod_name[50];
};

void Product::EnterInfo(bool out_2_file)
{
  if(out_2_file){
    cin.ignore();
    cout<<pn<<"Enter the product name: ";
    cin.getline(prod_name, 49);
  }

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

void Product::OutFileText(char filename[50])
{
  ofstream output_file;
  output_file.open(filename, ios::app);
  output_file<<prod_name<<", "<<units<<", $"<<case_cost;
  output_file<<", "<<unit_size<<"oz, "<<portion_size;
  output_file<<"oz, "<<GetNumPort()<<", $"<<setprecision(2);
  output_file<<fixed<<GetPrice()<<endl;
}

void Create_OFile(string filename)
{
  ofstream output_file;

  output_file.open(filename, ios::out | ios::trunc);
  output_file<<"Product Name, Case Size, Case Cost, Unit Size, ";
  output_file<<"Portion Size, Estimated Portions, Estimated Price Per"<<endl;
}

void cls()
{
  cout<<"\033[2J\033[1;1H";
}

void welcome_msg()
{
  cout<<"[Food Service Price Calculator]"<<endl;
}

void startup()
{
  cls();
  welcome_msg();
}

void get_info(bool out_file)
{
  Product NewProd;
  bool continue_prog = 1;
  char usr_chc;
  char filename[50];
  char out_to_which;

  if (out_file) {
    while(1)
    {
      cout<<pn<<"Type '1' to add to an old file and '2' to output to a new file: ";
      cin>>out_to_which;
      if(out_to_which == '1' | out_to_which == '2') {
        break;
      }
      bad_inp(1);
    }

    cout<<pn<<"Enter file name (Max: 50 characters): ";
    cin>>filename;
    strcat(filename, ".csv");

    if(out_to_which == '1')
    {
          ifstream file_exists;
          file_exists.open(filename);
          if(file_exists)
          {
            cout<<pn<<"Outputting to existing <"<<filename<<">..."<<endl;
          } else {
            cout<<pn<<"<"<<filename<<"> does not exist. Creating..."<<endl;
            Create_OFile(filename);
          }
    } else {
          Create_OFile(filename);
    }
  }

while(continue_prog){
    if(out_file){
      NewProd.EnterInfo(1);
    }else{
      NewProd.EnterInfo(0);
    }

    cout<<pn<<"For a portion size of "<<NewProd.DispPortSize();
    cout<<"oz you should be charging ~$"<<setprecision(2)<<fixed<<NewProd.GetPrice();
    cout<<" per sale \nwith a total of ~"<<NewProd.GetNumPort();
    cout<<" available portions per case!"<<endl;

    if(out_file){
      NewProd.OutFileText(filename);
      cout<<pn<<"Information outputted to <"<<filename<<".csv>"<<endl;
    }

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
}

int main(){
  bool valid_inp;
  char usr_chc;

  startup();

  cout<<pn<<"Would you like to output your product information to a file? (Y/n): ";
  cin>>usr_chc;

  if (usr_chc == 'Y' | usr_chc == 'y') {
    get_info(1);
  } else if (usr_chc == 'N' | usr_chc == 'n') {
    get_info(0);
  } else {
    bad_inp(2);
  }

  return 0;
}
