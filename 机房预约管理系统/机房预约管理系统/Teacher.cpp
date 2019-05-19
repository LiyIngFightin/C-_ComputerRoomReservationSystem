#include "Teacher.h"
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

Teacher::Teacher(void)
{
}


Teacher::~Teacher(void)
{
}


Teacher::Teacher(string _name,string _psw,int _id)
{
	name=_name;
	psw=_psw;
	teaID=_id;
}
Teacher::Teacher(const Teacher &t)
{
	name=t.name;
	psw=t.psw;
	teaID=t.teaID;
}
void Teacher::menuDis(void)
{
	cout<<endl;
	cout<<"----------------------机房预约系统----------------------"<<endl;
	cout<<"             |********老师身份登录******* |         "<<endl;
	cout<<"             |   1:   管理学生预约        |         "<<endl;
	cout<<"             |   2:   查询所有预约        |         "<<endl;
	cout<<"             |   3:   查询机房状态        |         "<<endl;
	cout<<"             |   4:   更改身份信息        |         "<<endl;
	cout<<"             |   5:   ----------        |         "<<endl;
	cout<<"             |   6:   ----------        |         "<<endl;
	cout<<"             |   7:   ----------        |         "<<endl;
	cout<<"             |   8:   ----------        |         "<<endl;	
	cout<<"             |   9:   ----------        |         "<<endl;	
	cout<<"             |   0:   退出老师身份        |         "<<endl;	
	cout<<"             |********老师登录界面********|         "<<endl;
	cout<<"----------------------机房预约系统----------------------"<<endl;
}
class isTea
{
public:
	isTea(string _name,string _psw,int _id)
	{
		name=_name;
		psw=_psw;
		id=_id;
	}
	bool operator()(const Teacher &t)
	{
		if(t.name==this->name && t.teaID==this->id && t.psw==this->psw)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
public:
	string name;
	string psw;
	int id;
};
class isRec
{
public:
	isRec(const RoomRecord &t)
	{
		rr.Date=t.Date;
		rr.Name=t.Name;
		rr.Num=t.Num;
		rr.Seat=t.Seat;
		rr.Time=t.Time;
		rr.Status=t.Status;

	}
	bool operator()(const RoomRecord &t)
	{
		if(rr.Status=="取消"&& t.Status=="取消预约")
		{
			return true;
		}
		else if(rr.Status=="审核"&& t.Status=="预约审核中")
		{
			return true;
		}
		else if(rr.Date==t.Date && rr.Name == t.Name && rr.Num==t.Num && rr.Seat==t.Seat && rr.Status==t.Status && rr.Time==t.Time)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	RoomRecord rr;
};
static void printRoomRec(RoomRecord &v)
{
	cout<<"预约时间："<<v.Date<<v.Time<<"		姓名："<<v.Name<<"	预约"<<v.Num<<"号机房"<<v.Seat<<"座次	"<<"预约状态：	"<<v.Status<<endl;;
}

static void printCRoom(ComputerRoom &v)
{
	cout<<"机房号码："<<v.Num<<"	已使用座位："<<v.Status<<"	机房总座位："<<v.size<<endl;;
}
void Teacher::InitVector()
{
	ifstream ifs;
	string fname;
	string fpsw;
	int fid;
	vStu.clear();
	vTea.clear();
	vRoomRec.clear();
	vCpuRoom.clear();
	ifs.open(STUDENTFILE,ios::in);
	if(! ifs.is_open() )
	{
		cout<<"初始化学生容器失败"<<endl;
		system("pause");
	}
	while(ifs>>fid && ifs>>fname && ifs>>fpsw)
	{

		vStu.push_back(Student(fname,fpsw,fid));
	}
	ifs.close();
	ifs.open(TEACHERFILE,ios::in);
	if(! ifs.is_open() )
	{
		cout<<"初始化老师容器失败"<<endl;
		system("pause");
	}
	while(ifs>>fid && ifs>>fname && ifs>>fpsw)
	{

		vTea.push_back(Teacher(fname,fpsw,fid));
	}
	ifs.close();


	ComputerRoom cr;
	ifs.open(CALROOMSTATUS,ios::in);
	if(! ifs.is_open() )
	{
		cout<<"初始化机房容器失败"<<endl;
		system("pause");
	}
	while(ifs>>cr.Num && ifs>>cr.Status && ifs>>cr.size)
	{
		vCpuRoom.push_back(cr);
	}
	ifs.close();


	RoomRecord rr;
	ifs.open(RECORDFILE,ios::in);
	if(! ifs.is_open() )
	{
		cout<<"初始化记录容器失败"<<endl;
		system("pause");
	}
	while(ifs>>rr.Date && ifs>>rr.Time && ifs>>rr.Name && ifs>>rr.Num && ifs>>rr.Seat && ifs>>rr.Status)
	{
		vRoomRec.push_back(rr);
	}
	ifs.close();
}
void Teacher::ModifyInfor(void)
{
	while(1)
	{
		InitVector();
		int logid;
		string logname;
		string logpsw;
		string modpsw;
		char y;
		cout<<"确定修改个人信息密码？ y/n"<<endl;
		cin>>y;
		if(y=='y'||y=='Y')
		{
			cout<<endl<<"请输入您的工号："<<endl;
			cin>>logid;
			cout<<endl<<"请输入您的姓名："<<endl;
			cin>>logname;
			cout<<endl<<"请输入您的密码："<<endl;
			cin>>logpsw;
			vector<Teacher>:: iterator it=find_if(vTea.begin(),vTea.end(),isTea(logname,logpsw,logid));
			if(it == vTea.end())
			{
				cout<<"输入信息有误"<<endl;
				cout<<"将重新返回修改页面~"<<endl;
			}
			else
			{
				cout<<"验证成功，请输入修改的密码："<<endl;
				cin>>modpsw;
				it->psw=modpsw;
				ofstream ofs(TEACHERFILE,ios::out|ios::trunc);
				if(!ofs)
				{
					cout<<"打开文件失败"<<endl;
					system("pause");
				}
				for(vector<Teacher>:: iterator vit=vTea.begin();vit!=vTea.end();vit++)
				{
					ofs<<vit->teaID<<"\t"<<vit->name<<"\t"<<vit->psw<<endl;
				}
				ofs.close();
				cout<<"修改成功~~~"<<endl;
				system("pause");
				return;
			}
		}
		else
		{
			return;
		}
	}

}
void Teacher::CheckReserve()
{
	InitVector();
	cout<<"预约信息如下："<<endl;
	for_each(vRoomRec.begin(),vRoomRec.end(),printRoomRec);
}
void Teacher::CheckRoom()
{
	InitVector();
	cout<<"机房信息如下："<<endl;
	for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
}
void Teacher::VerifyReserve()
{
	while(1)
	{
		int select=0;
		InitVector();
		cout<<"审核预约开始~~~"<<endl;
		cout<<endl;
		CheckReserve();
		cout<<endl;
		RoomRecord rtemp;
		vector<RoomRecord> vtemp;
		vtemp.clear();
		char y;
		cout<<"审核预约："<<endl;
		cout<<"	1:处理取消预约	2：审核申请预约	"<<endl;
		cin>>select;
		if(select == 1)
		{
			cout<<endl;
			rtemp.Status="取消";
			cout<<"学生主动取消预约如下："<<endl;
			vector<RoomRecord>::iterator rit_find=vRoomRec.begin();
			while(1)
			{

				rit_find=find_if(rit_find,vRoomRec.end(),isRec(rtemp));
				if(rit_find != vRoomRec.end())
				{
					vtemp.push_back(*rit_find);
					rit_find++;
				}
				else
				{
					break;
				}

			}
			if(vtemp.size() == 0 )
			{
				cout<<"没有取消预约的学生~~~"<<endl;
				
			}
			else
			{
				for_each(vtemp.begin(),vtemp.end(),printRoomRec);
				cout<<endl;
				cout<<"是否全部删除？ y/n"<<endl;
				cin>>y;
				if(y=='y'||y=='Y')
				{
					for(vector<RoomRecord>::iterator vit=vtemp.begin();vit!=vtemp.end();vit++)
					{
						rit_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(*vit));
						vRoomRec.erase(rit_find);
					}
					ofstream ofs(RECORDFILE,ios::out|ios::trunc);
					if(!ofs)
					{
						cout<<"打开文件失败"<<endl;
						system("pause");
					}
					for(vector<RoomRecord>::iterator vit=vRoomRec.begin();vit!=vRoomRec.end();vit++)
					{
						ofs<< vit->Date<<"\t"<< vit->Time<<"\t"<< vit->Name<<"\t"<< vit->Num<<"\t"<< vit->Seat<<"\t"<< vit->Status<<endl;
					}
					
				}
				else
				{

				}


			}
		}

	}
}
void Teacher::DealOper(void)
{
	while(1)
	{
		int select;
		cin>>select;
			/*
			cout<<endl;
			cout<<"----------------------机房预约系统----------------------"<<endl;
			cout<<"             |********老师身份登录******* |         "<<endl;
			cout<<"             |   1:   管理学生预约        |         "<<endl;
			cout<<"             |   2:   查询所有预约        |         "<<endl;
			cout<<"             |   3:   查询机房状态        |         "<<endl;
			cout<<"             |   4:   更改身份信息        |         "<<endl;
			cout<<"             |   5:   ----------        |         "<<endl;
			cout<<"             |   6:   ----------        |         "<<endl;
			cout<<"             |   7:   ----------        |         "<<endl;
			cout<<"             |   8:   ----------        |         "<<endl;	
			cout<<"             |   9:   ----------        |         "<<endl;	
			cout<<"             |   0:   退出老师身份        |         "<<endl;	
			cout<<"             |********老师登录界面********|         "<<endl;
			cout<<"----------------------机房预约系统----------------------"<<endl;
		*/
		switch(select)
		{
			case 1:

				break;
			case 2:
				CheckReserve();
				system("pause");
				break;
			case 3:
				CheckRoom();
				system("pause");
				break;
			case 4:
				ModifyInfor();
				break;
			case 5:

				break;
			case 6:

				break;
			case 7:

				break;
			case 0:
				system("cls");
				return;

		}
		system("cls");
		menuDis();
		cout<<"输入您要进行的操作编号："<<endl;
	}
}
