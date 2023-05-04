#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

class Actor
{
private:
    char* nume_actor;
    int varsta;
public:
    Actor ();
    Actor (char*, int);
    Actor (Actor&);
    ~Actor ();
    void set_nume_actor(char*);
    void set_varsta(int);
    char* get_nume_actor() {return nume_actor;};
    int get_varsta() {return varsta;};
    void afisare(ostream& out);
    void citire(istream &in);
    friend istream& operator>>(istream &in, Actor& a);
    friend ostream& operator<<(ostream&out, Actor& a);
    friend class Teatru;
};
Actor::Actor()
{
    nume_actor = NULL;
    this->varsta = 0;
}
Actor::Actor(char* num, int varsta)
{
    if (num != NULL)
    {
        this->nume_actor = new char[strlen(num)];
        strcpy(nume_actor, num);
    }
    else
        this->nume_actor = num;

    this->varsta = varsta;
}
Actor::Actor(Actor &a)
{
    if (a.nume_actor != NULL)
    {
        this->nume_actor = new char[strlen(a.nume_actor)];
        strcpy(nume_actor, a.nume_actor);
    }
    else
        a.nume_actor = NULL;
    this->varsta = a.varsta;
}
Actor::~Actor()
{
    delete nume_actor;
    this->varsta = 0;
}
void Actor::set_nume_actor(char* num)
{
    nume_actor = new char[strlen(num)];
    strcpy(nume_actor, num);
}
void Actor::set_varsta(int v)
{
    this->varsta = v;
}
void Actor::citire(istream &in)
{
    char s[256];
    cout << "Introduceti numele actorului: " << endl;
    in.get();
    in.getline(s, 256);
    nume_actor = new char[strlen(s) + 1];
    strcpy(nume_actor, s);
    cout << "Introduceti varsta actorului: " << endl;
    in >> varsta;
}
istream& operator>>(istream& in, Actor& a)
{
    a.citire(in);
    return in;
}
void Actor::afisare(ostream& out)
{
    cout << "Numele actorului este: ";
    out << nume_actor;
    cout << "\n";
    cout << "Varsta actorului este: ";
    out << varsta;
}
ostream& operator<<(ostream& out, Actor& a)
{
    a.afisare(out);
    return out;
}

