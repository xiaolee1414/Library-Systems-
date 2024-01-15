#pragma once
using namespace std;
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include"librarything.h"
#include "sqlite3.h"
#include "database.h"

ofstream ofs;
ifstream ifs;
auto currentTime = chrono::system_clock::now();
time_t currentTimeStamp = chrono::system_clock::to_time_t(currentTime);
tm* currentTimeStruct = localtime(&currentTimeStamp);

struct User {
    int id;
    string username;
    string password;
    User* next; // 链表指针
};
struct people {
    int id;
    string username;
    string password;
    string state;
    int bill;
    
};


struct  waiting
{   public:
    string Id;
    string name ;
    string state ;
    string username;
    string genre;
    waiting* next;
};

struct Borrow{
    int UserID;
    string Username,BookingId,BookingName,BookingGenre,BookingState,BookingDate,BookingTime;
    Borrow* next;
};

struct Return{
    
    string Username;
    string ReturnId;
    string ReturnName;
    string UserID;
    string ReturnDate;
    string ReturnTime;
    Return* next;

    Return(string username, string returnId, string returnName, string userID, string returnDate, string returnTime, Return* nextNode = nullptr)
        : Username(username), ReturnId(returnId), ReturnName(returnName), UserID(userID), ReturnDate(returnDate), ReturnTime(returnTime), next(nextNode) {
    }
};

 class Book 
{
public:
time_t dueDate;
int Bid;
string Bname;
string Bauthor ;
string Bgenre;
string Bstate;
vector<Book> book;
waiting w;
vector<waiting>wait;

void AddtoBorrow(string Name,int Id,vector<Book>book,int select , vector<Book>::iterator it ){
                string confirm;
                cout  << "Now the book are Active\nAre you want to borrow now(y/n):";
                cin >> confirm;
                ofs.open(BORROW_FILE,ios_base::out|ios_base::app);//insert
                string returnDate = to_string(currentTimeStruct->tm_year + 1900) + "-" +
                        to_string(currentTimeStruct->tm_mon + 1) + "-" +
                        to_string(currentTimeStruct->tm_mday);

                string returnTime=to_string(currentTimeStruct->tm_hour) +":"+to_string(currentTimeStruct->tm_min);
                if (confirm=="Y"||confirm=="y")
                {    
                 insertBorrow(Id,Name,to_string(it->Bid),it->Bname,it->Bgenre,"Borrowed",returnDate,returnTime);
                ofs<<"\n" <<Id<<" "<<Name<<" B"<<it->Bid<< " "<<it->Bname<<" "<<it->Bgenre<<" "<< "Borrowed "<<
                (currentTimeStruct->tm_year +1900) << "-" << (currentTimeStruct->tm_mon +1) << "-"
                << currentTimeStruct->tm_mday<<" "<<currentTimeStruct->tm_hour <<":"<<currentTimeStruct->tm_min<<endl;
                ofs.close();
                cout<< "Borrow Succefull"<< endl;
                int borrowId = it->Bid;
                string borrowName = it->Bname;
                string borrowGenre = it->Bgenre;        
                string borrowAuthor=it->Bauthor;

                 int removeId=select;
                 
                 auto bookToRemove = find_if(book.begin(), book.end(), [removeId](const Book& b) {
                 return b.Bid == removeId;
                });

             if (bookToRemove != book.end()) 
                 {updateState("Book","Book_State","Borrowed","Book_Title",bookToRemove->Bname);
                 book.erase(bookToRemove);
                  ofs.open(BOOKS_FILE, ios_base::out | ios_base::trunc);
                for (const Book& b :book)
                 {
                  ofs << b.Bid << " " << b.Bname << " " << b.Bauthor <<" " << b.Bgenre << " " << b.Bstate << endl;
                 }
                ofs.close();
                }        
                 ofs.open(BOOKS_FILE, ios_base::out|ios_base::app);
                 
                 ofs <<borrowId<< " " << borrowName << " " <<borrowAuthor<< " " <<borrowGenre << " Borrowed" << endl;
                  ofs.close();
                system("pause");
                system("cls"); 
                return;
}               else if(confirm=="no"||confirm=="n"){return;}
}

int ShowBookMenu(int page,vector<Book> book){
 int move=(page -1 )*5;
 int totalPages = (book.size() + 5 - 1) / 5;

    

    cout << "*****Book*****" << endl;
    cout << left << setw(5) << "Id" << setw(25) << "Title" << setw(15) << "Author" <<setw(15) << "Genre" << setw(15) << "State" << endl;
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;
    for(int i=move ; i < book.size() && i < move+5; ++i){
      
         const Book& currentBook = book[i];
    
    cout << left << setw(5) << currentBook.Bid << setw(25) << currentBook.Bname<< setw(15) << currentBook.Bauthor << setw(15) << currentBook.Bgenre <<  setw(15)  << currentBook.Bstate << endl;
    }   
    

    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;
    
    if (page<=1){
        cout <<" Select BId for your Borrow or \"1\" to Next Page\nOr you don't want borrow ,Enter \"3\" to quit "<<endl;
        }
        else if(page>totalPages-1){
              cout <<"Select BId for your Borrow or  \"2\" to Back Page\nOr you don't want borrow ,Enter \"3\" to quit"<<endl;       
        }
        else{ 
             cout <<"Select BId for your Borrow ,\"1\" to Next Page  or  \"2\" to Back\nOr you don't want borrow ,Enter \"3\" to quit"<<endl;
         }
         
         return totalPages;};

void AddBookinglist(string Name,int Id){
    
     bool check;
    string confirm;
    int  select;
    vector<Book>::iterator it ;
    
    ifstream ifs;
     int page=1;
     int totalPages;
     while(true){ 
    check=false;
    book.clear();
    ifs.open(BOOKS_FILE, ios_base::in);  
    Book b;
     while (ifs >> b.Bid&&ifs >>b.Bname&&ifs >> b.Bauthor&&ifs >>b.Bgenre&&ifs>>b.Bstate)
     {
        book.push_back(b);
     }
     
     ifs.close();
     totalPages=ShowBookMenu( page,book);
    cin >>select;

      if (select ==1){
        page+=1;} 
        else if (select == 2) {        
           page-=1;           
        }else if (select == 3) {        
           return;           
        }
        else{
          //  page==1;
        }
       
        if (page<=0){
            page=1;
        }
         if (page>totalPages){
            page=totalPages;
        }
        
    
    for(it=book.begin();it!=book.end();it++){
            if(select ==it->Bid){
                check=true;
                break;
            } }
             
    if (check) {
        
            cout << "Selected  ID: " << select << endl;
            cout << "Title :" << it->Bname<<endl;
            cout << "Author :"<<it->Bauthor<<endl;
            cout << "Genre :"<<it->Bgenre<<endl;
            cout << "State :"<<it->Bstate << endl;
            ifs.open(MEMBER_FILE,ios_base::in);
            people u;
             while (ifs >> u.id  && ifs >>u.username &&ifs >>u.password && ifs >>u.bill &&ifs >>u.state){
            if(u.username==Name&&u.state=="Negative"){
            cout << "Sorry please return bill,or you can not borrow"<<endl;
            return;
            break;
            }
             }ifs.close();
            if(it->Bstate=="Active"){
                AddtoBorrow(Name,Id,book,select,it);
                }
            
            else if (it->Bstate=="Borrowed"){
            int wp=0;
            ifs.open(Order_File,ios_base::in);
            while (ifs >> w.Id && ifs >> w.name&& ifs >> w.genre && ifs >> w.username&&ifs >> w.state) {
              if (w.username==Name&&w.name==it->Bname){
                    cout << "This book you are already Reserve"<<endl;
                    return;
                }
            }
                 ifs.close();
                  Borrow borrowList;
                ifs.open(BORROW_FILE,ios_base::in);
                while (ifs >> borrowList.BookingId,ifs>>borrowList.Username,ifs>>borrowList.BookingId,ifs>>borrowList.BookingName,
                ifs>>borrowList.BookingGenre,ifs>>borrowList.BookingState>>borrowList.BookingDate,ifs>>borrowList.BookingTime)
                {
                    if(borrowList.Username==Name&&borrowList.BookingName==it->Bname){
                        cout<<"This book you are already borrow"<<endl; 
                        return;
                    }
                }
                
                ifs.close();

                ifs.open(Order_File,ios_base::in);
                while (ifs >> w.Id && ifs >> w.name&& ifs >> w.genre && ifs >> w.username&&ifs >> w.state) {
                if(w.state=="Reserve"&&w.name==it->Bname){
                    wp+=1;
                    ifs.close();
                }}
                

                
                cout <<"Waiting this reserve have "<<wp<<" people\nYou want to Reserve(y/n):";
                cin >> confirm;
                if (confirm=="Y"||confirm=="y"){
                ofs.open(Order_File,ios_base::out|ios_base::app);//insert
                insertOrder("B"+to_string(it->Bid) ,it->Bname ,it->Bgenre ,Name ," Reserve" );
                ofs << "B"<<it->Bid <<" "<<it->Bname <<" "<< it->Bgenre<<" "<< Name<<" Reserve"<< endl;
                cout<< "Reserve successfull"<<endl;
                ofs.close();
                }
                else if(confirm=="N"||confirm=="n"){
                    return;
                }
            }
    }
          }

       
}};


