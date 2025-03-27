#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <list>
#include <typeinfo>
#include <stdexcept>

using namespace std;

class Iointerface
{
public:
    virtual istream& citire(istream&)=0;
    virtual ostream& afisare(ostream&)const=0;

};

class Masina:public Iointerface
{
protected:
    const int idMasina;
    static int contor;
    double capacitateMax;
    double cantitateRufe;
    string timer;
    string erori;

public:
    Masina();
    Masina(double, double, string, string);
    Masina(const Masina& obj);
    Masina& operator=(const Masina& obj);
    istream& citire (istream&);
    ostream& afisare(ostream&)const;
    int getId()
    {
        return this->idMasina;
    }
    friend bool operator ==(const Masina&, const Masina&);
    friend ostream& operator<<(ostream&, const Masina&);
    friend istream& operator>>(istream& in, Masina&);
    virtual ~Masina(){};
};

Masina::Masina():idMasina(contor++), capacitateMax(0), cantitateRufe(0), timer("necunoscut"),erori("necunoscut"){}
Masina::Masina(double capacitateMax, double cantitateRufe, string timer, string erori):idMasina(contor++), capacitateMax(capacitateMax),
cantitateRufe(cantitateRufe), timer(timer), erori(erori){}
Masina::Masina(const Masina& obj):idMasina(contor++),capacitateMax(obj.capacitateMax),
cantitateRufe(obj.cantitateRufe), timer(obj.timer), erori(obj.erori){}
bool operator==(const Masina &obj1, const Masina& obj2)
{
    return obj1.idMasina==obj2.idMasina;
}
Masina& Masina::operator=(const Masina& obj)
{
    if(this!=&obj)
    {
        this->capacitateMax=obj.capacitateMax;
        this->cantitateRufe=obj.cantitateRufe;
        this->timer=obj.timer;
        this->erori=obj.erori;
    }
    return *this;
}

int Masina::contor=1;
istream& Masina::citire(istream& in)
{
    cout<<"Capacitatea maxima a masinii este de:"<<endl;
    in>>capacitateMax;
    cout<<"Cantitate de rufe prezenta este de:"<<endl;
    in>>cantitateRufe;
    if(capacitateMax<cantitateRufe)
        erori="greutate prea mare";
    erori="nu exista";
    cout<<"Timpul unui ciclu este:"<<endl;
    in>>timer;
    return in;
}
ostream& Masina::afisare(ostream& out)const
{
    out<<"Capacitatea maxima a masinii este de:"<<capacitateMax<<endl;
    out<<"Cantitatede rufe prezenta este de:"<<cantitateRufe<<endl;
    if(erori=="nu exista")
    {
        out<<"Erorile prezente: "<<erori<<endl;
        out<<"Timpul necesar este:"<<timer<<endl;
    }
    else
        out<<erori<<endl;
    return out;
}
istream& operator >>(istream& in, Masina& obj)
{
    return obj.citire(in);
}
ostream& operator <<(ostream& out, const Masina& obj)
{
    return obj.afisare(out);
}



class MasinaDeSpalat:public Masina
{
protected:
    vector<string>programe;
    string programCurent;
    double cantitateDet;
    double temperatura;
public:
    MasinaDeSpalat();
    MasinaDeSpalat(vector<string>, double, double, double, double, string, string, string);
    MasinaDeSpalat(const MasinaDeSpalat&);
    MasinaDeSpalat& operator =(const MasinaDeSpalat& );
    istream& citire(istream& in);
    ostream& afisare(ostream& out)const;
    friend istream& operator >>(istream& in, MasinaDeSpalat&);
    friend ostream& operator <<(ostream& out, const MasinaDeSpalat&);
    ~MasinaDeSpalat(){}
};
MasinaDeSpalat::MasinaDeSpalat() : Masina(), cantitateDet(0), temperatura(0), programCurent("inexistent") {}

MasinaDeSpalat::MasinaDeSpalat(vector<string> programe, double cantitateDet, double temperatura, double capacitateMax, double cantitateRufe, string timer, string erori, string programCurent)
    : Masina(capacitateMax, cantitateRufe, timer, erori), programe(programe), cantitateDet(cantitateDet), temperatura(temperatura), programCurent(programCurent) {}

MasinaDeSpalat::MasinaDeSpalat(const MasinaDeSpalat& obj)
    : Masina(obj), programe(obj.programe), cantitateDet(obj.cantitateDet), temperatura(obj.temperatura), programCurent(obj.programCurent) {}

