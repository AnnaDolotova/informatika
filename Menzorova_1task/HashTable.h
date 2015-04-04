#include "string.h"
#include <iostream>

using namespace std;

class HashTable {
private:
    
    int max_table_size;
    int count; // количество элементов в массиве
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
    
    //это функция добалвеня элемента, она вернёт false, если таблица переполнена, и вернёт true, если элемент удлалось добавить.
    bool addelement(char* string)
    {
        if (count == max_table_size) {
            cout << "Таблица переполнена" << endl;
            return false;
        }
        
        int hash_element = hashfunction(string) % max_table_size;
        for(int i = 0; i < max_table_size; i++){
			cout << "I:" << i << " hash_element:" << hash_element << endl;
            if (hashtable[hash_element]==0) {
                hashtable[hash_element] = string;
                count++;
				cout << "Элемент успешно добавлен!" << endl;
				return true;
            }
			 if (hashtable[hash_element]==(char*)0x1){
                hashtable[hash_element] = string;
                count++;
				cout << "Элемент успешно добавлен!" << endl;
				return true;
            }
            else {
                hash_element = (hash_element + 1) % max_table_size;
            }
        }
        cout << "нет!" << endl;
        return false;
    }
    
    //функция удаления элемета. Если элемент
    int deleteelement (char* string)
    {
        int res = Innerfind(string);
        if(res == -1){
            cout << "Удаляемый элемент не найден!" << endl;
            return -1;
        }
        hashtable[res] = (char*)0x1;
        cout << "Удаление произошло успешно!"<< endl;
        return 1;
    }
    int findelement(char* string){
        int index = Innerfind(string);
        
        if(index == -1){
            cout << "Элемент не найден!" << endl;
            return -1;
        }
         cout << "Такой элемент есть!" << endl;
        return 1;
    }
    
};
