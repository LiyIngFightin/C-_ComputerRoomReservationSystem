#include "RoomRecord.h"



#include<string>
#include<iostream>
using namespace std;

RoomRecord::RoomRecord(void)
{
	Date="";
	Time="";
	Name="";
	Status="";
	Num=0;
	Seat=0;
}
RoomRecord::RoomRecord(const RoomRecord &r)
{
	Date=r.Date;
	Time=r.Time;
	Name=r.Name;
	Status=r.Status;
	Num=r.Num;
	Seat=r.Seat;
}
RoomRecord::RoomRecord(string _date,string _time,string _name,string _sta,int _num,int _seat)
{
	Date=_date;
	Time=_time;
	Name=_name;
	Status=_sta;
	Num=_num;
	Seat=_seat;
}

RoomRecord::~RoomRecord(void)
{
}

