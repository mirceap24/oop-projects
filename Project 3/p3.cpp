#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unordered_set>

using namespace std;

class Examen
{
protected:
    const int id_examen;
    string denumire_materie;
    string data;
    double nota_scris;
    static int examene_citite;

public:
    Examen(string, string, double);
    Examen(Examen&);
    virtual ~Examen();
    void set_denumire_materie(string);
    void set_data(string);
    void set_nota_scris(double);
    int get_id_examen() const
    {
        return id_examen;
    };
    string get_denumire_materie() const
    {
        return denumire_materie;
    }
    string get_data() const
    {
        return data;
    }
    double get_nota_scris() const
    {
        return nota_scris;
    }
    virtual void citire(istream& in);
    virtual void afisare(ostream& out);
    friend istream& operator>>(istream& in, Examen& e);
    friend ostream& operator<<(ostream& out, Examen& e);
    Examen& operator=(Examen& e);
    static void numarExamene()
    {
        cout << "Au fost citite informatii despre " << examene_citite << " examene" << "\n";
    }
};
int Examen::examene_citite;

Examen::Examen(string denumire_materie = "", string data = "", double nota_scris = 0):id_examen(++examene_citite)
{
    this->denumire_materie = denumire_materie;
    this->data = data;
    this->nota_scris = nota_scris;
}
Examen::~Examen()
{
    this->examene_citite = 0;
    this->denumire_materie = "";
    this->data = "";
    this->nota_scris = 0;

}
Examen::Examen(Examen& e):id_examen(e.id_examen)
{
    this->denumire_materie = e.denumire_materie;
    this->data = e.data;
    this->nota_scris = e.nota_scris;
}

void Examen::set_denumire_materie(string denumire_materie)
{
    this->denumire_materie = denumire_materie;
}
void Examen::set_data(string data)
{
    this->data = data;
}
void Examen::set_nota_scris(double nota_scris)
{
    this->nota_scris = nota_scris;
}

void Examen::citire(istream& in)
{
    try
    {
        in.get();
        cout << "Introduceti materia la care se sustine examenul: ";
        getline(in, denumire_materie);
        for (int i = 0; i < denumire_materie.length(); i ++)
        {
            int uppercaseChar = toupper(denumire_materie[i]);
            if ((uppercaseChar < 'A' || uppercaseChar > 'Z') && uppercaseChar != ' ')
                throw 1;
        }
        cout << "Introduceti data examenului: ";
        in >> data;
        for (int i = 0; i < data.length(); i ++)
        {
            if ((data[i] < '0' || data[i] > '9') && data[i] != '.')
                throw 2;
        }
        cout << "Introduceti nota obtinuta la scris: ";
        in >> nota_scris;
        in.get();
        if (nota_scris < 1 || nota_scris > 10) /// am considerat ca notele obtinute se afla in intervalul 1-10
            throw 3;
    }
    catch(int i)
    {
        if (i == 1)
        {
            cout << "Eroare, denumirea examenului contine doar litere sau caracterul spatiu (exemplu: Programare orientata pe obiecte!" << endl;
            exit(EXIT_FAILURE);
        }
        if (i == 2)
        {
            cout << "Eroare, data examenului este de forma zi.luna.an! (exemplu: 24.03.2019)" << endl;
            exit(EXIT_FAILURE);
        }
        if (i == 3)
        {
            cout << "Eroare, nota examenului este un numar rational cuprins intre 1 si 10!" << endl;
            exit(EXIT_FAILURE);
        }
    }
}
void Examen::afisare(ostream& out)
{
    out << endl;
    out << "Numarul examenului este " << id_examen << endl;
    out << "Materia la care se sustine examenul este " << denumire_materie << endl;
    out << "Data examenului este " << data << endl;
    out << "Nota obtinuta la proba scrisa este " << nota_scris << endl;
}
istream& operator>>(istream& in, Examen& e)
{
    e.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Examen& e)
{
    e.afisare(out);
    return out;
}
Examen& Examen::operator=(Examen &e)
{
    this->denumire_materie = e.denumire_materie;
    this->data = e.data;
    this->nota_scris = e.nota_scris;
}
///---------------------------------------------------