MasinaDeSpalat& MasinaDeSpalat::operator=(const MasinaDeSpalat& obj) {
    if (this!=&obj){
        Masina::operator=(obj);
        this->programe=obj.programe;
        this->cantitateDet=obj.cantitateDet;
        this->temperatura=obj.temperatura;
        this->programCurent=obj.programCurent;
    }
    return *this;
}

istream& MasinaDeSpalat::citire(istream& in) {
    Masina::citire(in);
    int numPrograme;
    cout<<"Numarul de programe: "<<endl;
    in>>numPrograme;
    programe.resize(numPrograme);
    cout<<"Introduceti programele: "<<endl;
    for (int i=0; i<numPrograme; ++i) {
        in>>programe[i];
    }
    cout<<"Alege programul Curent:"<<endl;
    in>>programCurent;
    cout<<"Cantitate detergent: "<<endl;
    in>>cantitateDet;
    cout<<"Temperatura: "<<endl;
    in>>temperatura;
    return in;
}

ostream& MasinaDeSpalat::afisare(ostream& out) const {
    Masina::afisare(out);
    out<<"Programe: ";
    for (const auto& program : programe) {
        out<<" "<<program<<endl;
    }
    out<<endl;
    out<<"Programul curent este"<<programCurent<<endl;
    out<<"Cantitate detergent: "<<cantitateDet<<endl;
    out<<"Temperatura: "<<temperatura<<endl;
    return out;
}

istream& operator>>(istream& in, MasinaDeSpalat& obj) {
    return obj.citire(in);
}
ostream& operator<<(ostream& out, const MasinaDeSpalat& obj) {
    return obj.afisare(out);
}

class MasinaSpalUsc:public MasinaDeSpalat
{
    int nrFolosiri;
public:
   MasinaSpalUsc();
   MasinaSpalUsc(vector<string>, double, double, double, double, string, string, string, int);
   MasinaSpalUsc(const MasinaSpalUsc&);
   MasinaSpalUsc& operator=(const MasinaSpalUsc&);
   istream& citire(istream& in);
   ostream& afisare(ostream& out)const;
   friend istream& operator >>(istream& in, MasinaSpalUsc&);
   friend ostream& operator <<(ostream& out, const MasinaSpalUsc&);
};
MasinaSpalUsc::MasinaSpalUsc():MasinaDeSpalat(), nrFolosiri(0) {}

MasinaSpalUsc::MasinaSpalUsc(vector<string> programe, double cantitateDet, double temperatura, double capacitateMax, double cantitateRufe, string timer, string erori, string programCurent, int nrFolosiri)
    : MasinaDeSpalat(programe, cantitateDet, temperatura, capacitateMax, cantitateRufe, timer, erori, programCurent), nrFolosiri(nrFolosiri) {}

MasinaSpalUsc::MasinaSpalUsc(const MasinaSpalUsc& obj)
    : MasinaDeSpalat(obj), nrFolosiri(obj.nrFolosiri) {}

MasinaSpalUsc& MasinaSpalUsc::operator=(const MasinaSpalUsc& obj) {
    if (this!=&obj) {
        MasinaDeSpalat::operator=(obj);
        this->nrFolosiri=obj.nrFolosiri;
    }
    return *this;
}

istream& MasinaSpalUsc::citire(istream& in) {
    MasinaDeSpalat::citire(in);
    cout<<"Numarul de folosiri: ";
    in>>nrFolosiri;
    return in;
}

ostream& MasinaSpalUsc::afisare(ostream& out) const {
    MasinaDeSpalat::afisare(out);
    out << "Numarul de folosiri: "<<nrFolosiri<<endl;
    return out;
}

istream& operator>>(istream& in, MasinaSpalUsc& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream& out, const MasinaSpalUsc& obj) {
    return obj.afisare(out);
}



class Uscator:public Masina
{
    vector<string>programe;
    string programCurent;
    int nrFolosiri;
public:

    Uscator();
    Uscator(double, double, string, string, vector<string>, string, int);
    Uscator(const Uscator&);
    Uscator& operator=(const Uscator&);
    istream& citire(istream& in);
    ostream& afisare(ostream& out)const;
    friend istream& operator >>(istream& in, Uscator&);
    friend ostream& operator <<(ostream& out, const Uscator&);
    ~Uscator(){};
};

