#pragma once
#include "Student.h"
#include"Identity.h"
#include"FileName.h"
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include"ComputerRoom.h"
#include"RoomRecord.h"
#include<algorithm>
using namespace std;
class Teacher:public Identity
{
public:

	Teacher(void);
	Teacher(string _name,string _psw,int _id);
	Teacher(const Teacher &t);
	virtual void menuDis(void);
	~Teacher(void);
	void CheckReserve();
	void InitVector();
	void DealOper(void);
	void ModifyInfor(void);
	void CheckRoom();
	void VerifyReserve();
public:
	int teaID;
	vector<ComputerRoom> vCpuRoom;
	vector<RoomRecord>	vRoomRec;
	vector<Student> vStu;
	vector<Teacher>	vTea;
};

