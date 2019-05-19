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
		if(rr.Date==t.Date && rr.Time==t.Time && rr.Num==t.Num && rr.Seat==t.Seat && rr.Status=="ԤԼ����")
		{
			return true;
		}
		else if(rr.Status == "����ԤԼ" && rr.Name == t.Name)
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
	cout<<"ԤԼʱ�䣺"<<v.Date<<v.Time<<"		������"<<v.Name<<"	ԤԼ"<<v.Num<<"�Ż���"<<v.Seat<<"����	"<<"ԤԼ״̬��	"<<v.Status<<endl;;
}

static void printCRoom(ComputerRoom &v)
{
	cout<<"�������룺"<<v.Num<<"	��ʹ����λ��"<<v.Status<<"	��������λ��"<<v.size<<endl;;
}
void Student::menuDis(void)
{
	cout<<endl;
	cout<<"----------------------����ԤԼϵͳ----------------------"<<endl;
	cout<<"             |********ѧ����ݵ�¼******* |         "<<endl;
	cout<<"             |   1:   ԤԼ����λ��        |         "<<endl;
	cout<<"             |   2:   ��ѯ����ԤԼ        |         "<<endl;
	cout<<"             |   3:   �����Լ�ԤԼ        |         "<<endl;
	cout<<"             |   4:   ��ѯԤԼ״̬        |         "<<endl;
	cout<<"             |   5:   ��ѯ����״̬        |         "<<endl;
	cout<<"             |   6:   ���������Ϣ        |         "<<endl;
	cout<<"             |   7:   ȡ���Լ�ԤԼ        |         "<<endl;
	cout<<"             |   8:   ----------        |         "<<endl;	
	cout<<"             |   9:   ----------        |         "<<endl;	
	cout<<"             |   0:   �˳�ѧ�����        |         "<<endl;	
	cout<<"             |********ѧ����¼����********|         "<<endl;
	cout<<"----------------------����ԤԼϵͳ----------------------"<<endl;
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
		cout<<"��ʼ��ѧ������ʧ��"<<endl;
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
void Student::ReserveRoom(void)
{
	while(1)
	{
		InitVector();
		RoomRecord vtemp;
		char y;
		cout<<"������Ϣ���£�"<<endl;
		for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
		cout<<"���Ծ��鿴ԤԼ��Ϣ������ԤԼ~~~~"<<endl;
		cout<<"������ԤԼʱ�䣺����һ������"<<endl;
		cin>> vtemp.Date;
		cout<<"������ԤԼʱ��Σ� ����/����"<<endl;
		cin>> vtemp.Time;
		cout<<"������ԤԼ�������룺 1/2/3"<<endl;
		cin>>vtemp.Num;
		cout<<"������ԤԼ�������Σ�"<<endl;
		cin>>vtemp.Seat;
		vtemp.Name=this->name;
		vtemp.Status="ԤԼ����";
		if(vCpuRoom[vtemp.Num].size !=vCpuRoom[vtemp.Num].Status)
		{
			if(vCpuRoom[vtemp.Num].size >= vtemp.Seat)
			{
				vector<RoomRecord>::iterator it_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(vtemp));
				if( it_find == vRoomRec.end())
				{		
					vtemp.Status="ԤԼ�����";
					ofstream ofs(RECORDFILE,ios::out|ios::app);
					if(!ofs)
					{
						cout<<"�ļ���ʧ��"<<endl;
						system("pause");
						return ;
					}
					ofs<<vtemp.Date<<"\t"<<vtemp.Time<<"\t"<<vtemp.Name<<"\t"<<vtemp.Num<<"\t"<<vtemp.Seat<<"\t"<<vtemp.Status<<endl;
					ofs.close();
					cout<<"����ԤԼ�У��ȴ���ʦ���~~~"<<endl;
					cout<<endl;
					cout<<endl;
				}
				else
				{
					cout<<"��ʱ��θ�λ���ѱ�ԤԼ������ԤԼ��~~"<<endl;
					cout<<endl;
					cout<<endl;
				}
			}
			else
			{
				cout<<"ԤԼ�����β���ȷ����鿴������Ϣ"<<endl;
			}
		}
		else
		{
			cout<<"ԤԼ�ķ�������~~~~~"<<endl;
		}
		cout<<"�Ƿ����ԤԼ���� y/n"<<endl;
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
	cout<<"ԤԼ��Ϣ���£�"<<endl;
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
		rtemp.Status="����ԤԼ";
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
			cout<<"��������Ҫȡ������һ��"<<endl;
			int n;
			cin>>n;
			if(n>vtemp.size()|| n<=0)
			{
				cout<<"�������~~~"<<endl;
			}
			else
			{
				vector<RoomRecord>::iterator rit_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(vtemp[n-1]));
				cout<<"ȷ��Ҫȡ��������Ϣ��y/n"<<endl;
				printRoomRec(*rit_find);
				cin>>y;
				if(y=='y'||y=='Y')
				{
					int index=distance(vRoomRec.begin(),rit_find);
					vRoomRec[index].Status="ȡ��ԤԼ";
					ofstream ofs(RECORDFILE,ios::out|ios::trunc);
					for(vector<RoomRecord>::iterator iit=vRoomRec.begin();iit!=vRoomRec.end();iit++)
					{
						ofs<<iit->Date<<"\t"<<iit->Time<<"\t"<<iit->Name<<"\t"<<iit->Num<<"\t"<<iit->Seat<<"\t"<<iit->Status<<endl;
					}
					ofs.close();
					cout<<"ȡ���ɹ�~~~"<<endl;
				}
				else
				{
					cout<<"��ȡ���˴�ԤԼ"<<endl;
				}
			}
			cout<<"�Ƿ�����޸ģ� y/n"<<endl;
			cin>>y;
			if(y=='y'||y=='Y')
			{

			}
			else
			{
				cout<<"�˳��޸Ľ���"<<endl;
				system("pause");
				return;
			}
		}
		else
		{
			cout<<"����û��ԤԼ~~~~"<<endl;
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
		cout<<"ȷ���޸ĸ�����Ϣ���룿 y/n"<<endl;
		cin>>y;
		if(y=='y'||y=='Y')
		{
			cout<<endl<<"����������ѧ�ţ�"<<endl;
			cin>>logid;
			cout<<endl<<"����������������"<<endl;
			cin>>logname;
			cout<<endl<<"�������������룺"<<endl;
			cin>>logpsw;
			vector<Student>:: iterator it=find_if(vStu.begin(),vStu.end(),isStu(logname,logpsw,logid));
			if(it == vStu.end())
			{
				cout<<"������Ϣ����"<<endl;
				cout<<"�����·����޸�ҳ��~"<<endl;
			}
			else
			{
				cout<<"��֤�ɹ����������޸ĵ����룺"<<endl;
				cin>>modpsw;
				it->psw=modpsw;
				ofstream ofs(STUDENTFILE,ios::out|ios::trunc);
				if(!ofs)
				{
					cout<<"���ļ�ʧ��"<<endl;
					system("pause");
				}
				for(vector<Student>:: iterator vit=vStu.begin();vit!=vStu.end();vit++)
				{
					ofs<<vit->stuID<<"\t"<<vit->name<<"\t"<<vit->psw<<endl;
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
		rtemp.Status="����ԤԼ";
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
			cout<<"��������Ҫ���ĵ���һ��"<<endl;
			int n;
			cin>>n;
			if(n>vtemp.size()|| n<=0)
			{
				cout<<"�������~~~"<<endl;
			}
			else
			{
				vector<RoomRecord>::iterator rit_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(vtemp[n-1]));
				cout<<"ȷ��Ҫ����������Ϣ��y/n"<<endl;
				printRoomRec(*rit_find);
				cin>>y;
				if(y=='y'||y=='Y')
				{
					cout<<"������Ϣ���£�"<<endl;
					for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
					cout<<"���Ծ��鿴ԤԼ��Ϣ������ԤԼ~~~~"<<endl;
					cout<<"��������ĺ��ԤԼʱ�䣺����һ������"<<endl;
					cin>> rtemp.Date;
					cout<<"��������ĺ��ԤԼʱ��Σ� ����/����"<<endl;
					cin>> rtemp.Time;
					cout<<"��������ĺ��ԤԼ�������룺 1/2/3"<<endl;
					cin>>rtemp.Num;
					cout<<"��������ĺ��ԤԼ�������Σ�"<<endl;
					cin>>rtemp.Seat;
					rtemp.Name=this->name;
					rtemp.Status="ԤԼ����";
					if(vCpuRoom[rtemp.Num].size !=vCpuRoom[rtemp.Num].Status)
					{
						if(vCpuRoom[rtemp.Num].size >= rtemp.Seat)
						{
							vector<RoomRecord>::iterator it_find=find_if(vRoomRec.begin(),vRoomRec.end(),isRec(rtemp));
							if( it_find == vRoomRec.end())
							{		
								rtemp.Status="ԤԼ�����";
								int index=distance(vRoomRec.begin(),rit_find);
								vRoomRec[index]=rtemp;
								ofstream ofs(RECORDFILE,ios::out|ios::trunc);
								for(vector<RoomRecord>::iterator iit=vRoomRec.begin();iit!=vRoomRec.end();iit++)
								{
									ofs<<iit->Date<<"\t"<<iit->Time<<"\t"<<iit->Name<<"\t"<<iit->Num<<"\t"<<iit->Seat<<"\t"<<iit->Status<<endl;
								}
								ofs.close();
								cout<<"�޸ĳɹ�~~~"<<endl;
							}
							else
							{
								cout<<"��ʱ��θ�λ���ѱ�ԤԼ������ԤԼ��~~"<<endl;
								cout<<"�޸�ʧ��~~~~"<<endl;
								cout<<endl;
								cout<<endl;
							}
						}
						else
						{
							cout<<"ԤԼ�����β���ȷ����鿴������Ϣ"<<endl;
							cout<<"�޸�ʧ��~~~~"<<endl;
						}
					}
					else
					{
						cout<<"ԤԼ�ķ�������~~~~~"<<endl;
						cout<<"�޸�ʧ��~~~~"<<endl;
					}

				}
				else
				{
					cout<<"���޸Ĵ˴�ԤԼ"<<endl;
				}
			}
			cout<<"�Ƿ�����޸ģ� y/n"<<endl;
			cin>>y;
			if(y=='y'||y=='Y')
			{

			}
			else
			{
				cout<<"�˳��޸Ľ���"<<endl;
				system("pause");
				return;
			}
		}
		else
		{
			cout<<"����û��ԤԼ~~~~"<<endl;
			return ;
		}

	}
}
void Student::CheckRoom()
{
	InitVector();
	cout<<"������Ϣ���£�"<<endl;
	for_each(vCpuRoom.begin(),vCpuRoom.end(),printCRoom);
}
void Student::CheckReserveSta()
{
	InitVector();
	RoomRecord vtemp;
	vtemp.Name=this->name;
	vtemp.Status="����ԤԼ";
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
			cout<<"----------------------����ԤԼϵͳ----------------------"<<endl;
			cout<<"             |********ѧ����ݵ�¼******* |         "<<endl;
			cout<<"             |   1:   ԤԼ����λ��        |         "<<endl;
			cout<<"             |   2:   ��ѯ����ԤԼ        |         "<<endl;
			cout<<"             |   3:   �����Լ�ԤԼ        |         "<<endl;
			cout<<"             |   4:   ��ѯԤԼ״̬        |         "<<endl;
			cout<<"             |   5:   ��ѯ����״̬        |         "<<endl;
			cout<<"             |   6:   ���������Ϣ        |         "<<endl;
			cout<<"             |   7:   ȡ���Լ�ԤԼ        |         "<<endl;
			cout<<"             |   8:   ----------        |         "<<endl;	
			cout<<"             |   9:   ----------        |         "<<endl;	
			cout<<"             |   0:   �˳�ѧ�����        |         "<<endl;	
			cout<<"             |********ѧ����¼����********|         "<<endl;
			cout<<"----------------------����ԤԼϵͳ----------------------"<<endl;
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
		cout<<"������Ҫ���еĲ�����ţ�"<<endl;
	}
}