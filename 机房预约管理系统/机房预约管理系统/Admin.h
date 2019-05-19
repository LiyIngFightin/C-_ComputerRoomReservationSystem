#pragma once
#include"Identity.h"
#include<string>
#include<vector>
#include"ComputerRoom.h"
#include"RoomRecord.h"
#include"Student.h"
#include"Teacher.h"
#include<iostream>
using namespace std;

class Admin:public Identity
{
public:
	Admin(void);
	Admin(string _name,string _psw);
	Admin(const Admin &adm);
	virtual void menuDis(void);
	~Admin(void);
	void AddOperator(void);
	void DeleteOperator(void);
	void DealOper();
	void InitVector();
	void CheckReserve();
	void CheckRoom();
	void CheckOperator();

	vector<Student> vStu;
	vector<Teacher>	vTea;
	vector<Admin>	vAdm;
	vector<ComputerRoom> vCpuRoom;
	vector<RoomRecord>	vRoomRec;
};


