#include <iostream>
#include <stdlib.h>
using namespace std;

class Nod
{
private:
    double coef, expo;
    Nod* urm;

public:
    Nod(); ///constructor de initializare fara parametri
    Nod(double, double); ///constructor de initializare parametrizat
    Nod(Nod&); ///constructor de copiere
    ~Nod(); ///destructor
    double get_expo() { return expo; };
    double get_coef() { return coef; };
    Nod* get_urm() { return urm; };
    void set_coef(double x) { this-> coef = x; };
    void set_expo(double x) { this-> expo = x; };
    void set_urm(Nod &nod) { *(this-> urm) = nod; };

    Nod& operator =(Nod &n); ///supraincarcarea operatorului de atribuire
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator >>(istream &in, Nod& n);  ///supraincarcare pe >>
    friend ostream& operator <<(ostream &out, Nod& n); ///supraincarcare pe <<

    friend class Polinom_dinamic; ///clasa Polinom_dinamic (echivalenta unei clase pentru liste simplu inlantuite, implementata ca friend class pentru
                                        ///accesul facil la membrii clasei Nod
};

Nod::Nod()
{
    this-> coef = 0;
    this-> expo = 0;
}

Nod::Nod(double c, double e)
{
    this-> coef = c;
    this-> expo = e;
}

Nod::Nod(Nod &n)
{
    this-> coef = n.coef;
    this-> expo = n.expo;
    this-> urm = n.urm;
}

Nod::~Nod()
{
    delete this-> urm;
}

void Nod::citire(istream &in)
{
    cout << "Cititi coeficientul: ";
    in >> coef;
    cout << endl << "Cititi exponentul: ";
    in >> expo;
    urm = NULL;
}

istream& operator>>(istream& in, Nod& n)
{
    n.citire(in);
    return in;
}

void Nod::afisare(ostream &out)
{
    out << "Coeficient: " << coef << ", exponent: " << expo << ". Urmatoarea adresa: " << urm;
}

ostream& operator<<(ostream& out, Nod& n)
{
    n.afisare(out);
    return out;
}

Nod& Nod::operator =(Nod &n)
{
    this-> coef = n.coef;
    this-> expo = n.expo;
    this-> urm = n.urm;
}

class Polinom_dinamic
{
private:
    Nod *cap; //nodul de la inceputul listei
    Nod *coada; //nodul de la sfarsitul listei
    int nr_elem; //numarul curent de elemente din polinom
public:
    Polinom_dinamic (); //constructor de initializare fara parametri
    Polinom_dinamic (double, double); //constructor de initializare cu parametri
    ~Polinom_dinamic (); //destructor
    void set_cap (Nod*);
    void set_coada (Nod*);
    void set_nr_elem( int);
    Nod* get_cap () { return cap; };
    Nod* get_coada () { return coada; };
    int get_nr_elem () { return nr_elem; };

    void adauga_nod_opt (double, double); //metoda pentru adaugarea unui nod, cu meniu de optiuni; utilizata (alaturi de functia duplicat) la
                                                //introducerea de monoame in polinom - nu permite existenta a doua noduri cu exponenti egali
    void adauga_nod (double, double); //metoda pentru adaugarea unui nod, fara meniu => permite existenta a doua noduri cu exponenti egali; folosita pentru
                                                //operatiile cu polinoame, alaturi de functia sterge_duplicate
    void adauga_cap (double, double); //metoda pentru adaugarea unui nod pe prima pozitie din lista (cap)
    void adauga_coada (double, double); //metoda pentru adaugarea unui nod pe ultima pozitie din lista (coada)
    void adauga_dupa (Nod*, double, double); //metoda pentru adaugarea unui nod pe o pozitie data - dupa un anume nod
    int duplicat (Nod*, double); //metoda care verifica unicitatea exponentului unui nod de introdus in polinom
    void sterge_duplicate (); //metoda care sterge multiple aparitii ale unui exponent in polinom (prin adunarea coeficientilor)

