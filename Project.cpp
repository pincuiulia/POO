#include <iostream>
#include <cstring>

using namespace std;

//clasa exceptie custom
class Varsta_Invalida : public std::exception {
public:
    const char* what() const noexcept override {
        return "Project managerul nu are varsta necesara pentru functie.";
    }
};

// DATA

class Data //facem clasa ddl cu mostenire cu un camp bool respectat/nerespectat
   {
    int zi, luna, an;

public:
    // constructor
    Data(int zi = 0, int luna = 0, int an = 0){
        this->zi = zi;
        this->luna = luna;
        this->an = an;
    }

    // constructor de copiere
    Data(Data &d){
        this->zi = d.zi;
        this->luna = d.luna;
        this->an = d.an;
    }

    // setteri si getter
    void setData(int zi, int luna, int an){
        this->zi = zi;
        this->luna = luna;
        this->an = an;
    }
    // zi
    void setZi(int zi){
        this->zi = zi;
    }
    int getZi(){
        return this->zi;
    }
    // luna
    void setLuna(int luna){
        this->luna = luna;
    }
    int getLuna(){
        return this->luna;
    }
    // an
    void setAn(int an){
        this->an = an;
    }
    int getAn(){
        return this->an;
    }
    // operatori
    Data &operator=(Data const &d) //de ce trebuie const?
    {
        this->zi = d.zi;
        this->luna = d.luna;
        this->an = d.an;
        return *this;
    }
    // afisare
    friend ostream &operator<<(ostream &, Data &);
};
ostream &operator<<(ostream &out, Data &d){
    out << d.zi << "." << d.luna << "." << d.an;
    return out;
}

class Perioada{

    Data start;
    Data finish;

public:
    // constructor de initializare
    Perioada() : start(), finish() {}

    // constructor
    Perioada(Data start, Data finish){
        this->start = start;
        this->finish = finish;
    }

    // constructor de copiere
    Perioada(Perioada &p){
        this->start = p.start;
        this->finish = p.finish;
    }

    // setteri si getteri

    void setPerioada(Data start, Data finish){
        this->start = start;
        this->finish = finish;
    }
    // start si finish
    Data getStart(){
        return this->start;
    }

    Data getFinish(){
        return this->start;
    }

    // operatori
    Perioada &operator=(Perioada &d);

    // afisare
    friend ostream &operator<<(ostream &, Perioada &p);
};

ostream &operator<<(ostream &out, Perioada &p){
    out << p.start << " - " << p.finish;
    return out;
}

Perioada &Perioada::operator=(Perioada &d){
    this->start = d.start;
    this->finish = d.finish;
    return *this;
}

// PERSOANA

class Persoana
{
private:

    static int nrPersoane;
    char  telefon[11];

protected:

    char *nume, *prenume; //minim 2 modificatori de acces

public:
    // constructori
    Persoana(){
        ++nrPersoane;
        this->nume = NULL;
        this->prenume = NULL;
        strcpy(this->telefon, "0770000000");
    }

    Persoana(char *nume, char *prenume, char *telefon){
        ++nrPersoane;
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
        this->prenume = new char[strlen(prenume) + 1];
        strcpy(this->prenume, prenume);
        strcpy(this->telefon, telefon);
    }

    // destructor
    ~Persoana(){
        --nrPersoane;
        delete this->nume;
        delete this->prenume;
    }

    // constructor de copiere
    Persoana(Persoana &p){
        ++nrPersoane;
        this->nume = new char[strlen(p.nume) + 1];
        strcpy(this->nume, p.nume);
        this->prenume = new char[strlen(p.prenume) + 1];
        strcpy(this->prenume, p.prenume);
        strcpy(this->telefon, p.telefon);
    }

    Persoana &operator=(Persoana &p){
        this->nume = new char[strlen(p.nume) + 1];
        strcpy(this->nume, p.nume);
        this->prenume = new char[strlen(p.prenume) + 1];
        strcpy(this->prenume, p.prenume);
        strcpy(this->telefon, p.telefon);
        return *this;
    }

    // setteri & getteri
    void setNume(char *nume){
        delete this->nume;
        this->nume = new char[strlen(nume) + 1];
        strcpy(this->nume, nume);
    }

    char *getNume(){
        return this->nume;
    }

    void setPrenume(const char *prenume){
        delete this->prenume;
        this->prenume = new char[strlen(prenume) + 1];
        strcpy(this->prenume, prenume);
    }

