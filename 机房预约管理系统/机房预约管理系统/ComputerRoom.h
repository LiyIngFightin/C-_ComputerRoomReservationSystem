#pragma once
#include<string>
#include<iostream>
using namespace std;
class ComputerRoom
{
public:
	ComputerRoom(void);
	ComputerRoom(const ComputerRoom &c);
	ComputerRoom(int _sta,int _num,int _size);
	~ComputerRoom(void);
	
	int		Status;
	int		Num;
	int		size;
};

