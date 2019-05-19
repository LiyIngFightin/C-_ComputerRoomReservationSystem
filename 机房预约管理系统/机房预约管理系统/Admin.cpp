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
	cout<<"--------�������--------"<<endl;
	cout<<"		1���鿴ԤԼ	      "<<endl;
	cout<<"		2���鿴����		  "<<endl;
	cout<<"		3���鿴��Ա	      "<<endl;
	cout<<"		4�������Ա		  "<<endl;
	cout<<"		5��ɾ����Ա		  "<<endl;
	cout<<"		0���˳�����		  "<<endl;
	cout<<"-----------------------"<<endl;
	cout<<"�������ѡ��"<<endl;
}
static void printCRoom(ComputerRoom &v)
{
	cout<<"�������룺"<<v.Num<<"	��ʹ����λ��"<<v.Status<<"	��������λ��"<<v.size<<endl;;
}
static void printRoomRec(RoomRecord &v)
{
	cout<<"ԤԼʱ�䣺"<<v.Date<<v.Time<<"		������"<<v.Name<<"	ԤԼ"<<v.Num<<"�Ż���"<<v.Seat<<"����"<<"	ԤԼ״̬��"<<v.Status<<endl;;
}
static void printStu(Student &v)
{
	cout<<"ѧ�ţ�"<<v.stuID<<"	������"<<v.name<<"	���룺"<<v.psw<<endl;;
}
static void printTea(Teacher &v)
{
	cout<<"���ţ�"<<v.teaID<<"	������"<<v.name<<"	���룺"<<v.psw<<endl;;
}
static void printAdm(Admin &v)
{
	cout<<"������"<<v.name<<"	���룺"<<v.psw<<endl;;
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
		cout<<"��ʼ��ѧ������ʧ��"<<endl;
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
		cout<<"��ʼ����ʦ����ʧ��"<<endl;
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
		cout<<"��ʼ������Ա����ʧ��"<<endl;
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
		cout<<"��ʼ����������ʧ��"<<endl;
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
		cout<<"��ʼ����¼����ʧ��"<<endl;
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
		cout<<"��ѡ�������Ա���"<<endl;
		cout<<"		0:ѧ��	1:��ʦ	2:����"<<endl;
		cin>>n;
		if(n==0)
		{
			cout<<"���������ѧ��ѧ�ţ�"<<endl;
			cin>>addid;
			cout<<"���������ѧ��������"<<endl;
			cin>>addname;
			cout<<"���������ѧ�����룺"<<endl;
			cin>>addpsw;
			filename=STUDENTFILE;
			for(vector<Student>::iterator it=vStu.begin();it!=vStu.end();it++)
			{
				if(it->stuID == addid)
				{
					cout<<"��ѧ���Ѵ���~~~"<<endl;
					count=2;
					break;
				}
			}
		}
		else if(n==1)
		{
			cout<<"�����������ʦ���ţ�"<<endl;
			cin>>addid;
			cout<<"�����������ʦ������"<<endl;
			cin>>addname;
			cout<<"�����������ʦ���룺"<<endl;
			cin>>addpsw;
			filename=TEACHERFILE;
			for(vector<Teacher>::iterator it=vTea.begin();it!=vTea.end();it++)
			{
				if(it->teaID == addid)
				{
					cout<<"����ʦ�Ѵ���~~~"<<endl;
					count=2;
					break;
				}
			}
		}
		else if(n==2)
		{
			cout<<"��������ӹ���������"<<endl;
			cin>>addname;
			cout<<"��������ӹ������룺"<<endl;
			cin>>addpsw;
			filename=ADMINFILE;
			for(vector<Admin>::iterator it=vAdm.begin();it!=vAdm.end();it++)
			{
				if(it->name == addname)
				{
					cout<<"�ù����Ѵ���~~~"<<endl;
					count=2;
					break;
				}
			}
		}
		else
		{
			cout<<"��������~����������"<<endl;
			count=1;
		}
		if(count==0)
		{
			ofstream ofs(filename,ios::out|ios::app);
			if(!ofs)
			{
				cout<<"���ļ�ʧ��~~~"<<endl;
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
			cout<<"�����Ա�ɹ�~~"<<endl;
		}	
		cout<<"�Ƿ������ӣ�y/n"<<endl;

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
		cout<<"������ɾ����Ա�����"<<endl;
		cout<<"	0:ѧ��	1:��ʦ	2:����"<<endl;
		int n;
		char y;
		int count=0;
		string delname;
		cin>>n;
		if(n==2)
		{
			cout<<"������ɾ�������������"<<endl;
			cin>>delname;
			for(vector<Admin>::iterator it=vAdm.begin();it!=vAdm.end();it++)
			{
				if(it->name == delname)
				{
					cout<<"�ó�Ա���ڣ�ȷ��ɾ����y/n"<<endl;
					cin>>y;
					if(y== 'y'||y=='Y')
					{
						vAdm.erase(it);
						cout<<"ɾ���ɹ�~~"<<endl;
						count=1;

					}
					else
					{
						cout<<"����ɾ���ó�Ա~~"<<endl;
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
				cout<<"�ó�Ա������~~~"<<endl;
			}
		}
		else if(n==0)
		{
			cout<<"������ɾ��ѧ����������"<<endl;
			cin>>delname;
			for(vector<Student>::iterator it=vStu.begin();it!=vStu.end();it++)
			{
				if(it->name == delname)
				{
					cout<<"�ó�Ա���ڣ�ȷ��ɾ����y/n"<<endl;
					cin>>y;
					if(y== 'y'||y=='Y')
					{
						vStu.erase(it);
						count=1;

					}
					else
					{
						cout<<"����ɾ���ó�Ա~~"<<endl;
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
				cout<<"�ó�Ա������~~~"<<endl;
			}
		}
		else if(n==1)
		{
			cout<<"������ɾ����ʦ��������"<<endl;
			cin>>delname;
			for(vector<Teacher>::iterator it=vTea.begin();it!=vTea.end();it++)
			{
				if(it->name == delname)
				{
					cout<<"�ó�Ա���ڣ�ȷ��ɾ����y/n"<<endl;
					cin>>y;
					if(y== 'y'||y=='Y')
					{
						vTea.erase(it);
						count=1;

					}
					else
					{
						cout<<"����ɾ���ó�Ա~~"<<endl;
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
				cout<<"�ó�Ա������~~~"<<endl;
			}
		}
		cout<<"�Ƿ����ɾ��~~~y/n"<<endl;
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
	cout<<"�Ѿ��Ǽǵ�ѧ����"<<endl;
	for_each(vStu.begin(),vStu.end(),printStu);
	cout<<endl;
	cout<<"�Ѿ��Ǽǵ���ʦ��"<<endl;
	for_each(vTea.begin(),vTea.end(),printTea);
	cout<<endl;
	cout<<"�Ѿ��ǼǵĹ���Ա��"<<endl;
	for_each(vAdm.begin(),vAdm.end(),printAdm);
}
void Admin::CheckRoom()
{
	InitVector();
	cout<<"������Ϣ���£�"<<endl;
	for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
}
void Admin::CheckReserve()
{
	InitVector();
	cout<<"ԤԼ��Ϣ���£�"<<endl;
	for_each(vRoomRec.begin(),vRoomRec.end(),printRoomRec);
}

void Admin::DealOper()
{
	while(1)
	{
		int select;
		cin>>select;
			/*
		cout<<"--------�������--------"<<endl;
		cout<<"		1���鿴ԤԼ	      "<<endl;
		cout<<"		2���鿴����		  "<<endl;
		cout<<"		3���鿴��Ա	      "<<endl;
		cout<<"		4�������Ա		  "<<endl;
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