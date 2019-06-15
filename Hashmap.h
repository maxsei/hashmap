#ifndef _Hashmap_h
#define _Hashmap_h

#include <cstdlib>
#include <iostream>
#include <string>

class node {
public:
    std::string key;
    std::string data;
    node* next;
};

class Hashmap{
    
    public:
    
    //constructors
    Hashmap();
    Hashmap(int cap);
    //doers
    void insert(std::string key, std::string data); //will not overwrite duplicates
    void emplace(std::string key, std::string data); //will overwrite duplicates
    void erase(std::string key); //removes object at key
    
    //getters
    std::string at(std::string key); //returns data at key
    node* find(std::string key); //returns pointer to where key is else returns pointer.end()
    
    int getBucketCount();
    int getCapacity();
    int getElementCount();
    std::string getPublicKey();
    
    private:
    
    int hashFunction(std::string key);   //runs key through hash to get array value
    void generateKey(int len);      //used at start and when passed in keys exceed _key_length
    
    std::string _key = "";
    std::string _validKeyChars = "_1234567890qwertyuiopasdfghjklzxcvbnm";
    int _capac = 16;
    int _elements = 0;
    int collisions = 0;
    
    node* _data[16] = {NULL};
    
};

#endif