#include<iostream>
#include"identify.h"
#include <fstream>
#include<string>
#include "globalFile.h"
#include<vector>
#include"librarything.h"
#include<iomanip>
#include <algorithm>
#include "sqlite3.h"
#include "database.h"
#include <sstream>
using namespace std;


void Menu(string filename,string Title,string tablename) ;

bool checkRepeatUserID(string& filename,int id){
     ifstream ifs;
     int fId,s3;
     string s1,s2,s4;
    
    ifs.open(filename,ios_base::in);
    while (ifs >> fId>>s1>>s2>>s3>>s4) {
       
        if (fId == id) {
            ifs.close();
            return true;
        }
    }

    ifs.close();
    return false;
   
}

bool checkRepeatCatelogID(string& filename,int id){
     ifstream ifs;
     int fId;
     string s1,s2,s4,s3;
    
    ifs.open(filename,ios_base::in);
    while (ifs >> fId>>s1>>s2>>s3>>s4) {
       
        if (fId == id) {
            ifs.close();
            return true;
        }
    }

    ifs.close();
    return false;
   
}



struct BookingList{

    string BookingId,BookingName,BookingGenre,BookingUser,BookingState;
    BookingList* next;
};


class Member :public Identity//member.h
{
public:
Borrow borrowList;
vector<Borrow>list;
vector<int>returnId;
waiting w;
vector<waiting>wait;
vector<Book>book;
vector<Audiovisual>audiovisual;
vector<Digital>digital;;
Audiovisual a;
Book b;
Digital d;
Member();
Member(int id , string name ,string pwd,int bill ,string state);
void openMenu();

//booking system
void BookingSystem();

void  ViewAccount();

bool checkHavingReverse(int selectedId, vector<Borrow> list);
            
//check bookinglist
void CheckBookingList();


//borrowsystem
void BorrowsSystem();
//returnsystem
void ReturnSystem();

};

int calculateDateDifference(const string& startDate, const string& endDate) {
    // 将日期字符串转换为tm结构体
    tm start = {};
    tm end = {};
    stringstream(startDate) >> get_time(&start, "%Y-%m-%d");
    stringstream(endDate) >> get_time(&end, "%Y-%m-%d");

    // 将tm结构体转换为time_t
    time_t startTime = mktime(&start);
    time_t endTime = mktime(&end);

    // 计算时间差
    double secondsDifference = difftime(endTime, startTime);

    // 转换为天数
    int daysDifference = static_cast<int>(secondsDifference / (60 * 60 * 24));

    return daysDifference;
}

Member :: Member()//member.cpp
{}
Member ::Member(int id , string name ,string pwd,int bill,string state)
{
vector<Book>book;
this->T_Id=id;
this->T_Name=name;
this->T_pwd=pwd;
this->T_bill=bill;
this->T_state=state;
}
void Member :: openMenu()
{
    std::cout << "\nWelcome ,"+this->T_Name  ;
   std:: cout << "\n***************************\n";
    std::cout << "****  1. Booking       ****\n";
    std::cout << "****  2. Borrow        ****\n";
    std::cout << "****  3. Return        ****\n";
    std::cout << "****  4. View          ****\n";
    std::cout << "****  5. Exit          ****\n";
    std::cout << "***************************\n\n";
    std::cout << "Enter the code \n" ;
}
//booking system
void Member ::BookingSystem()
{   
    int select;
   
    cout<< "\n1.Book\n2.Audiovisual item\n3.Digital Resource\n4.MyBookingList\nBooking Type:";
    cin>>select;
    if (select==1)
    {  
        b.AddBookinglist(T_Name,T_Id);
        }
    else if (select==2)
    {  a.AddBookinglist(T_Name,T_Id);
      }
    else if (select==3)
    {
        d.AddBookinglist(T_Name,T_Id);
    }
     else if (select==4)
    {
       CheckBookingList();
    }
    }

bool Member::checkHavingReverse(int selectedId, vector<Borrow> list) {
    ifstream ifs;
    ifs.open(Order_File, ios_base::in);
    bool found = false;
    while (ifs >> w.Id && ifs >> w.name && ifs >> w.genre && ifs >> w.username && ifs >> w.state) {
        if (w.name == list[selectedId].BookingName) {
            found = true;
            break;  // Found a match, no need to continue the loop
        }
    }
    ifs.close();
    return found;
}
//check bookinglist
void Member ::CheckBookingList()
{    int select ;
    int wp=0;
    people u;
    vector<User>userlist;
    vector<BookingList> bookList;
    vector<int> userbooking;
    BookingList b;
    int Id = 1;
    userlist.clear();
    bookList.clear();  
    ifs.open(Order_File, ios_base::in);
    while (ifs >> b.BookingId && ifs >> b.BookingName && ifs >> b.BookingGenre && ifs >> b.BookingUser && ifs >> b.BookingState) {
        bookList.push_back(b);
    }
    ifs.close();
    cout<< "\n\n "<< setw(30)<<"My Booking List"<<endl;
    cout << setfill('-') << setw(75) << "" << setfill(' ') << endl;
    cout << "\n" << setw(5) << "ID" << setw(15) << "BookingID" << setw(20) << "BookingName" << setw(15) << "Genre"
                << setw(20) << "State" << endl;
     


    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].BookingUser == this->T_Name) {
            cout << setfill('-') << setw(75) << "" << setfill(' ') << endl;
            cout <<"\n" << setw(5)<<Id << " " << setw(15)<< bookList[i].BookingId << " "<< setw(20) << bookList[i].BookingName << " " << setw(15)<< bookList[i].BookingGenre  << " " << setw(20)<< bookList[i].BookingState << endl;
            Id++;
            userbooking.push_back(i);
        }
        
    }
        cout << setfill('-') << setw(75) << "" << setfill(' ') << endl;
    cout << "\nWhen bookingState is \"Can Be Borrow\",\nyou can enter the id to borrow now, or enter \"99\" to quit: ";
    cin >> select;
    if (select <= Id) {
        ifs.open(MEMBER_FILE,ios_base::in);
        while (ifs >> u.id  && ifs >>u.username &&ifs >>u.password && ifs >>u.bill &&ifs >>u.state)
        {
        if(u.username==this->T_Name&&u.state=="Positive"){        
        int selectedId = userbooking[select - 1];
        if (bookList[selectedId].BookingState == "Can_Be_Borrow") {
            ofs.open(BORROW_FILE, ios_base::out | ios_base::app);//insertBorrow
           
            ofs << "\n" << this->T_Id << " " << this->T_Name << " " << bookList[selectedId].BookingId << " " << bookList[selectedId].BookingName << " " << bookList[selectedId].BookingGenre << " " << "Borrowed " <<(currentTimeStruct->tm_year +1900) << "-" << (currentTimeStruct->tm_mon +1) << "-"
                << currentTimeStruct->tm_mday<<" "<<currentTimeStruct->tm_hour <<":"<<currentTimeStruct->tm_min<<endl;
            ofs.close();
            
            string returnDate = to_string(currentTimeStruct->tm_year + 1900) + "-" +
                        to_string(currentTimeStruct->tm_mon + 1) + "-" +
                        to_string(currentTimeStruct->tm_mday);

            string returnTime=to_string(currentTimeStruct->tm_hour) +":"+to_string(currentTimeStruct->tm_min);

             insertBorrow(this->T_Id,this->T_Name,bookList[selectedId].BookingId,bookList[selectedId].BookingName,bookList[selectedId].BookingGenre,"Borrowed",returnDate,returnTime);
            
            cout << "Borrow Successful" << endl;


            ofs.open(Order_File, ios_base::out|ios_base::trunc);//update
            updateState("Book","Book_State","Borrowed","Book_Title",bookList[selectedId].BookingName);
            for (size_t i = 0; i < bookList.size(); i++)
            {   
                if(i != selectedId){
                 ofs  <<bookList[i].BookingId<<" "<<bookList[i].BookingName<<" "<< bookList[i].BookingGenre<<" "<< bookList[i].BookingUser<<" "<<bookList[i].BookingState<< endl;
                }
            }
            ofs.close(); }
            else if (bookList[selectedId].BookingState == "Reserve"){
            for (int  i = 0; i < bookList.size(); i++)
            {    if (bookList[selectedId].BookingState == "Reserve" && bookList[selectedId].BookingName == bookList[i].BookingName) {
                  wp+=1;
            }
            else if(bookList[selectedId].BookingUser==T_Name){
                break;
            }
                }
               cout << "Reserve this book still have "<<wp-1 << " people"<<endl;
            }
            ifs.close();
            break;}
        
        else if(u.username==this->T_Name&&u.state=="Negative"){

            cout << "Sorry please return bill,or you can not borrow"<<endl;
            break;
        }
            }}
        else if(select==0) {return;}
        else {cout << "Id have not found "<<endl;}
    }
    

