#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

/// optiunile 5, 6, 7, 8 si 9 au fost create in plus pentru a ilustra toate cerintele proiectului

class Contract
{
protected:
    int nrContract;
    int an;
    string beneficiar;
    string furnizor;
    int valoare;
    static int n; /// variabila statica folosita pentru a numara cate contracte avem declarate

public:
    Contract();
    Contract(int, string, string, int);
    Contract(Contract&);
    virtual ~Contract();
    void set_nrContract(int);
    void set_an(int);
    void set_beneficiar(string);
    void set_furnizor(string);
    void set_valoare(int);
    virtual void upcast()
    {
        cout << "Aceasta este clasa Contract.";
    };
    virtual void downcast()
    {
        cout << "A fost ilustrat conceptul de downcasting.";
    };
    int get_nrContract()
    {
        return nrContract;
    };
    int get_an()
    {
        return an;
    };
    string get_beneficiar()
    {
        return beneficiar;
    };
    string get_furnizor()
    {
        return furnizor;
    };
    int get_valoare()
    {
        return valoare;
    }
    virtual void citire(istream& in);
    virtual void afisare(ostream& out);
    friend istream& operator>>(istream& in, Contract& c);
    friend ostream& operator<<(ostream& out, Contract& c);
    Contract& operator=(Contract &c);
    static void numarContracte()
    {
        cout << "A fost citit un numar de " << n << " contracte" << endl;
    }
};
int Contract::n; ///declaram variabila

Contract::Contract()
{
    nrContract = ++n; /// atribuim variabila statica datei membru nrContract
    an = 0;
    beneficiar = "";
    furnizor = "";
    valoare = 0;
}
Contract::Contract(int anul, string ben, string fun, int val)
{
    this->nrContract = ++n;
    this->an = anul;
    this->beneficiar = ben;
    this->furnizor = fun;
    this->valoare = val;
}
Contract::~Contract()
{
    nrContract = 0;
    an = 0;
    beneficiar = "";
    furnizor = "";
    valoare = 0;
}
Contract::Contract(Contract &c)
{
    this->nrContract = c.nrContract;
    this->an = c.an;
    this->beneficiar = c.beneficiar;
    this->furnizor = c.furnizor;
    this->valoare = c.valoare;
}
void Contract::set_nrContract(int nrcon)
{
    nrcon = Contract::n;
    this->nrContract = nrcon;
}
void Contract::set_an(int a)
{
    this->an = an;
}
void Contract::set_beneficiar(string b)
{
    this->beneficiar = b;
}
void Contract::set_furnizor(string f)
{
    this->furnizor = f;
}
void Contract::set_valoare(int v)
{
    this->valoare = v;
}
void Contract::citire(istream& in)
{
    cout << "Introduceti anul semnarii contractului de cumparare: ";
    in >> an;
    cout << "Introduceti numele beneficiarului: ";
    in.get();
    getline(in, beneficiar);
    cout << "Introduceti numele furnizorului: ";
    getline(in, furnizor);
    cout << "Introduceti valoarea contractului: ";
    in >> valoare;
}
void Contract::afisare(ostream& out)
{
    out << "Numarul contractului: " << nrContract << "\n";
    out << "Anul semnarii contractului: " << an << "\n";
    out << "Numele beneficiarului: " << beneficiar << "\n";
    out << "Numele furnizorului: " << furnizor << "\n";
    out << "Valoarea contractului: " << valoare << "\n";
}
istream& operator>>(istream& in, Contract& c)
{
    c.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Contract& c)
{
    c.afisare(out);
    return out;
}
Contract& Contract::operator=(Contract &c)
{
    this->nrContract = c.nrContract;
    this->an = c.an;
    this->beneficiar = c.beneficiar;
    this->furnizor = c.furnizor;
    this->valoare = c.valoare;
}
///---------------------------------------------------

