//Decrypt program
//Programmer: Jake Carrico
//This program decrypts the encrypted message given that the user knows the a and b values to complete the algorithm

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

char encrypt(int a, int b, char c);

int main(){
    int a, b;
    char c;
    ifstream infile;
    infile.open("encryption.txt", ios::in);
    ofstream outfile;
    outfile.open("decryption.txt", ios::out);
    vector<char> key(128, '~');
    vector<char> data(128, '~');
    cout << "Enter the a and b value for solving the encryption." << '\n';
    cin >> a >> b;
    for(int i=0; i < 128; i++){
        data[i] = i;
    }
    for(int x=0; x < 128; x++){
        c = data[x];
        key[x] = encrypt(a,b,c);
    }
    while(infile.get(c) && !infile.eof()){
        for(int t=0; t <= 128; t++){
            if(c == key[t]){
                char q = data[t];
                outfile << q;
            }
        }
    }
    return 0;
}

char encrypt(int a, int b, char c){
    int n=128;
    char t;
    t = (c*a+b)%n;
    return t;
}
