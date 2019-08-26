#include <iostream>
#include <string>

using namespace std;

// Generates a random alphabetic string
int main(){
    int MAX = 64;
    int loop = 10;
    srand(time(NULL));
    string res = "";
    for(int i = 0; i < loop; i++){
        char v = char((rand() % 26) + 97);
        // res += (isalnum(v)) ? v : "";
        res += v;
    }
    cout << res << endl;
}
