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
		cout<<"打开失败"<<endl;
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
		cout<<endl<<"请输入学生学号："<<endl;
		while(!(cin>>logid))
		{
			cin.clear();
			cout<<"输入类型有误~~~"<<endl;
			while(cin.get() != '\n'){
				continue;
			}
			cout<<"please input again"<<endl;
			cout<<endl<<"请输入学生学号："<<endl;
		}
		cout<<endl<<"请输入学生姓名："<<endl;
		while(!(cin>>logname))
		{
			cin.clear();
			cout<<"输入类型有误~~~"<<endl;
			while(cin.get() != '\n'){
				continue;
			}
			cout<<"please input again"<<endl;
			cout<<endl<<"请输入学生姓名："<<endl;
		}
		cout<<endl<<"请输入学生密码："<<endl;
		
		while(!(cin>>logpsw))
		{
			cin.clear();
			cout<<"输入类型有误~~~"<<endl;
			while(cin.get() != '\n'){
				continue;
			}
			cout<<"please input again"<<endl;
			cout<<endl<<"请输入学生姓名："<<endl;
		}
		while(ifs>>fid && ifs>>fname && ifs>>fpsw)
		{
			if( fid==logid && fname==logname && fpsw==logpsw)
			{
				cout<<"验证成功~~~~"<<endl;
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
		cout<<endl<<"请输入老师工号："<<endl;
		cin>>logid;
		cout<<endl<<"请输入老师姓名："<<endl;
		cin>>logname;
		cout<<endl<<"请输入老师密码："<<endl;
		cin>>logpsw;
		while(ifs>>fid && ifs>>fname && ifs>>fpsw)
		{
			if( fid==logid && fname==logname && fpsw==logpsw)
			{
				cout<<"验证成功~~~~"<<endl;
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
		cout<<endl<<"请输入管理员姓名："<<endl;
		cin>>logname;
		cout<<endl<<"请输入管理员密码："<<endl;
		cin>>logpsw;
		while(ifs>>fname && ifs>>fpsw)
		{
			if(fname==logname && fpsw==logpsw)
			{
				cout<<"验证成功~~~~"<<endl;
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
	cout<<"验证失败~~~"<<endl;


}
void SysDisp()
{
	while(1)
	{
		int n;
		char y;
		cout<<endl;
		cout<<"--------------------机房预约系统--------------------"<<endl;
		cout<<"             |********登录********|                "<<endl;
		cout<<"             |   1:   学生        |                "<<endl;
		cout<<"             |   2:   老师        |                "<<endl;
		cout<<"             |   3:   管理        |                "<<endl;
		cout<<"             |   0:   退出        |                "<<endl;
		cout<<"             |********界面********|                "<<endl;
		cout<<"--------------------机房预约系统--------------------"<<endl;

		cout<<"请输入身份选项："<<endl;
		cin>>n;
		cout<<endl;
		switch(n)
		{
			case 0:
				cout<<"感谢您的使用，欢迎您下次使用~~~~~"<<endl;
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
				cout<<"输入有误~~~~"<<endl;
				cout<<"是否重新输入？y/n"<<endl;

				cin>>y;
				if( y=='y' || y== 'Y')
				{
					system("cls");
				}
				else	
				{
					cout<<"感谢您的使用，欢迎您下次使用~~~~~"<<endl;
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