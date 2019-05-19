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

Student::Student(void)
{
	this->name="";
	this->psw="";
	this->stuID=1000;
}
Student::Student(string _name,string _psw,int _id):Identity(_name,_psw),stuID(_id)
{

}

Student::Student(const Student &t)
{
	this->name=t.name;
	this->psw=t.psw;
	this->stuID=t.stuID;
}
class isStu
{
public:
	isStu(string _name,string _psw,int _id)
	{
		name=_name;
		psw=_psw;
		id=_id;
	}
	bool operator()(const Student &t)
	{
		if(t.name==this->name && t.stuID==this->id && t.psw==this->psw)
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
		if(rr.Date==t.Date && rr.Time==t.Time && rr.Num==t.Num && rr.Seat==t.Seat && rr.Status=="预约申请")
		{
			return true;
		}
		else if(rr.Status == "查找预约" && rr.Name == t.Name)
		{
			return true;
		}
		else if(rr.Date==t.Date && rr.Time==t.Time && rr.Num==t.Num && rr.Seat==t.Seat && rr.Status==t.Status)
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
void Student::menuDis(void)
{
	cout<<endl;
	cout<<"----------------------机房预约系统----------------------"<<endl;
	cout<<"             |********学生身份登录******* |         "<<endl;
	cout<<"             |   1:   预约机房位置        |         "<<endl;
	cout<<"             |   2:   查询所有预约        |         "<<endl;
	cout<<"             |   3:   更改自己预约        |         "<<endl;
	cout<<"             |   4:   查询预约状态        |         "<<endl;
	cout<<"             |   5:   查询机房状态        |         "<<endl;
	cout<<"             |   6:   更改身份信息        |         "<<endl;
	cout<<"             |   7:   取消自己预约        |         "<<endl;
	cout<<"             |   8:   ----------        |         "<<endl;	
	cout<<"             |   9:   ----------        |         "<<endl;	
	cout<<"             |   0:   退出学生身份        |         "<<endl;	
	cout<<"             |********学生登录界面********|         "<<endl;
	cout<<"----------------------机房预约系统----------------------"<<endl;
}

Student::~Student(void)
{

}
void Student::InitVector()
{
	ifstream ifs;
	string fname;
	string fpsw;
	int fid;
	vStu.clear();
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
void Student::ReserveRoom(void)
{
	while(1)
	{
		InitVector();
		RoomRecord vtemp;
		char y;
		cout<<"机房信息如下："<<endl;
		for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
		cout<<"请自觉查看预约信息来进行预约~~~~"<<endl;
		cout<<"请输入预约时间：仅周一至周五"<<endl;
		cin>> vtemp.Date;
		cout<<"请输入预约时间段： 上午/下午"<<endl;
		cin>> vtemp.Time;
		cout<<"请输入预约机房号码： 1/2/3"<<endl;
		cin>>vtemp.Num;
		cout<<"请输入预约机房座次："<<endl;
		cin>>vtemp.Seat;
		vtemp.Name=this->name;
		vtemp.Status="预约申请";
		if(vCpuRoom[vtemp.Num].size !=vCpuRoom[vtemp.Num].Status)
		{
			if(vCpuRoom[vtemp.Num].size >= vtemp.Seat)
			{
				vector<RoomRecord>::iterator it_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(vtemp));
				if( it_find == vRoomRec.end())
				{		
					vtemp.Status="预约审核中";
					ofstream ofs(RECORDFILE,ios::out|ios::app);
					if(!ofs)
					{
						cout<<"文件打开失败"<<endl;
						system("pause");
						return ;
					}
					ofs<<vtemp.Date<<"\t"<<vtemp.Time<<"\t"<<vtemp.Name<<"\t"<<vtemp.Num<<"\t"<<vtemp.Seat<<"\t"<<vtemp.Status<<endl;
					ofs.close();
					cout<<"正在预约中，等待老师审核~~~"<<endl;
					cout<<endl;
					cout<<endl;
				}
				else
				{
					cout<<"该时间段该位置已被预约或正在预约中~~"<<endl;
					cout<<endl;
					cout<<endl;
				}
			}
			else
			{
				cout<<"预约的座次不正确，请查看机房信息"<<endl;
			}
		}
		else
		{
			cout<<"预约的房间已满~~~~~"<<endl;
		}
		cout<<"是否继续预约申请 y/n"<<endl;
		cin>>y;
		if( y=='y' || y=='Y')
		{
			system("cls");
		}
		else
		{
			system("pause");
			return;
		}
	}
}
void Student::CheckReserve()
{
	InitVector();
	cout<<"预约信息如下："<<endl;
	for_each(vRoomRec.begin(),vRoomRec.end(),printRoomRec);
}
void Student::CancelReserve()
{
	while(1)
	{
		InitVector();
		char y='n';
		vector<RoomRecord> vtemp;
		vtemp.clear();
		RoomRecord rtemp;
		rtemp.Name=this->name;
		rtemp.Status="查找预约";
		vector<RoomRecord>::iterator vit=vRoomRec.begin();
		while(1)
		{
			vit=find_if(vit,vRoomRec.end(),isRec(rtemp));
			if(vit !=vRoomRec.end())
			{
				vtemp.push_back(*vit);
				cout<<vtemp.size()<<":";
				printRoomRec(*vit);
				vit++;
			}
			else
			{
				break;
			}
		}
		if(vtemp.size() > 0)
		{
			cout<<"请输入您要取消的哪一行"<<endl;
			int n;
			cin>>n;
			if(n>vtemp.size()|| n<=0)
			{
				cout<<"输入错误~~~"<<endl;
			}
			else
			{
				vector<RoomRecord>::iterator rit_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(vtemp[n-1]));
				cout<<"确定要取消下面信息：y/n"<<endl;
				printRoomRec(*rit_find);
				cin>>y;
				if(y=='y'||y=='Y')
				{
					int index=distance(vRoomRec.begin(),rit_find);
					vRoomRec[index].Status="取消预约";
					ofstream ofs(RECORDFILE,ios::out|ios::trunc);
					for(vector<RoomRecord>::iterator iit=vRoomRec.begin();iit!=vRoomRec.end();iit++)
					{
						ofs<<iit->Date<<"\t"<<iit->Time<<"\t"<<iit->Name<<"\t"<<iit->Num<<"\t"<<iit->Seat<<"\t"<<iit->Status<<endl;
					}
					ofs.close();
					cout<<"取消成功~~~"<<endl;
				}
				else
				{
					cout<<"不取消此次预约"<<endl;
				}
			}
			cout<<"是否继续修改？ y/n"<<endl;
			cin>>y;
			if(y=='y'||y=='Y')
			{

			}
			else
			{
				cout<<"退出修改界面"<<endl;
				system("pause");
				return;
			}
		}
		else
		{
			cout<<"您还没有预约~~~~"<<endl;
			return ;
		}

	}
}
void Student::ModifyInfor(void)
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
			cout<<endl<<"请输入您的学号："<<endl;
			cin>>logid;
			cout<<endl<<"请输入您的姓名："<<endl;
			cin>>logname;
			cout<<endl<<"请输入您的密码："<<endl;
			cin>>logpsw;
			vector<Student>:: iterator it=find_if(vStu.begin(),vStu.end(),isStu(logname,logpsw,logid));
			if(it == vStu.end())
			{
				cout<<"输入信息有误"<<endl;
				cout<<"将重新返回修改页面~"<<endl;
			}
			else
			{
				cout<<"验证成功，请输入修改的密码："<<endl;
				cin>>modpsw;
				it->psw=modpsw;
				ofstream ofs(STUDENTFILE,ios::out|ios::trunc);
				if(!ofs)
				{
					cout<<"打开文件失败"<<endl;
					system("pause");
				}
				for(vector<Student>:: iterator vit=vStu.begin();vit!=vStu.end();vit++)
				{
					ofs<<vit->stuID<<"\t"<<vit->name<<"\t"<<vit->psw<<endl;
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
void Student::ModifyReserve(void)
{
	while(1)
	{
		InitVector();
		char y='n';
		vector<RoomRecord> vtemp;
		vtemp.clear();
		RoomRecord rtemp;
		rtemp.Name=this->name;
		rtemp.Status="查找预约";
		vector<RoomRecord>::iterator vit=vRoomRec.begin();
		while(1)
		{
			vit=find_if(vit,vRoomRec.end(),isRec(rtemp));
			if(vit !=vRoomRec.end())
			{
				vtemp.push_back(*vit);
				cout<<vtemp.size()<<":";
				printRoomRec(*vit);
				vit++;
			}
			else
			{
				break;
			}
		}
		if(vtemp.size() > 0)
		{
			cout<<"请输入您要更改的哪一行"<<endl;
			int n;
			cin>>n;
			if(n>vtemp.size()|| n<=0)
			{
				cout<<"输入错误~~~"<<endl;
			}
			else
			{
				vector<RoomRecord>::iterator rit_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(vtemp[n-1]));
				cout<<"确定要更改下面信息：y/n"<<endl;
				printRoomRec(*rit_find);
				cin>>y;
				if(y=='y'||y=='Y')
				{
					cout<<"机房信息如下："<<endl;
					for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
					cout<<"请自觉查看预约信息来进行预约~~~~"<<endl;
					cout<<"请输入更改后的预约时间：仅周一至周五"<<endl;
					cin>> rtemp.Date;
					cout<<"请输入更改后的预约时间段： 上午/下午"<<endl;
					cin>> rtemp.Time;
					cout<<"请输入更改后的预约机房号码： 1/2/3"<<endl;
					cin>>rtemp.Num;
					cout<<"请输入更改后的预约机房座次："<<endl;
					cin>>rtemp.Seat;
					rtemp.Name=this->name;
					rtemp.Status="预约申请";
					if(vCpuRoom[rtemp.Num].size !=vCpuRoom[rtemp.Num].Status)
					{
						if(vCpuRoom[rtemp.Num].size >= rtemp.Seat)
						{
							vector<RoomRecord>::iterator it_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(rtemp));
							if( it_find == vRoomRec.end())
							{		
								rtemp.Status="预约审核中";
								int index=distance(vRoomRec.begin(),rit_find);
								vRoomRec[index]=rtemp;
								ofstream ofs(RECORDFILE,ios::out|ios::trunc);
								for(vector<RoomRecord>::iterator iit=vRoomRec.begin();iit!=vRoomRec.end();iit++)
								{
									ofs<<iit->Date<<"\t"<<iit->Time<<"\t"<<iit->Name<<"\t"<<iit->Num<<"\t"<<iit->Seat<<"\t"<<iit->Status<<endl;
								}
								ofs.close();
								cout<<"修改成功~~~"<<endl;
							}
							else
							{
								cout<<"该时间段该位置已被预约或正在预约中~~"<<endl;
								cout<<"修改失败~~~~"<<endl;
								cout<<endl;
								cout<<endl;
							}
						}
						else
						{
							cout<<"预约的座次不正确，请查看机房信息"<<endl;
							cout<<"修改失败~~~~"<<endl;
						}
					}
					else
					{
						cout<<"预约的房间已满~~~~~"<<endl;
						cout<<"修改失败~~~~"<<endl;
					}

				}
				else
				{
					cout<<"不修改此次预约"<<endl;
				}
			}
			cout<<"是否继续修改？ y/n"<<endl;
			cin>>y;
			if(y=='y'||y=='Y')
			{

			}
			else
			{
				cout<<"退出修改界面"<<endl;
				system("pause");
				return;
			}
		}
		else
		{
			cout<<"您还没有预约~~~~"<<endl;
			return ;
		}

	}
}
void Student::CheckRoom()
{
	InitVector();
	cout<<"机房信息如下："<<endl;
	for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
}
void Student::CheckReserveSta()
{
	InitVector();
	RoomRecord vtemp;
	vtemp.Name=this->name;
	vtemp.Status="查找预约";
	vector<RoomRecord>::iterator vit=vRoomRec.begin();
	while(1)
	{
		vit=find_if(vit,vRoomRec.end(),isRec(vtemp));
		if(vit !=vRoomRec.end())
		{
			printRoomRec(*vit);
			vit++;
		}
		else
		{
			break;
		}
	}
}
void Student::DealOper()
{
	while(1)
	{
		int select;
		cin>>select;
			/*
			cout<<"----------------------机房预约系统----------------------"<<endl;
			cout<<"             |********学生身份登录******* |         "<<endl;
			cout<<"             |   1:   预约机房位置        |         "<<endl;
			cout<<"             |   2:   查询所有预约        |         "<<endl;
			cout<<"             |   3:   更改自己预约        |         "<<endl;
			cout<<"             |   4:   查询预约状态        |         "<<endl;
			cout<<"             |   5:   查询机房状态        |         "<<endl;
			cout<<"             |   6:   更改身份信息        |         "<<endl;
			cout<<"             |   7:   取消自己预约        |         "<<endl;
			cout<<"             |   8:   ----------        |         "<<endl;	
			cout<<"             |   9:   ----------        |         "<<endl;	
			cout<<"             |   0:   退出学生身份        |         "<<endl;	
			cout<<"             |********学生登录界面********|         "<<endl;
			cout<<"----------------------机房预约系统----------------------"<<endl;
		*/
		switch(select)
		{
			case 1:
				ReserveRoom();
				break;
			case 2:
				CheckReserve();
				system("pause");
				break;
			case 3:
				ModifyReserve();
				break;
			case 4:
				CheckReserveSta();
				system("pause");
				break;
			case 5:
				CheckRoom();
				system("pause");
				break;
			case 6:
				ModifyInfor();
				system("cls");
				break;
			case 7:
				CancelReserve();
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