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
    
    /* Constructors */
    Hashmap();
    Hashmap(int cap);
	/* destructor */
	/* ~Hashmap(); */

    /* Doers */
	/* will not overwrite duplicates */
    void Insert(std::string key, std::string value); 
	/* /will overwrite duplicates */
    void Emplace(std::string key, std::string value);
	/* removes object at key */
    void Erase(std::string key);
    
    /* Getters */
	/* returns data at key */
    std::string At(std::string key);
    
    int GetBucketCount();
    int GetCapacity();
    int GetElementCount();
    
    private:
    
    std::string getPublicKey();
	/* returns pointer to where key is else returns pointer.end() */
    node* find(std::string key);

	/* runs key through hash to get array value */
    int hashFunction(std::string key);
	/* called at initializtion and when passed in keys exceed _key_length */
    void generateKey(int len);
    
    std::string _key = "";
    std::string _validKeyChars = "_1234567890qwertyuiopasdfghjklzxcvbnm";
    int _capac = 16;
    int _elements = 0;
    
    node* _data[16] = {NULL};
    /* node* _data = new node[16]; */
};

#endif
