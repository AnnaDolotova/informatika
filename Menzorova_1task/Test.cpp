#include "HashTable.h"
#include <stdio.h>
#include <iostream>

using namespace std;

// My hashfunction
int hashfunction(char* string)
{
    int hash=0;
	for (int i = 0; i < strlen(string); i++)
    {
        hash+=string[i]*10;
    }
    return hash;
}
//For easy checking of all cases, take max_table_size=3
int main() {
    setlocale (LC_ALL,"Russian");
    int max_table_size;
    cout << "Enter the size of the table";
    cin >> max_table_size;
    HashTable *First = new HashTable(max_table_size, *hashfunction);
    
    //Check the addelement function. These elements have the same hash
    First->addelement("asfdae");
    First->addelement("aasfde");
    First->addelement("aaedfs");
    
    //Add two more elements to test an overflow of our hash-table
    First->addelement("lishiy");
    
    //Check the findelement. (remove the middle element to get the unusual case of searching the third element with the same hash
    First->deleteelement("aasfde");
    
    //check the findelement. (unusual case)
    First->findelement("aaedfs");
    
    //check the findelement (usual case)
    First->findelement("asfdae");
    
    //check the findelement (there is no such element)
    First->findelement("hochu_kushat");
    
    // removal of not existing element
    First->deleteelement("hochu_kushat");
	delete First;
	system ("pause");
	return 0;
}