    char *getPrenume(){
        return this->prenume;
    }

    void setTelefon(char *telefon){
        strcpy(this->telefon, telefon);
    }

    char *getTelefon(){
        return this->telefon;
    }

    void afisare(){
        cout << this->nume << " " << this->prenume << " " << this->telefon;
    }

    static void afisareNrPersoane() {
        cout << "Exista " << nrPersoane << " persoane in proiect.";
    }

    friend ostream &operator<<(ostream &, Persoana &);
};

int Persoana::nrPersoane = 0;

ostream &operator<<(ostream &out, Persoana &p){
    out <<endl<< "--->Nume: " << p.nume << " " << p.prenume << "; Telefon: " << p.telefon;
    return out;
}

//Project_Manager

class Project_Manager : public Persoana{

private:
    Data data_nastere;
    char *departament;

public:
    Project_Manager(char *nume, char *prenume, char *telefon, Data data_nastere, char *departament) : Persoana(nume,prenume,telefon)
    {
        this->data_nastere=data_nastere;
        this->departament = new char[strlen(departament) + 1];
        strcpy(this->departament,departament);
    }

    //cpnstructor de initializare
    Project_Manager(): Persoana(){
        this->data_nastere = Data (0,0,0);
    }

    Project_Manager(Project_Manager& p): Persoana(dynamic_cast<Persoana&>(p)) {
        this->setTelefon(p.getTelefon());
        this->data_nastere = p.data_nastere;
        this->departament = new char[strlen(p.departament) + 1];
        strcpy(this->departament, p.departament);
    }

    Project_Manager &operator=(Project_Manager &p)
    {
        this->nume = new char[strlen(p.nume) + 1];
        strcpy(this->nume, p.nume);
        this->prenume = new char[strlen(p.prenume) + 1];
        strcpy(this->prenume, p.prenume);
        this->setTelefon(p.getTelefon());
        this->data_nastere = p.data_nastere;
        this->departament = new char[strlen(p.departament) + 1];
        strcpy(this->departament, p.departament);
        return *this;
    }

    Data get_data_nastere(){
        return data_nastere;
    }
    void verificaVarsta() {
        if (data_nastere.getAn() > 2003 || data_nastere.getAn() < 1999) {
            throw Varsta_Invalida();
        }
        std::cout << "Project Managerul are varsta necesara.\n";}

    friend ostream& operator<<(ostream& out, Project_Manager& p) {
        out << static_cast<Persoana&>(p)<<"; Data nastere: "<< p.data_nastere << "; Departament: " << p.departament <<endl;
        return out;
    }
};


// TASK

class Task{
    static int nrTaskuri;
    char *nume;
    int nrResponsabili;
    Persoana *responsabili;
    Data deadline;

public:
    // constructor
    Task(char *nume, int nrResponsabili, Persoana *responsabili, Data deadline);

    // constructor de initializare

    Task();

    // constructor de copiere
    Task(Task &t);

    // destructor

    ~Task(){
        delete this->nume;
        delete[] this->responsabili;
        this->nrResponsabili = 0;
        --this->nrTaskuri;
    }
    // operatori
    Task &operator=(Task &t);

    Task &operator+(Persoana &p); // task + persoana => imi adauga persoana la task

    //getter
    Data getDataTask(){
        return this->deadline;
    }

    char* getNumeTask(){
        return this->nume;
    }

   void afisareNrTaskuri() { //aici putem sa folosim interfata
        cout << "In momentul actual, exista " << nrTaskuri << " taskuri, care asteapta sa fie efectuate.";
    }

    // afisare

    friend ostream &operator<<(ostream &, Task &);
};

int Task::nrTaskuri = 0;

// constructor
Task::Task(char *nume, int nrResponsabili, Persoana *responsabili, Data deadline)
{
    ++this->nrTaskuri;
    this->nume = new char[strlen(nume) + 1];
    strcpy(this->nume, nume);
    this->nrResponsabili = nrResponsabili;
    this->responsabili = new Persoana[nrResponsabili];
    for (int i = 0; i < nrResponsabili; ++i)
    {
        this->responsabili[i] = responsabili[i];
    }
    this->deadline = deadline;
}

Task::Task()
{
    ++this->nrTaskuri;
    this->nume = NULL;
    this->nrResponsabili = 0;
}

