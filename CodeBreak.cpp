//CodeBreak program
//Programmer: Jake Carrico
//This program decrypts the encrypted message without needing to know the a and b values in the algorithm

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

char encrypt(int a, int b, char c); //runs the linear encryption algorithm
bool run_filters(vector<char> a); //runs all filters
bool filter1(vector<char> a); //non-printable filter
bool filter2(vector<char> a); //space filter
bool filter3(vector<char> a); //'q' filter
bool filter4(vector<char> a); //vowel filter
bool filter5(vector<char> a); //punctuation filter

int main(){
    char c; //temp variable
    int d=0; //will serve as a ticker to count the number of final candidates
    ifstream infile;
    infile.open("encryption.txt", ios::in); //reads encrypted message
    ofstream outfile;
    outfile.open("codebreak.txt", ios::out); //outputs into codebreak message
    vector<char> key(128, '~'); //used to develop a key for each ascii value given an a and b
    vector<char> data(128, '~'); //will hold all ascii values
    vector<char> message(1, '~'); //will hold the encrypted message given a and b
    for(int i=0; i < 128; i++){ //"data" is made
        data[i] = i;
    }
    for(int a=1; a<128; a+=2){ //every value of a is checked
        for(int b=1; b<128; b++){ //every value of b is checked
            for(int x=0; x < 128; x++){ //"key" is made
                c = data[x];
                key[x] = encrypt(a,b,c);
            }
            infile.clear(); //resets pointer to the beginning of the infile
            infile.seekg(0); //resets pointer to the beginning of the infile
            while(infile.get(c)){ //reads whole file
                for(int t=0; t < 128; t++){ //checks every character in key for a match
                    if(c == key[t]){ //when it finds the match,
                        char q = data[t]; //it sets the character equal to the correspond  original ascii
                        message.push_back(q); //increases message vector by 1 and fills it with the decrypted character
                    }
                }
            }
            if(run_filters(message) == true){ //runs each candidate through all filters
                for(int r=0; r<message.size(); r++){ //if it passes all filters, this displays the message
                    outfile << message[r];
                    }
            outfile << '\n' << '\n' << "a=" << a << "     b=" << b; //displays the a and b value corresponding to the message
            outfile << '\n' << "-------------------------------------------------------" << '\n' << '\n'; //displays separator
            d++; //increases the "number of possibilities" value
            }
            message.clear();//clears the contents of message so it can be refilled
        }
    }
    outfile << "Number of possibilities: " << d; //after all a and b values are checked, this displays the total number of possible messages
    return 0;
}

char encrypt(int a, int b, char c){ //runs the encrypt algorithm
    int n=128;
    char t;
    t = (c*a+b)%n;
    return t;
}

bool run_filters(vector<char> a){ //runs all filters on each candidate
    if(filter1(a) == true && filter2(a) == true && filter3(a) == true && filter4(a) == true && filter5(a) == true){
        return true;
    }
    return false;
}

bool filter1(vector<char> a){ //filters out codes with non printable values (ascii below 32)
    for(int i=0; i<a.size(); i++){
        if((a[i] >= 1 && a[i] <= 8) || (a[i] >= 11 && a[i] <= 31) || (a[i] == 127)){
            return false;
        }
    }
    return true;
}

bool filter2(vector<char> a){ //filters out codes that don't contain a space
    for(int i=0; i<a.size(); i++){
        if(a[i] == 32){
            return true;
        }
    }
    return false;
}

bool filter3(vector<char> a){ //filters out codes that have a 'q' that isn't followed by a 'u'
    for(int i=0; i<a.size()-1; i++){
        if((a[i] == 'q' || a[i] == 'Q') && (a[i+1] != 'u') && (a[i+1] != 'U')){
                return false;
        }
    }
    return true;
}

bool filter4(vector<char> a){ //filters out codes that do not have vowels in them at all
    for(int i=0; i<a.size(); i++){
        if(a[i] == 'a' || a[i] == 'e' || a[i] == 'i' || a[i] == 'o' || a[i] == 'u' || a[i] == 'A' || a[i] == 'E' || a[i] == 'I' || a[i] == 'O' || a[i] == 'U'){
            return true;
        }
    }
    return false;
}

bool filter5(vector<char> a){ //filters out codes that have incorrect uses of symbols
    for(int i=0; i<a.size()-1; i++){
        if((a[i] == '?' || a[i] == '!' || a[i] == '.') && (a[i+1] != ' ' && a[i+1] != 10)){ //filters out codes that don't have spaces after punctuation
            return false;
        }
        if((a[i] == '$' || a[i] == '#') && (a[i+1] != '0' && a[i+1] != '1' && a[i+1] != '2' && a[i+1] != '3' && a[i+1] != '4'
                                        &&  a[i+1] != '5' && a[i+1] != '6' && a[i+1] != '7' && a[i+1] != '8' && a[i+1] != '9')){
            return false; //filters out codes that do not have numbers after a '$' or a '#'
        }
        if(a[i] == '`' || a[i] == '|' || a[i] == '^' || a[i] == 92 || a[i] == '*' || a[i] == '[' || a[i] == ']' || a[i] == '@' || a[i] == '~'){

            return false; //filters codes that have certain symbols such as: `, ^, ~ and *
        }
    }
    return true;
}