Uscator::Uscator(): Masina(), programCurent("inexistent"), nrFolosiri(0){}
Uscator::Uscator(double capacitateMax, double cantitateRufe, string timer, string erori, vector<string>programe, string programCurent, int nrFolosiri):Masina(capacitateMax, cantitateRufe,timer, erori),
programe(programe), programCurent(programCurent), nrFolosiri(nrFolosiri){}
Uscator::Uscator(const Uscator& obj):Masina(obj),programe(obj.programe), programCurent(obj.programCurent), nrFolosiri(obj.nrFolosiri){}
Uscator& Uscator:: operator =(const Uscator& obj)
{
    if(this!=&obj)
    {
        Masina::operator=(obj);
        this->programe=programe;
        this->programCurent=programCurent;
        this->nrFolosiri=nrFolosiri;
    }
    return *this;
}
istream& Uscator::citire(istream& in) {
    Masina::citire(in);
    int numPrograme;
    cout<<"Numarul de programe: "<<endl;
    in>>numPrograme;
    programe.resize(numPrograme);
    cout<<"Introduceti programele: "<<endl;
    for (int i=0; i<numPrograme; ++i) {
        in>>programe[i];
    }
    cout<<"Alege programul curent: "<<endl;
    in>>programCurent;
    cout<<"Numarul de folosiri: "<<endl;
    in>>nrFolosiri;
    return in;
}

ostream& Uscator::afisare(ostream& out) const {
    Masina::afisare(out);
    out<<"Programe: ";
    for(const auto& program : programe) {
        out<<" "<<program << endl;
    }
    out<<endl;
    out<<"Programul curent este "<<programCurent << endl;
    out<<"Numarul de folosiri: "<<nrFolosiri << endl;
    return out;
}

istream& operator>>(istream& in, Uscator& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream& out, const Uscator& obj) {
    return obj.afisare(out);
}

template <class T> class Utilizator: public Iointerface
{
    string nume;
    map<int, T> programSpalare;
    map<int, T> programUscare;
public:
    Utilizator();
    Utilizator(string nume, map<int, T> programSpalare, map<int, T>programUscare);
    Utilizator(const Utilizator&);
    Utilizator& operator=(const Utilizator&);
    istream& citire(istream& in);
    ostream& afisare(ostream& out)const;
    template <class U>
    friend istream& operator>>(istream& in, Utilizator<U>& obj);

    template <class U>
    friend ostream& operator<<(ostream& out, const Utilizator<U>& obj);
    ~Utilizator(){}
};
template<class T>
Utilizator<T>::Utilizator() : nume("Necunoscut"){}

template<class T>
Utilizator<T>::Utilizator(string nume, map<int, T>programSpalare, map<int, T>pogramUscare)
    : nume(nume), programSpalare(programSpalare), programUscare(programUscare) {}

template<class T>
Utilizator<T>::Utilizator(const Utilizator& obj)
    : nume(obj.nume), programSpalare(obj.programSpalare), programUscare(obj.programUscare) {}

// Operator de atribuire

template<class T>
Utilizator<T>& Utilizator<T>::operator=(const Utilizator& obj) {
    if(this != &obj) {
        this->nume = obj.nume;
        this->programSpalare=obj.programSpalare;
        this->programUscare=obj.programUscare;
    }
    return *this;
}

// Metode de citire și afișare

