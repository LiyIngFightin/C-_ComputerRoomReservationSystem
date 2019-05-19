#pragma once
#include<iostream>
#include<string>
using namespace std;
class Identity
{
public:
	Identity(void);
	Identity(string _name,string _psw):name(_name),psw(_psw)
	{
	}
	~Identity(void);
	virtual void menuDis(void)=0;
public:
	string name;
	string psw;
};

