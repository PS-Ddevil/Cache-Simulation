#include <iostream>
#include <fstream> 
#include <string>
#include <iomanip>
#include <bits/stdc++.h>
#include <queue>
#include <algorithm>

using namespace std;

int mod_val(unsigned int a, int z){
    return a%z;
}

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
        // cout << mod_val(x) << endl;
        // cout << line << endl;
        if((cache[mod_val(x,z)] == 1) && (data[mod_val(x,z)] == x/ws)){
            hit++;
            // cout << line << endl;
            cache[mod_val(x,z)] = 1;
            // data[mod_val(x,z)] = line;
        }else{
            cache[mod_val(x,z)] = 1;
            data[mod_val(x,z)] = x/ws;
        }
    }
    fin.close();
    return hit;
}

int setassoc_fifo(int z, int w){
    int ws = 16*w;
    ifstream fin; 
    string line;
    fin.open("address.txt");
    std::list<int> *cache = new std::list<int>[z/4];
    // vector <list <string>> cache;
    // std::list<int> m[]
    // cache.resize(z/4);
    // cout << cache.size();
    // for(int i = 0; i < z/4; i++)cache[i].resize(4);
    // for(int i = 0; i < z/4; i++)cout << cache[i].size() << endl;
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
        // cout << z/4;
        // cout << line << ' ';
        // cout << index << ' ';
        // cout << cache[index].size() << ' '; 
        if(std::find(cache[index].begin(), cache[index].end(), x/ws) != cache[index].end()){
            hit++;
        }else if(cache[index].size() < 4){
            cache[index].push_front(x/ws); 
        }else if(cache[index].size() == 4){
            cache[index].pop_back();
            cache[index].push_front(x/ws); 
        }
        // cout << hit << '\n';
    }
    // cout << "\n\n";
    return hit;
}

int setassoc_lru(int z, int w){
    int ws = 16*w;
    ifstream fin; 
    string line;
    fin.open("address.txt");
    std::list<int> *cache = new std::list<int>[z/4];
    // vector <list <string>> cache;
    // std::list<int> m[]
    // cache.resize(z/4);
    // cout << cache.size();
    // for(int i = 0; i < z/4; i++)cache[i].resize(4);
    // for(int i = 0; i < z/4; i++)cout << cache[i].size() << endl;
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
        // cout << z/4;
        // cout << line << ' ';
        // cout << index << ' ';
        // cout << cache[index].size() << ' '; 
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
        // cout << hit << '\n';
    }
    // cout << "\n\n";
    return hit;
}

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