Task::Task(Task &t)
{
    ++this->nrTaskuri;
    this->nume = new char[strlen(t.nume) + 1];
    strcpy(this->nume, t.nume);
    this->nrResponsabili = t.nrResponsabili;
    this->responsabili = new Persoana[t.nrResponsabili];
    for (int i = 0; i < t.nrResponsabili; ++i)
    {
        this->responsabili[i] = t.responsabili[i];
    }
    this->deadline = t.deadline;
}

Task &Task::operator=(Task &t)
{
    delete[] this->nume;
    this->nume = new char[strlen(t.nume) + 1];
    strcpy(this->nume, t.nume);
    this->nrResponsabili = t.nrResponsabili;
    delete[] this->responsabili;
    this->responsabili = new Persoana[t.nrResponsabili];
    for (int i = 0; i < t.nrResponsabili; ++i)
    {
        this->responsabili[i] = t.responsabili[i];
    }
    this->deadline = t.deadline;
    return *this;
}

Task &Task::operator+(Persoana &p)
{
    Persoana aux[this->nrResponsabili];
    for (int i = 0; i < this->nrResponsabili; ++i)
    {
        aux[i] = this->responsabili[i];
    }
    delete[] this->responsabili;
    this->responsabili = new Persoana[this->nrResponsabili + 1];
    for (int i = 0; i < this->nrResponsabili; ++i)
    {
        this->responsabili[i] = aux[i];
    }
    this->responsabili[this->nrResponsabili] = p;
    ++this->nrResponsabili;

    return *this;
}
// afisare
ostream &operator<<(ostream &out, Task &t)
{
    out << "Task: " << t.nume << endl
        << "Deadline: " << t.deadline << endl
        << "Numar responsabili: " << t.nrResponsabili << endl;

    for(int i=0;i<t.nrResponsabili; ++i)
        out << "Responsabili: " << t.responsabili[i] << endl;


    return out;
}

// PROIECT

class Proiect
{
private:
    Project_Manager PM;
    Task *taskuri;
    int nrTaskuri;
    Perioada perioada;

public:
    // constructori
    Proiect(Project_Manager PM, Task *taskuri, Perioada perioada, int nrTaskuri);
    Proiect(){
        nrTaskuri=0;
    }
    Proiect(Proiect &p);
    // destructor
    ~Proiect();
    // setteri si getteri
    // PM

    void setPM(Project_Manager PM)
    {
        this->PM = PM;
    }

    Project_Manager getPM()
    {
        return this->PM;
    }

    // nrtaskuri
    void setNrTaskuri(int nrTaskuri)
    {
        this->nrTaskuri = nrTaskuri;
    }

    int getNrTaskuri()
    {
        return this->nrTaskuri;
    }

    // Taskuri
    void setTaskuri(Task *taskuri, int nrTaskuri)
    {
        delete this->taskuri;
        this->taskuri = new Task[nrTaskuri];
        for (int i = 0; i < nrTaskuri; i++)
            this->taskuri[i] = taskuri[i];
    }

    Task *getTaskuri()
    {
        return this->taskuri;
    }

    // perioada
    void setPerioadaProiect(Perioada perioada)
    {
        this->perioada = perioada;
    }

    Perioada getPerioadaProiect()
    {
        return this->perioada;
    }

    // operatori
    friend ostream &operator<<(ostream &out, Proiect &p);

    // metoda
    int CalculTaskuri(int nr , Perioada p);
};

// constructori
Proiect::Proiect(Project_Manager PM, Task *taskuri, Perioada perioada, int nrTaskuri)
{
    this->PM = PM;
    this->nrTaskuri = nrTaskuri;
    this->taskuri = new Task[nrTaskuri];
    for (int i = 0; i < nrTaskuri; i++)
        this->taskuri[i] = taskuri[i];
    this->perioada = perioada;
}

Proiect::Proiect(Proiect &p)
{
    this->PM = p.PM;
    this->nrTaskuri = p.nrTaskuri;
    this->taskuri = new Task[p.nrTaskuri];
    for (int i = 0; i < nrTaskuri; i++)
        this->taskuri[i] = p.taskuri[i];
    this->perioada = p.perioada;
}

// destructor

Proiect::~Proiect()
{
    delete this->taskuri;
    nrTaskuri = 0;
}

// operatori

ostream &operator<<(ostream &out, Proiect &p)
{
    out << "Project Managerul proiectului are urmatoarele date:" << p.PM << " " << endl
        << "Numar Taskuri: " << p.nrTaskuri << endl<< "Taskuri: " <<endl;
    for(int i=0;i<p.nrTaskuri;++i)
        out << "~"<<p.taskuri[i].getNumeTask() << endl;
    out <<"Perioada: " << p.perioada<<endl<<endl;
    return out;
}
// metoda

