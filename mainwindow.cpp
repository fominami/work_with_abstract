#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>
#include<iostream>
#include <QString>
#include <QFile>
#include<QTextStream>
#include<string>
#include<QDataStream>
#include<QStandardItemModel>
#include <QMessageBox>
using  namespace std;
struct Items
{
    QString Name;
    QString Date;
    QString Section;
    int count;
    friend QDataStream& operator>>(QDataStream&bin,Items& person);
    friend QDataStream& operator<<(QDataStream&bin,Items& person);
    friend QTextStream& operator>>(QTextStream&bin,Items& person);
    friend ostream& operator<<(ostream&out,Items&person);
};
QDataStream& operator<<(QDataStream&bin,Items& person)
{
    bin<<person.Name<<person.Date<<person.Section<<person.count;
    return bin;
}
QTextStream& operator<<(QTextStream& stream, const Items& stud1)
{
    stream <<" "<<stud1.Name <<" "<<stud1.Date<<" " <<stud1.Section<<" "<< stud1.count;
    return stream;
}
QTextStream& operator>>(QTextStream&bin,Items& person)
{
    bin>>person.Name>>person.Date>>person.Section>>person.count;
    return bin;
}
QDataStream& operator>>(QDataStream&bin,Items& person)
{
    bin>>person.Name>>person.Date>>person.Section>>person.count;
    return bin;
}
ostream& operator<<(ostream&out,Items&person)
{
    out<<person.Name.toStdString()<<" "<<person.Date.toStdString()<<" "<<person.Section.toStdString()<<" "<<person.count<<endl;
    return out;
}
struct Price
{
    QString Name;
    double pr;
    friend QDataStream& operator>>(QDataStream&bin,Price& person);
    friend QDataStream& operator<<(QDataStream&bin,Price& person);
    friend QTextStream& operator>>(QTextStream&bin,Price& person);
    friend ostream& operator<<(ostream&out,Price&person);
};
QDataStream& operator<<(QDataStream&bin,Price& person)
{
    bin<<person.Name<<person.pr;
    return bin;
}
QTextStream& operator<<(QTextStream& stream, const Price& stud1)
{
    stream <<" "<<stud1.Name <<" "<<stud1.pr;
    return stream;
}
QTextStream& operator>>(QTextStream&bin,Price& person)
{
    bin>>person.Name>>person.pr;
    return bin;
}
QDataStream& operator>>(QDataStream&bin,Price& person)
{
    bin>>person.Name>>person.pr;
    return bin;
}
ostream& operator<<(ostream&out, Price&person)
{
    out<<person.Name.toStdString()<<" "<<person.pr<<endl;
    return out;
}
struct Med
{
    QString Name;
    QString Date;
    QString Section;
    double pr;
    int count;
    friend QDataStream& operator<<(QDataStream&bin,Med& person);
    friend QTextStream& operator<<(QTextStream&bin,Med& person);
    friend ostream& operator<<(ostream&out,Med&person);
};
QDataStream& operator<<(QDataStream&bin,Med& person)
{
    bin<<person.Name<<person.Date<<person.Section<<person.pr<<person.count;
    return bin;
}
QTextStream& operator<<(QTextStream& stream, const Med& stud1)
{
    stream <<" "<<stud1.Name <<" "<<stud1.Date<<" " <<stud1.Section<<" "<<stud1.pr<<" "<< stud1.count;
    return stream;
}
ostream& operator<<(ostream&out,Med&person)
{
    out<<person.Name.toStdString()<<" "<<person.Date.toStdString()<<" "<<person.Section.toStdString()<<" "<<person.pr<<" "<<person.count<<endl;
    return out;
}
class ABS_Med
{
public:
    virtual int GetSize()=0;
    virtual void GetMeds(QFile&a,QFile&c)=0;
    virtual void WriteMeds(QFile &a)=0;
    virtual void Putmeds(ostream&a)=0;
    virtual void Putmeds(QFile&a)=0;
    virtual void SortUp()=0;
    virtual void Search()=0;
    virtual ~ABS_Med(){};
};