class Partial:public Examen
{
private:
    double nota_oral;

public:
    Partial(string, string, double, double);
    Partial(Partial&);
    ~Partial();
    void set_nota_oral(double);
    double get_nota_oral()
    {
        return nota_oral;
    }
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream&, Partial& p);
    friend ostream& operator<<(ostream&, Partial& p);
    Partial& operator=(Partial &p);
    friend class Examen;
};

Partial::Partial(string denumire_materie = "", string data = "", double nota_scris = 0, double nota_oral = 0):Examen(denumire_materie, data, nota_scris)
{
    this->nota_oral = nota_oral;
}
Partial::Partial(Partial &p):Examen(p)
{
    this->nota_oral = p.nota_oral;
}
Partial::~Partial()
{
    this->examene_citite = 0;
    this->denumire_materie = "";
    this->data = "";
    this->nota_scris = 0;
    this->nota_oral = 0;
}
void Partial::set_nota_oral(double nota_oral)
{
    this->nota_oral = nota_oral;
}
void Partial::citire(istream& in)
{
    Examen::citire(in);
    cout << "Introduceti nota obtinuta la proba orala: ";
    try
    {
        in >> nota_oral;
        if (nota_oral < 1 || nota_oral > 10)
            throw 1;
    }
    catch(int i)
    {
        if (i == 1)
            cout << "Eroare, nota examenului este un numar rational cuprins intre 1 si 10!" << endl;
        exit(EXIT_FAILURE);
    }
}
void Partial::afisare(ostream& out)
{
    Examen::afisare(out);
    out << "Nota obtinuta la proba orala: " << nota_oral << endl;
}
istream& operator>>(istream& in, Partial& p)
{
    p.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Partial& p)
{
    p.afisare(out);
    return out;
}
Partial& Partial::operator=(Partial &p)
{
    Examen::operator=(p);
    this->nota_oral = p.nota_oral;
}
///---------------------------------------------------

class ExamenFinal:public Examen
{
private:
    double puncte_proiect;

public:
    ExamenFinal(string, string, double, double);
    ExamenFinal(ExamenFinal&);
    ~ExamenFinal();
    void set_puncte_proiect(double);
    double get_puncte_proiect()
    {
        return puncte_proiect;
    }
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream&, ExamenFinal &Ef);
    friend ostream& operator<<(ostream&, ExamenFinal &Ef);
    ExamenFinal& operator=(ExamenFinal& ef);
};

ExamenFinal::ExamenFinal(string denumire_materie = "", string data = "", double nota_scris = 0, double puncte_proiect = 0):Examen(denumire_materie, data, nota_scris)
{
    this->puncte_proiect = puncte_proiect;
}
ExamenFinal::ExamenFinal(ExamenFinal &ef):Examen(ef)
{
    this->puncte_proiect = ef.puncte_proiect;
}
ExamenFinal::~ExamenFinal()
{
    this->examene_citite = 0;
    this->denumire_materie = "";
    this->data = "";
    this->nota_scris = 0;
    this->puncte_proiect = 0;
}
void ExamenFinal::set_puncte_proiect(double puncte_proiect)
{
    this->puncte_proiect = puncte_proiect;
}
void ExamenFinal::citire(istream& in)
{
    Examen::citire(in);
    cout << "Introduceti punctajul obtinut pe proiect: ";
    try
    {
        in >> puncte_proiect;
        if (puncte_proiect < 1 || puncte_proiect > 10)
            throw 1;
    }
    catch(int i)
    {
        if (i == 1)
            cout << "Eroare, nota proiectului este un numar rational cuprins intre 1 si 10!" << endl;
        exit(EXIT_FAILURE);
    }
}
void ExamenFinal::afisare(ostream& out)
{
    Examen::afisare(out);
    out << "Nota obtinuta la proiect este " << puncte_proiect << endl;
}
istream& operator>>(istream& in, ExamenFinal& ef)
{
    ef.citire(in);
    return in;
}
ostream& operator<<(ostream& out, ExamenFinal& ef)
{
    ef.afisare(out);
    return out;
}
ExamenFinal& ExamenFinal::operator=(ExamenFinal &ef)
{
    Examen::operator=(ef);
    this->puncte_proiect = ef.puncte_proiect;
}
///---------------------------------------------------

