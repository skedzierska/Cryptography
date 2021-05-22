// Sonia Kedzierska

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "std_lib_facilities.h"
#include <sstream>

using namespace std;

vector<int> klucz_Alicji;
vector<int> klucz_Boba;
vector<int> klucz_Ewy;
vector<int> kluczAE;
vector<int> kluczEB;

string tekst1 = "ala ma kota";
string tekst2 = "ala wcale nie ma kota";

int p = 11;
int g = 3;

vector<int> aA;
vector<int> aB;
vector<int> aE;

vector<int> k1;
vector<int> k2;
vector<int> t1;
vector<int> t2;

void generowanie_pubklucza(vector<int>& v, vector<int>& l, int p, int g) {
    for (int i = 0; i<8; i++) {
        int a = randint(1,20);
        l.push_back(a);
        int A = ((long long int)pow(g,a)) % p;
        v.push_back(A);
    }
    for (int i = 0; i<v.size(); i++) {
        cout << v[i];
    }
}

void generowanie_privklucza(vector<int>& v1, vector<int>& v2, vector<int>& a, int p) {
    for(int i = 0; i<8; i++) {
        int k = ((long long int)pow(v1[i],v2[i])) % p;
        a.push_back(k);
    }
    for (int i = 0; i<a.size(); i++) {
        cout << a[i];
    }
}

void key_to_bin(vector<int>& v1, vector<int>& v2) {
    stringstream ss;
    for (size_t i = 0; i<v1.size(); i++) {
        ss << v1[i];
    }
    string s = ss.str();
    int a[64];
    for (char& c : s) {
        for(int i=0; i < 8; i++){
            a[i] = c%2;
            c = c/2;
        }
        for(int i=7; i >= 0 ;i--){
            v2.push_back(a[i]);
        }
    }
}

string padding(string tekst) {
    if (tekst.size() % 8 != 0) {
        int a = 8 - (tekst.size() % 8);
        tekst.append(a, '0');
    }
    return tekst;
}

void cbc(string s, vector<int>& v1, vector<int>& v2) {
    vector<int> o;
    vector<int> v;
    vector<int> p;
    cout << "Zaszyfrowany tekst: ";
    int i, j = 0;
    for(char& txt : s) {
        int a[8];
        for(i=0; i < 8; i++){
            a[i] = txt%2;
            txt = txt/2;
        }
        for(i=7; i >= 0; i--){
            v1.push_back(a[i]);
        }
    }
    for (i = 0; i<64; i++) {
        int b = rand() % 2;
        v.push_back(b);
    }
    for(i = 0; i<v1.size(); i++) {
        if(j == 64) {
            j = 0;
        }
        if(v1[i] == v[j]) {
            p.push_back(0);
        } else {
            p.push_back(1);
        }
        j++;
    }
    for(i = 0; i<p.size(); i++) {
        if(j == 64) {
            j = 0;
        }
        if(p[i] == v2[j]) {
            o.push_back(0);
        } else {
            o.push_back(1);
        }
        j++;
    }
    for (int i = 0; i<o.size(); i++) {
        cout << o[i];
    }
    cout << endl;
}

int main()
{
    cout << "Klucz, ktory wysyla Alicja Bobowi, a otrzymuje go Ewa: ";
    generowanie_pubklucza(klucz_Alicji, aA, p, g);
    cout << endl;
    cout << "Klucz, ktory generuje Ewa i wysyla go do Boba: ";
    generowanie_pubklucza(klucz_Ewy, aE, p, g);
    cout << endl;
    cout << "Klucz, ktory Bob przekazuje Ewie, myslac, ze wysyla go Alicji: ";
    generowanie_pubklucza(klucz_Boba, aB, p, g);
    cout << endl;
    cout << "Ewa wysyla swoj klucz Alicji";
    cout << endl;
    cout << endl;

    cout << "Wspolny sekretny klucz Alicji i Ewy: ";
    generowanie_privklucza(klucz_Alicji, aE, kluczAE, p);
    cout << endl;
    cout << "Wspolny sekretny klucz Ewy i Boba: ";
    generowanie_privklucza(klucz_Ewy, aB, kluczEB, p);
    cout << endl;
    cout << endl;

    cout << "Tekst wyslany przez Alicje: " << tekst1 << endl;
    tekst1 = padding(tekst1);
    key_to_bin(kluczAE, k1);
    cbc(tekst1, t1, k1);
    cout << endl;
    cout << "Tekst otrzymany przez Boba: " << tekst2 << endl;
    tekst2 = padding(tekst2);
    key_to_bin(kluczEB, k2);
    cbc(tekst2, t2, k2);
    return 0;
}