    void citire (istream &in);
    void afisare (ostream &out);
    friend istream& operator >> (istream &in, Polinom_dinamic& p);  //supraincarcare pe >>
    friend ostream& operator << (ostream &out, Polinom_dinamic& p); //supraincarcare pe <<
    Polinom_dinamic& operator = (Polinom_dinamic &p); //supraincarcarea operatorului de atribuire
    Polinom_dinamic (const Polinom_dinamic&); //constructor de copiere
    friend Polinom_dinamic& operator + (Polinom_dinamic& p1, Polinom_dinamic& p2); //supraincarcare operatorului +
    friend Polinom_dinamic& operator -( Polinom_dinamic& p1, Polinom_dinamic& p2); //supraincarcare operatorului -
    friend Polinom_dinamic& operator * (Polinom_dinamic& p1, Polinom_dinamic& p2); //supraincarcare operatorului *
    double valoare_pct ( double ); //metoda pentru calculul valorii unui polinom intr-un punct dat
};

Polinom_dinamic::Polinom_dinamic()
{
    this-> cap = NULL;
    this-> coada = NULL;
    nr_elem = 0;
}

Polinom_dinamic::Polinom_dinamic(double coef, double expo)
{
    this->adauga_cap(coef, expo);
    this-> nr_elem = 1;
}

Polinom_dinamic::~Polinom_dinamic() ///sterg elementele -nodurile- din lista unul cate unul, de la cap spre coada, asigurandu-ma ca nu
{                                       ///pierd legatura dintre noduri cu ajutorului nodului auxiliar numit urmator
    Nod *urmator;
    while ( cap != NULL )
    {
        urmator = cap->urm;
        delete cap;
        cap = urmator;
    }
    delete cap;
    delete coada;
    this-> nr_elem = 0;
}

void Polinom_dinamic::set_cap( Nod *n )
{
    this-> cap = n;
}

void Polinom_dinamic::set_coada( Nod *n )
{
    this-> coada = n;
}

void Polinom_dinamic::set_nr_elem( int nr )
{
    this-> nr_elem = nr;
}

Polinom_dinamic::Polinom_dinamic ( const Polinom_dinamic &c )
{
    this-> cap = c.cap;
    this-> coada = c.coada;
    this-> nr_elem = c.nr_elem;
}

void Polinom_dinamic::adauga_nod( double coef, double expo )
{
    while ( coef == 0 )        /// verific ca valoarea coeficientului sa fie corecta
    {
        cout << "Coeficientul trebuie sa fie diferit de 0. Dati o valoare nenula: ";
        cin >> coef;
    }
    if ( this-> cap == NULL || this-> cap->expo > expo )
            adauga_cap(coef, expo);

    else if ( this-> coada->expo < expo )
            adauga_coada(coef, expo);
    else ///caut nodul al carui exponent este ultimul din lista mai mic decat exponentul nodului de introdus; apelez functia care adauga
    {           ///un nod nou dupa nodul dorit
        Nod *poz;
        Nod *ant;
        poz = this->cap;
        while ( poz-> expo < expo)
            {
                ant = poz;
                poz = poz->urm;
            }
        adauga_dupa(ant, coef, expo);
    }
}

void Polinom_dinamic::adauga_nod_opt( double coef, double expo )
{
    while ( coef == 0 )
    {
        cout << "Coeficientul trebuie sa fie diferit de 0. Dati o valoare nenula: ";
        cin >> coef;
    }

    if ( this-> cap == NULL || this-> cap->expo > expo )
            adauga_cap(coef, expo);

    else if ( this-> coada->expo < expo )
            adauga_coada(coef, expo);

    else if ( this-> coada->expo == expo )      /// 2 este cazul in care utilizatorul doreste adunarea coeficientilor celor doua noduri; nu se apeleaza
        if ( duplicat(coada, expo) == 2 )        /// nicio functie de adaugare nod, deci variabila nr_elem din obiectul de tip Polinom_dinamic nu va creste;
            this-> coada->coef += coef;          /// totusi, in implementarea aceasta, doua noduri cu exponenti identici ai caror coeficienti se aduna vor fi
        else                                       /// considerati doua intrari separate de noduri (daca, de exemplu, intr-o lista in care se doreste
        {                                          /// citirea a 5 noduri, nod 2 are acelasi exponent cu nodul 1 si se aduna coeficientii celor doua
            double coef2, expo2;                   ///  noduri, urmatorul nod citit este nodul 3, nu se revine asupra citirii a inca un nod "2"
            cout<<"\nIntroduceti noul coeficient: ";    /// ramura else, in cazul in care valoarea returnata de functia duplicat este 1, cere in mod interactiv
            cin>>coef2;                                 /// introducerea unui nod nou
            cout<<"Introduceti exponent: ";
            cin>>expo2;
            adauga_nod_opt(coef2, expo2);
        }
    else        ///adaugarea unui nod dupa un nod dat, in ordinea exponentilor
    {
        Nod *poz;
        Nod *ant;
        poz = this-> cap;
        while ( poz-> expo <= expo)
            {
                ant = poz;
                poz = poz-> urm;
            }
        if ( ant-> expo == expo )
            if ( duplicat(ant, expo) == 2 )
                ant-> coef += coef;
            else
            {
                double coef2, expo2;
                cout<<"Introduceti noul coeficient: ";
                cin>>coef2;
                cout<<"\nIntroduceti exponent: ";
                cin>>expo2;
                adauga_nod_opt(coef2, expo2);
            }
        else adauga_dupa(ant, coef, expo);

    }
}

