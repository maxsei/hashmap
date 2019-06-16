#include <iostream>
#include <cstdlib>
#include <stdexcept> 
#include "Hashmap.h"

using namespace std;

int main(){

	/* hashmap default constructor */
	Hashmap h1();
	/* hashmap with a capacity of 10 */
    Hashmap h2(10);
	h2.Insert("foo", "bar");
	string foo;
	foo = h2.At("foo");
	cout << foo << endl;
	/* cout << "ok" << endl; */
}