int Proiect::CalculTaskuri(int nr, Perioada p){
    nr=0;
    for(int i=0;i<this->nrTaskuri;++i)

        if(this->taskuri[i].getDataTask().getAn() == p.getFinish().getAn() && this->taskuri[i].getDataTask().getAn() == p.getStart().getAn() )
            if(this->taskuri[i].getDataTask().getLuna() >= p.getStart().getLuna() && this->taskuri[i].getDataTask().getLuna() <= p.getFinish().getLuna())
                if(this->taskuri[i].getDataTask().getZi() >= p.getStart().getZi() && this->taskuri[i].getDataTask().getZi() <= p.getFinish().getZi())
                {
                    cout<<nr;
                    nr++;
                }


    return nr;

}

//LOCATIE
class Locatie {
    char *adresa, capacitate[6]; // capacitate = mica/mare/medie

public:
    Locatie() {
        this->adresa = new char[1];
        strcpy(this->adresa, "");
        strcpy(capacitate, "idk");
    }

    Locatie(char *adresa, char *capacitate) {
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        strcpy(this->capacitate, capacitate);
    }

    Locatie(char *adresa) {
        this->adresa = new char[strlen(adresa) + 1];
        strcpy(this->adresa, adresa);
        strcpy(this->capacitate, "idk");
    }


    Locatie(Locatie& l) {
        this->adresa = new char[strlen(l.adresa) + 1];
        strcpy(this->adresa, l.adresa);
        strcpy(this->capacitate, l.capacitate);
    }

    Locatie& operator=(Locatie& l) {
        delete[] this->adresa;
        this->adresa = new char[strlen(l.adresa) + 1];
        strcpy(this->adresa, l.adresa);
        strcpy(this->capacitate, l.capacitate);
    }

    char* getAdresa() {
        return this->adresa;
    }

    char* getCapacitate() {
        return this->capacitate;
    }

    friend ostream& operator<<(ostream&, Locatie&);
};

ostream& operator<<(ostream& out, Locatie& l) {
    out << "Adresa " << l.adresa << " are o capacitate " << l.capacitate << ".";
    return out;
}

//SEDINTA

class Sedinta : private Data{ //sa mosteneasca task

private:
    char ora[6];

protected:

    Locatie locatie;
    int nrParticipanti;
    bool verificareLocatie(Locatie& l) {
        if (this->nrParticipanti <= 10) {
            return true;
        }
        if (this->nrParticipanti <= 25) {
            if (strcmp(l.getCapacitate(), "mica") != 0) {
                return true;
            }
            return false;
        }
        if (strcmp(l.getCapacitate(), "mare") == 0) {
            return true;
        }
        return false;
    }

public:
    Sedinta(int zi, int luna, int an, char *ora,Locatie locatie, int nrParticipanti = 0): Data(zi,luna,an){
        strcpy(this->ora,ora);
        this->locatie= locatie;
        this->nrParticipanti = nrParticipanti;
    }

    Sedinta(Data data, char *ora,Locatie locatie, int nrParticipanti = 0): Data(data){
        strcpy(this->ora,ora);
        this->locatie= locatie;
        this->nrParticipanti = nrParticipanti;
    }

    Sedinta(): Data(){
        strcpy(this->ora,"99:99");
    }

    friend ostream &operator<<(ostream &out, Sedinta &s){
        out<<"***Detalii sedinta***"<<endl;
        out<<"Data sedintei: "<< static_cast<Data&>(s)<<endl;
        out<<"Ora: "<<s.ora<<"\n";
        out<<"Locatia: "<<s.locatie<<"\n";
        return out;
    }
};



//SEDINTA PROIECT
class Sedinta_Proiect : public Sedinta , public Proiect{
private:
    Persoana *participanti;
    int nrParticipanti;
public:
    Sedinta_Proiect() : Proiect(),Sedinta(){

        this->participanti=NULL;
        nrParticipanti=0;

    }
    Sedinta_Proiect(Sedinta sedinta, Project_Manager pm, Persoana *participanti, int nrParticipanti): Sedinta(sedinta) {
        this->participanti = new Persoana[nrParticipanti];
        this->nrParticipanti = nrParticipanti;
        for (int i = 0; i < nrParticipanti; ++i) {
            this->participanti[i] = participanti[i];
        }
    }