template<class T>
istream& Utilizator<T>::citire(istream& in)
{
    cout<<"Nume utilizator: "<<endl;
    in>>nume;

    int nrMasini1;
    cout << "Numarul de masini pentru spalat: "<<endl;
    in >> nrMasini1;
    programSpalare.clear();
    for (int i=0; i<nrMasini1; ++i) {
        int cheie;
        T valoare1, valoare2;
        cout << "Introduceti cheie (int) masina de spalat " << i + 1 << ": "<<endl;
        in>>cheie ;
        cout<<"Ora de inceput si ora de final"<<endl;
        in>> valoare1>>valoare2;
        programSpalare[cheie] = make_pair(valoare1, valoare2);
    }

    int nrMasini2;
    cout << "Numarul de masini pentru uscat: ";
    in >> nrMasini2;
    programUscare.clear();
    for (int i = 0; i < nrMasini2; ++i) {
        int cheie;
        string valoare1, valoare2;
        cout << "Introduceti cheie (int)masina de uscat " << i + 1 << ": ";
        in >> cheie;
        cout<<"Ora de inceput si ora de final"<<endl;
        in>>valoare1>>valoare2;
        programUscare[cheie]=make_pair(valoare1, valoare2);
    }

    return in;
}
template <>
istream& Utilizator<vector<pair<int, int>>>::citire(istream& in)
{

    cout<<"Nume utilizator: "<<endl;
    in>>nume;

    int nrMasini1;
    cout<<"Numarul de masini pentru spalat: "<<endl;
    in>>nrMasini1;
    programSpalare.clear();
    for (int i=0; i<nrMasini1; ++i) {
        int cheie;
        vector<pair<int, int>> valori;
        cout <<"Introduceti cheie (int) pentru masina de spalat "<<i + 1<< ": "<<endl;
        in>>cheie;
        cout<<"Numarul de programari pentru aceasta masina: "<<endl;
        int nrValori;
        in>>nrValori;
        valori.resize(nrValori);
        cout<<"Introduceti programarile pentru aceasta masina: "<<endl;

        for(int j=0; j<nrValori; ++j)
            in>>valori[j].first>>valori[j].second;

        programSpalare[cheie]=valori;
    }

    int nrMasini2;
    cout << "Numarul de masini pentru uscat: "<<endl;
    in >> nrMasini2;
    programUscare.clear();
    for (int i = 0; i < nrMasini2; ++i) {
        int cheie;
        vector<pair<int, int>> valori;
        cout<<"Introduceti cheie (int) pentru masina de uscat " << i + 1 << ": "<<endl;
        in>>cheie;
        cout<<"Numarul de programari pentru acest uscator: "<<endl;
        int nrValori;
        in>>nrValori;
        valori.resize(nrValori);
        cout<<"Introduceti perechile pentru acest uscator: "<<endl;
        for (int j=0; j<nrValori; ++j) {
            in>>valori[j].first>>valori[j].second;
        }
        programUscare[cheie]=valori;
    }

    return in;
}


template<class T>
ostream& Utilizator<T>::afisare(ostream& out)const
{
    out<<"Nume utilizator: "<<nume<<endl;

    out<<"Programari la spalat:"<<endl;
    for (const auto& [cheie, valoare] : programSpalare)
        out<<"Masina: "<<cheie<<"  Incepe:"<<valoare.first<<"  Se termina"<<valoare.second<<endl;

    out<<"Programari la uscat:"<<endl;
    for (const auto& [cheie, valoare] : programUscare)
        out<<"Uscatorul"<<cheie<<" Incepe"<<valoare.first<<" Se termina" <<valoare.second<<endl;

    return out;
}

template<>
ostream& Utilizator<vector<pair<int, int>>>::afisare(ostream& out)const
{
    out<<endl;
    out<<"Nume utilizator:"<<nume<<endl;
    out<<"Programari la spalat:"<<endl;
    for(const auto &[cheie,valori]:programSpalare)
    {
    out<<"Masina"<<cheie<<"Programari:";
        for(const auto& val:valori)
            out<<"("<<val.first<<"-"<<val.second<<")";
    out<<endl;
    }
    out<<"Programari la uscat:"<<endl;
    for(const auto &[cheie,valori]:programUscare)
    {
    out<<"Masina"<<cheie<<"Programari:";
        for(const auto& val:valori)
        out<<"("<<val.first<<"-"<<val.second<<")";
    out<<endl;
    }
    return out;
}
template <class U>
istream& operator >>(istream& in, Utilizator<U>& obj)
{
    return obj.citire(in);
}
template <class U>
ostream& operator<<(ostream& out, const Utilizator<U>& obj)
{
     return obj.afisare(out);
}



class Spalatorie:public Iointerface
{
    int nrMasini;
    vector<Masina> listaMasina;
    map<int, set<int>> disponibilitate;

public:


    Spalatorie();
    Spalatorie(int, vector<Masina>, map<int, set<int>>);
    Spalatorie(const Spalatorie&);
    Spalatorie& operator =(const Spalatorie&);
    istream& citire(istream& in);
    ostream& afisare(ostream& out)const;
    vector<Masina> getMasina()
    {
        return listaMasina;
    }
    void setMasina(vector<Masina>& obj)
    {
        this->listaMasina=obj;
    }
    map<int, set<int>> getDisp()
    {
        return disponibilitate;
    }
    friend istream& operator>>(istream& in, Spalatorie&);
    friend ostream& operator<<(ostream& out, const Spalatorie&);

};
Spalatorie::Spalatorie():nrMasini(0){}

Spalatorie::Spalatorie(int nrMasini, vector<Masina> listaMasina, map<int, set<int>> disponibilitate)
    : nrMasini(nrMasini), listaMasina(listaMasina), disponibilitate(disponibilitate) {}

