#pragma once
#include"Identity.h"
#include<string>
#include<iostream>
#include"ComputerRoom.h"
#include"RoomRecord.h"
#include<vector>
using namespace std;
class Student:public Identity
{
public:
	Student(void);
	Student(string _name,string _psw,int _id);
	Student(const Student &t);
	virtual void menuDis(void);
	void InitVector(void);
	void CheckReserveSta();
	void ModifyReserve();
	void CancelReserve();
	~Student(void);
	void DealOper(void);
	void ReserveRoom(void);
	void ModifyInfor(void);
	void CheckReserve();
	void CheckRoom();
public:
	int stuID;
	vector<Student> vStu;
	vector<ComputerRoom> vCpuRoom;
	vector<RoomRecord>	vRoomRec;
};

