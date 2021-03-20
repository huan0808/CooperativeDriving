#include <iostream>
#include <bitset>
using namespace std;


//convert int or hex to bitset then output the string of binary
int main()
{
    bitset<11> bs = 6000;
    //cout<< bs.to_string() << endl;
    string s = bs.to_string();
    //cout<< a <<endl;

    //cout << hex << 0b010101 << endl; 
    cout << s << endl;


}