Spalatorie::Spalatorie(const Spalatorie& obj) {
    nrMasini=obj.nrMasini;
    listaMasina=obj.listaMasina;
    disponibilitate=obj.disponibilitate;
}

Spalatorie& Spalatorie::operator=(const Spalatorie& obj) {
    if (this!=&obj) {
        nrMasini=obj.nrMasini;
        listaMasina=obj.listaMasina;
        disponibilitate=obj.disponibilitate;
    }
    return *this;
}
istream& Spalatorie::citire(istream& in)
{
    cout<<"Numarul de masini: ";
    in>>nrMasini;

    cout<<"Introduceti detaliile pentru fiecare masina:"<<endl;
    for (int i=0; i<nrMasini; ++i){
        Masina masina;
        cout << "Masina "<<i+1 << ":" << endl;
        in>>masina;
        listaMasina.push_back(masina);
    }

    cout<<"Introduceti detaliile pentru disponibilitatea masinilor:"<<endl;
    for (int i=0; i<nrMasini; ++i)
    {
        int masina;
        cout<<""<<i+1<<": "<<endl;
        in>>masina;
        int nrOre;
        cout<<"Numarul de ore pentru masina " <<i+1<< ":";
        in>>nrOre;
        set<int>ore;
        cout<<"Introduceti orele pentru masina " << i+1<<":";
        for(int j=0; j<nrOre; ++j)
        {
            int ora;
            in>>ora;
            ore.insert(ora);
        }
        disponibilitate[masina]=ore;
    }

    return in;
}

ostream& Spalatorie::afisare(ostream& out) const {
    out<<"Numarul de masini: "<<nrMasini<<endl;

    out<<"Detaliile pentru fiecare masina:"<<endl;
    for(int i=0; i<nrMasini; ++i)
        out<<listaMasina[i]<<endl;

    out<<"Detaliile pentru disponibilitatea masinilor:" << endl;
    for(const auto& [id, ore]:disponibilitate)
    {
        out<<"Masina "<<id<<", Ore disponibile: ";
        for(const auto& ora : ore)
            out<<ora<<" ";
        out<<endl;
    }

    return out;
}
istream& operator >>(istream& in, Spalatorie& obj)
{
     return obj.citire(in);
}

ostream& operator <<(ostream& out, const Spalatorie& obj)
{
    return obj.afisare(out);
}

class Menu
{
private:
    static Menu* ptrInstance;
public:

    static Menu* getInstance();
    void adaugaMasinaDeSpalat(MasinaDeSpalat* masina, vector<Masina*>&listaMasina);
    void adaugaUscator(Uscator* masina, vector<Masina*>&listaMasina);
    void stergeMasina(Masina& masina, vector<Masina*>&listaMasina);
    list<MasinaDeSpalat*> filtreazaMasiniDeSpalat(const vector<Masina*>& listaMasina);
    list<Uscator*>filtreazaUscator(const vector<Masina*>&listaMasina);
    void showSpalDis(Spalatorie& spalatorie, vector<Masina*>& masini);
};
Menu* Menu :: ptrInstance = NULL;
Menu* Menu:: getInstance()
{
    if(Menu::ptrInstance != NULL)
    {
        return Menu::ptrInstance;
    }
    else
    {
       ptrInstance = new Menu();
       return ptrInstance;
    }
}
void Menu::adaugaMasinaDeSpalat(MasinaDeSpalat* masina, vector<Masina*>&listaMasina)
{
    Masina* ptr=dynamic_cast<Masina*>(masina);
    listaMasina.push_back(ptr);
}

void Menu::adaugaUscator(Uscator* masina, vector<Masina*>&listaMasina)
{
    Masina* ptr=dynamic_cast<Masina*>(masina);
    listaMasina.push_back(ptr);
}
void Menu::stergeMasina(Masina& masina, vector<Masina*>&listaMasina)
{
    for(auto it=listaMasina.begin(); it!=listaMasina.end(); ++it)
    {
        if (**it==masina)
        {
            listaMasina.erase(it);
            cout<<"Masina a fost stearsa"<<endl;
            return;
        }
    }
}

