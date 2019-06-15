#include "Hashmap.h"
#include <stdexcept> 

using namespace std;

//eventually put copy, destructor, and assignment

Hashmap::Hashmap(){
    Hashmap::generateKey(10);
}
Hashmap::Hashmap(int cap){
    Hashmap::generateKey(10);
    _capac = cap;
    _data[cap] = {NULL};
}

//public methods
void Hashmap::insert(string k, string d){ 
    
    int loc = hashFunction(k);
    
    node* inNode = new node();
    inNode->key = k;
    inNode->data = d;
    
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
void Hashmap::emplace(string k, string d){
    
}
void Hashmap::erase(string k){
    
}
string Hashmap::at(std::string k){//maybe a find method that returns pointer would be more effective
    
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
node* Hashmap::find(string key){
    int loc = hashFunction(key);
    node* hashNode = _data[loc];
    while(hashNode->data != key and hashNode != NULL){
        hashNode = hashNode->next;
    }
    return hashNode;
}
int Hashmap::getBucketCount(){
    return sizeof(_data);
}
int Hashmap::getCapacity(){
    return _capac;
}
int Hashmap::getElementCount(){
    return _elements;
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