int Polinom_dinamic::duplicat( Nod* verif, double expo )
{
    int opt = 0;
    while ( opt != 1 && opt != 2 )
    {
        cout << "---Exponentul dat se afla deja in polinom. Alegeti una dintre urmatoarele optiuni: " << endl;
        cout << "1. Introduceti o noua pereche coeficient-exponent." << endl;
        cout << "2. Aduna cei doi coeficienti." << endl;
        cout << "Optiunea aleasa este: ";
        cin >> opt;
        if ( opt != 1 && opt != 2 )
            cout<<"Ati introdus o valoare nepermisa. Introduceti una dintre valorile poibile." << endl << endl;
    }

        return opt;
}

void Polinom_dinamic::adauga_cap( double coef, double expo )
{
    Nod *aux = new Nod;
    aux-> coef = coef;
    aux-> expo = expo;
    if ( this-> cap == NULL )
    {
        aux-> urm = NULL;
        this-> cap = aux;
        this-> coada = aux;
    }
    else
    {
    aux-> urm = cap;
    cap = aux;
    }
    this->nr_elem++;

}

void Polinom_dinamic::adauga_coada( double coef, double expo )
{
    Nod *aux = new Nod;
    aux-> coef = coef;
    aux-> expo = expo;
    aux-> urm = NULL;

    coada-> urm = aux;
    coada = coada-> urm;
    this->nr_elem++;

}

void Polinom_dinamic::adauga_dupa( Nod* a, double coef, double expo )
{
    Nod* aux = new Nod;
    aux-> coef = coef;
    aux-> expo = expo;
    aux-> urm = a->urm;
    a-> urm = aux;
    this->nr_elem++;

}

void Polinom_dinamic::sterge_duplicate()
{
    Nod* ant = this-> get_cap();
    Nod* urmator = ant-> urm;   ///nodul urmator este o copie care urmareste comportamentul nodului ant; "urmator" este nodul imediat dupa ant,
    while( ant-> get_urm() != NULL )    ///cu rol in compararea exponentilor a doua noduri consecutive
    {
        if( ant-> get_expo() == urmator-> get_expo() ) /// verific existenta a doua noduri (care pot fi doar consecutive) cu exponenti egali
        {
            Nod* aux;
            aux = ant-> urm;
            ant-> urm = aux-> urm; /// distrug legatura cu nodul cu exponent duplicat
            ant-> coef += aux-> coef; /// adun coeficientul din nodul auxiliar care contine datele celui sters
            urmator = ant-> get_urm();
            this-> nr_elem--;
        }
        else
            {
                ant = ant-> get_urm();
                urmator = ant-> get_urm();
            }
    }
    delete urmator;
}

void Polinom_dinamic::citire( istream &in )
{
    int nr_per; //numar perechi din polinom;
    cout << "Numarul de perechi coeficient-exponent din polinom: ";
    cin >> nr_per;
    while ( nr_per <= 0 )
    {
        cout << "In polinom trebuie sa fie cel putin o pereche de tip coeficient-exponent. Dati un numar valid (mai mare sau egal cu 1): ";
        cin >> nr_per;
    }

    double coef, expo;
    for (int i = 1; i <= nr_per; i++)
    {
        cout << endl<<"Perechea " << i << " :\n";
        cout << "Dati coeficientul nodului: ";
        cin >> coef;
        cout << "Dati exponentul nodului: ";
        cin >> expo;
        this->adauga_nod_opt(coef, expo);
    }
}

