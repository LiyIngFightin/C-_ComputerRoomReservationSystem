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
	cout<<"----------------------����ԤԼϵͳ----------------------"<<endl;
	cout<<"             |********��ʦ��ݵ�¼******* |         "<<endl;
	cout<<"             |   1:   ����ѧ��ԤԼ        |         "<<endl;
	cout<<"             |   2:   ��ѯ����ԤԼ        |         "<<endl;
	cout<<"             |   3:   ��ѯ����״̬        |         "<<endl;
	cout<<"             |   4:   ���������Ϣ        |         "<<endl;
	cout<<"             |   5:   ----------        |         "<<endl;
	cout<<"             |   6:   ----------        |         "<<endl;
	cout<<"             |   7:   ----------        |         "<<endl;
	cout<<"             |   8:   ----------        |         "<<endl;	
	cout<<"             |   9:   ----------        |         "<<endl;	
	cout<<"             |   0:   �˳���ʦ���        |         "<<endl;	
	cout<<"             |********��ʦ��¼����********|         "<<endl;
	cout<<"----------------------����ԤԼϵͳ----------------------"<<endl;
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
		if(rr.Status=="ȡ��"&& t.Status=="ȡ��ԤԼ")
		{
			return true;
		}
		else if(rr.Status=="���"&& t.Status=="ԤԼ�����")
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
	cout<<"ԤԼʱ�䣺"<<v.Date<<v.Time<<"		������"<<v.Name<<"	ԤԼ"<<v.Num<<"�Ż���"<<v.Seat<<"����	"<<"ԤԼ״̬��	"<<v.Status<<endl;;
}

static void printCRoom(ComputerRoom &v)
{
	cout<<"�������룺"<<v.Num<<"	��ʹ����λ��"<<v.Status<<"	��������λ��"<<v.size<<endl;;
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
		cout<<"ȷ���޸ĸ�����Ϣ���룿 y/n"<<endl;
		cin>>y;
		if(y=='y'||y=='Y')
		{
			cout<<endl<<"���������Ĺ��ţ�"<<endl;
			cin>>logid;
			cout<<endl<<"����������������"<<endl;
			cin>>logname;
			cout<<endl<<"�������������룺"<<endl;
			cin>>logpsw;
			vector<Teacher>:: iterator it=find_if(vTea.begin(),vTea.end(),isTea(logname,logpsw,logid));
			if(it == vTea.end())
			{
				cout<<"������Ϣ����"<<endl;
				cout<<"�����·����޸�ҳ��~"<<endl;
			}
			else
			{
				cout<<"��֤�ɹ����������޸ĵ����룺"<<endl;
				cin>>modpsw;
				it->psw=modpsw;
				ofstream ofs(TEACHERFILE,ios::out|ios::trunc);
				if(!ofs)
				{
					cout<<"���ļ�ʧ��"<<endl;
					system("pause");
				}
				for(vector<Teacher>:: iterator vit=vTea.begin();vit!=vTea.end();vit++)
				{
					ofs<<vit->teaID<<"\t"<<vit->name<<"\t"<<vit->psw<<endl;
				}
				ofs.close();
				cout<<"�޸ĳɹ�~~~"<<endl;
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
	cout<<"ԤԼ��Ϣ���£�"<<endl;
	for_each(vRoomRec.begin(),vRoomRec.end(),printRoomRec);
}
void Teacher::CheckRoom()
{
	InitVector();
	cout<<"������Ϣ���£�"<<endl;
	for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
}
void Teacher::VerifyReserve()
{
	while(1)
	{
		int select=0;
		InitVector();
		cout<<"���ԤԼ��ʼ~~~"<<endl;
		cout<<endl;
		CheckReserve();
		cout<<endl;
		RoomRecord rtemp;
		vector<RoomRecord> vtemp;
		vtemp.clear();
		char y;
		cout<<"���ԤԼ��"<<endl;
		cout<<"	1:����ȡ��ԤԼ	2���������ԤԼ	"<<endl;
		cin>>select;
		if(select == 1)
		{
			cout<<endl;
			rtemp.Status="ȡ��";
			cout<<"ѧ������ȡ��ԤԼ���£�"<<endl;
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
				cout<<"û��ȡ��ԤԼ��ѧ��~~~"<<endl;
				
			}
			else
			{
				for_each(vtemp.begin(),vtemp.end(),printRoomRec);
				cout<<endl;
				cout<<"�Ƿ�ȫ��ɾ���� y/n"<<endl;
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
						cout<<"���ļ�ʧ��"<<endl;
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
			cout<<"----------------------����ԤԼϵͳ----------------------"<<endl;
			cout<<"             |********��ʦ��ݵ�¼******* |         "<<endl;
			cout<<"             |   1:   ����ѧ��ԤԼ        |         "<<endl;
			cout<<"             |   2:   ��ѯ����ԤԼ        |         "<<endl;
			cout<<"             |   3:   ��ѯ����״̬        |         "<<endl;
			cout<<"             |   4:   ���������Ϣ        |         "<<endl;
			cout<<"             |   5:   ----------        |         "<<endl;
			cout<<"             |   6:   ----------        |         "<<endl;
			cout<<"             |   7:   ----------        |         "<<endl;
			cout<<"             |   8:   ----------        |         "<<endl;	
			cout<<"             |   9:   ----------        |         "<<endl;	
			cout<<"             |   0:   �˳���ʦ���        |         "<<endl;	
			cout<<"             |********��ʦ��¼����********|         "<<endl;
			cout<<"----------------------����ԤԼϵͳ----------------------"<<endl;
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
		cout<<"������Ҫ���еĲ�����ţ�"<<endl;
	}
}