//borrowsystem
void Member ::BorrowsSystem()
{     

    
int Id=1;
  list.clear();
  ifs.open(BORROW_FILE,ios_base::in);
  while (ifs >> borrowList.UserID&&ifs>>borrowList.Username&&ifs>>borrowList.BookingId&&ifs>>borrowList.BookingName,
  ifs>>borrowList.BookingGenre&&ifs>>borrowList.BookingState&&ifs>>borrowList.BookingDate&&ifs>>borrowList.BookingTime)
  {
    list.push_back(borrowList);
  }
  ifs.close();
  bool found=false;
  
   
   cout<< "\n\nMy Borrow List"<<endl;
   cout<<"***************************************************************************************************"<<endl;
   cout << "\n" << setw(5) << "ID" << setw(12) << "BorrowID" << setw(20) << "Book Name" << setw(20) << "Genre"
                 << setw(20) << "Date"   << endl;
   for (int i = 0; i < list.size(); i++) {
        if (list[i].Username == this->T_Name) {
           cout << "********************************************************************************************" << endl;
          
            cout << setw(5) << Id++ << setw(12) << list[i].BookingId << setw(20) << list[i].BookingName
                 << setw(20) << list[i].BookingGenre << setw(20) << list[i].BookingDate <<endl;
                 found=true;
        }
        }
        if(!found){
            cout << "********************************************************************************************" << endl;
            cout<<"Sorry you have be borrow thing"<<endl;
        }
        cout << "********************************************************************************************" << endl;
        cout <<"Warning :Please return it within 15 days, otherwise you will be fined. \nThere will be a fine of RM1 for each day late. ";
          
    system("pause");
    system("cls");
    return;
  }