class Quiz:public Examen
{
private:
    int numar_itemi;

public:
    Quiz(string, string, double, int);
    Quiz(Quiz&);
    ~Quiz();
    void set_numar_itemi(int);
    int get_numar_itemi()
    {
        return  numar_itemi;
    }
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream&, Quiz& q);
    friend ostream& operator<<(ostream&, Quiz& q);
    Quiz& operator=(Quiz& q);

};

Quiz::Quiz(string denumire_materie = "", string data = "", double nota_scris = 0, int numar_itemi = 0):Examen(denumire_materie, data, nota_scris)
{
    this->numar_itemi = numar_itemi;
}
Quiz::Quiz(Quiz& q):Examen(q)
{
    this->numar_itemi = q.numar_itemi;
}
Quiz::~Quiz()
{
    this->examene_citite = 0;
    this->denumire_materie = "";
    this->data = "";
    this->nota_scris = 0;
    this->numar_itemi = 0;
}
void Quiz::set_numar_itemi(int numar_itemi)
{
    this->numar_itemi = numar_itemi;
}
void Quiz::citire(istream& in)
{
    Examen::citire(in);
    cout << "Introduceti cati itemi contine quiz-ul: " << endl;
    try
    {
        in >> numar_itemi;
        if (numar_itemi <= 0)
            throw 1;
    }
    catch(int i)
    {
        if (i == 1)
            cout << "Eroare, quiz-ul trebuie sa contina un numar pozitiv de itemi mai mare decat 0!" << endl;
        exit(EXIT_FAILURE);
    }
}
void Quiz::afisare(ostream& out)
{
    Examen::afisare(out);
    out << "Numarul de itemi din quiz: " << numar_itemi << endl;
}
istream& operator>>(istream& in, Quiz& q)
{
    q.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Quiz& q)
{
    q.afisare(out);
    return out;
}
Quiz& Quiz::operator=(Quiz &q)
{
    Examen::operator=(q);
    this->numar_itemi = q.numar_itemi;
}
///---------------------------------------------------

class Elev
{
private:
    string nume;
    string prenume;
    vector<Examen*> examene_sustinute;
    vector<Partial*> partial;
    vector<Quiz*> quiz;
    vector<ExamenFinal*> examenfinal;
    static int nr_elev;

public:
    Elev(string, string, vector<Examen*>);
    Elev(Elev&);
    ~Elev();
    void set_nume(string);
    void set_prenume(string);
    void set_examene_sustinute(vector<Examen*>);
    void set_partial(vector<Partial*>);
    void set_quiz(vector<Quiz*>);
    void set_examenfinal(vector<ExamenFinal*>);
    void set_numar_examene_date(int);
    string get_nume()
    {
        return nume;
    }
    string get_prenume()
    {
        return prenume;
    }
    vector<Examen*> get_examene_sustinute()
    {
        return examene_sustinute;
    }
    vector<Partial*> get_partial()
    {
        return partial;
    }
    vector<Quiz*> get_quiz()
    {
        return quiz;
    }
    vector<ExamenFinal*> get_examenfinal()
    {
        return examenfinal;
    }
    void citire(istream& in);
    void afisare(ostream& out);
    friend istream& operator>>(istream &in, Elev &e);
    friend ostream& operator<<(ostream &out, Elev &e);
    Elev& operator=(Elev &e);
};
int Elev::nr_elev;