class ContractInchiriere:public Contract
{
private:
    int perioada;
public:
    ContractInchiriere();
    ContractInchiriere(int, string, string, int, int);
    ContractInchiriere(ContractInchiriere&);
    ~ContractInchiriere();
    void set_perioada(int);
    int get_perioada()
    {
        return perioada;
    };
    void citire(istream& in);
    void afisare(ostream& out);
    void mesaj()
    {
        cout << "Aceasta este clasa ContractInchiriere. S-a folosit upcast.";
    };
    void downcast()
    {
        cout << "Downcasting";
    };
    friend istream& operator>>(istream&, ContractInchiriere& ci);
    friend ostream& operator<<(ostream&, ContractInchiriere& ci);
    ContractInchiriere& operator=(ContractInchiriere &ci);
    friend class Dosar;
};
ContractInchiriere::ContractInchiriere():Contract()
{
    perioada = 0;
}
ContractInchiriere::ContractInchiriere(int anul, string ben, string fun, int val, int per):Contract(anul, ben, fun, val)
{
    perioada = per;
}
ContractInchiriere::ContractInchiriere(ContractInchiriere &ci):Contract(ci)
{
    this->perioada = ci.perioada;
}
ContractInchiriere::~ContractInchiriere()
{
    nrContract = 0;
    an = 0;
    beneficiar = "";
    furnizor = "";
    valoare = 0;
    perioada = 0;
}
void ContractInchiriere::set_perioada(int p)
{
    perioada = p;
}
void ContractInchiriere::citire(istream &in)
{
    Contract::citire(in);
    cout << "Introduceti perioada contractului in numar de luni: ";
    in >> perioada;
}
void ContractInchiriere::afisare(ostream &out)
{
    Contract::afisare(out);
    out << "Perioada contractului: ";
    out << perioada << endl;
}
istream& operator>>(istream& in, ContractInchiriere& c)
{
    c.citire(in);
    return in;
}
ostream& operator<<(ostream& out, ContractInchiriere& c)
{
    c.afisare(out);
    return out;
}
ContractInchiriere& ContractInchiriere::operator=(ContractInchiriere &ci)
{
    Contract::operator=(ci);
    this->valoare = ci.valoare;

}
///---------------------------------------------------