//returnsystem
void Member ::ReturnSystem()
{ bool found=false;
  int select;
  int Id=1;
  ifs.open(BORROW_FILE,ios_base::in);
  list.clear();
  while (ifs >> borrowList.UserID&&ifs>>borrowList.Username&&ifs>>borrowList.BookingId&&ifs>>borrowList.BookingName&&
  ifs>>borrowList.BookingGenre&&ifs>>borrowList.BookingState&&ifs>>borrowList.BookingDate&&ifs>>borrowList.BookingTime)
  {
    list.push_back(borrowList);
  }
  ifs.close();
   cout<< "\n\nMy Borrow List"<<endl;
   cout << "\n" << setw(5) << "ID" << setw(13) << "BorrowID" << setw(25) << "Book Name" << setw(20) << "Genre"
                << setw(20) << "Date" << endl;
    
   for (int i = 0; i < list.size(); i++) {
        
        if (list[i].Username == this->T_Name) {
            cout << "****************************************************************************************************" << endl;
            cout << "\n" << setw(5) << Id << setw(13) << list[i].BookingId << setw(25) << list[i].BookingName << setw(20) << list[i].BookingGenre
                << setw(20) << list[i].BookingDate << endl;
            Id++;
            returnId.push_back(i);
            found=true;
        }}
        if(!found){
             cout << "****************************************************************************************************" << endl;
               cout<<"Sorry you have be borrow thing"<<endl;
        }
    cout << "****************************************************************************************************" << endl;
    cout << "Enter your Id to return or \"99\"to quit :";
    cin >> select;
    if(select<=Id){
        int selectedId = returnId[select-1];
        cout<<"Id:"<<list[selectedId].BookingId<<"\nName:"<<list[selectedId].BookingName<<"\nGenre:"<<list[selectedId].BookingGenre<<endl;
        cout<<"Conform return(y/n):";
        string confirm;
       

        cin >>confirm;
        if (confirm == "Y" || confirm == "y")
{   
    ifs.open(Order_File,ios_base::in);
    while (ifs >> w.Id && ifs >> w.name&& ifs >> w.genre && ifs >> w.username&&ifs >> w.state){
    wait.push_back(w);
    }
    ifs.close();
    bool ret = checkHavingReverse(selectedId, list);
    if (ret)
    {  
        for (int i = 0; i < wait.size(); i++)
        {   
            if (wait[i].name == list[selectedId].BookingName)
            {
                wait[i].state = "Can_Be_Borrow";
                ofs.open(Order_File, ios_base::out | ios_base::trunc);
                for (int i = 0; i < wait.size(); i++)
                {
                    ofs << wait[i].Id << " " << wait[i].name << " " << wait[i].genre << " " << wait[i].username << " " << wait[i].state << endl;
                }
                
                ofs.close();
                break;
            }
        }
    }
    else
    {
       if(list[selectedId].BookingGenre=="Book"){
         book.clear();
         ifs.open(BOOKS_FILE,ios_base::in);
         while (ifs >> b.Bid && ifs >> b.Bname&& ifs>>b.Bauthor&&ifs >> b.Bgenre && ifs >> b.Bstate){
         book.push_back(b);
        }
         ifs.close();
        for (int i = 0; i < book.size(); i++)
        {   
            if (book[i].Bname == list[selectedId].BookingName)
            {  
                book[i].Bstate = "Active";
                updateState("Book","Book_STATE","Active","Book_TITLE",list[selectedId].BookingName);
                ofs.open(BOOKS_FILE, ios_base::out | ios_base::trunc);//update
                for (int j = 0; j < book.size(); j++)
                {
                    ofs << book[j].Bid << " " << book[j].Bname << " " <<book[j].Bauthor<<" "<< book[j].Bgenre << " " << book[j].Bstate<< endl;
                }
                
                ofs.close();
                break;
            }
        }}
        //elseif(digital)
        else if(list[selectedId].BookingGenre=="Digital"){
         digital.clear();
         ifs.open(DIGITAL_FILE,ios_base::in);
         while (ifs >> d.Did && ifs >> d.Dname&&ifs  >> d.Dauthor&& ifs >> d.Dgenre && ifs >> d.Dstate){
         digital.push_back(d);
        }
         ifs.close();
        for (int i = 0; i < digital.size(); i++)
        {   
            if (digital[i].Dname == list[selectedId].BookingName)
            {   \
                digital[i].Dstate = "Active";
                updateState("Digital","Digital_STATE","Active","Digital_TITLE",list[selectedId].BookingName);
                ofs.open(DIGITAL_FILE, ios_base::out | ios_base::trunc);
                for (int j = 0; j < digital.size(); j++)
                {
                    ofs << digital[j].Did << " " << digital[j].Dname << " " << digital[j].Dauthor<<" "<< digital[j].Dgenre << " " << digital[j].Dstate<< endl;
                }
                
                ofs.close();
                break;
            }
        }}
        //elseif(audiovisual)
        else if(list[selectedId].BookingGenre=="Audiovisual"){
         audiovisual.clear();
         ifs.open(AUDIOVISUAL_FILE,ios_base::in);
         while (ifs >> a.Aid && ifs >> a.Aname&& ifs>>a.Aauthor&&ifs >> a.Agenre&& ifs >> a.Astate){
         audiovisual.push_back(a);
        }
         ifs.close();
        for (int i = 0; i < audiovisual.size(); i++)
        {   
            if (audiovisual[i].Aname == list[selectedId].BookingName)
            {   
                audiovisual[i].Astate = "Active";
                updateState("Audiovisual","Audiovisual_STATE","Active","Audiovisuall_TITLE",list[selectedId].BookingName);
                ofs.open(AUDIOVISUAL_FILE, ios_base::out | ios_base::trunc);
                for (int j = 0; j < audiovisual.size(); j++)
                {
                    ofs << audiovisual[j].Aid << " " << audiovisual[j].Aname << " " <<audiovisual[j].Aauthor<<" "<< audiovisual[j].Agenre << " " << audiovisual[j].Astate<< endl;
                }
                
                ofs.close();
                break;
            }
        }}
    }


    
    string borrowDate;
    ofs.open(BORROW_FILE,ios_base::out |ios_base::trunc);
    for (size_t i = 0; i <list.size(); i++)
    {
     if(list[selectedId].BookingName!=list[i].BookingName){
          borrowDate = list[i].BookingTime;
      ofs<< list[i].UserID<<" "<<list[i].Username<<" "<<list[i].BookingId<<" "<<list[i].BookingName<<" "<<
      list[i].BookingGenre<<" "<<list[i].BookingState<<" "<<list[i].BookingDate<<" "<<list[i].BookingTime<<endl;}
    }
    ofs.close();
    
        string returnDate = to_string(currentTimeStruct->tm_year + 1900) + "-" +
                        to_string(currentTimeStruct->tm_mon + 1) + "-" +
                        to_string(currentTimeStruct->tm_mday);
   
  
    int daysDifference = calculateDateDifference(borrowDate, returnDate);
    
    if (daysDifference > 15) {
        people u;
        vector <people>user;
        BookingList b;
        vector<BookingList>bookList;
        string returnDate,returnTime;
        cout << "Fine: $1.00 for exceeding per days." << endl;
        int bill =daysDifference-15+T_bill;
        ifs.open(MEMBER_FILE,ios_base::in);
        while (ifs>>u.id>>u.username>>u.password>>u.bill>>u.state)
        {
            user.push_back(u);
        }
        ifs.close();
        ifs.open(Order_File,ios_base::in);
        while (ifs >> b.BookingId && ifs >> b.BookingName && ifs >> b.BookingGenre && ifs >> b.BookingUser && ifs >> b.BookingState) {
        bookList.push_back(b);
        }
        ifs.close();
        ofs.open(MEMBER_FILE,ios_base::out|ios_base::trunc);
        for (size_t i = 0; i < user.size(); i++)
        {
            if(user[i].id=T_Id&&user[i].username==T_Name){
                ofs<<user[i].id<<" "<<user[i].username<<" "<<user[i].password<<" "<<bill<<" "<<"Negative"<<endl;
                //update
                 updateState("User","USER_STATE","Negative","USER_USERNAME",user[i].username);
                 updateBill("User","USER_Bill",to_string(bill),"USER_USERNAME",user[i].username);
            }
            else{
                ofs<<user[i].id<<" "<<user[i].username<<" "<<user[i].password<<" "<<user[i].bill<<" "<<user[i].state<<endl;
            }
        }
        ofs.close();
        ofs.open(Order_File,ios_base::out|ios_base::trunc);
        for (size_t i = 0; i < user.size(); i++)
        {
            if(bookList[i].BookingUser!=T_Name){
                ofs<<bookList[i].BookingId<<" "<<bookList[i].BookingName<<" "<<bookList[i].BookingGenre<<" "<<bookList[i].BookingUser<<" "<<bookList[i].BookingState<<endl;
            }
    
        }
        ofs.close();
        
    } 
    
    ofs.open(RETURN_FILE,ios_base::out |ios_base::app);//insert
               
                ofs << list[selectedId].BookingId <<" " << list[selectedId].BookingName <<" "<< list[selectedId].BookingGenre <<" "<< this->T_Id<<" "
                << list[selectedId].Username <<" "<<(currentTimeStruct->tm_year +1900) << "-" << (currentTimeStruct->tm_mon +1) << "-"
                << currentTimeStruct->tm_mday<<" "<<currentTimeStruct->tm_hour <<":"<<currentTimeStruct->tm_min<<endl;
                ofs.close();
                
                  returnDate = to_string(currentTimeStruct->tm_year + 1900) + "-" +
                        to_string(currentTimeStruct->tm_mon + 1) + "-" +
                        to_string(currentTimeStruct->tm_mday);

                string returnTime=to_string(currentTimeStruct->tm_hour) +":"+to_string(currentTimeStruct->tm_min);
                insertReturn(this->T_Id,this->T_Name,list[selectedId].BookingId,list[selectedId].BookingName,list[selectedId].BookingGenre,"Borrowed",returnDate,returnTime);                

                cout <<"Return sucessfull"<<endl;

     
}else if (confirm=="n"||confirm=="no")
       {
        return;
       }        
    }else if(select==99){
        return ;
    }else{cout<<"Wrong enter"<<endl;}     
} 

