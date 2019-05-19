#include "ComputerRoom.h"
#include<string>
#include<iostream>
using namespace std;

ComputerRoom::ComputerRoom(void)
{
	Status=0;
	Num=0;
	size=0;
}
ComputerRoom::ComputerRoom(const ComputerRoom &c)
{
	Status=c.Status;
	Num=c.Num;
	size=c.size;
}
ComputerRoom::ComputerRoom(int _sta,int _num,int _size)
{

	Status=_sta;
	Num=_num;
	size=_size;
}

ComputerRoom::~ComputerRoom(void)
{
}