    ~Sedinta_Proiect(){
        cout<<"Sedinta nu va mai avea loc";
    }

    friend ostream& operator<<(ostream&, Sedinta_Proiect&);

    //Afisare participanti
    void Participanti(){
        if(nrParticipanti>5){
            cout<<"Lista cu participantii este urmatoarea: ";
            for(int i=0;i<=nrParticipanti;++i)
                cout<<participanti[i]<<" "<<endl;
        }
        else{
            cout<<0;
        }
    }
    void Numar_Participanti(){
        if(nrParticipanti>5)
            cout<<"Numarul de participanti este: "<<nrParticipanti;
        else
            cout<<0;

    }
};

ostream& operator<<(ostream& out, Sedinta_Proiect& s) {
    out << static_cast<Sedinta&>(s) << endl;
    if (s.verificareLocatie(s.locatie)) {
        out << s.locatie;
    } else {
        out << "! LOCATIA NU ESTE POTRIVITA";
    }
    return out;
}

//**CLASA ABSTRACTA SI DERIVATELE**
class Bani_ONG {
protected:
    static float buget_propriu, fonduri_europene, buget_facultate;
    int bugete_alocate=0;
public:
    virtual void calcul_buget() = 0;
    virtual void Calcul_nr_Bugete(){
        if (bugete_alocate==0)
            cout<<"Bugetul nu a fost alocat\n";
        else if(bugete_alocate==1)
            cout<<"Bugetul a fost alocat\n";
        else
            cout<<"ATENTIE! Bugetul a fost alocat de mai multe ori!\n";

    }
    virtual void Adaugare_Bani(float suma){
        buget_propriu+=suma;
        //Pentru UPCASTING si pentru a adauga banii generati de proiect
        cout<<"A fost adaugata suma "<<suma<<" la buegtul ONG-ului care are acum "<<buget_propriu<<" RON in bugetul propriu\n";
    };
    virtual ~Bani_ONG() {
        cout<<"PROIECT FINALIZAT \n Bugetul a fost sters \n";
    };
};

float Bani_ONG::buget_propriu=3000;
float Bani_ONG::fonduri_europene=3000;
float Bani_ONG::buget_facultate=3000;


class Buget_Departament : virtual public Bani_ONG {
protected:
    float bugetD;
public:
    void calcul_buget() override {
        bugetD = 0;
        bugetD = bugetD + 15 / 100.0 * buget_propriu + 5 / 100.0 * buget_facultate;
        buget_propriu = buget_propriu - 20 / 100.0 * buget_propriu;
        buget_facultate = buget_facultate - 10 / 100.0 * buget_facultate;
        bugete_alocate++;
        cout << "Bugetul alocat pentru un departament este " << bugetD << " RON, iar bugetul alocat tuturor departamentelor este: "
             << 4 * bugetD << " RON\n";
    }


};

class Buget_Proiect : virtual public Bani_ONG {
protected:
float bugetP;
public:
    void set_buget(int b){
        bugetP=b;
    }
    void calcul_buget() override {

        bugetP = bugetP + 20 / 100.0 * buget_propriu + 30 / 100.0 * fonduri_europene + 10 / 100.0 * buget_facultate;
        buget_propriu = buget_propriu - 20 / 100.0 * buget_propriu;
        fonduri_europene = fonduri_europene - 30 / 100.0 * fonduri_europene;
        buget_facultate = buget_facultate - 10 / 100.0 * buget_facultate;
        bugete_alocate++;
        cout << "Bugetul alocat proiectului este " << bugetP << " RON\n";
    }


};

class Bani_Cheltuiti : public Buget_Proiect, public Buget_Departament {
    float totalBuget;
public:
    void calcul_buget() override {
        totalBuget = bugetD + bugetP;
        cout << "Bani cheltuiți: " << totalBuget << " RON\n";
    }
};

// Clasa interfață Bilet
class Bilet {
public:
    virtual void afisareDetalii() = 0;
    virtual void elibereazaBilet() = 0;
    virtual void accesZonaVIP()=0;
    ~Bilet() {}
};

// Clasa BiletSimplu care implementează interfața Bilet
class BiletSimplu : public Bilet {
public:
    void afisareDetalii() override {
        cout << "Bilet simplu - Detalii:\n"
        <<"-Pret: 30 RON\n"
        <<"-Acces general\n";
    }
    void elibereazaBilet() override {
        cout << "Bilet simplu - Eliberat\n";
    }
    void accesZonaVIP() {
        cout << "NU\n";
    }
};