class Audiovisual{ 
public:
time_t dueDate;
vector<Audiovisual> audiovisual;
waiting w;
vector<waiting>wait;
int Aid;string Aname;string Agenre;string Astate;
string Aauthor ;

void AddtoBorrow(string Name,int Id,vector<Audiovisual>audiovisual,int select , vector<Audiovisual>::iterator it){
                string confirm;
                cout  << "Now the book are Active\nAre you want to borrow now(y/n):";
                cin >> confirm;
                string returnDate = to_string(currentTimeStruct->tm_year + 1900) + "-" +
                        to_string(currentTimeStruct->tm_mon + 1) + "-" +
                        to_string(currentTimeStruct->tm_mday);

                string returnTime=to_string(currentTimeStruct->tm_hour) +":"+to_string(currentTimeStruct->tm_min);

                ofs.open(BORROW_FILE,ios_base::out|ios_base::app);
                if (confirm=="Y"||confirm=="y")
                {    //insert
                 insertBorrow(Id,Name,to_string(it->Aid),it->Aname,it->Agenre,"Borrowed",returnDate,returnTime);
                
                ofs<<"\n" <<Id<<" "<<Name<<" A"<<it->Aid<< " "<<it->Aname<<" "<<it->Agenre<<" "<< "Borrowed "<<
                (currentTimeStruct->tm_year +1900) << "-" << (currentTimeStruct->tm_mon +1) << "-"
                << currentTimeStruct->tm_mday<<" "<<currentTimeStruct->tm_hour <<":"<<currentTimeStruct->tm_min<<endl;
                ofs.close();
                cout<< "Borrow Succefull"<< endl;
                int borrowId = it->Aid;
                string borrowName = it->Aname;
                string borrowGenre = it->Agenre;        
                string borrowAuthor = it->Aauthor;      

                 int removeId=select;
                   
                 auto bookToRemove = find_if(audiovisual.begin(), audiovisual.end(), [removeId](const Audiovisual& a) {
                 return a.Aid == removeId;
                });

             if (bookToRemove != audiovisual.end()) 
                 {
                 audiovisual.erase(bookToRemove);
                  ofs.open(AUDIOVISUAL_FILE, ios_base::out | ios_base::trunc);
                for (const Audiovisual& a :audiovisual)
                 {
                  ofs << a.Aid << " " << a.Aname <<" " << a.Aauthor  <<" " << a.Agenre << " " << a.Astate << endl;
                 }
                ofs.close();
                }        
                 ofs.open(AUDIOVISUAL_FILE, ios_base::out|ios_base::app);//update
                 ofs <<borrowId<< " " << borrowName << " " <<borrowAuthor<<" "<<borrowGenre << " Borrowed" << endl;
                  ofs.close();
                system("pause");
                system("cls"); 
                return;
}               else if(confirm=="no"||confirm=="n"){return;}
}


void ShowAudiovisualMenu(int page,vector<Audiovisual> audiovisual){
 int move=(page -1 )*5;
 int totalPages = (audiovisual.size() + 5 - 1) / 5;

    int i =0,j=0;

    cout << "*****Audiovisual item*****" << endl;
    cout << left << setw(5) << "Id" << setw(25) << "Title" << setw(15) << "Author" <<setw(15) << "Genre" << setw(15) << "State" << endl;
    cout << setfill('-') << setw(75) << "-" << setfill(' ') << endl;
    for(int i=move ; i < audiovisual.size() && i < move+5; ++i){
      
         const Audiovisual& currentBook = audiovisual[i];
    
    cout << left << setw(5) << currentBook.Aid << setw(25) << currentBook.Aname << setw(15) << currentBook.Aauthor<< setw(15) << currentBook.Agenre <<  setw(15)  << currentBook.Astate << endl;
    }   
    

    cout << setfill('-') << setw(85) << "-" << setfill(' ') << endl;
    
    if (page<=1){
        cout <<" Select AId for your Borrow or \"1\" to Next Page\nOr you don't want borrow ,Enter \"3\" to quit "<<endl;
        }
        else if(page>totalPages-1){
              cout <<"Select AId for your Borrow or  \"2\" to Back Page\nOr you don't want borrow ,Enter \"3\" to quit"<<endl;       
        }
        else{ 
             cout <<"Select AId for your Borrow ,\"1\" to Next Page  or  \"2\" to Back\nOr you don't want borrow ,Enter \"3\" to quit"<<endl;
         }}


void AddBookinglist(string Name,int Id) {
    bool check=false;
    string confirm;
    int  select;
    vector<Audiovisual>::iterator it ;
    
    ifstream ifs;
     int page=1;
     int totalPages;
     while(true){ 
 
    audiovisual.clear();
    ifs.open(AUDIOVISUAL_FILE, ios_base::in);  
    Audiovisual a;
     while (ifs >> a.Aid&&ifs >>a.Aname&& ifs >>a.Aauthor&&ifs >>a.Agenre&&ifs>>a.Astate)
     {
        audiovisual.push_back(a);
     }
     ifs.close();
    ShowAudiovisualMenu( page,audiovisual);
    cin >>select;

      if (select ==1){
        page+=1;} 
        else if (select == 2) {        
           page-=1;           
        }else if (select == 3) {        
           return;           
        }
        if (page<=0){
            page=1;
        }
         if (page>totalPages){
            page=totalPages;
        }
        
    for(it=audiovisual.begin();it!=audiovisual.end();it++){
            if(select ==it->Aid){
                check=true;
                break;
            } }
             
    if (check) {
        
            cout << "Selected  ID: " << select << endl;
            cout << "Title :" << it->Aname<<endl;
            cout << "Author :"<<it->Aauthor<<endl;
            cout << "Genre :"<<it->Agenre<<endl;
            cout << "State :"<<it->Astate << endl;
            people u;
             while (ifs >> u.id  && ifs >>u.username &&ifs >>u.password && ifs >>u.bill &&ifs >>u.state){
            if(u.username==Name&&u.state=="Negative"){
            cout << "Sorry please return bill,or you can not borrow"<<endl;
            return;
            break;
            }
             }
            if(it->Astate=="Active"){
                AddtoBorrow(Name,Id,audiovisual,select,it);
                }
            
            else if (it->Astate=="Borrowed"){
            int wp=0;
            ifs.open(Order_File,ios_base::in);
            while (ifs >> w.Id && ifs >> w.name&& ifs >> w.genre && ifs >> w.username&&ifs >> w.state) {
              if (w.username==Name&&w.name==it->Aname){
                    cout << "This item you are already Reserve"<<endl;
                    return;
                }
            }
                 ifs.close();
                  Borrow borrowList;
                ifs.open(BORROW_FILE,ios_base::in);
                while (ifs >> borrowList.BookingId,ifs>>borrowList.Username,ifs>>borrowList.BookingId,ifs>>borrowList.BookingName,
                ifs>>borrowList.BookingGenre,ifs>>borrowList.BookingState>>borrowList.BookingDate,ifs>>borrowList.BookingTime)
                {
                    if(borrowList.Username==Name&&borrowList.BookingName==it->Aname){
                        cout<<"This item you are already borrow"<<endl; 
                        return;
                    }
                }
                ifs.close();
                
                ifs.open(Order_File,ios_base::in);
                while (ifs >> w.Id && ifs >> w.name&& ifs >> w.genre && ifs >> w.username&&ifs >> w.state) {
                if(w.state=="Reserve"&&w.name==it->Aname){
                    wp+=1;
                }}
                ifs.close();

                cout <<"Waiting this reserve have "<<wp<<" people\nYou want to Reserve(y/n):";
                cin >> confirm;
                if (confirm=="Y"||confirm=="y"){
                ofs.open(Order_File,ios_base::out|ios_base::app);//insert
                insertOrder("A"+to_string(it->Aid) ,it->Aname ,it->Agenre ,Name ," Reserve" );
                ofs << "A"<<it->Aid <<" "<<it->Aname <<" "<< it->Agenre<<" "<< Name<<" Reserve"<< endl;
                cout<< "Reserve successfull"<<endl;
                ofs.close();
                }
                else if(confirm=="N"||confirm=="n"){
                    return;
                }
            }
    }
           else {
            cout << "Book with ID " << select << " not found." << endl;
            
        }}

       
}};

