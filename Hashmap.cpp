#include "Hashmap.h"
#include <stdexcept> 

using namespace std;

Hashmap::Hashmap(){
    Hashmap::generateKey(32);
}
Hashmap::Hashmap(int cap){
    Hashmap::generateKey(32);
    _capac = cap;
    _data[cap] = {NULL};
}
/* destructor */
/* Hashmap::~Hashmap(){ */
/* 	cout << "ok" << endl; */
/* 	delete[] _data; */
/* } */
/* TODO: put copy, and assignment */

/* 
 * PUBLIC METHODS 
 */

/* Insert will insert a key value string into a hashmap if the key does not
 * already exist */
void Hashmap::Insert(string k, string v){ 
    
    node* inNode = new node();
    inNode->key = k;
    inNode->data = v;
    
    int loc = hashFunction(k);
    node* hashNode = _data[loc];
    
    if(hashNode == NULL){
        _data[loc] = inNode;
        _elements++;
        return;
    }
    
    while(hashNode->next != NULL){
        if(hashNode->key == k){
            return;
        }else{
            hashNode = hashNode->next;
        }
    }
    
    _elements++;
    hashNode->next = inNode;
    
}

/* Emplace will attempt to create or overwrite a given key value pair */
void Hashmap::Emplace(string k, string v){
    
}

/* Erase will remove the node with a given key from the hashmap */
void Hashmap::Erase(string k){

}

/* At returns the data for a given key otherwise it will return null and throw an error */
std::string Hashmap::At(std::string k){
    int loc = hashFunction(k);
    node* hashNode = _data[loc];
    
    while(hashNode != NULL){
        if(hashNode->key == k){
            return hashNode->data;
        }
    }
    std::cerr << "Out of Range error: " << endl;
    return NULL;
}
int Hashmap::GetBucketCount(){
    return sizeof(_data);
}
int Hashmap::GetCapacity(){
    return _capac;
}
int Hashmap::GetElementCount(){
    return _elements;
}
/*
 * PRIVATE METHODS
 */

/* find returns pointer to the node of a given key otherwise find returns 
 * pointer.end() */
node* Hashmap::find(string key){
    int loc = hashFunction(key);
    node* hashNode = _data[loc];
    while(hashNode->data != key and hashNode != NULL){
        hashNode = hashNode->next;
    }
    return hashNode;
}
string Hashmap::getPublicKey(){
    return _key;
}
//private mehtods
int Hashmap::hashFunction(string k){
    if(k.length() > _key.length()){
        generateKey(Hashmap::_key.length());
    }
    int result = 0;
    for(int i = 0; i < k.length(); i++){
        result += ((int)_key[i]) * ((int)k[i]);
    }
    return result % _capac;
    return 0;
}
void Hashmap::generateKey(int len){
    srand(time(NULL));
    string k = "";
    for(int j = 0; j < len; j++){
        k += _validKeyChars[rand() % _validKeyChars.length()];
    }
    _key += k;
}
