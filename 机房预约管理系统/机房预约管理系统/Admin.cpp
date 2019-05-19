#include "Admin.h"
#include"Identity.h"
#include<string>
#include"FileName.h"
#include<fstream>
#include<algorithm>
#include<iostream>
using namespace std;


Admin::Admin(void)
{
}
Admin::Admin(const Admin &adm)
{
	name=adm.name;
	psw=adm.psw;
}

Admin::~Admin(void)
{
}

Admin::Admin(string _name,string _psw):Identity(_name,_psw)
{

}

void Admin::menuDis(void)
{
	cout<<"--------管理界面--------"<<endl;
	cout<<"		1：查看预约	      "<<endl;
	cout<<"		2：查看机房		  "<<endl;
	cout<<"		3：查看人员	      "<<endl;
	cout<<"		4：添加人员		  "<<endl;
	cout<<"		5：删除人员		  "<<endl;
	cout<<"		0：退出界面		  "<<endl;
	cout<<"-----------------------"<<endl;
	cout<<"输入操作选项"<<endl;
}
static void printCRoom(ComputerRoom &v)
{
	cout<<"机房号码："<<v.Num<<"	已使用座位："<<v.Status<<"	机房总座位："<<v.size<<endl;;
}
static void printRoomRec(RoomRecord &v)
{
	cout<<"预约时间："<<v.Date<<v.Time<<"		姓名："<<v.Name<<"	预约"<<v.Num<<"号机房"<<v.Seat<<"座次"<<"	预约状态："<<v.Status<<endl;;
}
static void printStu(Student &v)
{
	cout<<"学号："<<v.stuID<<"	姓名："<<v.name<<"	密码："<<v.psw<<endl;;
}
static void printTea(Teacher &v)
{
	cout<<"工号："<<v.teaID<<"	姓名："<<v.name<<"	密码："<<v.psw<<endl;;
}
static void printAdm(Admin &v)
{
	cout<<"姓名："<<v.name<<"	密码："<<v.psw<<endl;;
}
void Admin::InitVector()
{
	ifstream ifs;
	string fname;
	string fpsw;
	int fid;
	vStu.clear();
	vTea.clear();
	vAdm.clear();
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
	ifs.open(ADMINFILE,ios::in);
	if(! ifs.is_open() )
	{
		cout<<"初始化管理员容器失败"<<endl;
		system("pause");
	}
	while(ifs>>fname && ifs>>fpsw)
	{
		vAdm.push_back(Admin(fname,fpsw));
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
void Admin::AddOperator(void)
{
	while(1)
	{
		int n;
		int count=0;
		char y;
		string addname;
		string addpsw;
		int addid;
		string filename;
		InitVector();
		cout<<"请选择添加人员类别："<<endl;
		cout<<"		0:学生	1:老师	2:管理"<<endl;
		cin>>n;
		if(n==0)
		{
			cout<<"请输入添加学生学号："<<endl;
			cin>>addid;
			cout<<"请输入添加学生姓名："<<endl;
			cin>>addname;
			cout<<"请输入添加学生密码："<<endl;
			cin>>addpsw;
			filename=STUDENTFILE;
			for(vector<Student>::iterator it=vStu.begin();it!=vStu.end();it++)
			{
				if(it->stuID == addid)
				{
					cout<<"该学生已存在~~~"<<endl;
					count=2;
					break;
				}
			}
		}
		else if(n==1)
		{
			cout<<"请输入添加老师工号："<<endl;
			cin>>addid;
			cout<<"请输入添加老师姓名："<<endl;
			cin>>addname;
			cout<<"请输入添加老师密码："<<endl;
			cin>>addpsw;
			filename=TEACHERFILE;
			for(vector<Teacher>::iterator it=vTea.begin();it!=vTea.end();it++)
			{
				if(it->teaID == addid)
				{
					cout<<"该老师已存在~~~"<<endl;
					count=2;
					break;
				}
			}
		}
		else if(n==2)
		{
			cout<<"请输入添加管理姓名："<<endl;
			cin>>addname;
			cout<<"请输入添加管理密码："<<endl;
			cin>>addpsw;
			filename=ADMINFILE;
			for(vector<Admin>::iterator it=vAdm.begin();it!=vAdm.end();it++)
			{
				if(it->name == addname)
				{
					cout<<"该管理已存在~~~"<<endl;
					count=2;
					break;
				}
			}
		}
		else
		{
			cout<<"输入有误~请重新输入"<<endl;
			count=1;
		}
		if(count==0)
		{
			ofstream ofs(filename,ios::out|ios::app);
			if(!ofs)
			{
				cout<<"打开文件失败~~~"<<endl;
				system("pause");
			}
			if(n==2)
			{
				ofs<<addname<<"\t"<<addpsw<<endl;
			}
			else
			{
				ofs<<addid<<"\t"<<addname<<"\t"<<addpsw<<endl;
			}
			ofs.close();
			cout<<"添加人员成功~~"<<endl;
		}	
		cout<<"是否继续添加？y/n"<<endl;

		cin>>y;
		if( y=='y' || y== 'Y')
		{

		}
		else
			return;

	}

}
void Admin::DeleteOperator(void)
{
	while(1)
	{
		InitVector();
		cout<<"请输入删除成员的类别："<<endl;
		cout<<"	0:学生	1:老师	2:管理"<<endl;
		int n;
		char y;
		int count=0;
		string delname;
		cin>>n;
		if(n==2)
		{
			cout<<"请输入删除管理的姓名："<<endl;
			cin>>delname;
			for(vector<Admin>::iterator it=vAdm.begin();it!=vAdm.end();it++)
			{
				if(it->name == delname)
				{
					cout<<"该成员存在，确定删除？y/n"<<endl;
					cin>>y;
					if(y== 'y'||y=='Y')
					{
						vAdm.erase(it);
						cout<<"删除成功~~"<<endl;
						count=1;

					}
					else
					{
						cout<<"不会删除该成员~~"<<endl;
					}
					break;
				}
			}
			if(count!=0)
			{
				ofstream ofs(ADMINFILE,ios::out|ios::trunc);
				for(vector<Admin>::iterator it=vAdm.begin();it!=vAdm.end();it++)
				{
					ofs<<it->name<<"\t"<<it->psw<<endl;
				}
			}
			else
			{
				cout<<"该成员不存在~~~"<<endl;
			}
		}
		else if(n==0)
		{
			cout<<"请输入删除学生的姓名："<<endl;
			cin>>delname;
			for(vector<Student>::iterator it=vStu.begin();it!=vStu.end();it++)
			{
				if(it->name == delname)
				{
					cout<<"该成员存在，确定删除？y/n"<<endl;
					cin>>y;
					if(y== 'y'||y=='Y')
					{
						vStu.erase(it);
						count=1;

					}
					else
					{
						cout<<"不会删除该成员~~"<<endl;
					}
					break;
				}
			}
			if(count!=0)
			{
				ofstream ofs(STUDENTFILE,ios::out|ios::trunc);
				for(vector<Student>::iterator it=vStu.begin();it!=vStu.end();it++)
				{
					ofs<<it->stuID<<"\t"<<it->name<<"\t"<<it->psw<<endl;
				}
			}
			else
			{
				cout<<"该成员不存在~~~"<<endl;
			}
		}
		else if(n==1)
		{
			cout<<"请输入删除老师的姓名："<<endl;
			cin>>delname;
			for(vector<Teacher>::iterator it=vTea.begin();it!=vTea.end();it++)
			{
				if(it->name == delname)
				{
					cout<<"该成员存在，确定删除？y/n"<<endl;
					cin>>y;
					if(y== 'y'||y=='Y')
					{
						vTea.erase(it);
						count=1;

					}
					else
					{
						cout<<"不会删除该成员~~"<<endl;
					}
					break;
				}
			}
			if(count!=0)
			{
				ofstream ofs(TEACHERFILE,ios::out|ios::trunc);
				for(vector<Teacher>::iterator it=vTea.begin();it!=vTea.end();it++)
				{
					ofs<<it->teaID<<"\t"<<it->name<<"\t"<<it->psw<<endl;
				}
			}
			else
			{
				cout<<"该成员不存在~~~"<<endl;
			}
		}
		cout<<"是否继续删除~~~y/n"<<endl;
		cin>>y;
		if(y=='y'||y=='Y')
		{

		}
		else
		{
			system("cls");
			return;
		}
	}

}
void Admin::CheckOperator()
{
	InitVector();
	cout<<endl;
	cout<<"已经登记的学生："<<endl;
	for_each(vStu.begin(),vStu.end(),printStu);
	cout<<endl;
	cout<<"已经登记的老师："<<endl;
	for_each(vTea.begin(),vTea.end(),printTea);
	cout<<endl;
	cout<<"已经登记的管理员："<<endl;
	for_each(vAdm.begin(),vAdm.end(),printAdm);
}
void Admin::CheckRoom()
{
	InitVector();
	cout<<"机房信息如下："<<endl;
	for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
}
void Admin::CheckReserve()
{
	InitVector();
	cout<<"预约信息如下："<<endl;
	for_each(vRoomRec.begin(),vRoomRec.end(),printRoomRec);
}

void Admin::DealOper()
{
	while(1)
	{
		int select;
		cin>>select;
			/*
		cout<<"--------管理界面--------"<<endl;
		cout<<"		1：查看预约	      "<<endl;
		cout<<"		2：查看机房		  "<<endl;
		cout<<"		3：查看人员	      "<<endl;
		cout<<"		4：添加人员		  "<<endl;
		cout<<"-----------------------"<<endl;
		*/
		switch(select)
		{
			case 1:
				CheckReserve();
				system("pause");
				break;
			case 2:
				CheckRoom();
				system("pause");
				break;
			case 3:
				CheckOperator();
				system("pause");
				break;
			case 4:
				AddOperator();
				break;
			case 5:
				DeleteOperator();
				break;
			case 0:
				system("cls");
				return;

		}
		system("cls");
		menuDis();
	}


}