void Member ::ViewAccount(){
    people u;
    int Phone;
    
    ifs.open(MEMBER_FILE,ios_base::in);
    while(ifs >> u.id >>u.username>>u.password >>u.bill >>u.state){
        if (u.id==this->T_Id &&u.state=="Positive")
        {   cout <<"\n******************************************";
            cout << "\nDon't worry you have not compensation ( ^_^ ) ";

            cout <<"\n******************************************"<<endl;
            ifs.close();
            system("pause");
            system("cls");
            break;
                   }
        else if(u.id==this->T_Id &&u.state=="Negative")
        {   cout <<"Now put the phone and pay compensation (^n^)";
            cout <<"\n**************************************\n";
            cout <<setw(10)<<"/(^.^)/ RM:"<<u.bill;
            cout <<"\n**************************************"<<endl;
            ifs.close();
            cout << setw(10)<<"Phone Number:";
            cin  >>Phone;
            string phoneStr = to_string(Phone);
            if (phoneStr.length() == 10){
                cout <<"\n**************************************\n";
                cout <<"\nWant to pay it  ( ! _ $ )"<<endl;
                cout <<"**************************************\n";
                cout << setw(10)<<"(Y/N):";
                string confirm;
                cin >> confirm;
                if (confirm=="y"||confirm=="Y"){
                    people u;
                    vector <people>user;
                     ifs.open(MEMBER_FILE,ios_base::in);
                    while (ifs>>u.id&&ifs>>u.username&&ifs>>u.password&&ifs>>u.bill&&ifs>>u.state)
                     {
                       user.push_back(u);
                    }
                     ifs.close();

                    for (size_t i = 0; i < user.size(); i++) {
                    if (user[i].id == T_Id && user[i].username == T_Name) {//update
                     user[i].bill = 0;
                     user[i].state="Positive";  // 修改账单数据
                     updateState("User","USER_STATE","Positive","USER_USERNAME",user[i].username);
                     updateBill("User","USER_Bill","0","USER_USERNAME",user[i].username);
                     }
                    }
                     ofs.open(MEMBER_FILE,ios_base::out|ios_base::trunc);//不用
                    for (size_t i = 0; i < user.size(); i++)
                          {
                      
                       ofs<<user[i].id<<" "<<user[i].username<<" "<<user[i].password<<" "<<user[i].bill<<" "<<user[i].state<<endl;
                        
                     }
                  ofs.close();
                cout <<"\n**************************************\n";
                cout <<setw(5)<<"Thank you for fill ($.$)"<<endl;
                 cout <<setw(5)<<"Now you can Borrow thing now (^_^)"<<endl;
                cout <<"**************************************\n";
                system("pause");
                system("cls");
                break;
                }
                else if(confirm=="N"||confirm=="n"){
                cout <<"\n**************************************\n";
                cout <<setw(5)<<"ERM..... (?_?)"<<endl;
                cout <<"**************************************\n";
                system("pause");
                system("cls");
                break;
                }
            }
            else if (phoneStr.length()!=10){
                  cout <<"\n**************************************\n";
                cout <<setw(5)<<"Please enter ten number  (O_u)"<<endl;
                cout <<"**************************************\n";
                system("pause");
                system("cls");
                break;
            }
        }
        
    }

}


class Admin : public Identity ///admin.h
{
public:
Admin();
Admin(int id , string name ,string pwd);

void openMenu();

//show catelog

//addbook
void addbook(int select);
void removeitem();
//removebook
void removebook();
//showUser
void removeaudio();
void removedigital();
//showUser
void showUser();
//Check-In
void CheckIn();
//Check-Out
void CheckOut();

void initVector();
//容器

vector<Member>member;
vector<Admin>admin;
vector<Book>book;
};



Admin :: Admin()//admin.cpp
{}
Admin ::Admin(int id , string name ,string pwd)
{
this->T_Id=id;
this->T_Name=name;
this->T_pwd=pwd;
this->initVector();
       ifstream ifs;  
 ifs.open(BOOKS_FILE,ios_base::in);
    
     Book b;
     while (ifs >> b.Bid&&ifs >>b.Bname&&ifs >>b.Bauthor&&ifs >>b.Bgenre&&ifs>>b.Bstate)
     {
        book.push_back(b);
     }
     ifs.close();
}

void Admin :: openMenu()
{
      cout << "Welcome ,"+this->T_Name  ;
      cout << "\n***********************************\n";
      cout << "****  1. resource manage       ****\n";
      cout << "****  2. user manage           ****\n";
      cout << "****  3. CheckIn               ****\n";
      cout << "****  4. CheckOut              ****\n";
      cout << "****  5. Exit                  ****\n";
      cout << "***********************************\n\n";
      cout << "Enter the code \n" ; 
    cout << ": " ; 
}


void Admin ::addbook(int select)
{
   int id;
   string name;          
   string genre;
   string author ;
   string filename;
   string state="Active";
   
   if (select==1)
   {
      filename="books.txt";
      genre="Book";
   }
   else if (select==2)
   {
      filename="audipovisual.txt";
      genre="Audiovisual";
   }
   else if(select==3){
      filename="digital.txt";
      genre="Digital";
   }
   ofstream ofs;
ofs.open(filename,ios_base::out|ios_base::app);
 
while (true)
{
    cout << "Enter your Id :";
    cin >> id;
    bool ret =checkRepeatCatelogID(filename,id);
    if(ret){
     cout <<"This id already exists"<<endl;
    }
    else{break;}
}

cout << "\nEnter For Title  :";
cin.ignore();
getline(cin,name);
cout << "Author :";
cin >> author;


ofs <<"\n" <<id<<" "<<name<< " "<<author <<" "<<genre<<" "<<state<<endl;
if(genre=="Book"){
   insertBook(id,author,name,genre,state);
}
else if (genre=="Audiovisual")
{
    insertAudiovisual(id,author,name,genre,state);
}
else if (genre=="Digital"){
    insertDigital(id,author,name,genre,state);
}

cout <<"Adding Succesfull"<< endl;
system("pause");
system("cls");
return;
}

