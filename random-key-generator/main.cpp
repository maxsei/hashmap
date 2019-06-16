#include <iostream>
#include <fstream>
#include <vector>
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
int hashFunction(string masterKey, string key, int n);
void readData(std::string text);
void simulate();
void generateTestData();

int main(){
    
    /*
        THIS PROGRAM WILL:
            - produce a list of unique keys
            - offer summary statistics on hashing 
    */
    
    readData("gibbon.txt");
    simulate();
    generateTestData();

}

void simulate(){
    
    srand(time(NULL));
    
    double collisionMean = 0;
    double collisionStd = 0;
    for(int k = 0; k < simulations; k++){
        
        
        int collisions = 0;
        int hashCollisionArray[hashSize] = {0};
        publicKey = generateKey(maxKeyLength);
        
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
        
        /* how good was our hashing algorithm? */
        double sum = 0;
        for(int i : hashCollisionArray){
            if(i > 1){
                collisions += i - 1;
            }
            sum += pow(i - numberOfKeys/hashSize ,2);
        }
        collisionStd += sqrt(sum / (numberOfKeys - 1));
        collisionMean += collisions;
    }
    
    collisionStd /= simulations;
    collisionMean /= simulations;
    
    cout << "standard deviation per simulation: " << collisionStd << endl;
    cout << "mean number of collisions per simulation:  " << collisionMean << endl;
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

/* generateKey will generate a random string of characters of random length that
varies between the two specified bounds */ 
string generateKey(int minLen, int maxLen){
    keyLength = rand() % (maxLen - minLen) + minLen;
    string key = "";
    for(int j = 0; j < keyLength; j++){
        key += validKeyChars[rand() % validKeyChars.length()];
    }
    return key;
}

/* generateKey will generate a random key of a given length */
string generateKey(int len){
    keyLength = len;
    string key = "";
    for(int j = 0; j < keyLength; j++){
        key += validKeyChars[rand() % validKeyChars.length()];
    }
    return key;
}

/* hashFunction will take two keys and hash the two keys together within a given 
size of the hash ranging from 0, n - 1 */
int hashFunction(string masterKey, string key, int n){
    int result = 0;
    for(int i = 0; i < key.length(); i++){
        result += ((int)masterKey[i]) * ((int)key[i]);
    }
    return result % n;
}

/* readData will read read in the name of a given text file */
void readData(string text){
    ifstream fin(text);
    istream& in = fin;
    string s;
    while (!in.eof()) {
        in >> s;
        s.erase(remove_if(s.begin(), s.end(), [](char c) { return !isalpha(c); } ), s.end());
        /* word.erase(std::remove_if(word.begin(), word.end(),(int(*)(int))std::isalnum), word.end()); */
        data.push_back(s);
    }
    fin.close();
}