Elev::Elev(string nume = "", string prenume = "", vector<Examen*> examene_sustinute = vector<Examen*>())
{
    nr_elev++;
    this->nume = nume;
    this->prenume = prenume;
    this->examene_sustinute = examene_sustinute;
}
Elev::Elev(Elev& e)
{
    this->nume = e.nume;
    this->prenume = e.prenume;
    this->examene_sustinute = e.examene_sustinute;
}
Elev::~Elev()
{
    nr_elev--;
    this->nume = "";
    this->prenume = "";
    examene_sustinute.clear();
}
void Elev::set_nume(string nume)
{
    this->nume = nume;
}
void Elev::set_prenume(string prenume)
{
    this->prenume = prenume;
}
void Elev::set_examene_sustinute(vector<Examen*> examene_sustinute)
{
    this->examene_sustinute = examene_sustinute;
}
void Elev::set_partial(vector<Partial*> partial)
{
    this->partial = partial;
}
void Elev::set_quiz(vector<Quiz*> quiz)
{
    this-> quiz = quiz;
}
void Elev::set_examenfinal(vector<ExamenFinal*> examenfinal)
{
    this->examenfinal = examenfinal;
}
void Elev::citire(istream& in)
{
    cout << "Introduceti numele elevului: ";
    in >> nume;
    for (int i = 0; i < nume.length(); i ++)
    {
        int uppercaseNume = toupper(nume[i]);
        if ((uppercaseNume < 'A' || uppercaseNume > 'Z'))
            throw 1;
    }
    cout << "Introduceti prenumele elevului: ";
    in >> prenume;
    for (int i = 0; i < prenume.length(); i ++)
    {
        int uppercasePrenume = toupper(prenume[i]);
        if ((uppercasePrenume < 'A' || uppercasePrenume > 'Z'))
            throw 2;
    }
    string optiune;
    cout << "Elevul a sustinut examenul partial? (Introduceti DA sau NU): ";
    in >> optiune;
    if (optiune == "DA")
    {
        Partial *p = new Partial;
        cin >> *p;
        partial.push_back(p);
    }
    cout << "Elevul a sustinut quiz-ul? (Introduceti DA sau NU): ";
    in >> optiune;
    if (optiune == "DA")
    {
        cout << "Introduceti cate quiz-uri a sustinut elevul: ";
        int nr_quizuri;
        cin >> nr_quizuri;
        for (int i = 1; i <= nr_quizuri; i ++)
        {
            Quiz *q = new Quiz;
            cin >> *q;
            quiz.push_back(q);
        }
    }
    cout << "Elevul a sustinut examenul final? (Introduceti DA sau NU): ";
    in >> optiune;
    if (optiune == "DA")
    {
        for (auto i = partial.begin(); i != partial.end(); i ++)
        {
            if ((*i)->get_nota_scris() < 5 || (*i)->get_nota_oral() < 5)
            {
                cout << "Nu s-a obtinut o nota de trecere la partial. Trebuie refacut!" << endl;
                double notascris, notaoral;
                cout << "Nota la scris dupa refacere: ";
                cin >> notascris;
                cout << "Nota la oral dupa refacere: ";
                cin >> notaoral;
                (*i)->set_nota_scris(notascris);
                (*i)->set_nota_oral(notaoral);
            }
        }
        ExamenFinal* ef = new ExamenFinal;
        cin >> *ef;
        examenfinal.push_back(ef);
    }
}
void Elev::afisare(ostream& out)
{
    out << "Numele elevului este: " << nume << endl;
    out << "Prenumele elevului este: " << prenume << endl;
    out << "Informatii despre evaluarile sustinute de elev: " << endl;
    for(auto i = partial.begin(); i != partial.end(); i ++)
        out << (**i) << endl;
    for(auto i = quiz.begin(); i != quiz.end(); i ++)
        out << (**i) << endl;
    for(auto i = examenfinal.begin(); i != examenfinal.end(); i ++)
        out << (**i) << endl;
}
istream& operator >> (istream& in, Elev& e)
{
    e.citire(in);
    return in;
}