istream& operator >>( istream &in, Polinom_dinamic& p )
{
    p.citire( in );
    return in;
}

void Polinom_dinamic::afisare( ostream &out )
{
    Nod *aux = new Nod;
    aux = cap;
    while ( aux != NULL )
    {
        if ( aux-> expo >= 0 )
            out << aux-> coef << "*x^" << aux-> expo;
        else out << aux-> coef << "*x^(" << aux-> expo << ")";
            if (aux-> urm != NULL)
        {
            if (aux-> urm-> get_coef() > 0)
                out<< " +";
            else out << " ";
        }
        aux = aux-> urm;
        }
        out << endl;
}

ostream& operator <<( ostream &out, Polinom_dinamic& p )
{
    p.afisare(out);
    return out;
}

Polinom_dinamic& Polinom_dinamic::operator =( Polinom_dinamic &p )
{
    this-> cap = p.cap;
    this-> coada = p.coada;
    this-> nr_elem = p.nr_elem;
}

double Polinom_dinamic::valoare_pct( double pct )
{
    double suma = 0;
    double temp = pct;

    Nod *aux;
    aux = this-> cap;

    while( aux != NULL )
    {
        temp = pct;
        if ( aux-> expo == 0 )              ///tratez separat cazurile posibile pentru exponentul lui x: pozitiv, negativ sau nul
            temp = 1;
        else
            for ( int i = 1; i < aux-> expo; i++ )
            {
                if ( aux-> expo > 0)
                    temp *= pct;
                else
                    temp /= pct;
            }
        temp *= aux-> coef;
        suma += temp;
        aux = aux-> urm;
    }

    return suma;
}

inline Polinom_dinamic& operator +( Polinom_dinamic& p1, Polinom_dinamic& p2 )
{
    Polinom_dinamic *rez = new Polinom_dinamic;
    Nod *n1 = new Nod;
    Nod *n2 = new Nod;
    n1 = p1.cap;
    n2 = p2.cap;

    while ( n1 != NULL && n2 != NULL )
    {
        if ( n1-> get_expo() == n2-> get_expo() )
        {
            if ( n1-> get_coef() + n2-> get_coef() != 0 )
                rez-> adauga_nod( n1-> get_coef() + n2-> get_coef(), n1-> get_expo() );
            n1 = n1-> get_urm();
            n2 = n2-> get_urm();
        }
        else if ( n1-> get_expo() < n2-> get_expo() )
        {
            rez-> adauga_nod( n1-> get_coef(), n1-> get_expo() );
            n1 = n1-> get_urm();
        }
        else if ( n1-> get_expo() > n2-> get_expo() )
        {
            rez-> adauga_nod( n2-> get_coef(), n2-> get_expo() );
            n2 = n2-> get_urm();
        }
    }

    if ( n1 == NULL)
        while ( n2 != NULL )
        {
            rez-> adauga_nod( n2-> get_coef(), n2-> get_expo() );
            n2 = n2-> get_urm();
        }

    else if ( n2 == NULL)
        while ( n1 != NULL )
        {
            rez-> adauga_nod ( n1-> get_coef(), n1-> get_expo() );
            n1 = n1-> get_urm();
        }

    if ( rez-> cap == NULL ) rez->adauga_cap(0, 0);
    return *rez;
}

inline Polinom_dinamic& operator -( Polinom_dinamic& p1, Polinom_dinamic& p2 ) ///supraincarcare operator -
{
    Polinom_dinamic *rez = new Polinom_dinamic;
    Nod *n1 = new Nod;
    Nod *n2 = new Nod;
    n1 = p1.cap;
    n2 = p2.cap;

    while ( n1 != NULL && n2 != NULL )
    {
        if ( n1-> get_expo() == n2-> get_expo() )
        {
            if ( n1-> get_coef() - n2-> get_coef() != 0 )
                rez-> adauga_nod( n1-> get_coef() - n2-> get_coef(), n1-> get_expo() );
            n1 = n1-> get_urm();
            n2 = n2-> get_urm();
        }
        else if ( n1-> get_expo() < n2-> get_expo() )
        {
            rez-> adauga_nod( n1-> get_coef(), n1-> get_expo() );
            n1 = n1-> get_urm();
        }
        else if ( n1-> get_expo() > n2-> get_expo() )
        {
            rez-> adauga_nod( (-1)*n2-> get_coef(), n2-> get_expo() );
            n2 = n2-> get_urm();
        }
    }

    if ( n1 == NULL)
        while ( n2 != NULL )
        {
            rez-> adauga_nod( (-1)*n2-> get_coef(), n2-> get_expo() );
            n2 = n2-> get_urm();
        }

    else if ( n2 == NULL)
        while ( n1 != NULL )
        {
            rez-> adauga_nod( n1-> get_coef(), n1->get_expo() );
            n1 = n1-> get_urm();
        }
    if ( rez-> cap == NULL ) rez->adauga_cap(0, 0);
    return *rez;
}