list<MasinaDeSpalat*> Menu:: filtreazaMasiniDeSpalat(const vector<Masina*>& listaMasina)
{
    list<MasinaDeSpalat*> masiniDeSpalat;
    for(auto* masina:listaMasina)
    {
        if(auto* masinaDeSpalat=dynamic_cast<MasinaDeSpalat*>(masina))
        {
            masiniDeSpalat.push_back(masinaDeSpalat);
        }
    }
    return masiniDeSpalat;
}
list<Uscator*> Menu:: filtreazaUscator(const vector<Masina*>&listaMasina)
{
    list<Uscator*>uscatoare;
    for(auto* masina:listaMasina)
    {
        if(auto* uscator=dynamic_cast<Uscator*>(masina))
            uscatoare.push_back(uscator);
    }
    return uscatoare;
}

void Menu::showSpalDis(Spalatorie& spalatorie, vector<Masina*>&masini)
{

    cout<<"Masinile de Spalat Disponibile:"<<endl;
    map<int, set<int>> myMap=spalatorie.getDisp();
    for(auto masina: masini)
    {
        if(typeid(masina)==typeid(MasinaDeSpalat))
        {
            int i=masina->getId();
            cout<<"Masina"<<i<<":";
            for (const auto& elem:myMap[i])
            {
                cout<<elem<<" ";
            }
            cout<<endl;
        }
    }
    cout<<endl;
    cout<<"Uscatoarele Disponibile:"<<endl;
    for(auto masina: masini)
    {
        if(typeid(masina)==typeid(Uscator))
        {
            int i=masina->getId();
            cout<<"Uscatorul"<<i<<":";
            for (const auto& elem:myMap[i])
            {
                cout<<elem<<" ";
            }
            cout<<endl;
        }
    }
}


int main()
{
    cout<<"pentru a adauga o masina de spalat apasati tasta 1"<<endl;
    cout<<"pentru a adauga un uscator apasati tasta 2"<<endl;
    cout<<"pentru a vedea inventarul de masini de spalat si uscatoare apasati tasta 3"<<endl;
    cout<<"pentru a vedea disponibilitatea masinilor si uscatparelor apasati tasta 4"<<endl;
    cout<<"pentru a sterge o masina de spalat/uscat apasati tasta 5"<<endl;
    cout<<"pentru a face o programare apasati tasta 6"<<endl;


    vector<string> programe={"Normal", "Rapid", "Delicat"};
    MasinaDeSpalat m1(programe, 2.5, 40.0, 8.0, 5.0, "00:30", "Nicio eroare", "Normal");
    MasinaDeSpalat m2(programe, 1.5, 60.0, 5, 3, "1:20", "Nicio eroare", "Nicunul");
    Uscator a1(10.0, 5.0, "00:30", "Nicio eroare", programe, "Normal", 10);
    Uscator a2(7.0, 2.5, "02:20", "Nicio eroare", programe, "Normal", 7);

    vector<Masina>listaDeMasini;
    listaDeMasini.push_back(m1);
    listaDeMasini.push_back(m2);
    listaDeMasini.push_back(a1);
    listaDeMasini.push_back(a2);

    set<int> mySet;
    map<int, set<int>>myMap;
    for(int i=0; i<=23; i++)
    {
        mySet.insert(i);
    }
    myMap[1]=mySet;
    myMap[2]=mySet;
    myMap[3]=mySet;
    myMap[4]=mySet;

    Spalatorie spalatorie1(4, listaDeMasini, myMap);
    Menu menu;

    int optiune;
    try
    {
        do{
        cin>>optiune;
        if(cin.fail())
        {
            cin.clear();
            throw invalid_argument("Optiunea nu este corecta");

        }
        if(optiune<1 || optiune>7)
            throw invalid_argument("Optiunea nu este corecta");

        switch(optiune)
        {
        case 1:
            {
                MasinaDeSpalat m1;
                cin>>m1;
                vector<Masina> masini1=spalatorie1.getMasina();
                masini1.push_back(m1);
                spalatorie1.setMasina(masini1);
                break;
            }
        case 2:
            {
                Uscator m1;
                cin>>m1;
                vector<Masina> masini1=spalatorie1.getMasina();
                masini1.push_back(m1);
                spalatorie1.setMasina(masini1);

            }
        case 3:
            {

                vector<Masina> masini2=spalatorie1.getMasina();
                vector<Masina*>ptrMasina;
                 for (auto& masina : masini2)
                {
                        ptrMasina.push_back(&masina);
                }
                menu.showSpalDis(spalatorie1, ptrMasina);
            }
        default:
            {
                optiune=7;
                break;
            }
        }
        }
    while(optiune!=7);
    }
        catch(const invalid_argument& e)
        {
            cout<<"Eroare:"<<e.what()<<endl;
        }

    return 0;
}