class Dosar
{
private:
    ContractInchiriere **contractinchiriere;
    int nr_contracteinchiriere;
public:
    Dosar();
    Dosar(ContractInchiriere**, int);
    Dosar(Dosar&);
    ~Dosar ();
    void set_nrcontracteinchiriere(int);
    int get_nrcontracteinchiriere()
    {
        return nr_contracteinchiriere;
    };
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream &in, Dosar &d);
    friend ostream& operator<<(ostream &out, Dosar &d);
    Dosar& operator=(Dosar &d);
};
Dosar::Dosar()
{
    contractinchiriere = NULL;
    this->nr_contracteinchiriere = 0;
}
Dosar::Dosar(ContractInchiriere **contractinchiriere, int nr_contracteinchiriere)
{
    contractinchiriere = new ContractInchiriere*[nr_contracteinchiriere];
    for(int i = 0; i < nr_contracteinchiriere; i ++)
        contractinchiriere[i] = new ContractInchiriere;

    for (int i = 0; i < nr_contracteinchiriere; i ++)
    {
        contractinchiriere[i]->an = contractinchiriere[i]->an;
        contractinchiriere[i]->beneficiar = contractinchiriere[i]->beneficiar;
        contractinchiriere[i]->furnizor = contractinchiriere[i]->furnizor;
        contractinchiriere[i]->valoare = contractinchiriere[i]->valoare;
        contractinchiriere[i]->perioada = contractinchiriere[i]->perioada;
    }

    this->nr_contracteinchiriere = nr_contracteinchiriere;
}
Dosar::Dosar(Dosar &d)
{
    contractinchiriere = new ContractInchiriere*[nr_contracteinchiriere];
    for(int i = 0; i < nr_contracteinchiriere; i ++)
        contractinchiriere[i] = new ContractInchiriere;
    for (int i = 0; i < nr_contracteinchiriere; i ++)
    {
        contractinchiriere[i]->nrContract = d.contractinchiriere[i]->nrContract;
        contractinchiriere[i]->an = d.contractinchiriere[i]->an;
        contractinchiriere[i]->beneficiar = d.contractinchiriere[i]->beneficiar;
        contractinchiriere[i]->furnizor = d.contractinchiriere[i]->furnizor;
        contractinchiriere[i]->valoare = d.contractinchiriere[i]->valoare;
        contractinchiriere[i]->perioada = d.contractinchiriere[i]->perioada;
    }
    this->nr_contracteinchiriere = d.nr_contracteinchiriere;
}
Dosar::~Dosar()
{
    for (int i = 0; i < nr_contracteinchiriere; i ++)
        delete[] contractinchiriere[i];
    delete[] contractinchiriere;

    this->nr_contracteinchiriere = 0;
}
void Dosar::set_nrcontracteinchiriere(int nr)
{
    this->nr_contracteinchiriere = nr;
}
void Dosar::citire(istream &in)
{
    cout << "Introduceti numarul contractelor din dosar: ";
    in >> nr_contracteinchiriere;
    cout << "Urmeaza sa introduceti informatii cu privire la contractele din dosar. " << endl;
    contractinchiriere = new ContractInchiriere*[nr_contracteinchiriere];
    for (int i = 0; i < nr_contracteinchiriere; i ++)
        contractinchiriere[i] = new ContractInchiriere;
    for (int i = 0; i < nr_contracteinchiriere; i ++)
        in >> *contractinchiriere[i];
}
void Dosar::afisare(ostream &out)
{
    out << "Numarul contractelor citite: " << nr_contracteinchiriere << endl;
    out << "Mai jos gasiti detalii despre contractele citite." << endl;
    for (int i = 0; i < nr_contracteinchiriere; i ++)
        out << *contractinchiriere[i] << endl;
}
istream& operator>>(istream& in, Dosar &d)
{
    d.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Dosar &d)
{
    d.afisare(out);
    return out;
}
Dosar& Dosar::operator=(Dosar &d)
{
    contractinchiriere = new ContractInchiriere*[nr_contracteinchiriere];
    for(int i = 0; i < nr_contracteinchiriere; i ++)
        contractinchiriere[i] = new ContractInchiriere;
    for (int i = 0; i < nr_contracteinchiriere; i ++)
    {
        contractinchiriere[i]->an = d.contractinchiriere[i]->an;
        contractinchiriere[i]->beneficiar = d.contractinchiriere[i]->beneficiar;
        contractinchiriere[i]->furnizor = d.contractinchiriere[i]->furnizor;
        contractinchiriere[i]->valoare = d.contractinchiriere[i]->valoare;
        contractinchiriere[i]->perioada = d.contractinchiriere[i]->perioada;
    }
}

