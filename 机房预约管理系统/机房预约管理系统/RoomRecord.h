#pragma once
#pragma once
#include<string>
#include<iostream>
using namespace std;
class RoomRecord
{
public:
	RoomRecord(void);
	RoomRecord(const RoomRecord &r);
	RoomRecord(string _date,string _time,string _name,string _sta,int _num,int _seat);
	~RoomRecord(void);

	string	Date;
	string	Time;
	string	Name;
	string	Status;
	int		Num;
	int		Seat;
};



