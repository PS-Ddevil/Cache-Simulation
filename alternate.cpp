#include <iostream>
#include <fstream> 
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
#include <queue>
#include <algorithm>

using namespace std;

//Modulus Function
int mod_val(unsigned int a, int z){
    return a%z;
}

//Direct Addressing
int direct(int z, int w){
    int ws = 16*w;
    ifstream fin; 
    string line;
    fin.open("address.txt"); 
    int cache[z] = {0};
    int data[z] = {-1};
    unsigned int x;
    int hit = 0;
    while(fin) { 
        getline(fin, line); 
        stringstream ss;
        ss << std::hex << line;
        ss >> x;  
        x = x/ws;
        if((cache[mod_val(x,z)] == 1) && (data[mod_val(x,z)] == x/ws)){
            hit++;
            cache[mod_val(x,z)] = 1;
        }else{
            cache[mod_val(x,z)] = 1;
            data[mod_val(x,z)] = x/ws;
        }
    }
    fin.close();
    return hit;
}

//Set Associatin FIFO
int setassoc_fifo(int z, int w){
    int ws = 16*w;
    ifstream fin; 
    string line;
    fin.open("address.txt");
    std::list<int> *cache = new std::list<int>[z/4];
    int index;
    unsigned int x;
    int hit = 0;
    while(fin) {
        getline(fin, line); 
        stringstream ss;
        ss << std::hex << line;
        ss >> x; 
        x = x/ws;
        index = mod_val(x, z/4);
        if(std::find(cache[index].begin(), cache[index].end(), x/ws) != cache[index].end()){
            hit++;
        }else if(cache[index].size() < 4){
            cache[index].push_front(x/ws); 
        }else if(cache[index].size() == 4){
            cache[index].pop_back();
            cache[index].push_front(x/ws); 
        }
    }
    return hit;
}

//Set Association LRU
int setassoc_lru(int z, int w){
    int ws = 16*w;
    ifstream fin; 
    string line;
    fin.open("address.txt");
    std::list<int> *cache = new std::list<int>[z/4];
    int index;
    unsigned int x;
    int hit = 0;
    while(fin) {
        getline(fin, line); 
        stringstream ss;
        ss << std::hex << line;
        ss >> x; 
        x = x/ws;
        index = mod_val(x, z/4);
        if(std::find(cache[index].begin(), cache[index].end(), x/ws) != cache[index].end()){
            hit++;
            cache[index].remove(x/ws);
            cache[index].push_front(x/ws);
        }else if(cache[index].size() < 4){
            cache[index].push_front(x/ws); 
        }else if(cache[index].size() == 4){
            cache[index].pop_back();
            cache[index].push_front(x/ws); 
        }
    }
    return hit;
}

//Main Function
int main(){
    int a[8], b[8], c[8], d[8];
    for(int i = 0; i < 3; i++){
        a[i] = direct(1024*(pow(2,i))/16, 1);
        b[i] = a[i];
        c[i] = setassoc_lru(1024*(pow(2,i))/16, 1);
        d[i] = setassoc_fifo(1024*(pow(2,i))/16, 1);
        a[i+3] = direct(1024*(pow(2,i))/32, 2);
        b[i+3] = a[i+3];
        c[i+3] = setassoc_lru(1024*(pow(2,i))/32, 2);
        d[i+3] = setassoc_fifo(1024*(pow(2,i))/32, 2);
    }
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    cout << "|            \t\t Direct Mapping \t\t\t\t|\t4-Way Set Associative\t\t\t|\n";
    cout << "|\tCache Size\t|\t1024\t|\t2048\t|\t4096\t|\t1024\t|\t2048\t\t|\t4096\t|\n";
    cout << "|\tLRU\t\t|";
    for(int i = 0; i < 3; i++){
        cout << "\t" << a[i] << "\t|";
    }
    for(int i = 0; i < 3; i++){
        cout << "\t" << c[i] << "\t|";
    }
    cout << "\n|\tFIFO\t\t|";
    for(int i = 0; i < 3; i++){
        cout << "\t" << b[i] << "\t|";
    }
    for(int i = 0; i < 3; i++){
        cout << "\t" << d[i] << "\t|";
    }
    return 0;
}