void menu_output()
{
    cout<<"\n Popescu Mircea-Mihail - Proiect 2 - Tema 8: \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Cititi din dosar detalii despre n contracte de inchiriere.";
    cout<<"\n";
    cout<<"2. Afisati detaliile despre cele n contracte de inchiriere citite la optiunea 1.";
    cout<<"\n";
    cout<<"3. Cititi un numar de contracte de inchiriere si afisati valoarea incasata in functie de perioada.";
    cout<<"\n";
    cout<<"4. Cititi un numar de contracte de inchiriere si afisati valoarea totala incasata.";
    cout<<"\n";
    cout<<"5. Cititi un numar de contracte de inchiriere si afisati suma valorilor tuturor contractelor. (Upcasting)";
    cout << "\n";
    cout << "6. Ilustrarea conceptului de upcasting.";
    cout << "\n";
    cout << "7. Ilustrarea conceptului de downcasting.";
    cout << "\n";
    cout << "8. Cititi un numar de contracte de inchiriere si afisati numarul acestora.";
    cout << "\n";
    cout << "9. Cititi un numar de contracte si afisati suma valorilor tuturor contractelor. (Downcasting)";
    cout << "\n";
    cout<<"0. Iesire.";
    cout<<"\n";
}
void menu()
{
    int option; ///optiunea aleasa din meniu
    int numar_contracte = 0;
    int nr_con = 0;
    int n_contracte = 0;
    int valoarea_totala = 0;
    int suma = 0;
    int suma2 = 0;
    option = 0;
    Dosar d;
    Contract **con;
    ContractInchiriere **ci, **c;
    do
    {
        menu_output();

        cout << "\nIntroduceti numarul actiunii: ";
        cin >> option;

        if (option == 1)
        {
            cin >> d;
        }
        if (option == 2)
        {
            cout << d;
        }
        if (option == 3)
        {
            cout << "Introduceti numarul de contracte: ";
            cin >> nr_con;
            c = new ContractInchiriere*[nr_con];
            for (int i = 0; i < nr_con; i ++)
            {
                c[i] = new ContractInchiriere[nr_con];
                cin >> *c[i];
            }
            cout << endl;
            for (int i = 0; i < nr_con; i ++)
            {
                cout << "Contractul " << i + 1 << " semnat pe o perioada de " << c[i]->get_perioada() << " luni " << "are valoarea " << c[i]->get_valoare() * c[i]->get_perioada() << endl;
            }
        }
        if (option == 4)
        {
            cout << "Introduceti numarul de contracte: ";
            cin >> numar_contracte;
            ci = new ContractInchiriere*[numar_contracte];
            for(int i = 0; i < numar_contracte; i ++)
            {
                ci[i] = new ContractInchiriere[numar_contracte];
                cin >> *ci[i];
            }
            for (int i = 0; i < numar_contracte; i ++)
            {
                valoarea_totala += ci[i]->get_perioada() * ci[i]->get_valoare();
            }
            cout << endl;
            cout << "Valoarea totala incasata este: " << valoarea_totala << endl;
        }
        if (option == 5)
        {
            cout << "Introduceti numarul de contracte: ";
            cin >> n_contracte;
            con = new Contract*[n_contracte];
            for (int i = 0; i < n_contracte; i ++)
            {
                con[i] = new ContractInchiriere[n_contracte];
                cin >> *con[i];
            }
            for (int i = 0; i < n_contracte; i ++)
                suma += con[i]->get_valoare();
            cout << endl;
            cout << "Suma valorilor contractelor citite este: " << suma << endl;
        }
        if (option == 6)
        {
            Contract *c = new ContractInchiriere;
            cin >> *c;
            cout << endl;
            cout << *c;
            c->upcast();
        }
        if (option == 7)
        {
            ContractInchiriere *coni = (ContractInchiriere*) new Contract;
            cin >> *coni;
            cout << endl;
            cout << *coni;
            coni->downcast();
        }
        if (option == 8)
        {
            int nr_con1 = 0;
            cout << "Introduceti numarul de contracte: ";
            cin >> nr_con1;
            ContractInchiriere *con1 = new ContractInchiriere[nr_con1];
            for (int i = 0; i < nr_con1; i ++)
            {
                cin >> con1[i];
            }
            cout << endl;
            ContractInchiriere::numarContracte();
        }
        if (option == 9)
        {
            int nr_con2 = 0;
            cout << "Introduceti numarul de contracte: ";
            cin >> nr_con2;
            ContractInchiriere **con2 = new ContractInchiriere*[nr_con2];
            for (int i = 0; i < nr_con2; i ++)
            {
                con2[i] = (ContractInchiriere*)new Contract[nr_con2];
                cin >> *con2[i];
            }
            for (int i = 0; i < nr_con2; i ++)
                suma2 += con2[i]->get_valoare();
            cout << endl;
            cout << "Suma valorilor contractelor citite este: " << suma2 << endl;
        }

        if (option == 0)
        {
            cout<<"\nEXIT!\n";
        }
        if (option < 0 || option > 9)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout << "\n" ;
        system("pause"); /// Pauza - Press any key to continue...
        system("cls");   /// Sterge continutul curent al consolei
    }
    while(option != 0);
}

int main()
{
    menu();
    return 0;
}
