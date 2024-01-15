#pragma once
#include <iostream>
using namespace std;
#include "globalFile.h"
#include <fstream>


class Identity
{
    public:
    virtual void openMenu()=0;
    int T_Id;
    string T_Name;
    string T_pwd;
    string T_state;
    int T_bill;
    
    
};