class MB1:public ABS_Med
{
    int size;
    Items *arr1;
public:
    MB1(){size=0; arr1=nullptr;};
    MB1(int s){size=s; arr1=new Items[s];};
    MB1(const MB1& other)
    {
        this->size=other.size;
        this->arr1= new Items[size];
        for(int i=0;i<other.size; i++)
        {
            this->arr1[i]=other.arr1[i];
        }
    }
    virtual ~MB1(){delete[] arr1;};
    MB1 & operator =(const MB1&other)
    {
        this -> size =other.size;
        if (this-> arr1!= nullptr)
        {     delete[] this->arr1;}
        this->arr1= new Items[other.size];
        for (int i=0;i<other.size;i++)
            this->arr1[i]=other.arr1[i];
        return *this;
    };
    Items operator[](int i)
    {
        return arr1[i];
    }
    void GetMeds(QFile&a,QFile&c)override;
    void WriteMeds(QFile &a)override{};
    void Putmeds(ostream&a)override;
    void Putmeds(QFile&a)override;
    int Partition(int low, int high);//часть сортировки
    void QuickSort(int low, int high);//основная часть сортировки
    void SortUp()override;
    void Search()override;
    int GetSize()override{return size;};
};
void MB1::Search()
{
    string inputWord;
    cout << "Enter a word: ";
    cin >> inputWord;
    for(int i=0;i<size;i++)
    {
        if(inputWord==arr1[i].Name.toStdString())
        {
            cout<<arr1[i]<<endl;
        }
    }
}
int MB1::Partition(int low, int high) {
    Items pivot = arr1[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr1[j].Name<=pivot.Name) {
            i++;
            swap(arr1[i], arr1[j]);
        }
    }
    swap(arr1[i + 1], arr1[high]);
    return (i + 1);
}
void MB1::QuickSort(int low, int high) {
    if (low < high) {
        cout<<1;
        int pi = Partition(low, high);

        QuickSort(low, pi - 1);
        QuickSort(pi + 1, high);
    }
}
void MB1::SortUp()
{QuickSort(0,size-1);}
void MB1::GetMeds(QFile&a,QFile&c)
{
    QTextStream texstr2(&a);
    QDataStream str3(&c);
    QDataStream str4(&c);
    if(!a.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        cout<<"problems with txt"<<endl;
    }
    cout<<"Information from txt"<<endl;
    int ct(0);
    while (!a.atEnd()) {
        a.readLine();
        ct++;
    }
    size=ct;
    arr1=new Items[size];
    //cout<<lineCount;
    a.close();
    a.open(QIODevice::ReadOnly | QIODevice::Text);
    for(int i=0;i<size;i++)
    {
        texstr2>>arr1[i];
    }
    /*for (int i=0;i<size;i++) {
        cout<<arr1[i];
    }*/
    a.close();
    if (!c.open(QIODevice::WriteOnly))
    {
        cout<<"problems with yout binary file 1.txt"<<endl;
    }
    for (int i=0;i<size;i++) {
        str3<<arr1[i];
    }
    c.close();
    if (!c.open(QIODevice::ReadOnly)) {
        cout<< "Could not open binary file for reading";

    }
    for(int i=0;i<size;i++)
    {
        str4>>arr1[i];
    }
    cout<<endl;

    c.close();
}
void MB1::Putmeds(QFile&a)
{
    ;
    QTextStream textstr(&a);
    if (!a.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        cout<<"problems with yout text file 1.txt"<<endl;
    }
    for (int i=0;i<size;i++) {
        textstr<<arr1[i]<<'\n';
    }
    a.close();
}
void MB1::Putmeds(ostream&a)
{
    a<< "Read from binary file and sort:"<<endl;
    for(int i=0;i<size;i++)
    {
        a<<arr1[i]<<endl;
    }
    //cout<<"Here";
    a<<endl;
}
class MB2:public ABS_Med
{
    int size2;
    Price *arr2;
public:
    MB2(){size2=0; arr2=nullptr;};
    MB2(int s){size2=s; arr2=new Price[s];};
    MB2(const MB2& other)
    {
        this->size2=other.size2;
        this->arr2= new Price[size2];
        for(int i=0;i<other.size2; i++)
        {
            this->arr2[i]=other.arr2[i];
        }
    }
    virtual ~MB2(){delete[] arr2;};
    MB2 & operator =(const MB2&other)
    {
        this -> size2 =other.size2;
        if (this-> arr2!= nullptr)
        {     delete[] this->arr2;}
        this->arr2= new Price[other.size2];
        for (int i=0;i<other.size2;i++)
            this->arr2[i]=other.arr2[i];
        return *this;
    };
    Price operator[](int i)
    {
        return arr2[i];
    }
    void GetMeds(QFile&a,QFile&c)override;
    void WriteMeds(QFile &a)override{};
    void Putmeds(ostream&a)override;
    void Putmeds(QFile&a)override;
    int Partition(int low, int high);//часть сортировки
    void QuickSort(int low, int high);//основная часть сортировки
    void SortUp()override;
    void Search() override{};
    int GetSize()override{return size2;};
};
void MB2::Putmeds(ostream&a)
{
    a<< "Read from binary file and sort:"<<endl;
    for(int i=0;i<size2;i++)
    {
        a<<arr2[i]<<endl;
    }
    //cout<<"Here";
    a<<endl;
}
int MB2::Partition(int low, int high) {
    Price pivot = arr2[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr2[j].Name<=pivot.Name) {
            i++;
            swap(arr2[i], arr2[j]);
        }
    }
    swap(arr2[i + 1], arr2[high]);
    return (i + 1);
}
void MB2::QuickSort(int low, int high) {
    if (low < high) {
        cout<<1;
        int pi = Partition(low, high);

        QuickSort(low, pi - 1);
        QuickSort(pi + 1, high);
    }
}
void MB2::SortUp()
{QuickSort(0,size2-1);}
void MB2::GetMeds(QFile&a,QFile&c)
{
    QTextStream texstr5(&a);
    QDataStream str6(&c);
    QDataStream str7(&c);
    if(!a.open(QIODevice::ReadOnly | QIODevice::Text))
    {

        cout<<"problems with txt"<<endl;
    }
    cout<<"Information from txt"<<endl;
    int ct(0);
    while (!a.atEnd()) {
        a.readLine();
        ct++;
    }
    size2=ct;
    arr2=new Price[size2];
    //cout<<lineCount;
    a.close();
    a.open(QIODevice::ReadOnly | QIODevice::Text);
    for(int i=0;i<size2;i++)
    {
        texstr5>>arr2[i];
    }
    for (int i=0;i<size2;i++) {
        cout<<arr2[i];
    }
    a.close();
    if (!c.open(QIODevice::WriteOnly))
    {
        cout<<"problems with yout binary file 1.txt"<<endl;
    }
    for (int i=0;i<size2;i++) {
        str6<<arr2[i];
    }
    c.close();
    if (!c.open(QIODevice::ReadOnly)) {
        cout<< "Could not open binary file for reading";

    }
    for(int i=0;i<size2;i++)
    {
        str7>>arr2[i];
    }
    cout<<endl;

    c.close();
}
void MB2::Putmeds(QFile&a)
{
    QTextStream textstr1(&a);
    if (!a.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        cout<<"problems with yout text file 1.txt"<<endl;
    }
    for (int i=0;i<size2;i++) {
        textstr1<<arr2[i]<<'\n';
    }
    a.close();
}
class MB3:public ABS_Med
{
    int size3;
    Med *arr3;
public:
    MB3(){size3=0; arr3=nullptr;};
    MB3(int s){size3=s; arr3=new Med[s];};
    MB3(const MB3& other)
    {
        this->size3=other.size3;
        this->arr3= new Med[size3];
        for(int i=0;i<other.size3; i++)
        {
            this->arr3[i]=other.arr3[i];
        }
    }
    virtual ~MB3(){delete[] arr3;};
    Med operator[](int i)
    {
        return arr3[i];
    }
    MB3 & operator =(const MB3&other)
    {
        this -> size3 =other.size3;
        if (this-> arr3!= nullptr)
        {     delete[] this->arr3;}
        this->arr3= new Med[other.size3];
        for (int i=0;i<other.size3;i++)
            this->arr3[i]=other.arr3[i];
        return *this;
    };
    int Partition(int low, int high);//часть сортировки
    void QuickSort(int low, int high);//основная часть сортировки
    void GetMeds(QFile&a,QFile&c)override{};
    void WriteMeds(QFile &a)override;
    void Putmeds(ostream&a) override;
    void Putmeds(QFile&a)override{};
    void SortUp()override;
    void Search() override{};
    int GetSize()override{return size3;};
    void Union(MB1 M1,MB2 M2);
};
void MB3::WriteMeds(QFile &a)
{
    QDataStream binstr(&a);
    if (!a.open(QIODevice::WriteOnly))
    {
        cout<<"problems with yout binary file 1.txt"<<endl;
    }
    for (int i=0;i<size3;i++) {
        binstr<<arr3[i];
    }
    a.close();
}
void MB3::Putmeds(ostream&a)
{
    a<< "Read from binary file and sort:"<<endl;
    for(int i=0;i<size3;i++)
    {
        a<<arr3[i]<<endl;
    }
    //cout<<"Here";
    a<<endl;
}
int MB3::Partition(int low, int high) {
    Med pivot = arr3[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr3[j].Name<=pivot.Name) {
            i++;
            swap(arr3[i], arr3[j]);
        }
    }
    swap(arr3[i + 1], arr3[high]);
    return (i + 1);
}
void MB3::QuickSort(int low, int high) {
    if (low < high) {
        cout<<1;
        int pi = Partition(low, high);

        QuickSort(low, pi - 1);
        QuickSort(pi + 1, high);
    }
}
void MB3::SortUp()
{QuickSort(0,size3-1);}
void MB3::Union(MB1 M1,MB2 M2)
{
    bool flag;
    Med *arr;
    int size0;
    size0=M1.GetSize();
    arr=new Med[size0];
    int count0(0);
    cout<<"union: "<<endl;
    for(int i=0;i<M1.GetSize();i++)
    {
        flag=false;
        for(int j=0;j<M2.GetSize();j++)
        {

            if(M1[i].Name==M2[j].Name)
            {
                arr[count0].Name=M1[i].Name;
                arr[count0].Date=M1[i].Date;
                arr[count0].Section=M1[i].Section;
                arr[count0].pr=M2[i].pr;
                arr[count0].count=M1[i].count;
                count0++;
            }
        }
    }
    size3=count0;
    arr3=new Med[size3];
    for(int i=0;i<size3;i++)
    {
        arr3[i]=arr[i];
    }
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    MB1 M1; MB2 M2; MB3 M3;
    ABS_Med *A1,*A2;
    QFile input1("Input1.txt");
    QFile in1("Ob1.bin");
    QFile input2("Input2.txt");
    A1 = &M1;
    A1->GetMeds(input1,in1);
    A1->SortUp();
    A1->Putmeds(input2);
    QStandardItemModel *model = new QStandardItemModel(this);//выделяем память под модель, this - наш mainwindow.
    ui->tableView->setModel(model);//придали табличке модель
    model->setColumnCount(4);
    model->setRowCount(A1->GetSize());//GETTER для класса MB1(не 3 короче)
    for(int i = 0; i < A1->GetSize(); i++){
        QString str(M1[i].Name);
        QString str1(M1[i].Date);
        QString str2(M1[i].Section);
        model->setData(model->index(i,0), str);
        model->setData(model->index(i,1), str1);
        model->setData(model->index(i,2), str2);
        model->setData(model->index(i,3), M1[i].count);
    }
    QFile input3("Input3.txt");
    QFile in2("Ob2.bin");
    QFile input4("Input4.txt");
    A2 = &M2;
    A2->GetMeds(input3,in2);
    A2->SortUp();
    A2->Putmeds(input4);
    QStandardItemModel *m = new QStandardItemModel(this);//выделяем память под модель, this - наш mainwindow.
    ui->table2->setModel(m);//придали табличке модель
    m->setColumnCount(2);
    m->setRowCount(A2->GetSize());//GETTER для класса MB1(не 3 короче)
    for(int i = 0; i < A2->GetSize(); i++){
        QString str(M2[i].Name);
        m->setData(m->index(i,0), str);
        m->setData(m->index(i,1), M2[i].pr);
    }
    M3.Union(M1,M2);
    QFile res("res.bin");
    A2=&M3;
    A2->SortUp();
    A2->WriteMeds(res);
    QStandardItemModel *ml = new QStandardItemModel(this);//выделяем память под модель, this - наш mainwindow.
    ui->table3->setModel(ml);//придали табличке модель
    ml->setColumnCount(5);
    ml->setRowCount(A2->GetSize());//GETTER для класса MB1(не 3 короче)
    for(int i = 0; i < A2->GetSize(); i++){
        QString str(M3[i].Name);
        QString str1(M3[i].Date);
        QString str2(M3[i].Section);
        ml->setData(ml->index(i,0), str);
        ml->setData(ml->index(i,1), str1);
        ml->setData(ml->index(i,2), str2);
        ml->setData(ml->index(i,3), M3[i].pr);
        ml->setData(ml->index(i,4), M3[i].count);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    MB1 M1;
    QFile input1("Input1.txt");
    QFile in1("Ob1.bin");
    M1.GetMeds(input1,in1);
    QString name=ui->lineEdit->text();
    bool flag;
    flag=false;
    for(int i=0;i<M1.GetSize();i++)
    {
        if(name==M1[i].Name)
        {
            flag=true;
            QString answer=M1[i].Name+" "+M1[i].Date+" "+M1[i].Section;
            QMessageBox::about(this,"Результат поиска",answer);
        }
    }
    if(!flag)
    {
        QMessageBox::warning(this,"Результат поиска","Таких лекарств  нет");
    }
}


