
#pragma once
#include<string>
#include<iostream>
using namespace std;
#include "sqlite3.h"

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    if(argc>1){
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;}
    else{
        cout <<"Sorry id cannot be find it "<<endl;
        return 0;
    }
}


void insertUser( int id,string Username ,string password,int bill ,string State){
    sqlite3* DB;
    int exit = sqlite3_open("Library.db", &DB);
    char* messageError;

    string sql_insert_data = "INSERT INTO USER(USER_ID, USER_USERNAME, USER_PASSWORD,USER_Bill,USER_STATE) VALUES ("
                         + to_string(id) + ", "
                         + "'" + Username + "', "
                         + "'" + password + "',"
                         + " " + to_string(bill) + " ,"
                         + "'" + State + "');";

    exit = sqlite3_exec(DB, sql_insert_data.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error inserting data: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Data inserted successfully" << endl;
    }   
}


void insertAdmin( int id,string Username ,string password){
    sqlite3* DB;
    int exit = sqlite3_open("Library.db", &DB);
    char* messageError;

    string sql_insert_data = "INSERT INTO Admin(ADMIN_ID, ADMIN_USERNAME, ADMIN_PASSWORD) VALUES ("
                         + to_string(id) + ", "
                         + "'" + Username + "', "
                         + "'" + password + "');";

    exit = sqlite3_exec(DB, sql_insert_data.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error inserting data: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Data inserted successfully" << endl;
    }   
}


void insertBook(int id,string author ,string title ,string genre ,string state){
{sqlite3* DB;
    int exit = sqlite3_open("library.db", &DB);
    char* messageError;
    string sql_insert_data = "INSERT INTO Book (BOOK_ID, BOOK_AUTHOR, BOOK_TITLE, BOOK_Genre, BOOK_STATE) "
                             "VALUES ('" + to_string(id) + "', '" + author + "', '" + title + "', '" + genre + "', '"+ state + "');";
    exit = sqlite3_exec(DB, sql_insert_data.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error inserting data: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Data inserted successfully" << endl;
    }
}
   
    }   
            
void insertAudiovisual(int id,string author ,string title ,string genre ,string state){
{sqlite3* DB;
    int exit = sqlite3_open("library.db", &DB);
    char* messageError;
    string sql_insert_data = "INSERT INTO Audiovisual (AUDIOVISUAL_ID, AUDIOVISUAL_AUTHOR, AUDIOVISUAL_TITLE, AUDIOVISUAL_Genre, AUDIOVISUAL_STATE) "
                             "VALUES ('" + to_string(id) + "', '" + author + "', '" + title + "', '"+ genre + "','" + state + "');";
    exit = sqlite3_exec(DB, sql_insert_data.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error inserting data: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Data inserted successfully" << endl;
    }
}
     
    }   


void insertDigital(int id,string author ,string title ,string genre ,string state){
{sqlite3* DB;
    int exit = sqlite3_open("library.db", &DB);
    char* messageError;
    string sql_insert_data = "INSERT INTO Digital (DIGITAL_ID, DIGITAL_AUTHOR, DIGITAL_TITLE, DIGITAL_Genre, DIGITAL_STATE) "
                             "VALUES ('" + to_string(id) + "','"  + author + "', '" + title + "', '"+ genre + "','" + state + "');";
    exit = sqlite3_exec(DB, sql_insert_data.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error inserting data: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Data inserted successfully" << endl;
    }
}
     
    } 
    
void insertOrder(string Order_id ,string Order_name ,string Order_Genre ,string Username ,string state ){
{sqlite3* DB;
    int exit = sqlite3_open("library.db", &DB);
    char* messageError;
    string sql_insert_data = "INSERT INTO Reserve (Reserve_ID, Reserve_Name, Reserve_Genre, Username, State) "
                             "VALUES ('" + Order_id + "', '" + Order_name + "', '" + Order_Genre + "', '" + Username + "', '"+ state + "');";
    exit = sqlite3_exec(DB, sql_insert_data.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error inserting data: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Data inserted successfully" << endl;
    }
}
    
    }   


