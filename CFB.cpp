// Sonia Kedzierska

#include <iostream>
#include <fstream>
#include "std_lib_facilities.h"

using namespace std;

string ifile = "tekst.txt";
string ofile = "zaszyfrowany_tekst.txt";
string klucz = "ramionka";
char text;
int i, j;
int c = 0;
int d = 1;
vector<int> k;
vector<int> t;
vector<int> o;
vector<int> v;
vector<int> p;

void f() {
    ifstream ist {"tekst.txt"};
    if (!ist) error("can't open input file", ifile);
    ofstream ost {"zaszyfrowany_tekst.txt"};
    if (!ist) error("can't open input file", ofile);
    int a[64], i;
    for(char& text : klucz) {
        for(i=0; i < 8; i++){
            a[i] = text%2;
            text = text/2;
        }
        for(i=i-1; i >= 0 ;i--){
            k.push_back(a[i]);
        }
    }

     for (int i = 0; i< 64; i++) {
        int b = rand() % 2;
        v.push_back(b);
    }

    while (ist >> text) {
        if (!ist.eof()) {
            for(j = 0; j < 8; j++) {
                if(v[j] == k[j]) {
                    p.push_back(c);
                } else if (v[j] != k[j]) {
                    p.push_back(d);
                    }
            }
            for(i=0; i < 8; i++){
                a[i] = text%2;
                text = text/2;
            }
            for(i=i-1 ;i >= 0 ;i--){
                t.push_back(a[i]);
            }
            if (t.size() % 64 != 0) {
                t.resize(t.size() + (64 - (t.size() % 64)));
                t.push_back(c);
            }
            for(j = 0; j < 8; j++) {
                if(p[j] == t[j]) {
                    o.push_back(c);
                } else if (p[j] != t[j]) {
                    o.push_back(d);
                }
            }
            for(i=0; i<8; i++) {
                ost << o[i];
            }
            for(i=0; i<8; i++) {
                v[i]=o[i];
            }
        }
    }
}

int main()
{
    f();
    return 0;
}