ostream& operator << (ostream& out, Elev& e)
{
    e.afisare(out);
    return out;
}

Elev& Elev::operator = (Elev& e)
{
    this->nume = e.nume;
    this->prenume = e.prenume;
    this->examene_sustinute = e.examene_sustinute;
}
///---------------------------------------------------
template <class t> class CatalogIndividual
{
private:
    int numar_matricol;
    int numar_examene;
    static int nr_matricol;
    unordered_set<t> elevi_restanta;

public:
    CatalogIndividual(int numar_matricol = 0, int numar_examene = 0, unordered_set<t> elevi_restanta = unordered_set<t>())
    {
        nr_matricol++;
        this->numar_matricol = nr_matricol;
        this->numar_examene = numar_examene;
        this->elevi_restanta = elevi_restanta;
    }

    CatalogIndividual(CatalogIndividual &ci)
    {
        this->numar_matricol = ci.numar_matricol;
        this->numar_examene = ci.numar_examene;
        this->elevi_restanta = ci.elevi_restanta;
    }

    ~CatalogIndividual()
    {
        this->numar_matricol = 0;
        this->numar_examene = 0;
        this->elevi_restanta.clear();
    }

    void citire(istream& in)
    {
        cout << "Introduceti cate examene au sustinut elevii: ";
        in >> numar_examene;
        for(int i = 1 ; i <= numar_examene ; i++)
        {
            cout << "Introduceti numarul elevilor care nu au promovat examenul: ";
            int m;
            in >> m;
            for(int j = 1 ; j <= m ; j++)
            {
                Examen *ex = new Examen;
                in >> *ex;
                if (ex -> get_nota_scris() < 5)
                {
                    t *e = new t;
                    in >> *e;
                    elevi_restanta.insert(*&e);
                }
            }

        }

    }

    void afisare(ostream& out)
    {
        out << "Numarul matricol: " << nr_matricol << endl;
        out << "Numarul examenelor: " << numar_examene << endl;
        out << "Informatii despre elevii care nu au promovat examenul: " << endl;
        for(auto i = elevi_restanta.begin(); i != elevi_restanta.end(); i ++)
        {
            out << **i << endl;
        }
    }
    friend istream& operator >> (istream &in, CatalogIndividual <t> &ci)
    {
        ci.citire(in);
        return in;
    }
    friend ostream& operator << (ostream &out, CatalogIndividual<t> &ci)
    {
        ci.afisare(out);
        return out;
    }
    CatalogIndividual& operator = (CatalogIndividual& ci)
    {
        this->numarmatricol = ci.numarmatricol;
        this->numar_examene = ci.numar_examene;
        this->elevi_restanta = ci.elevi_restanta;
    }

    CatalogIndividual& operator += (t student_picat)
    {
        numar_examene++;
        elevi_restanta.insert(student_picat);
    }
};
template <class t> int CatalogIndividual<t>::nr_matricol;

