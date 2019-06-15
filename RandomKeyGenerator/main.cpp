#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <set>
#include <algorithm>  
#include <iostream>

using namespace std;

const int simulations = 1000;
const int hashSize = 100;
const int numberOfKeys = 100;
const int minKeyLength = 4;
const int maxKeyLength = 20;
const string validKeyChars = "1234567890qwertyuiopasdfghjklzxcvbnm";
const bool uniqueKeys = true;

int keyLength;
int hashCollisionArray[hashSize];
set<string> keys;
vector<string> data;
string publicKey;

string generateKey(int minLen, int maxLen);
string generateKey(int len);
int hashFunction(string masterKey, string key, int hashSize);
void readData();
void simulate();
void generateTestData();

int main(){
    
    /*
        THIS PROGRAM DOES A FEW THINGS
            - produces a list of unique keys or not
            - offers statistics on hashing 
    */

    
    readData();
    //simulate();
    generateTestData();

}

void simulate(){
    
    srand(time(NULL));
    
    double avgcol = 0;
    double avgstd = 0;
    for(int k = 0; k < simulations; k++){
        
        
        int collisions = 0;
        int hashCollisionArray[hashSize] = {0}; //resets values to 0
        publicKey = generateKey(maxKeyLength);
        //cout << "generating " << numberOfKeys 
        //<< " keys with public key " << publicKey << endl;
        
        ofstream fout;
        fout.open("keys.txt");

        
        for(int i = 0; i < numberOfKeys; i++){
            string key = generateKey(minKeyLength, maxKeyLength);
            while(keys.count(key) != 0 and uniqueKeys){
                key = generateKey(minKeyLength, maxKeyLength);
            }
            hashCollisionArray[hashFunction(publicKey, key, hashSize)] += 1;
            keys.insert(key);
            fout << key <<  endl;
        } 
    
        fout.close();
        
        //how good was our hashing algorithm?
        double sum = 0;
        //cout << "[";
        for(int i : hashCollisionArray){
            if(i > 1){
                collisions += i - 1;
            }
            sum += pow(i - numberOfKeys/hashSize ,2);
            //cout << i << ", ";
        }
        avgstd += sqrt(sum / (numberOfKeys - 1));
        avgcol += collisions;
        //cout << "] \t" ;
        //cout << "standard deviation of " << sqrt(sum / (numberOfKeys - 1)) << endl;
        //cout << "had " << collisions << " collisions" << endl;
    }
    
    avgstd /= simulations;
    avgcol /= simulations;
    
    cout << "average standard deviation is " << avgstd << endl;
    cout << "average number of collisions is " << avgcol << endl;
}

void generateTestData(){
        
    srand(time(NULL));

    ofstream fout;
    fout.open("../hashdata.txt");

    for(int i = 0; i < numberOfKeys; i++){
        string key = generateKey(minKeyLength, maxKeyLength);
        while(keys.count(key) != 0 and uniqueKeys){
            key = generateKey(minKeyLength, maxKeyLength);
        }
        hashCollisionArray[hashFunction(publicKey, key, hashSize)] += 1;
        keys.insert(key);
        fout << key <<"\t" << data.at(rand() % data.size()) <<  endl;
    } 

    fout.close();
}

string generateKey(int minLen, int maxLen){
    keyLength = rand() % (maxLen - minLen) + minLen;
    string key = "";
    for(int j = 0; j < keyLength; j++){
        key += validKeyChars[rand() % validKeyChars.length()];
    }
    return key;
}
string generateKey(int len){
    keyLength = len;
    string key = "";
    for(int j = 0; j < keyLength; j++){
        key += validKeyChars[rand() % validKeyChars.length()];
    }
    return key;
}
int hashFunction(string masterKey, string key, int hashSize){
    int result = 0;
    for(int i = 0; i < key.length(); i++){
        result += ((int)masterKey[i]) * ((int)key[i]);
    }
    return result % hashSize;
}
void readData(){
    ifstream fin("gibbon.txt");
    istream& in = fin;
    string s;
    while (!in.eof()) {
        in >> s;
        s.erase(remove_if(s.begin(), s.end(), [](char c) { return !isalpha(c); } ), s.end());
        //word.erase(std::remove_if(word.begin(), word.end(),(int(*)(int))std::isalnum), word.end());
        data.push_back(s);
    }
    fin.close();
}