inline Polinom_dinamic& operator*( Polinom_dinamic& p1, Polinom_dinamic& p2 ) ///supraincarcare operator *
{
    Polinom_dinamic *rez = new Polinom_dinamic;
    Nod *n1 = new Nod;
    Nod *n2 = new Nod;
    n1 = p1.cap;
    n2 = p2.cap;

    while ( n1 != NULL)
    {
        n2 = p2.cap;
        while ( n2 != NULL)
        {
            rez-> adauga_nod( n1-> get_coef() * n2-> get_coef(), n1-> get_expo() + n2-> get_expo() );
            n2 = n2-> get_urm();

        }
        n1 = n1-> get_urm();
    }

    rez-> sterge_duplicate( );
    return *rez;
}


void output_meniu(){
    cout << "Programul salveaza polinoamele intr-un vector, setat pentru a retine un numar de 10 de polinoame.";
    cout << "\n\nMENIU:\n\n";
    cout << "1. Citeste unul sau mai multe polinoame\n";
    cout << "2. Afiseaza unul sau mai multe polinoame\n";
    cout << "3. Aduna doua polinoame\n";
    cout << "4. Scade doua polinoame\n";
    cout << "5. Inmulteste doua polinoame\n";
    cout << "6. Calculeaza valoarea unui polinom intr-un punct\n";

    cout << "0. Iesire.\n";
}