void Admin::removeitem(){
int select;
    int removeId;
    string filename;
    cout << "Remove of genre:\n1. Book\n2. Audiovisual Item\n3. Digital Resource\n Enter select:" << endl;
    cin >> select;

    if (select == 1)
    { 
               removebook();
                return;
    }
    else if (select == 2)
    {
               removeaudio();
                return;
    }
    else if (select == 3)
    {
               removedigital();
                return;
    }
    else
    {
        cout << "Invalid selection" << endl;
        return;
    }
}


void Admin::removebook()
{   vector<Book>book;
    Book b;
    
    ifs.open(BOOKS_FILE,ios_base::in);
    while (ifs >> b.Bid&&ifs >>b.Bname&&ifs>>b.Bauthor&&ifs >>b.Bgenre&&ifs>>b.Bstate)
    {
        book.push_back(b);
    }
    ifs.close();
    cout << "Enter your remove id:";
    int removeId;
    cin >> removeId;

    auto bookToRemove = find_if(book.begin(), book.end(), [removeId](const Book& b) {
        return b.Bid == removeId;
    });

    if (bookToRemove != book.end()) 
    {
        
        cout << "Removing item with ID: " << removeId << endl;
        cout << "Details " << endl;
        cout << "Book ID:"<<setw(10)<<bookToRemove->Bid<<endl; 
        cout<< "Title:" <<setw(10)<< bookToRemove->Bname<<endl;
        cout  << "Author:"<<setw(10)<<bookToRemove->Bauthor<<endl;
        cout  << "Genre:"<<setw(10)<<bookToRemove->Bgenre<<endl;
        cout << "State:" <<setw(10)<< bookToRemove->Bstate << endl;
        cout << "Confirm delete?(y/n):"<<endl;
        string confirm;
        cin >> confirm;
           if (confirm=="yes"||confirm=="y")
                {
                 Delete("Book",to_string(bookToRemove->Bid),"Book_ID");
                 book.erase(bookToRemove);
                 
        
                ofstream ofs(BOOKS_FILE, ios_base::out | ios_base::trunc);
                for (const Book& b :book)
                 {
                  ofs << b.Bid << " " << b.Bname << " " <<b.Bauthor <<" "<<b.Bgenre << " " << b.Bstate << endl;
                 }
                ofs.close();

                 cout << "Item with ID " << removeId << " removed successfully." << endl;
                    }
               
                else if (confirm=="n"||confirm=="no")
                {return;}
       
                 else
                 {
                   cout << "Error enter" << endl;
                 }

    system("pause");
    system("cls");
    return;
        }
        else{cout<<"Sorry id cannot find it "<<endl;
        system("pause");
         system("cls");
        return;}}
void Admin::removeaudio()
{   vector<Audiovisual>audio;
    Audiovisual a;
    ifs.open(AUDIOVISUAL_FILE,ios_base::in);
    while (ifs >> a.Aid&&ifs >>a.Aname&&ifs>>a.Aauthor&&ifs >>a.Agenre&&ifs>>a.Astate)
    {
        audio.push_back(a);
    }
    ifs.close();
    cout << "Enter your remove id:";
    int removeau;
    cin >> removeau;

    auto bookToRemove = find_if(audio.begin(), audio.end(), [removeau](const Audiovisual& a) {
        return a.Aid == removeau;
    });

    if (bookToRemove != audio.end()) 
    {
        
         cout << "Removing item with ID: " << removeau << endl;
        cout << "Details " << endl;
        cout << "Audiovisual ID:"<<setw(10)<<bookToRemove->Aid<<endl; 
        cout<< "Title:" <<setw(10)<< bookToRemove->Aname<<endl;
        cout  << "Author:"<<setw(10)<<bookToRemove->Aauthor<<endl;
        cout << "State:" <<setw(10)<< bookToRemove->Astate << endl;
         cout << "Confirm delete?(y/n):"<<endl;
        string confirm;
        cin >> confirm;
           if (confirm=="yes"||confirm=="y")
                {
                 Delete("Audiovisual",to_string(bookToRemove->Aid),"Audiovisual_ID");
                 audio.erase(bookToRemove);//delete

        
                ofstream ofs(AUDIOVISUAL_FILE, ios_base::out | ios_base::trunc);
                for (const Audiovisual& A :audio)
                 {
                  ofs << A.Aid << " " << A.Aname << " "<<A.Aauthor <<" " << A.Agenre << " " << A.Astate << endl;
                 }
                ofs.close();

                 cout << "Item with ID " << removeau << " removed successfully." << endl;
                    }
               
                else if (confirm=="n"||confirm=="no")
                {return;}
       
                 else
                 {
                    cout << "Error enter" << endl;
                 }

    system("pause");
    system("cls");
    return;
        }
        else{cout<<"Sorry id cannot find it "<<endl;
        system("pause");
         system("cls");
        return;}}
void Admin::removedigital()
{   vector<Digital>digital;
    Digital d;
     ifs.open(DIGITAL_FILE,ios_base::in);
   while (ifs >> d.Did&&ifs >>d.Dname&&ifs >>d.Dauthor&&ifs >>d.Dgenre&&ifs>>d.Dstate)
    {
        digital.push_back(d);
    }
    ifs.close();
    cout << "Enter your remove id:" ;
    int removedg;
    cin >> removedg;

    auto bookToRemove = find_if(digital.begin(), digital.end(), [removedg](const Digital& d) {
        return d.Did == removedg;
    });

    if (bookToRemove != digital.end()) 
    {
        
        cout << "Removing item with ID: " << removedg << endl;
        cout << "Details " << endl;
        cout << "Digital ID:"<<setw(10)<<bookToRemove->Did<<endl; 
        cout<< "Title:"<<setw(10) << bookToRemove->Dname<<endl;
        cout  << "Author:"<<setw(10)<<bookToRemove->Dauthor<<endl;
        cout << "State:" <<setw(10)<< bookToRemove->Dstate << endl;
        cout << "Confirm delete?(y/n):"<<endl;
        string confirm;
        cin >> confirm;
           if (confirm=="yes"||confirm=="y")
                {Delete("Digital",to_string(bookToRemove->Did),"Digital_ID");
                 digital.erase(bookToRemove);//delete
                ofstream ofs(DIGITAL_FILE, ios_base::out | ios_base::trunc);
                for (const Digital& D :digital)
                 {
                  ofs << D.Did << " " << D.Dname << " "<<D.Dauthor <<" " << D.Dgenre << " " << D.Dstate << endl;
                 }
                ofs.close();

                 cout << "Item with ID " << removedg << " removed successfully." << endl;
                    }
               
                else if (confirm=="n"||confirm=="no")
                {return;}
       
                 else
                 {
                   cout << "Error enter" << endl;
                 }

    system("pause");
    system("cls");
    return;
        }
        else{cout<<"Sorry id cannot find it "<<endl;
        system("pause");
         system("cls");
        return;}}