template <> class CatalogIndividual <Elev>
{
private:
    int nr_matricol;
    int nr_examene;
    static int nr_mat;
    unordered_set<Elev*> elevi_restanta;

public:
    CatalogIndividual(int nr_matricol = 0, int nr_examene = 0, unordered_set<Elev*> elevi_restanta = unordered_set<Elev*>())
    {
        nr_mat++;
        this->nr_matricol = nr_matricol;
        this->nr_examene = nr_examene;
        this->elevi_restanta = elevi_restanta;
    }

    CatalogIndividual(CatalogIndividual &z)
    {
        nr_mat++;
        this->nr_matricol = z.nr_matricol;
        this->nr_examene = z.nr_examene;
        this->elevi_restanta = z.elevi_restanta;
    }

    ~CatalogIndividual()
    {
        nr_matricol = 0;
        nr_mat--;
        nr_examene = 0;
        elevi_restanta.clear();
    }

    void citire(istream& in)
    {
        nr_matricol = nr_mat;
        cout << "Introduceti numarul de examene sustinute de elevi: ";
        int nr_examene;
        in >> nr_examene;
        for(int i = 1 ; i <= nr_examene; i++)
        {
            cout << "Introduceti numarul studentilor care nu au promovat examenul: ";
            int numar_elevi;
            in >> numar_elevi;

            for(int j = 1 ; j <= numar_elevi ; j ++)
            {
                Examen *ex = new Examen;
                in >> *ex;
                if (ex->get_nota_scris() < 5)
                {
                    cout << "Urmeaza sa introduceti informatii despre elevul care nu a promovat examenul." << endl;
                    Elev *e = new Elev;
                    in >> *e;
                    elevi_restanta.insert(*&e);
                }
            }
        }
    }

    void afisare(ostream& out)
    {
        out << "Numarul de examene sustinute: " << nr_examene << endl;
        out << "Informatii despre elevii care nu au promovat examenul: " << endl;
        for(auto i = elevi_restanta.begin() ; i != elevi_restanta.end() ; ++i)
        {
            cout << **i << " ";
        }
    }

    friend istream& operator >> (istream &in, CatalogIndividual &z)
    {
        z.citire(in);
        return in;
    }

    friend ostream& operator << (ostream &out, CatalogIndividual &z)
    {
        z.afisare(out);
        return out;
    }

    CatalogIndividual& operator = (CatalogIndividual& z)
    {
        this->nr_examene = z.nr_examene;
        this->nr_matricol = z.nr_matricol;
        this->elevi_restanta = z.elevi_restanta;
    }

    CatalogIndividual& operator+=(Elev* student_restant)
    {
        nr_matricol++;
        elevi_restanta.insert(student_restant);
    }
};
int CatalogIndividual<Elev>::nr_mat;
///---------------------------------------------------


template <> class CatalogIndividual <Quiz>
{
private:
    int numarmatricol;
    int numarquiz;
    static int numar_mat;
    unordered_set<Elev*> quiz;

public:
    CatalogIndividual(int numarmatricol = 0, int numarquiz = 0, unordered_set<Elev*> quiz = unordered_set<Elev*>())
    {
        numar_mat ++;
        this->numarmatricol = numar_mat;
        this->numarquiz = numarquiz;
        this->quiz = quiz;
    }
    CatalogIndividual(CatalogIndividual &cati)
    {
        this->numarmatricol = cati.numarmatricol;
        this->numarquiz = cati.numarquiz;
        this->quiz = cati.quiz;
    }
    ~CatalogIndividual()
    {
        this->numarmatricol = 0;
        this->numarquiz = 0;
        this->quiz.clear();
    }
    void citire(istream& in)
    {
        cout << "Introduceti numarul de quiz-uri: ";
        in >> numarquiz;
        for (int i = 1; i <= numarquiz; i ++)
        {
            cout << "Introduceti numarul quiz-ului : ";
            int nr;
            in >> nr;
            cout << "Introduceti numarul elevilor care au sustinut quiz-ul: ";
            int n_elevi;
            cin >> n_elevi;
            for (int j = 1; j <= n_elevi; j ++)
            {
                Elev *elev = new Elev;
                in >> *elev;
                quiz.insert(*&elev);
            }
        }
    }
    void afisare(ostream& out)
    {
        vector<Elev*> elev;
        out << "Numarul quiz-urilor: " << numarquiz << endl;
        out << "Informatii despre elevii care au sustinut quiz-uri." << endl;
        for (auto i = quiz.begin(); i != quiz.end(); i ++)
            out << **i;
    }
    friend istream& operator >> (istream &in, CatalogIndividual &cati)
    {
        cati.citire(in);
        return in;
    }

    friend ostream& operator << (ostream &out, CatalogIndividual &cati)
    {
        cati.afisare(out);
        return out;
    }

    CatalogIndividual& operator = (CatalogIndividual& cati)
    {
        this->numarmatricol = cati.numarmatricol;
        this->numarquiz = cati.numarquiz;
        this->quiz = cati.quiz;
    }

    CatalogIndividual& operator+=(Elev *elev)
    {
        numarquiz ++;
        quiz.insert(elev);
    }
};
int CatalogIndividual<Quiz>::numar_mat;