class Teatru
{
private:
    char* denumire_piesa;
    int numar_actori;
    Actor *actori;
    float rating;
public:
    Teatru ();
    Teatru (char*, int, Actor*, float);
    Teatru (Teatru&);
    ~Teatru ();
    void set_denumire_piesa(char*);
    void set_numar_actori(int);
    void set_rating(float);
    char* get_denumire_piesa() {return denumire_piesa;};
    int get_numar_actori() {return numar_actori;};
    float get_rating() {return rating;};
    void afisare(ostream &out);
    void citire(istream &in);
    friend istream& operator>>(istream &in, Teatru &t);
    friend ostream& operator<<(ostream &out, Teatru &t);
    Teatru& operator=(Teatru &t); ///supraincarcarea operatorului de atribuire (doar ca metoda nu ca functie friend)
    friend bool operator<(const Teatru &t1, const Teatru &t2);
    friend bool operator>(const Teatru &t1, const Teatru &t2);
    friend bool operator==(const Teatru &t1, const Teatru &t2);
};
Teatru::Teatru()
{
    denumire_piesa = NULL;
    this->numar_actori = 0;
    for (int i = 0; i < numar_actori; i ++)
    {
        actori[i].nume_actor = NULL;
        actori[i].varsta = 0;
    }
    this->rating = 0;
}
Teatru::Teatru(char* num, int numar_actori, Actor *actori, float rating)
{
    if (num != NULL)
    {
        this->denumire_piesa = new char[strlen(num)];
        strcpy(denumire_piesa, num);
    }
    else
        this->denumire_piesa = num;
    this->numar_actori = numar_actori;
    for (int i = 0; i < numar_actori; i ++)
    {
        actori[i].nume_actor = actori[i].nume_actor;
        actori[i].varsta = actori[i].varsta;
    }
    this->rating = rating;
}
Teatru::Teatru(Teatru &t)
{if (t.denumire_piesa != NULL)
    {
        this->denumire_piesa = new char[strlen(t.denumire_piesa)];
        strcpy(denumire_piesa, t.denumire_piesa);
    }
    else
        this->denumire_piesa = NULL;
    this->numar_actori = t.numar_actori;
    for (int i = 0; i < numar_actori; i ++)
    {
        actori[i].nume_actor = t.actori[i].get_nume_actor();
        actori[i].varsta = t.actori[i].get_varsta();
    }
    this->rating = t.rating;
}
Teatru::~Teatru()
{
    this->denumire_piesa = 0;
    this->numar_actori = 0;
    delete actori;
    this->rating = 0;
}
void Teatru::set_denumire_piesa(char* num)
{
    denumire_piesa = new char[strlen(num) + 1];
    strcpy(denumire_piesa, num);
}
void Teatru::set_numar_actori(int nr)
{
    numar_actori = nr;
}
void Teatru::set_rating(float rt)
{
    rating = rt;
}
void Teatru::citire(istream &in)
{
    char aux[256];
    cout << "Introduceti denumirea piesei: " << endl;
    in.getline(aux, 256);
    denumire_piesa = new char[strlen(aux) + 1];
    strcpy(denumire_piesa, aux);
    cout << "Introduceti numarul actorilor: " << endl;
    in >> numar_actori;
    actori = new Actor[numar_actori];
    for (int i = 0; i < numar_actori; i ++)
    {
        cout << "Informatii privind actorul " << i << endl;
        in >> actori[i];
    }
    cout << "Introduceti ratingul piesei : " << endl;
    in >> rating;
}
istream& operator>>(istream& in, Teatru& t)
{
    t.citire(in);
    return in;
}
void Teatru::afisare(ostream &out)
{
    out << "Denumirea piesei este : " << denumire_piesa << endl;
    out << "Numarul actorilor din piesa este : " << numar_actori << endl;
    out << "Mai jos gasiti numele si varstele actorilor din piesa " << denumire_piesa << endl;
    for (int i = 0; i < numar_actori; i ++)
    {
        out << actori[i] << endl;
    }
    out << "Ratingul piesei este : " << rating << endl;
}
ostream& operator<<(ostream& out, Teatru& t)
{
    t.afisare(out);
    return out;
}
Teatru& Teatru::operator=(Teatru &t)
{
    if (t.denumire_piesa != NULL)
    {
        denumire_piesa = new char[strlen(t.denumire_piesa)];
        strcpy(denumire_piesa, t.denumire_piesa);
    }
    else
        denumire_piesa = NULL;
    numar_actori = t.numar_actori;
    for (int i = 0; i < numar_actori; i ++)
    {
        actori[i].nume_actor = t.actori[i].get_nume_actor();
        actori[i].varsta = t.actori[i].get_varsta();
    }
    rating = t.rating;
}
bool operator<(const Teatru &t1, const Teatru &t2)
{
    return (t1.rating < t2.rating);
}
bool operator>(const Teatru &t1, const Teatru &t2)
{
    return (t1.rating > t2.rating);
}
bool operator==(const Teatru &t1, const Teatru &t2)
{
    return (t1.rating == t2.rating);
}
void menu_output(){
    cout<<"\n Popescu Mircea-Mihail - Proiect 1 - Tema 19: \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Cititi informatii despre n piese de teatru"; cout<<"\n";
    cout<<"2. Afisati informatiile despre cele n piese de teatru citite"; cout<<"\n";
    cout<<"3. Modificati informatiile unei piese de teatru"; cout<<"\n";
    cout<<"4. Comparati doua piese de teatru pe baza ratingului"; cout<<"\n";
    cout<<"0. Iesire."; cout<<"\n";
}
void menu()
{
    int option;///optiunea aleasa din meniu
    option = 0;
    int n = 0;
    Teatru *t;
    do
    {
        menu_output();

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;

        if (option==1)
        {
            cout<<"Introduceti numarul de piese: ";
            cin >> n;
            cin.get();
            ///pentru a elimina ENTER-ul din buffer
            if (n > 0)
            {
                t = new Teatru[n];
                for (int i = 0; i < n; i ++)
                {
                    cin >> t[i];
                    cin.get();
                }

            }
            else
                cout<<"Valoarea n trebuie sa fie pozitiva";
        }
            if (option == 2)
            {
                if (n != 0)
                {
                    for (int i = 0; i < n; i ++)
                        cout << t[i];
                }
            }
            if (option==3)
            {
                int i;
                cout << "Introduceti numarul piesei asupra careia doriti sa faceti modificari" << endl;
                cin >> i;
                cout << "Veti face modificari asupra piesei " << t[i].get_denumire_piesa() << endl;
                cin.get();
                cin >> t[i];
            }
            if (option==4)
            {
                int i, j;
                cout << "Introduceti numerele pieselor pe care doriti sa le comparati" << endl;
                cout << "Numarul primei piese din comparatie: " << endl;
                cin >> i;
                cout << "Ati selectat piesa " << t[i].get_denumire_piesa() << endl;
                cout << "Numarul celei de-a doua piese din comparatie: " << endl;
                cin >> j;
                cout << "Ati selectat piesa " << t[j].get_denumire_piesa() << endl;
                if (t[i].get_rating() > t[j].get_rating()) {
                    cout << "Piesa " << t[i].get_denumire_piesa() << " are rating mai mare";
                }
                else if (t[i].get_rating() < t[j].get_rating()) {
                    cout << "Piesa " << t[j].get_denumire_piesa() << " are rating mai mare";
                }
                else
                    cout << "Piesele " << t[i].get_denumire_piesa() << " si " <<t[j].get_denumire_piesa() << " au acelasi rating";
            }
            if (option==0)
            {
                cout<<"\nEXIT!\n";
            }
            if (option<0||option>4)
            {
                cout<<"\nSelectie invalida\n";
            }
            cout<<"\n";
            system("pause"); ///Pauza - Press any key to continue...
            system("cls");   ///Sterge continutul curent al consolei
        }
        while(option!=0);
    }

int main()
{
    menu();
    return 0;
}

