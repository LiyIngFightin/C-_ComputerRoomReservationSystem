#include<iostream>
#include"Identity.h"
#include<fstream>
#include"Student.h"
#include"Admin.h"
#include"FileName.h"
using namespace std;
void operMenu(Identity *iid)
{
	iid->menuDis();
	Admin *ad=dynamic_cast<Admin *>(iid);
	if(ad != NULL)
	{
		ad->DealOper();
	}
	Student *stu=dynamic_cast<Student *>(iid);
	if(stu != NULL)
	{
		stu->DealOper();
	}
	Teacher *tea=dynamic_cast<Teacher *>(iid);
	if(tea != NULL)
	{
		tea->DealOper();
	}
}
void LogOn(string FILENAME,int Type)
{

	Identity *iid=NULL;
	ifstream ifs;
	ifs.open(FILENAME,ios::in);
	if(! ifs.is_open() )
	{
		cout<<"��ʧ��"<<endl;
		//return;
	}
	string logname;
	string logpsw;
	int logid;
	string fname;
	string fpsw;
	int fid;
	if(Type == 1)
	{
		cout<<endl<<"������ѧ��ѧ�ţ�"<<endl;
		while(!(cin>>logid))
		{
			cin.clear();
			cout<<"������������~~~"<<endl;
			while(cin.get() != '\n'){
				continue;
			}
			cout<<"please input again"<<endl;
			cout<<endl<<"������ѧ��ѧ�ţ�"<<endl;
		}
		cout<<endl<<"������ѧ��������"<<endl;
		while(!(cin>>logname))
		{
			cin.clear();
			cout<<"������������~~~"<<endl;
			while(cin.get() != '\n'){
				continue;
			}
			cout<<"please input again"<<endl;
			cout<<endl<<"������ѧ��������"<<endl;
		}
		cout<<endl<<"������ѧ�����룺"<<endl;
		
		while(!(cin>>logpsw))
		{
			cin.clear();
			cout<<"������������~~~"<<endl;
			while(cin.get() != '\n'){
				continue;
			}
			cout<<"please input again"<<endl;
			cout<<endl<<"������ѧ��������"<<endl;
		}
		while(ifs>>fid && ifs>>fname && ifs>>fpsw)
		{
			if( fid==logid && fname==logname && fpsw==logpsw)
			{
				cout<<"��֤�ɹ�~~~~"<<endl;
				system("cls");
				ifs.close();
				iid = new Student(logname,logpsw,logid);
				operMenu(iid);
				return;
			}
		}
		

	}
	else if(Type == 2)
	{
		cout<<endl<<"��������ʦ���ţ�"<<endl;
		cin>>logid;
		cout<<endl<<"��������ʦ������"<<endl;
		cin>>logname;
		cout<<endl<<"��������ʦ���룺"<<endl;
		cin>>logpsw;
		while(ifs>>fid && ifs>>fname && ifs>>fpsw)
		{
			if( fid==logid && fname==logname && fpsw==logpsw)
			{
				cout<<"��֤�ɹ�~~~~"<<endl;
				ifs.close();
				iid=new Teacher(logname,logpsw,logid);
				system("cls");
				operMenu(iid);
				return;
			}
		}
		
	}
	else if(Type == 3)
	{
		cout<<endl<<"���������Ա������"<<endl;
		cin>>logname;
		cout<<endl<<"���������Ա���룺"<<endl;
		cin>>logpsw;
		while(ifs>>fname && ifs>>fpsw)
		{
			if(fname==logname && fpsw==logpsw)
			{
				cout<<"��֤�ɹ�~~~~"<<endl;
				system("cls");
				ifs.close();
				iid = new Admin(logname,logpsw);
				operMenu(iid);
				return;
			}
		}
	}
	else
	{
		return;
	}
	cout<<"��֤ʧ��~~~"<<endl;


}
void SysDisp()
{
	while(1)
	{
		int n;
		char y;
		cout<<endl;
		cout<<"--------------------����ԤԼϵͳ--------------------"<<endl;
		cout<<"             |********��¼********|                "<<endl;
		cout<<"             |   1:   ѧ��        |                "<<endl;
		cout<<"             |   2:   ��ʦ        |                "<<endl;
		cout<<"             |   3:   ����        |                "<<endl;
		cout<<"             |   0:   �˳�        |                "<<endl;
		cout<<"             |********����********|                "<<endl;
		cout<<"--------------------����ԤԼϵͳ--------------------"<<endl;

		cout<<"���������ѡ�"<<endl;
		cin>>n;
		cout<<endl;
		switch(n)
		{
			case 0:
				cout<<"��л����ʹ�ã���ӭ���´�ʹ��~~~~~"<<endl;
				system("pause");
				return;
			case 1:
				LogOn(STUDENTFILE,n);
				break;
			case 2:
				LogOn(TEACHERFILE,n);
				break;
			case 3:
				LogOn(ADMINFILE,n);
				break;
			default:
				cout<<"��������~~~~"<<endl;
				cout<<"�Ƿ��������룿y/n"<<endl;

				cin>>y;
				if( y=='y' || y== 'Y')
				{
					system("cls");
				}
				else	
				{
					cout<<"��л����ʹ�ã���ӭ���´�ʹ��~~~~~"<<endl;
					system("pause");
					return;
				}

				break;
		}
	}

}
int main()
{
	SysDisp();
	return 0;
}