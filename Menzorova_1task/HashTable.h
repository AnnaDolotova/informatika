#include "string.h"
#include <iostream>

using namespace std;

class HashTable {
private:
    
    int max_table_size;
    int count; // the number of eements in the array
    char** hashtable;
    int (*hashfunction) (char* string);
    
    
    int Innerfind(char* string)
    {
        int hash_element = hashfunction(string) % max_table_size;
        
        for(int i = 0; i < max_table_size; i++){
            if(hashtable[hash_element] == 0){
                return -1;
            }
            if(hashtable[hash_element] == (char*)0x1) {
                hash_element = (hash_element + 1) % max_table_size;
                continue;
            }
            if(strcmp(string, hashtable[hash_element]) == 0){
                return hash_element;
                
            }
            hash_element = (hash_element + 1) % max_table_size;
        }
        
        
        return -1;
    }
    
public:
    HashTable(int max_table_size, int (*hashfunction) (char* string))
    {
        this -> max_table_size = max_table_size;
        this -> hashfunction = hashfunction;
        count = 0;
       hashtable = (char**)calloc(sizeof(char*), max_table_size);
		//char* hashtable[] = new char*[](); 
    }
    
    
    ~HashTable()
    {
        free(hashtable);
		//delete hashtable;
    }
    
    //the function of adding elements, it returns false, if the table is full, and returns true, if the element is able to add.
    bool addelement(char* string)
    {
        if (count == max_table_size) {
            cout << "Table is full" << endl;
            return false;
        }
        
        int hash_element = hashfunction(string) % max_table_size;
        for(int i = 0; i < max_table_size; i++){
			cout << "I:" << i << " hash_element:" << hash_element << endl;
            if (hashtable[hash_element]==0) {
                hashtable[hash_element] = string;
                count++;
				cout << "Element added successfully!" << endl;
				return true;
            }
			 if (hashtable[hash_element]==(char*)0x1){
                hashtable[hash_element] = string;
                count++;
				cout << "Element added successfully!" << endl;
				return true;
            }
            else {
                hash_element = (hash_element + 1) % max_table_size;
            }
        }
     
        return false;
    }
    
    //function of removal
    int deleteelement (char* string)
    {
        int res = Innerfind(string);
        if(res == -1){
            cout << "Deleted element is not found!" << endl;
            return -1;
        }
        hashtable[res] = (char*)0x1;
        cout << "Element deleted successfully!"<< endl;
        return 1;
    }
    int findelement(char* string){
        int index = Innerfind(string);
        
        if(index == -1){
            cout << "Element is not found!" << endl;
            return -1;
        }
         cout << "I found this element!!!" << endl;
        return 1;
    }
    
};