void insertBorrow(int user_id ,string username ,string borrow_id ,string borrow_name ,string borrow_genre ,string borrow_state ,string borrow_date ,string borrow_time){
{sqlite3* DB;
    int exit = sqlite3_open("library.db", &DB);
    char* messageError;
    string sql_insert_data = "INSERT INTO Borrow (USER_ID, USERNAME, BORROWID, BORROWNAME, BORROWGENRE, BORROWSTATE, BORROWDATE, BORROWTIME) "
                             "VALUES (" + to_string(user_id) + ", '" + username + "', '" + borrow_id + "', '" + borrow_name + "', '"+ borrow_genre + "','" + borrow_state + "','" + borrow_date + "','" + borrow_time + "');";
    exit = sqlite3_exec(DB, sql_insert_data.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error inserting data: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Data inserted successfully" << endl;
    }
}
    
    }   

void insertReturn(int user_id ,string username ,string return_id ,string return_name ,string return_genre ,string return_state ,string return_date ,string return_time){
{sqlite3* DB;
    int exit = sqlite3_open("library.db", &DB);
    char* messageError;
    string sql_insert_data = "INSERT INTO RETURN (USER_ID, USERNAME, RETURNID, RETURNNAME, RETURNGENRE, RETURNSTATE, RETURNDATE, RETURNTIME) "
                             "VALUES ('" + to_string(user_id) + "', '" + username + "', '" + return_id + "', '" + return_name + "', '"+ return_genre + "','" + return_state + "','" + return_date + "','" + return_time + "');";
    exit = sqlite3_exec(DB, sql_insert_data.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error inserting data: " << messageError << endl;
        sqlite3_free(messageError);
    } else {
        cout << "Data inserted successfully" << endl;
    }
}
    }


void  updateState(string TableName,string SetValue,string ChangeValue, string WhereValue ,string WhereAfterValue){
  
  sqlite3* DB;
  char* messaggeError;
  int exit = sqlite3_open("library.db", &DB);

                            //Book         Book_STATE     Borrowed                Book_TITLE       BookNAME
   string sql ="UPDATE "+TableName+" SET "+SetValue+" ='"+ChangeValue +"' WHERE "+WhereValue+"= '"+WhereAfterValue+"'";



   exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Update" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Record update Successfully!" << std::endl;
  
    sqlite3_close(DB);
}

void  updateBill(string TableName,string SetValue,string ChangeValue, string WhereValue ,string WhereAfterValue){
  
  sqlite3* DB;
  char* messaggeError;
  int exit = sqlite3_open("library.db", &DB);

                            //User          Bill          2                       Usernam         2270117
   string sql ="UPDATE "+TableName+" SET "+SetValue+" ="+ChangeValue +"  WHERE "+WhereValue+"= "+WhereAfterValue+"'";



   exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Update" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Record update Successfully!" << std::endl;
  
    sqlite3_close(DB);
}

void Select( string  tablename,int id,string Valuename) {
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);
    string query = "SELECT * FROM "+tablename +" WHERE "+Valuename+"='"+ to_string(id)+"';";
    
    cout <<"Select this id are:"<<endl;
     sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
     if (exit != SQLITE_OK) {
        std::cerr << "sorry cannot find it " << std::endl;
        sqlite3_free(messaggeError);
    }


}

void Delete( string  tablename,string condition,string Valuename) {
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("Library.db", &DB);
    string query = "DELETE  FROM "+tablename +" WHERE "+Valuename+" =  "+ condition+" ;";
    
    cout << query<<endl;
     sqlite3_exec(DB, query.c_str(), 0, NULL, NULL);
     if (exit != SQLITE_OK) {
        std::cerr << "Error  " << std::endl;
        sqlite3_free(messaggeError);
    }
    else {
        cout << "Data delete successfully" << endl;
    }


}