User* readUserData(string filename) {
    ifstream file(filename,ios_base::in);
    

    User* head = nullptr; // 链表头指针
    User* current = nullptr;

    int id,bill;
    string username, password,state;

    while (file >> id >> username >> password) {
        // 创建新节点
        User* newUser = new User{ id, username, password, nullptr };

        if (!head) {
            // 如果链表为空，将新节点设置为头节点
            head = newUser;
            current = newUser;
        } else {
            // 否则，将新节点链接到链表末尾
            current->next = newUser;
            current = newUser;
        }
    }

    file.close();
    return head;
}

void displayUsers(User* userList) {

    cout << left<<setw(20) << "ID" << setw(20) << "Username" << setw(20) << "Password" <<endl;
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;

    while (userList) {
        cout <<left <<setw(20) << userList->id << setw(20) << userList->username << setw(20) << userList->password<< setw(20)<<endl ;
        userList = userList->next;
    }
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
}

void displayUsers(){
    people b;
    ifs.open(MEMBER_FILE,ios_base::in);
    int id ,balance;
    string username,state,password;
    cout <<setw(50)<<"Member"<<endl;
    cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
    cout << left<<setw(20) << "ID" << setw(20) << "Username" << setw(20) << "Password" <<setw(20)<<"Balance(-RM)"<<setw(20)<<"State"<<endl;
    cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
    while (ifs >> id >> username >> password >>balance >> state)
    {
         cout <<left <<setw(20) << id << setw(20) << username << setw(20) << password<< setw(20)<< setw(20) << balance<< setw(20) << state<<endl ;
       
    }
    cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
    ifs.close();
}

void Admin ::showUser()
{
    
    User*adminList =readUserData(ADMIN_FILE);

    displayUsers();
    cout << "\n\nAdmins:" << endl;
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
    displayUsers(adminList);

     system("pause");
            system("cls");
            return;

} 




Borrow* readBorrowData(string filename) {
    ifstream file(filename,ios_base::in);
    

    Borrow* head = nullptr; // 链表头指针
    Borrow* current = nullptr;

    int UserID;
    string Username,BookingId,BookingName,BookingGenre,BookingState,BookingDate,BookingTime;

    while (file >> UserID>>Username>>BookingId>>BookingName>>BookingGenre>>BookingState>>BookingDate>>BookingTime) {
        // 创建新节点
        Borrow* borrowList = new Borrow{  UserID,Username,BookingId,BookingName,BookingGenre,BookingState,BookingDate,BookingTime,nullptr };

        if (!head) {
            // 如果链表为空，将新节点设置为头节点
            head = borrowList;
            current = borrowList;
        } else {
            // 否则，将新节点链接到链表末尾
            current->next = borrowList;
            current = borrowList;
        }
    }

    file.close();
    return head;
}



void displayBorrow(Borrow* borrowList) {
     int Id=1;

    cout<< "\n\n "<< setw(50)<<"Borrow List"<<endl;
    cout << setfill('-') << setw(109) << "" << setfill(' ') << endl;
    cout << "\n" << setw(5) << "ID" << setw(13) << "UserID" << setw(20) << "Username" << setw(15) << "BookingId"
                << setw(20) << "BookingName" << setw(20)<< "BookingDate"<<setw(15)<<"BookingTime"<< endl;
    
    cout << setfill('-') << setw(104) << "" << setfill(' ') << endl;

    while (borrowList) {
         cout << "\n" << setw(5) << Id << setw(13) << borrowList->UserID << setw(20) << borrowList->Username << setw(15) << borrowList->BookingId
              << setw(20) << borrowList->BookingName << setw(20)<< borrowList->BookingDate<<setw(15)<< borrowList->BookingTime<< endl;
        borrowList = borrowList->next;
        Id++;
    }
    cout << setfill('-') << setw(109) << "" << setfill(' ') << endl;
}



void Admin::CheckIn()
{   
    Return* returnList = nullptr; // 链表头指针
    Return* currentReturn = nullptr;

    ifstream ifs;
    ifs.open(RETURN_FILE, ios_base::in);

    string ReturnID;
    string ReturnName;
    string ReturnGenre;
    string userId;
    string Username;
    string ReturnDate;
    string ReturnTime;

    while (ifs >> ReturnID >> ReturnName >> ReturnGenre >> userId >> Username >> ReturnDate >> ReturnTime) {
        // 创建新节点
        Return* newReturn = new Return(Username, ReturnID, ReturnName, userId, ReturnDate, ReturnTime, nullptr);

        if (!returnList) {
            // 如果链表为空，将新节点设置为头节点
            returnList = newReturn;
            currentReturn = newReturn;
        } else {
            // 否则，将新节点链接到链表末尾
            currentReturn->next = newReturn;
            currentReturn = newReturn;
        }
    }

    ifs.close();
    cout<< "\n\n "<< setw(50)<<"Return List"<<endl;
    cout << setfill('-') << setw(119) << "" << setfill(' ') << endl;
    cout << "\n" << setw(5) << "ID" << setw(13) << "UserID" << setw(20) << "Username" << setw(15) << "BookingId"
                << setw(25) << "BookingName" << setw(25)<< "BookingDate"<<setw(15)<<"BookingTime"<< endl;
    
    cout << setfill('-') << setw(119) << "" << setfill(' ') << endl;
    // 打印 Return 列表
    int Id = 1;
    while (returnList) {
        cout << "\n" << setw(5) << Id << setw(13) << returnList->UserID << setw(20) << returnList->Username << setw(15) << returnList->ReturnId
             << setw(20) << returnList->ReturnName << setw(20) << returnList->ReturnDate << setw(15) << returnList->ReturnTime << endl;
        returnList = returnList->next;
        Id++;
    }
    cout << setfill('-') << setw(119) << "" << setfill(' ') <<"\n"<< endl;
}






void Admin::CheckOut()
{Borrow*borrowList= readBorrowData(BORROW_FILE);
     
    displayBorrow(borrowList);

     system("pause");
            system("cls");
            return;
}