class Digital  
{
public:
time_t dueDate;
vector<Digital> digital;
waiting w;
vector<waiting>wait;
int Did;string Dname;string Dgenre;string Dstate;
string Dauthor ;

void AddtoBorrow(string Name,int Id,vector<Digital>digital,int select , vector<Digital>::iterator it){
                string confirm;
                cout  << "Now the book are Active\nAre you want to borrow now(y/n):";
                cin >> confirm;
                ofs.open(BORROW_FILE,ios_base::out|ios_base::app);
                string returnDate = to_string(currentTimeStruct->tm_year + 1900) + "-" +
                        to_string(currentTimeStruct->tm_mon + 1) + "-" +
                        to_string(currentTimeStruct->tm_mday);

                string returnTime=to_string(currentTimeStruct->tm_hour) +":"+to_string(currentTimeStruct->tm_min);

                if (confirm=="Y"||confirm=="y")
                { insertBorrow(Id,Name,to_string(it->Did),it->Dname,it->Dgenre,"Borrowed",returnDate,returnTime);
                            //insert
                ofs<<"\n" <<Id<<" "<<Name<<" A"<<it->Did<< " "<<it->Dname<<" "<<it->Dgenre<<" "<< "Borrowed "<<
                (currentTimeStruct->tm_year +1900) << "-" << (currentTimeStruct->tm_mon +1) << "-"
                << currentTimeStruct->tm_mday<<" "<<currentTimeStruct->tm_hour <<":"<<currentTimeStruct->tm_min<<endl;
                ofs.close();
                cout<< "Borrow Succefull"<< endl;
                int borrowId = it->Did;
                string borrowName = it->Dname;
                string borrowGenre = it->Dgenre;  
                string borrowAuthor = it->Dauthor;     
                

                 int removeId=select;
                   
                 auto bookToRemove = find_if(digital.begin(), digital.end(), [removeId](const Digital& d) {
                 return d.Did == removeId;
                });

             if (bookToRemove != digital.end()) 
                 {
                 digital.erase(bookToRemove);
                  ofs.open(DIGITAL_FILE, ios_base::out | ios_base::trunc);
                for (const Digital& d :digital)
                 {
                  ofs << d.Did << " " << d.Dname << " " << d.Dauthor <<" " << d.Dgenre << " " << d.Dstate << endl;
                 }
                ofs.close();
                }        
                 ofs.open(DIGITAL_FILE, ios_base::out|ios_base::app);//update
                 //update
                 ofs <<borrowId<< " " << borrowName << " " <<borrowAuthor << " " <<borrowGenre << " Borrowed" << endl;
                  ofs.close();
                system("pause");
                system("cls"); 
                return;
}               else if(confirm=="no"||confirm=="n"){return;}
}
void ShowDigitalMenu(int page,vector<Digital>digital){
  int move=(page -1 )*5;
 int totalPages = (digital.size() + 5 - 1) / 5;

    int i =0,j=0;

    cout << "*****Digital resource*****" << endl;
    cout << left << setw(5) << "Id" << setw(25) << "Title" << setw(15) << "Author"<< setw(15) << "Genre" << setw(15) << "State" << endl;
    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    for(int i=move ; i < digital.size() && i < move+5; ++i){
      
         const Digital& currentBook = digital[i];
    
    cout << left << setw(5) << currentBook.Did << setw(25) << currentBook.Dname << setw(15) << currentBook.Dauthor << setw(15) << currentBook.Dgenre <<  setw(15)  << currentBook.Dstate << endl;
    }   
    

    cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
    
    if (page<=1){
        cout <<" Select DId for your Borrow or \"1\" to Next Page\nOr you don't want borrow ,Enter \"3\" to quit "<<endl;
        }
        else if(page>totalPages-1){
              cout <<"Select DId for your Borrow or  \"2\" to Back Page\nOr you don't want borrow ,Enter \"3\" to quit"<<endl;       
        }
        else{ 
             cout <<"Select DId for your Borrow ,\"1\" to Next Page  or  \"2\" to Back\nOr you don't want borrow ,Enter \"3\" to quit"<<endl;
         }}


void AddBookinglist(string Name,int Id)
{
    bool check=false;
    string confirm;
    int  select;
    vector<Digital>::iterator it ;
    
    ifstream ifs;
     int page=1;
     int totalPages;
     while(true){ 
 
    digital.clear();
    ifs.open(DIGITAL_FILE, ios_base::in);  
    Digital d;
     while (ifs >> d.Did&&ifs >>d.Dname&&ifs >>d.Dauthor&&ifs >>d.Dgenre&&ifs>>d.Dstate)
     {
        digital.push_back(d);
     }
     ifs.close();
    ShowDigitalMenu( page,digital);
    cin >>select;

      if (select ==1){
        page+=1;} 
        else if (select == 2) {        
           page-=1;           
        }else if (select == 3) {        
           return;           
        }
        if (page<=0){
            page=1;
        }
         if (page>totalPages){
            page=totalPages;
        }
        
    for(it=digital.begin();it!=digital.end();it++){
            if(select ==it->Did){
                check=true;
                break;
            } }
             
    if (check) {
        
            cout << "Selected  ID: " << select << endl;
            cout << "Title :" << it->Dname<<endl;
            cout << "Author :"<<it->Dauthor<<endl;
            cout << "Genre :"<<it->Dgenre<<endl;
            cout << "State :"<<it->Dstate << endl;
            people u;
             while (ifs >> u.id  && ifs >>u.username &&ifs >>u.password && ifs >>u.bill &&ifs >>u.state){
            if(u.username==Name&&u.state=="Negative"){
            cout << "Sorry please return bill,or you can not borrow"<<endl;
            return;
            break;
            }
             }
            if(it->Dstate=="Active"){
                AddtoBorrow(Name,Id,digital,select,it);
                }
            
            else if (it->Dstate=="Borrowed"){
            int wp=0;
            ifs.open(Order_File,ios_base::in);
            while (ifs >> w.Id && ifs >> w.name&& ifs >> w.genre && ifs >> w.username&&ifs >> w.state) {
              if (w.username==Name&&w.name==it->Dname){
                    cout << "This item you are already Reserve"<<endl;
                    return;
                }
            }
                 ifs.close();
                  Borrow borrowList;
                ifs.open(BORROW_FILE,ios_base::in);
                while (ifs >> borrowList.BookingId,ifs>>borrowList.Username,ifs>>borrowList.BookingId,ifs>>borrowList.BookingName,
                ifs>>borrowList.BookingGenre,ifs>>borrowList.BookingState>>borrowList.BookingDate,ifs>>borrowList.BookingTime)
                {
                    if(borrowList.Username==Name&&borrowList.BookingName==it->Dname){
                        cout<<"This item you are already borrow"<<endl; 
                        return;
                    }
                }
                wait.clear();
                ifs.close();
                ifs.open(Order_File,ios_base::in);
                while (ifs >> w.Id && ifs >> w.name&& ifs >> w.genre && ifs >> w.username&&ifs >> w.state) {
                if(w.state=="Reserve"&&w.name==it->Dname){
                    wp+=1;
                }}
                ifs.close();
                cout <<"Waiting this reserve have "<<wp<<" people\nYou want to Reserve(y/n):";
                cin >> confirm;
                
                if (confirm=="Y"||confirm=="y"){
                ofs.open(Order_File,ios_base::out|ios_base::app);
                //insert
                  insertOrder("D"+to_string(it->Did) ,it->Dname ,it->Dgenre ,Name ," Reserve" );
                ofs << "D"<<it->Did <<" "<<it->Dname <<" "<< it->Dgenre<<" "<< Name<<" Reserve"<< endl;
                cout<< "Reserve successfull"<<endl;
                ofs.close();
                }
                else if(confirm=="N"||confirm=="n"){
                    return;
                }
            }
    }
           else {
            cout << "Book with ID " << select << " not found." << endl;
            
        }}}};

       