void meniu()
{
    Polinom_dinamic P[10];
    int citite = 0;

    int optiune = 0;
    do
    {
        output_meniu();

        cout<<"\nIntroduceti numarul actiunii dorite: ";
        cin>> optiune;

        if (optiune == 1)
        {
            int opt = 0;
            cout << "Cate polinoame doriti sa cititi (maxim 10 polinoame)? ";
            cin >> opt;
            while ( opt < 1 || opt > 10)
            {
                cout << "Selectia este incorecta. Introduceti un numar intre 1 si 10.  -> ";
                cin >> opt;
            }
            for (int i = 0 ; i < opt && citite < 10; i++)
                {
                    cout << endl << "Polinomul "<< citite+1 << endl;
                    cin>>P[citite];
                    citite ++;
                }
            if ( citite == 1 ) cout << "Pana acum a fost citit 1 polinom.";
            else cout << "Pana acum au fost citite " << citite << " polinoame.";
            if ( citite == 10 ) cout << " S-a ajuns la numarul maxim de polinoame.";
        }

        if (optiune == 2)
        {
            if ( citite == 0 ) cout << "Nu a fost citit niciun polinom. Cititi cel putin un polinom.";
            else  if( citite == 1 )
                cout << "A fost citit un singur polinom. Polinomul 1:   " << P[0];
            else
            {
                int opt = 0;
                cout << "Cate polinoame doriti sa afisati? (maxim " << citite << " polinoame) -> ";
                cin >> opt;
                while ( opt < 1 || opt > citite)
                {
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";
                    cin >> opt;
                }
                if ( opt == 1 )
                {
                    cout << "Ce polinom doriti sa afisati? (introduceti un numar intre 1 si " << citite <<") -> ";
                    int i;
                    cin >> i;
                    while ( i < 1 || i > citite)
                    {
                        cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";
                        cin >> i;
                    }
                    cout << "Polinomul " << i << ":    ";
                    cout << P[i-1];
                }
                else
                    {
                        if ( opt < citite) cout << "Primele " << opt << " polinoame sunt: \n";
                        for (int i = 0 ; i < opt; i++)
                        {
                            cout << "Polinomul "<< i+1 << ":    ";
                            cout << P[i];
                        }
                    }
                if ( opt == citite ) cout << "\nS-au afisat toate polinoamele existente.";
            }
        }

        if (optiune == 3)
        {
            if (citite > 0)
            {
                cout << "Doriti sa afisati toate polinoamele existente? Optiuni posibile:" << endl;
                cout << "1. Da" << endl << "0. Nu" << endl;
                int af = 0;
                cout << "Optiunea dumnavoastra: ";
                cin >> af;
                while (af != 0 && af != 1)
                {
                        cout << "Selectia este incorecta. Introduceti un numar din lista data. -> ";
                        cin >> af;
                }
                if ( af == 1 )
                    for (int i = 0 ; i < citite; i++)
                    {
                        cout << "Polinomul "<< i+1 << ":    " << P[i];
                    }
            }

            if ( citite == 0 ) cout << "Nu a fost citit niciun polinom. Cititi cel putin un polinom.";
            else if ( citite == 1 )
            {
                cout << "\nA fost citit un singur polinom." << endl;
                cout << "1. Insumati acest polinom cu el insusi." << endl;
                cout << "2. Cititi inca cel putin un polinom.";
                int o;
                cout << endl << "Optiunea aleasa este: ";
                cin >> o;
                if( o == 1)
                {
                    cout << "Polinomul este: " << P[0];
                    cout << "Polinomul insumat cu el insusi este: " << P[0] + P[0];
                }
            }
            else
            {
                cout << "\nAlegeti cele doua polinoame care vor fi adunate (valori acceptate: intre 1 si " << citite << "). -> ";
                int p1, p2;
                cout << "Primul polinom ales: ";
                cin >> p1;
                while ( p1 < 1 || p1 > citite)
                {
                    if( !(p1 < 1 || p1 > citite) )  //am adaugat aceasta verificare (aparent) redundanta, deoarece, pentru orice valaore a lui p1,
                        break;                     //se intra in bucla while (chiar daca valoarea lui p1 era una acceptata) si nu am reusit sa imi
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";           //dau seama de ce se intampla
                    cin >> p1;                                                                                  //asta si cum altfel poate fi remediat
                }
                cout << "Polinomul " << p1 << ": " << P[p1-1] << endl;

                cout << "Cel de-al doilea polinom ales: ";
                cin >> p2;
                while ( p2 < 1 || p2 > citite)
                {
                    if( !(p2 < 1 || p2 > citite))
                        break;
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";
                    cin >> p2;
                }
                cout << "Polinomul " << p2 << ": " << P[p2-1];
                cout << endl <<"Suma celor doua polinoame este: ";
                cout << P[p1-1] + P[p2-1];
            }
        }

        if (optiune == 4)
        {
            if (citite > 1)
            {
                cout << "Doriti sa afisati toate polinoamele existente? Optiuni posibile:" << endl;
                cout << "1. Da" << endl << "0. Nu" << endl;
                int af = 0;
                cout << "Optiunea dumnavoastra: ";
                cin >> af;
                while (af != 0 && af != 1)
                {
                        cout << "Selectia este incorecta. Introduceti un numar din lista data. -> ";
                        cin >> af;
                }
                if ( af == 1 )
                    for (int i = 0 ; i < citite; i++)
                    {
                        cout << "Polinomul "<< i+1 << ":    " << P[i];
                    }
            }

            if ( citite == 0 ) cout << "Nu a fost citit niciun polinom. Cititi cel putin doua polinoame.";
            else if ( citite == 1 ) cout << "A fost citit un singur polinom. Cititi inca cel putin un polinom.";
            else
            {
                cout << "\nAlegeti cele doua polinoame care vor fi scazute (valori acceptate: intre 1 si " << citite << ")." << endl << endl;
                int p1, p2;
                cout << "Primul polinom ales (descazutul): ";
                cin >> p1;
                while ( p1 < 1 || p1 > citite)
                {
                    if( !(p1 < 1 || p1 > citite) ) 
                        break;                    
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";          
                    cin >> p1;
                }
                cout << "Polinomul " << p1 << ": " << P[p1-1];

                cout << "\nCel de-al doilea polinom ales (scazatorul): ";
                cin >> p2;
                while ( p2 < 1 || p2 > citite)
                {
                    if( !(p2 < 1 || p2 > citite) )
                        break;
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";
                    cin >> p2;
                }
                cout << "Polinomul " << p2 << ": " << P[p2-1];
                cout << endl <<"Diferenta dintre cele doua polinoame este: ";
                cout << P[p1-1] - P[p2-1];
            }
        }

        if (optiune == 5)
        {
            if (citite > 0)
            {
                cout << "Doriti sa afisati toate polinoamele existente? Optiuni posibile:" << endl;
                cout << "1. Da" << endl << "0. Nu" << endl;
                int af = 0;
                cout << "Optiunea dumnavoastra: ";
                cin >> af;
                while (af != 0 && af != 1)
                {
                        cout << "Selectia este incorecta. Introduceti un numar din lista data. -> ";
                        cin >> af;
                }
                if ( af == 1 )
                    for (int i = 0 ; i < citite; i++)
                    {
                        cout << "Polinomul "<< i+1 << ":    " << P[i];
                    }
            }
            if ( citite == 0 ) cout << "Nu a fost citit niciun polinom. Cititi cel putin un polinom.";
            else if ( citite == 1 )
            {
                cout << "\nA fost citit un singur polinom." << endl;
                cout << "1. Inmultiti acest polinom cu el insusi." << endl;
                cout << "2. Cititi inca cel putin un polinom.";
                int o;
                cout << endl << "Optiunea aleasa este: ";
                cin >> o;
                if( o == 1)
                {
                    cout << "\nPolinomul este: " << P[0];
                    cout << "Polinomul inmultit cu el insusi este: " << P[0] * P[0];
                }
            }
            else
            {
                cout << "Alegeti cele doua polinoame care vor fi inmultite (valori acceptate: intre 1 si " << citite << "). -> ";
                int p1, p2;
                cout << endl << "Primul polinom ales: ";
                cin >> p1;
                while ( p1 < 1 || p1 > citite)
                {
                    if( !(p1 < 1 || p1 > citite) )
                        break;
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";
                    cin >> p1;
                }
                cout << "Polinomul " << p1 << ": " << P[p1-1] << endl;

                cout << "Cel de-al doilea polinom ales: ";
                cin >> p2;
                while ( p2 < 1 || p2 > citite)
                {
                    if( !(p2 < 1 || p2 > citite) )
                        break;
                    cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";
                    cin >> p2;
                }
                cout << "Polinomul " << p2 << ": " << P[p2-1];
                cout << endl <<"Produsul celor doua polinoame este: ";
                cout << P[p1-1] * P[p2-1];
            }
        }

        if ( optiune == 6)
        {
            if (citite > 0)
            {
                cout << "Doriti sa afisati toate polinoamele existente? Optiuni posibile:" << endl;
                cout << "1. Da" << endl << "0. Nu" << endl;
                int af = 0;
                cout << "Optiunea dumnavoastra: ";
                cin >> af;
                while (af != 0 && af != 1)
                {
                        cout << "Selectia este incorecta. Introduceti un numar din lista data. -> ";
                        cin >> af;
                }
                if ( af == 1 )
                    for (int i = 0 ; i < citite; i++)
                    {
                        cout << "Polinomul "<< i+1 << ":    " << P[i];
                    }
            }
            if ( citite == 0 ) cout << "Nu a fost citit niciun polinom. Cititi cel putin un polinom.";
            else
            {
                double pct;
                int opt;
                if ( citite == 1 )
                {
                    cout << "\nA fost citit un singur polinom. Se va calcula valaorea acestui polinom in punctul dorit.\n";
                    opt = 1;
                }
                else
                {
                    cout << "\nAlegeti polinomul pentru care se va calcula valoarea intr-un punct (introduceti un numar intre 1 si " << citite << "). -> ";
                    cin >> opt;
                    while ( opt < 1 || opt > citite )
                    {
                        cout << "Selectia este incorecta. Introduceti un numar intre 1 si " << citite << ". -> ";
                        cin >> opt;
                    }
                }
                cout << "Polinomul " << opt << ": ";
                cout << P[opt-1];
                cout << "\nDati punctul in care doriti sa aflati valoarea polinomului: ";
                cin >> pct;
                cout << "\nValoarea polinomului " << opt << " in punctul " << pct << " este: " << P[opt-1].valoare_pct(pct);
            }
        }

        if (optiune == 0)
        {
            break;
        }

        if (optiune < 0 || optiune > 6)
        {
            cout<<"\nSelectia este incorecta. Introduceti un numar din lista data.\n";
        }
        cout<<"\n";
        system("pause");
        system("cls");
    }
    while(optiune!=0);
}



int main()
{
    meniu();

    return 0;
}