void Admin::initVector()
{  
    
    member.clear();
    admin.clear();
    ifstream ifs ;
    ifs.open(MEMBER_FILE,ios_base::in);
     if(!ifs.is_open()){
        cout << "ERROR OPEN FILE"<< endl;
        return;
     }
     
     Member m;
     while (ifs >> m.T_Id&&ifs >>m.T_Name&& ifs>> m.T_pwd&&ifs >>m.T_bill&&ifs >>m.T_state)
     {
        member.push_back(m);
     }
    cout << "\nNow The Member Have "<<member.size()<<endl;
     ifs.close();
    
    ifs.open(ADMIN_FILE,ios_base::in);
     if(!ifs.is_open()){
        cout << "ERROR OPEN FILE"<< endl;
        return;
     }

     Admin a;
     while (ifs >> a.T_Id&&ifs >>a.T_Name&&ifs >>a.T_pwd)
     {
        admin.push_back(a);
     }
    cout << "Now The Admin Have "<<admin.size()<<endl;
  
}


void MemberMenu(Identity*&member){
    while (true) {
    Member*man =(Member*)member;
        man->openMenu();
        int select=0;
        cin >>select;
    switch (select) {
        case 1: {
             man->BookingSystem();
               break;
        }
        case 2: {
               man->BorrowsSystem();
            break;
        }
        case 3: {
            man->ReturnSystem();
            break;
        }
        case 4: {
             man->ViewAccount();
            break;
        }
        case 5: {
            cout << "Byb" <<endl;
            system("pause");
            system("cls");
            return;
        }
        default: {
            cout << "Invalid selection" << endl;
            break;
        }
    }
} 
}


void AdminMenu(Identity*&admin){
    string filename;
    ofstream ofs;
    while (true) {
    admin->openMenu();
    Admin* man = (Admin*)admin;
    int select = 0;
    cin >> select;

    switch (select) {
        case 1: {
            cout << "\nSelect your function\n1. Add\n2. Delete\n3. Catelog" << endl;
            cin >> select;

            switch (select) {
                case 1: {
                    cout << "Add of genre:\n1. Book\n2. Audiovisual Item\n3. Digital Resource\nEnter select:" << endl;
                    cin >> select;
                    man->addbook(select);
                    break;
                }
                case 2: {
                    man->removeitem();
                    break;
                }
                case 3:{
                    cout<<"Select genre:\n1.Book\n2.Audiovisual\n3.Digital"<<endl;
                    int select;
                    cin >>select;
                    if(select==1){
                Menu(BOOKS_FILE,"Book","Book");
            }
                else if(select==2){
                  Menu(AUDIOVISUAL_FILE,"Audiovisual","Audiovisual");
            }
                 else if(select==3){
                  Menu(DIGITAL_FILE,"Digital","Digital");
            }

                }
                default: {
                    cout << "Invalid selection" << endl;
                    break;
                }
            }
            break;
        }
        case 2: {
            man->showUser();
            break;
        }
        case 3: {
            man->CheckIn();
            break;
        }
        case 4: {
            man->CheckOut();
            break;
        }
        case 5: {
            cout << "Bye" << endl;
            system("pause");
            system("cls");
            return;
        }
        default: {
            cout << "Invalid selection" << endl;
            break;
        }
    }
}

}
struct Catelog{
    int Id;
    string Name;
    string Genre;
    string State;
    string Author;
};

bool compareID(const Catelog& c1, const Catelog& c2) {
    return c1.Id < c2.Id;
}

void Menu(string filename,string Title,string tablename) {
    vector<Catelog> catelog;
    catelog.clear();
    Catelog c;
    ifstream ifs;
    ifs.open(filename, std::ios_base::in);
    

    while (ifs >> c.Id && ifs >> c.Name && ifs >> c.State && ifs >> c.Genre && ifs >> c.State) {
        catelog.push_back(c);
    }

    ifs.close();

   
    std::sort(catelog.begin(), catelog.end(), compareID);

    std::cout << "*****" << Title << "*****" << std::endl;
    std::cout << std::left << std::setw(5) << "Id" << std::setw(30) << "Name" << std::setw(25) << "Genre" << std::setw(20) << "State" << std::endl;
    std::cout << std::setfill('-') << std::setw(70) << "-" << std::setfill(' ') << std::endl;

    for (const auto& it : catelog) {
        std::cout << std::left << std::setw(5) << it.Id << std::setw(30) << it.Name << std::setw(25) << it.Genre << std::setw(20) << it.State << std::endl;
    }

    std::cout << std::setfill('-') << std::setw(70) << "-" << std::setfill(' ') << std::endl;
}
void LoginIn(string Filename , int type){
Identity *Person =NULL;

ifstream ifs;
ifs.open(Filename,ios_base::in);

if(!ifs.is_open()){
    cout << "file not create"<<endl;
    ifs.close();
    return;
}
int Mid;
string username ;
string pwd;

cout << "Enter your id :";
cin >> Mid;
cout << "Enter your username :";
cin >> username;
cout << "Enter password :";
cin >> pwd;


if (type ==1){
int fId,fBill;
string fName,fPwd,fState;
       
while (ifs >> fId  && ifs >>fName &&ifs >>fPwd && ifs >>fBill &&ifs >>fState)
{
    if (fPwd ==pwd &&fName == username&&fId == Mid){
        cout << "Login Succesfull"<< endl;
        Person=new Member(fId,username,pwd,fBill,fState);
        MemberMenu(Person);
        break;
    }
   
    } 
    if(fPwd !=pwd ||fName != username||fId != Mid){
        cout << "Login Failed" << endl;
    }
    
}

if (type ==2){
int fId;
string fName,fPwd;
       
while (ifs >> fId  && ifs >>fName&&ifs >>fPwd )
{
    if (fPwd ==pwd &&fName == username&&fId == Mid){
        cout << "Login Succesfull";
        Person=new Admin(fId,username,pwd);
        AdminMenu(Person);
        break;
    }     
    }
    if(fPwd !=pwd ||fName != username||fId != Mid){
        cout << "Login Failed" << endl;
    }
}}


void CreateAccount(string filename){

string Username,password;
int id;
string State="Positive";
int bill =0;

ofstream ofs;
ofs.open(filename,ios_base::out|ios_base::app);
 
while (true)
{
    cout << "Enter your Id :";
    cin >> id;
    bool ret =checkRepeatUserID(filename,id);
    if(ret){
     cout <<"This id already exists"<<endl;
    }
    else{break;}
}

cout << "\nEnter your Username :";
cin>> Username;
cout << "Enter your Password :";
cin>> password;

if (filename==MEMBER_FILE){
ofs <<"\n" <<id<<" "<<Username<< " "<< password<< " "<< bill<< " "<< State<<endl;
insertUser(id,Username,password,bill,State);
}
else if(filename ==ADMIN_FILE){
    ofs <<"\n" <<id<<" "<<Username<< " "<< password<<endl;
insertAdmin(id,Username,password);    
}
cout <<"Created Succesfull"<< endl;

system("pause");
system("cls");

ofs.close();
}

