//Encryption program
//Programmer: Jake Carrico
//This program takes a message and applies assignes each ascii value to a different ascii value using a linear shift algorithm 

#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int gcf(int a, int b); //returns the greatest common factor between two integers
void swap(int &x, int &y); //returns two integers in the opposite order they were sent
char encrypt(int a, int b, char c); //encrypts the message

int main(){
    int a, b; //a and b are the variables that the user will input to generate the encryption
    int n = 128; //n is hard-coded at 128 because that is the maximum ascii value
    char c; //testing character
    ifstream infile;
    infile.open("message.txt", ios::in); //takes in the file "message.text"
    ofstream outfile;
    outfile.open("encryption.txt", ios::out); //creates an output file "encryption.text"
    do{
        cout << "Input a positive number relatively prime with 128" << '\n';
        cout << "and a positive number that is less than 128" << '\n';
        cin >> a >> b;
        cout << '\n';
        if(gcf(a,n) != 1){ //if a and n are not relatively prime an error message appears
            cout << "The first number must be relatively prime with 128. Try again." << '\n' << '\n';
        }
        if(b > 128){ //if b is greater than 128 an error message appears
            cout << "The second number must be less than 129. Try again." << '\n' << '\n';
        }
        if(a == 117 && b == 69){
            cout << "For some reason, this combination doesn't work. Try again." << '\n' << '\n';
        }
        if(a == 69 && b == 117){
            cout << "For some reason, this combination doesn't work. Try again." << '\n' << '\n';
        }
    }
    while(gcf(a,n) != 1 || b > 128 || (a == 117 && b == 69) || (a == 69 && b == 117));
                                      //if a and n are not relatively prime OR b is greater than 128, the
                                      //algorithm will not work, so the user is re-prompted for new variables
    while(infile.get(c) && !infile.eof()){
        outfile << encrypt(a,b,c); //sends the character and user inputted numbers to be encrypted
        cout << encrypt(a,b,c);
    }
    return 0;
}

int gcf(int a, int b){
    if(b>a){ //makes sure a is greater than b
    swap(a,b);
    }
    while(b != 0){ //algorithm for greatest common factor
        int r;
        r = a%b;
        a=b;
        b=r;
    }
    return a; //returns greatest common factor
}
void swap(int &x, int &y){ //swaps the values of two variables
    int z;
    z=x;
    x=y;
    y=z;
}
char encrypt(int a, int b, char c){
    int n=128; //n is hard-coded at 128 based on the ascii table
    char t;
    t = (c*a+b)%n; //encrypting algorithm used to generate new character associations
    return t; //returns the new encrypted character
}