void menu_output()
{
    cout<<"\n Popescu Mircea-Mihail - Proiect 3 - Tema 3: \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Cititi informatii despre un numar de elevi.";
    cout<<"\n";
    cout<<"2. Afisati informatiile despre elevii cititi la optiunea 1.";
    cout << "\n";
    cout <<"3. Cititi informatii despre un numar de examene (S-a utilizat Upcasting).";
    cout << "\n";
    cout << "4. Afisati informatiile despre examenele citite la optiunea 3.";
    cout << "\n";
    cout << "5. Afisati informatiile despre quiz-urile citite la optiunea 3 (S-a folosit Dynamic Cast).";
    cout << "\n";
    cout << "6. Citire template Catalog Individual Elev. ";
    cout << "\n";
    cout << "7. Citire specializare Catalog Individual Quiz. ";
    cout << "\n";
}

void menu()
{
    int option;
    vector<Elev*>elevi_cititi;
    vector<Examen*> examene_citite;
    CatalogIndividual<Elev> elev;
    CatalogIndividual<Quiz> quiz;
    do
    {
        menu_output();
        cout << "\nIntroduceti numarul actiunii: ";
        cin >> option;
        int nr_elevi;
        Quiz *q = new Quiz;
        if (option == 1)
        {
            cout << "Introduceti numarul de elevi despre care doriti sa afisati informatii: ";
            cin >> nr_elevi;
            for (int i = 1; i <= nr_elevi; i ++)
            {
                Elev* el = new Elev;
                cin >> *el;
                elevi_cititi.push_back(*&el);
            }
        }
        if (option == 2)
        {
            for (auto i = elevi_cititi.begin(); i != elevi_cititi.end(); i ++)
                cout << **i << endl;
        }
        if (option == 3)
        {
            cout << "Introduceti numarul de examene: ";
            Examen *ex;
            int nr_examene;
            cin >> nr_examene;
            for (int i = 1; i <= nr_examene; i ++)
            {
                cout << "Alegeti tipul examenului: Examen, Partial, Quiz, Examen Final: ";
                string option1;
                cin >> option1;
                if (option1 == "Examen")
                {
                    ex = new Examen;
                    cin >> *ex;
                }
                else if (option1 == "Partial")
                {
                    ex = new Partial; /// UPCASTING
                    cin >> *ex;
                }
                else if (option1 == "Quiz")
                {
                    ex = new Quiz;
                    cin >> *ex; /// UPCASTING
                }
                else if (option1 == "Examen Final")
                {
                    ex = new ExamenFinal;
                    cin >> *ex; /// UPCASTING
                }
                examene_citite.push_back(*&ex);
            }
        }
        if (option == 4)
        {
            for (auto i = examene_citite.begin(); i != examene_citite.end(); i ++)
                cout << **i << endl;
        }
        if (option == 5)
        {
            for (auto i = examene_citite.begin(); i != examene_citite.end(); i ++)
            {
                if (q = dynamic_cast<Quiz *>(*i)) /// DYNAMIC CAST
                    cout << *q;
            }
        }
        if (option == 6)
        {
            cin >> elev;
            cout << elev;
        }
        if (option == 7)
        {
            cin >> quiz;
            cout << quiz;
        }
    }
    while (option != 0);
}

int main()
{
    menu();
}
