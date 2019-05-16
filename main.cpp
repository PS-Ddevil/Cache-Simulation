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
    int x, y,z,w;
    bool dec;
    cout << "Do you want to print all or Costomised Output (0/1):\n";
    cin >> dec;
    if(dec == 0){
        cout << "\n 16 Bytes \n";
        int a[10], b[10], c[10], d[10];
        for(int i = 0; i < 4; i++){
            a[i] = direct(1024*(pow(2,i))/16, 1);
            b[i] = a[i];
            c[i] = setassoc_lru(1024*(pow(2,i))/16, 1);
            d[i] = setassoc_fifo(1024*(pow(2,i))/16, 1);
            a[i+4] = direct(1024*(pow(2,i))/32, 2);
            b[i+4] = a[i+4];
            c[i+4] = setassoc_lru(1024*(pow(2,i))/32, 2);
            d[i+4] = setassoc_fifo(1024*(pow(2,i))/32, 2);
        }
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "|            \t\t Direct Mapping \t\t\t\t\t\t|\t\t\t4-Way Set Associative\t\t\t\t|\n";
        cout << "|-------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
        cout << "|\tCache Size\t|\t1024\t|\t2048\t|\t4096\t|\t8192\t|\t1024\t\t|\t2048\t|\t4096\t|\t8192\t|\n";
        cout << "|-------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
        cout << "|\tLRU\t\t|";
        for(int i = 0; i < 4; i++){
            cout << "\t" << a[i] << "\t|";
        }
        for(int i = 0; i < 4; i++){
            cout << "\t" << c[i] << "\t|";
        }
        cout << "\n|\tFIFO\t\t|";
        for(int i = 0; i < 4; i++){
            cout << "\t" << b[i] << "\t|";
        }
        for(int i = 0; i < 4; i++){
            cout << "\t" << d[i] << "\t|";
        }
        cout << '\n';
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "\n 32 Bytes \n";
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "|            \t\t Direct Mapping \t\t\t\t\t\t|\t\t\t4-Way Set Associative\t\t\t\t|\n";
        cout << "|-------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
        cout << "|\tCache Size\t|\t1024\t|\t2048\t|\t4096\t|\t8192\t|\t1024\t\t|\t2048\t|\t4096\t|\t8192\t|\n";
        cout << "|-------------------------------------------------------------------------------------------------------------------------------------------------------|\n";
        cout << "|\tLRU\t\t|";
        for(int i = 4; i < 8; i++){
            cout << "\t" << a[i] << "\t|";
        }
        for(int i = 4; i < 8; i++){
            cout << "\t" << c[i] << "\t|";
        }
        cout << "\n|\tFIFO\t\t|";
        for(int i = 4; i < 8; i++){
            cout << "\t" << b[i] << "\t|";
        }
        for(int i = 4; i < 8; i++){
            cout << "\t" << d[i] << "\t|";
        }
        cout << '\n';
        cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        return 0;
    }
    cout << "Select Mapping: (1)Direct Mapped (2)4-way set associative\n";
    cin >> x;
    cout << "Select Replacement Policy: (1)LRU (2)FIFO\n";
    cin >> y;
    cout << "Cache size: (0)All (1)1024 (2)2048 (3)4096 (4)8192\n";
    cin >> z;
    cout << "Block size: (1)16 Bytes (2)32 Bytes\n";
    cin >> w;
    int ws = 16*w;
    if(x == 1){
        if(z == 1) cout << direct(1024/ws, w);
        if(z == 2) cout << direct(2048/ws, w);
        if(z == 3) cout << direct(4096/ws, w);
        if(z == 4) cout << direct(8192/ws, w);
        if(z == 0) {
            int a, b, c, d;
            a = direct(1024/ws, w);
            b = direct(2048/ws, w);
            c = direct(4096/ws, w);
            d = direct(8192/ws, w);
            cout << "-----------------------------------------------------------------------------------------\n";
            cout << "|                             Direct Mapping " << ws; 
            if(y == 1)cout << " LRU ";
            else cout << " FIFO";
            cout << "                                    |\n";
            cout << "|---------------------------------------------------------------------------------------|\n";
            cout << "|\tCache Size\t|\t1024\t|\t2048\t|\t4096\t|\t8192\t|\n";
            cout << "|---------------------------------------------------------------------------------------|\n";
            cout << "|\tHits\t\t|\t" << a << "\t|\t" << b <<"\t|\t" << c << "\t|\t" << d <<"\t|\n";
            cout << "-----------------------------------------------------------------------------------------\n";
        }
    }
    else if(x == 2){
            if(y == 1){
                if(z == 1) cout << setassoc_lru(1024/ws, w);
                if(z == 2) cout << setassoc_lru(2048/ws, w);
                if(z == 3) cout << setassoc_lru(4096/ws, w);
                if(z == 4) cout << setassoc_lru(8192/ws, w);
                if(z == 0) {
                    int a, b, c, d;
                    a = setassoc_lru(1024/ws, w);
                    b = setassoc_lru(2048/ws, w);
                    c = setassoc_lru(4096/ws, w);
                    d = setassoc_lru(8192/ws, w);
                    cout << "-----------------------------------------------------------------------------------------\n";
                    cout << "|                           4-Way Set Associative " << ws << " Bytes"; 
                    if(y == 1)cout << " LRU ";
                    else cout << " FIFO";
                    cout << "                         |\n";
                    cout << "|---------------------------------------------------------------------------------------|\n";
                    cout << "|\tCache Size\t|\t1024\t|\t2048\t|\t4096\t|\t8192\t|\n";
                    cout << "|---------------------------------------------------------------------------------------|\n";
                    cout << "|\tHits\t\t|\t" << a << "\t|\t" << b <<"\t|\t" << c << "\t|\t" << d <<"\t|\n";
                    cout << "-----------------------------------------------------------------------------------------\n";
                }
            }else if(y == 2){
                if(z == 1) cout << setassoc_fifo(1024/ws, w);
                if(z == 2) cout << setassoc_fifo(2048/ws, w);
                if(z == 3) cout << setassoc_fifo(4096/ws, w);
                if(z == 4) cout << setassoc_fifo(8192/ws, w);
                if(z == 0) {
                    int a, b, c, d;
                    a = setassoc_fifo(1024/ws, w);
                    b = setassoc_fifo(2048/ws, w);
                    c = setassoc_fifo(4096/ws, w);
                    d = setassoc_fifo(8192/ws, w);
                    cout << "-----------------------------------------------------------------------------------------\n";
                    cout << "|                          4-Way Set Associative " << ws << " Bytes"; 
                    if(y == 1)cout << " LRU ";
                    else cout << " FIFO";
                    cout << "                          |\n";
                    cout << "|---------------------------------------------------------------------------------------|\n";
                    cout << "|\tHits\t\t|\t1024\t|\t2048\t|\t4096\t|\t8192\t|\n";
                    cout << "|---------------------------------------------------------------------------------------|\n";
                    cout << "|\tCache Size\t|\t" << a << "\t|\t" << b <<"\t|\t" << c << "\t|\t" << d <<"\t|\n";
                    cout << "-----------------------------------------------------------------------------------------\n";
                }
            // cout << (1024/ws);
        }
    }

}