int getValidInput() {
    int input;
    while (true) {
        cout<<":";
        cin >> input;
       
        if (cin.fail()) {
           
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Honey ,why you shihui please correctly input\n";
        } else {
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return input;
 }
}
}





int main(){
    
    sqlite3* DB;
    int exit=0;

    string sql_create_User = "CREATE TABLE USER("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                   "USER_ID INTEGER  NOT NULL, "
                                   "USER_USERNAME TEXT NOT NULL, "
                                   "USER_PASSWORD TEXT NOT NULL,"
                                   "USER_Bill INTEGER NOT NULL,"
                                   "USER_STATE TEXT NOT NULL);";

    string sql_create_Admin = "CREATE TABLE Admin("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                   "ADMIN_ID INTEGER  NOT NULL, "
                                   "ADMIN_USERNAME TEXT NOT NULL, "
                                   "ADMIN_PASSWORD TEXT NOT NULL);";

    string sql_create_Audiovisual = "CREATE TABLE Audiovisual("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                   "Audiovisual_ID INTEGER  NOT NULL, "
                                   "Audiovisual_AUTHOR  TEXT NOT NULL, "
                                   "Audiovisual_TITLE TEXT NOT NULL, "
                                   "Audiovisual_Genre TEXT NOT NULL, "
                                   "Audiovisual_STATE TEXT NOT NULL);";

    string sql_create_Book = "CREATE TABLE Book("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                   "Book_ID INTEGER  NOT NULL, "
                                   "Book_AUTHOR  TEXT NOT NULL, "
                                   "Book_TITLE TEXT NOT NULL, "
                                   "Book_Genre TEXT NOT NULL, "
                                   "Book_STATE TEXT NOT NULL);";

string sql_create_Digital = "CREATE TABLE Digital("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                   "Digital_ID INTEGER  NOT NULL, "
                                   "Digital_AUTHOR TEXT NOT NULL, "
                                   "Digital_TITLE TEXT NOT NULL, "
                                   "Digital_Genre TEXT NOT NULL, "
                                   "Digital_STATE TEXT NOT NULL);";
                                   


    string sql_create_Borrow = " CREATE TABLE Borrow("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                   "User_ID INTEGER  NOT NULL, "
                                   "USERNAME TEXT NOT NULL, "
                                   "BorrowID TEXT NOT NULL,"
                                   "BorrowName TEXT NOT NULL, "
                                   "BorrowGenre TEXT NOT NULL, "
                                   "BorrowState TEXT NOT NULL, "
                                   "BorrowDate DATE NOT NULL, "
                                   "BorrowTime TIME NOT NULL); ";

    string sql_create_Return = " CREATE TABLE Return("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                   "User_ID INTEGER  NOT NULL, "
                                   "USERNAME TEXT NOT NULL, "
                                   "ReturnID TEXT NOT NULL,"
                                   "ReturnName TEXT NOT NULL, "
                                   "ReturnGenre TEXT NOT NULL, "
                                   "ReturnState TEXT NOT NULL, "
                                   "ReturnDate DATE NOT NULL, "
                                   "ReturnTime TIME NOT NULL); ";

    string sql_create_Order = " CREATE TABLE Reserve("
                                   "ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
                                   "Reserve_ID INTEGER  NOT NULL, "
                                   "Reserve_Name TEXT NOT NULL, "
                                   "Reserve_Genre TEXT NOT NULL,"
                                   "Username TEXT NOT NULL, "
                                   "State TEXT NOT NULL); ";


    exit = sqlite3_open("Library.db", &DB);
    char* messaggeError;

    exit = sqlite3_exec(DB, sql_create_User.c_str(), 0, 0, &messaggeError);
    exit = sqlite3_exec(DB, sql_create_Order.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, sql_create_Admin.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, sql_create_Audiovisual.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, sql_create_Book.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, sql_create_Digital.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, sql_create_Borrow.c_str(), NULL, 0, &messaggeError);
    exit = sqlite3_exec(DB, sql_create_Return.c_str(), NULL, 0, &messaggeError);
    
    
    
    if (exit != SQLITE_OK) {
        cerr << "Error creating table: " << messaggeError << endl;
        sqlite3_free(messaggeError);
    } else {
        cout << "Table created successfully" << endl;
    }

    


    int select=0;
    int enter;
    int id;
    Book book;
    vector<Audiovisual>audiovisual;
    vector<Digital>digital;
    while (true)
    {cout << "\n**********************************"<<endl;
    cout << "*      LIBRARY MANAGEMENT        *"<<endl;
    cout << "**********************************\n";
    cout << "*    1.Catelog                   *\n";
    cout << "*    2.Login account             *\n";
    cout << "*    3.Create accont             *\n";
    cout << "*    4.Exit                      *\n";          
    cout << "**********************************\n\n";
    cout << "Enter the code " ; 
    select=getValidInput();
    switch (select)
    {
        
        case 1:
            cout << "Enter number to select\n1.Look List\n2.searching"<<endl;
            cin >>enter;
            cout << "\nSelect your number to wanted see genre\n1.Book\n2.Audiovisual\n3.Digital Resources"<<endl;
            select=getValidInput();
            if(enter==1){
            if(select==1){
                Menu(BOOKS_FILE,"Book","Book");
            }
            else if(select==2){
                  Menu(AUDIOVISUAL_FILE,"Audiovisual","Audiovisual");
            }
             else if(select==3){
                  Menu(DIGITAL_FILE,"Digital","Digital");
            }}
            else if(enter==2){
                cout << "Enter your id :";
                cin >>id ;
                 if(select==1){
                Select("Book",id,"Book_ID");
            }
            else if(select==2){
                Select("Audiovisual",id,"Audiovisual_ID");
                
            }
             else if(select==3){
                Select("Digital",id,"Digital_ID");
                 
            }
            }
            
            break;

        case 2:
            cout << "You are \n1.Member \n2.Admin"<< endl;
            select=getValidInput();
            if (select ==1){
                LoginIn(MEMBER_FILE,1);
            }
            else if (select ==2){
                LoginIn(ADMIN_FILE,2);
            }
            break;

        case 3:
        cout << "Create of ? \n1.Member \n2.Admin"<< endl;
            select=getValidInput();
            if (select ==1){
                CreateAccount(MEMBER_FILE);
            }
            else if (select ==2){
                CreateAccount(ADMIN_FILE);
            }

            break;
        

         case 4:
            cout <<"Sayonara";
            return 0;//exit
            break; 
        
        default:
            system("pause");
            system("cls");
            break;
        }}
}