// Clasa BiletVIP care implementează interfața Bilet
class BiletVIP : public Bilet {
public:
    void afisareDetalii() override {
        cout << "Bilet VIP - Detalii:\n"
        <<"-Pret: 50 RON\n"
        <<"-Acces in zona VIP";
    }
    void elibereazaBilet() override {
        cout << "Bilet VIP - Eliberat\n";
    }
    void accesZonaVIP() {
        cout << "DA\n";
    }
};


int main (){

    Data dataSTART(11, 3, 2023), dataFINISH(18, 4, 2023), data3(14, 4, 2023), data4(20, 4, 2023), data5(16, 4, 2023);
    Perioada perioada1(dataSTART, dataFINISH), perioada2(data3, data4);
    Persoana pm("Iulia", "Pincu", "0763307434"), responsabil1("Ion", "Marcel", "0712345678"), responsabil2("Ana", "Maria", "074567890");
    Persoana responsabili1[] = {responsabil1, responsabil2};
    Persoana  responsabil3("George", "Ionescu", "0761367890"),responsabil4("Floricica", "Margareta", "0781378890"),responsabil5("Bianca", "Malureanu", "0766367270");
    Persoana responsabili2[] = {responsabil3, responsabil4, responsabil5}, responsabili3[] = {responsabil1, responsabil5, responsabil2};
    Task task1("Impartit bilete", 2, responsabili1, data3),task2("Contorizare intrari concurs", 3, responsabili2, data4),task3("Bufet", 3, responsabili3, data5);

    cout<<"Descriere Taskul 1: "<<endl<<endl;

    cout << task1<<endl<<endl<<endl;

// Adaugam responsabil la task
    task1+responsabil3;

    cout<<"Adaugam responsabilul 3 la Taskul 1, dupa care vizualizam situatia actuala a acestuia:"<<endl;
    Project_Manager om("Iulia","Pincu","0763307434",dataSTART,"MF");


    cout<<task1<<endl<<endl<<endl;
    Task taskuri[]={task1,task2,task3};
    Proiect Giveaway(om,taskuri,perioada1,3);
    cout<<"Detalii despre Proiect"<<endl<<endl;
    cout<<Giveaway<<endl<<endl<<endl;

    int taskuri_perioada;

    taskuri_perioada=Giveaway.CalculTaskuri(taskuri_perioada, perioada1);
    cout<<"Numarul de taskuri din perioada "<<perioada1<<" este "<<taskuri_perioada;
    cout<<om<<endl<<endl;

    //SEDINTA
    Sedinta sedinta1(dataSTART,"10:00",Locatie("Facultate")), sedinta2(1,2,3,"23:00","The Pub");
    cout<<sedinta2<<endl<<endl;
    cout<<sedinta1<<endl<<sedinta2; //De ce nu afiseaza locatia??

    //BUGETE

    Bani_ONG* bani= new Buget_Proiect();;
    bani->calcul_buget();
    bani->Calcul_nr_Bugete();


    Bani_ONG* d1= new Buget_Departament();
    d1->calcul_buget();
    d1->calcul_buget();
    d1->calcul_buget();
    d1->Calcul_nr_Bugete();

        //UPCASTING 1
    Buget_Proiect bugetProiect;
    Bani_ONG* baniONG = &bugetProiect;
    baniONG->Adaugare_Bani(1500);




    //DESTRUCTOR VIRTUAL
    Data data_actuala(18,5,2023);
    Bani_ONG *buget = new Buget_Proiect(); //nu se ia in calcul
    buget->calcul_buget();

    //proiectul a trecut iar bugetul acordat trebuie sters
    if (data_actuala.getAn()>dataSTART.getAn())
        delete buget;
    else if(data_actuala.getLuna()>dataSTART.getLuna())
        delete buget;
    else if(data_actuala.getZi()>dataSTART.getZi())
        delete buget;


    cout<<"NU MERGE PROGRAMUL\n"; //DE CE AFISEAZA DE 2 ORI CA BUGETUL A FOST STERS

    //INTERFATA BILET
    Bilet* bilet1 = new BiletSimplu();
    bilet1->afisareDetalii();
    delete bilet1;

    Bilet* bilet2 = new BiletVIP();
    bilet2->accesZonaVIP();
    delete bilet2;


    try {
        om.verificaVarsta();
    } catch (const Varsta_Invalida& e) {
        std::cout << e.what() << "\n";
    }




    return 0;
}
