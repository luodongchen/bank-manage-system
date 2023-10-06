#if 1
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <list>
#include <stdio.h>

using namespace std;

//定义一个用户类
class user
{
public:
	user();//初始化用户信息
	void showuser(void);//显示用户信息
	void createuser(void);//创建用户
	int findusertransfer(long&);//查找用户用于转账,正确返回0，失败返回-1、销户
	int finduser(long&, string&);//查找用户并匹配密码用于登录,正确返回0，失败返回-1
	void deposit(void);//存款
	void dispense(void);//取款
	int transferfrom(string&);//转账
	void transferto(int&, string&);//转账
	int changepassword(void);//修改密码
	void writeuser(void);//写到文件中
	void readuser(void);//从文件中读取
	string gettime(void);//获取当前时间
	string getname(void);//获取当前账户姓名
	int getflag(void);//获取冻结标志
	void setflag(void);//冻结
	void resetflag(void);//解冻
	long getbankcardID(void);//获取当前账户，转账时比较
	string changeint(int&);//将整形转换成string类
	static long bankcardID0;//定义银行初始卡号为静态成员变量
private:
	string name;//姓名
	long bankcardID;//银行卡号 
	string userpassword;//用户密码
	string ID;//身份ID
	int income;//存入
	int expend;//支出
	int remaining;//余额
	string opdate;//操作日期
	string note;//操作备注
	list<string> usercheck;//用户账单
	int userchecknum;//用户账单数目
	int flag;//冻结标志
};

long user::bankcardID0 = 633304;

user::user()
{
	income = 0;
	expend = 0;
	remaining = 0;
	userchecknum = 0;
	flag = 1;
}

//输入用户的姓名 密码 ID
void user::createuser(void)
{
	cout << "请输入姓名" << endl;
	cin >> name;
	cout << "请输入密码" << endl;
	cin >> userpassword;
	cout << "请输入身份ID" << endl;
	cin >> ID;
	bankcardID = bankcardID0++;
}


//显示账户信息及明细
void user::showuser(void)
{
	cout << "姓名：" << name << endl;
	cout << "银行卡号：" << bankcardID << endl;
	cout << "身份ID：" << ID << endl;
	cout << "余额：" << remaining << endl;

	//显示该用户的账户明细
	list<string>::iterator iter = usercheck.begin();
	while (iter != usercheck.end())
	{
		cout << *iter << endl;
		iter++;
	}
}


//判断银行卡ID判断是否是当前用户
int user::findusertransfer(long& bi)
{
	if (bankcardID == bi)
		return 0;
	return -1;
}


//判断该密码是否是当前用户的密码
int user::finduser(long& bi, string& pw)
{
	if (bankcardID == bi && userpassword == pw)
	{
		return 0;
	}
	return -1;
}


void user::deposit(void)//存款
{
	cout << "请输入存款金额" << endl;
	cin >> income;
	remaining += income;
	cout << "当前余额：" << remaining << endl;

	//生成一条操作记录
	string newcheck;
	string string1 = "+";
	string string2 = changeint(income);  //将整型转换成字符串
	string string3 = "---余额:";
	string string4 = changeint(remaining);
	string string5 = gettime();
	string string6 = "---ATM存款---";
	newcheck = string1 + string2 + string3 + string4 + string6 + string5;
	usercheck.push_back(newcheck);
	userchecknum++;
}

void user::dispense(void)//取款
{
	cout << "请输入取款金额" << endl;
	cin >> expend;
	if (remaining < expend)
	{
		cout << "当前余额不足" << endl;
		return;
	}
	remaining -= expend;
	cout << "当前余额：" << remaining << endl;

	string newcheck;
	string string1 = "-";
	string string2 = changeint(expend);
	string string3 = "---余额:";
	string string4 = changeint(remaining);
	string string5 = gettime();
	string string6 = "---ATM取款---";
	newcheck = string1 + string2 + string3 + string4 + string6 + string5;
	usercheck.push_back(newcheck);
	userchecknum++;
}


//tempname 对方的名字 转出去
int user::transferfrom(string& tempname)//转账
{
	cout << "请输入转账金额" << endl;
	cin >> income;
	if (remaining < income)
	{
		cout << "账户余额不足" << endl;
		return -1;
	}
	else
	{
		remaining -= income;

		string newcheck;
		string string1 = "-";
		string string2 = changeint(income);
		string string3 = "---余额:";
		string string4 = changeint(remaining);
		string string5 = gettime();
		string string6 = "---转账给";
		string string7 = "---";

		newcheck = string1 + string2 + string3 + string4 + string6 + tempname + string7 + string5;
		usercheck.push_back(newcheck);
		userchecknum++;
		return income;
	}
}


//转进来 
void user::transferto(int& in, string& tempname)
{
	income = in;
	remaining += income;

	string newcheck;
	string string1 = "+";
	string string2 = changeint(income);
	string string3 = "---余额:";
	string string4 = changeint(remaining);
	string string5 = gettime();
	string string6 = "---来自";
	string string7 = "的转账---";
	newcheck = string1 + string2 + string3 + string4 + string6 + tempname + string7 + string5;
	usercheck.push_back(newcheck);
	userchecknum++;
}


//修改用户密码 
int user::changepassword(void)//修改密码
{
	string temppassword1;
	string temppassword2;
	string temppassword3;
	cout << "请输入当前密码" << endl;
	cin >> temppassword1;
	if (temppassword1 == userpassword)
	{
		cout << "请输入新的密码" << endl;
		cin >> temppassword2;
		cout << "请再次输入新的密码" << endl;
		cin >> temppassword3;
		if (temppassword2 == temppassword3)
		{
			userpassword = temppassword2;
			return 0;
		}
		else
		{
			cout << "新密码不一致，请重新输入" << endl;
		}
	}
	cout << "密码错误" << endl;
	return -1;
}


//保存用户信息及账户明细 到文件中 cout 重定向到文件
void user::writeuser(void)
{
	cout << userchecknum << endl;
	cout << name << endl;//姓名
	cout << bankcardID << endl;//银行卡号 
	cout << userpassword << endl;//用户密码
	cout << ID << endl;//身份ID
	cout << remaining << endl;//余额

	list<string>::iterator iter = usercheck.begin();
	while (iter != usercheck.end())
	{
		cout << *iter << endl;
		iter++;
	}
}

//cin重定向到文件
void user::readuser(void)
{
	string tempcheck;

	cin >> userchecknum;
	cin >> name;//姓名
	cin >> bankcardID;//银行卡号 
	cin >> userpassword;//用户密码
	cin >> ID;//身份ID
	cin >> remaining;//余额

	for (int i = 0; i < userchecknum; i++)
	{
		cin >> tempcheck;
		usercheck.push_back(tempcheck);
	}
}


string user::gettime(void)
{
	string mytime;
	time_t timep1;
	char* timep2;

	time(&timep1);
	timep2 = ctime(&timep1);
	timep2 = strtok(timep2, "\n");

	string p1 = strtok(timep2, " ");
	string p2 = strtok(NULL, " ");
	string p3 = strtok(NULL, " ");
	string p4 = strtok(NULL, " ");
	string p5 = strtok(NULL, " ");
	string p = "/";
	mytime = p1 + p + p2 + p + p3 + p + p4 + p + p5;

	return mytime;
}

string user::getname(void)
{
	return name;
}

string user::changeint(int& num)
{
	char buf[15] = { 0 };
	string retstring;

	sprintf(buf, "%d", num);
	retstring = buf;
	return retstring;
}

long user::getbankcardID(void)
{
	return bankcardID;
}

int user::getflag()
{
	return flag;
}

void user::setflag(void)//冻结
{
	flag = 0;
}

void user::resetflag(void)//解冻
{
	flag = 1;
}



//定义一个管理类 bank类
class admin
{
public:
	admin();//初始化管理密码为“123456”
	void showmain(void);//开户、登录、退出界面
	void establish(void);//开户
	int cancel(void);//销户,正确返回0，失败返回-1
	int login(void);//登录
	void loginchoose(user&);//用户登录成功后选择功能界面
	int admintransfer(user&);//转账
	int writeinfile(void);//将用户信息写入文件
	int readinfile(void);//从文件读出用户信息
	int resetuserflag(void);//解冻
private:
	string adminpassword;//管理密码
	vector<user> myuser;//用户容器
	static int usernum;//用户数量
};
int admin::usernum = 0;

admin::admin()
{
	adminpassword = "123456";
}


//开户业务
void admin::establish()
{
	string temppassword;
	cout << "请输入管理密码" << endl;
	cin >> temppassword;

	if (temppassword == adminpassword)
	{
		user newuser;
		newuser.createuser(); //输入用户信息 用户名 密码 ID
		cout << "开户成功" << endl;
		usernum++;
		cout << "您现在是否想要存款:1、是 2、否" << endl;

		int ah;
		cin >> ah;
		if (1 == ah)
		{
			newuser.deposit(); //调用存款函数完成存款的功能
		}

		myuser.push_back(newuser);
		newuser.showuser();
	}
	else
	{
		cout << "密码输入有误" << endl;
	}
}


// 销户的功能
int admin::cancel(void)
{
	string temppassword;
	long tempbankcardID;
	int i = 0;
	cout << "请输入管理密码" << endl;
	cin >> temppassword;

	if (temppassword == adminpassword)
	{
		cout << "请输入要注销的卡号" << endl;
		cin >> tempbankcardID;
		vector<user>::iterator iter = myuser.begin();
		while (iter != myuser.end())
		{
			if (iter->findusertransfer(tempbankcardID) == 0)
			{
				//根据ID找到用户
				myuser.erase(myuser.begin() + i);
				cout << "账户删除成功" << endl;
				usernum--;
				return 0;
			}
			iter++;
			i++;
		}
		cout << "卡号输入有误" << endl;
		return -1;
	}
	else
	{
		cout << "密码输入有误" << endl;
		return -1;
	}
}


//登录的功能
int admin::login()
{

	long tempbankcardID;
	string tempuserpassword;
	cout << "请输入卡号" << endl;
	cin >> tempbankcardID;

	vector<user>::iterator iter1 = myuser.begin();
	while (iter1 != myuser.end())
	{
		if (iter1->findusertransfer(tempbankcardID) == 0)
		{
			//在银行的用户数据库中找到了该卡号
			if (iter1->getflag() == 1)  //判断该账户是否被冻结
			{
				//如果没有冻结，就让用户输入密码
				for (int i = 3; i > 0; i--)
				{
					cout << "请输入密码,您还有" << i << "次尝试" << endl;
					cin >> tempuserpassword;
					vector<user>::iterator iter2 = myuser.begin();
					while (iter2 != myuser.end())
					{
						if (iter2->finduser(tempbankcardID, tempuserpassword) == 0)
						{
							//表示用户的账户和密码匹配,以当前用户名登录
							loginchoose(*iter2);
							return 0;
						}
						iter2++;
					}
					cout << "密码输入有误" << endl;
				}
				iter1->setflag();
				cout << "账户已冻结" << endl;
				return -1;
			}
			else
			{
				cout << "您的账户已冻结" << endl;
				return -1;
			}
		}
		iter1++;
	}

	cout << "卡号输入有误" << endl;
	return -1;
}

void admin::showmain()
{
	int ah;
label1:	cout << "请选择功能：1、开户 2、登录 3、销户 4、解冻 5、退出" << endl;
	cin >> ah;
	switch (ah)
	{
	case 1:
		establish();
		goto label1;
	case 2:
		login();
		goto label1;
	case 3:
		cancel();
		goto label1;
	case 4:
		resetuserflag();
		goto label1;
	default:
		break;
	}
}

void admin::loginchoose(user& curuser)
{
	int ah;
label2:	cout << "请选择功能：1、存款 2、取款 3、转账 4、查询 5、修改密码 6、退出" << endl;
	cin >> ah;
	switch (ah)
	{
	case 1:
		curuser.deposit();
		goto label2;
	case 2:
		curuser.dispense();
		goto label2;
	case 3:
		admintransfer(curuser);
		goto label2;
	case 4:
		curuser.showuser();
		goto label2;
	case 5:
		curuser.changepassword();
		goto label2;
	case 6:
		break;
	default:
		break;
	}
}

int admin::admintransfer(user& curuser)
{
	long tempbankID;
	long curbankID = curuser.getbankcardID();
	int tempmoney;
	string tempname1;
	string tempname2;
	cout << "请输入对方账户卡号" << endl;
	cin >> tempbankID;
	if (tempbankID == curbankID)
	{
		cout << "无法转账给自己" << endl;
		return -1;
	}

		vector<user>::iterator iter = myuser.begin();
	while (iter != myuser.end())
	{
		if (iter->findusertransfer(tempbankID) == 0)
		{ //找到了转账对方的用户信息

			tempname1 = iter->getname();
			tempname2 = curuser.getname();
			tempmoney = curuser.transferfrom(tempname1);
			if (tempmoney > 0)
			{
				iter->transferto(tempmoney, tempname2);
				return 0;
			}
			return -1;
		}
		iter++;
	}
	cout << "卡号输入有误" << endl;
	return -1;
}

int admin::writeinfile(void)//将用户信息写入文件
{
	//	cout<<"hello"<<endl;

	streambuf* backup;
	ofstream fout;
	fout.open("./bank.txt");
	backup = cout.rdbuf();
	cout.rdbuf(fout.rdbuf());//重定向

	cout << usernum << endl;
	cout << user::bankcardID0 << endl;

	cout.rdbuf(backup);//重定向回来
	fout.close();

	fout.open("./bank.txt", ios::app);
	backup = cout.rdbuf();
	cout.rdbuf(fout.rdbuf());//重定向

	vector<user>::iterator iter = myuser.begin();
	while (iter != myuser.end())
	{
		iter->writeuser();
		iter++;
	}

	cout.rdbuf(backup);//重定向回来
	fout.close();
	cout << "write called" << endl;
	return 0;
}

int admin::readinfile(void)//从文件读出用户信息
{
	int i = 0;
	streambuf* backup;
	ofstream fin;
	fin.open("./bank.txt", ios::in);
	backup = cin.rdbuf();
	cin.rdbuf(fin.rdbuf());//重定向

	cin >> usernum;
	cin >> user::bankcardID0;


	for (i = 0; i < usernum; i++)
	{
		user tempuser;
		tempuser.readuser();
		myuser.push_back(tempuser);
	}

	cin.rdbuf(backup);//重定向回来
	fin.close();

	cout << "read called" << endl;
	return 0;
}


//解冻用户信息
int admin::resetuserflag()
{
	string temppassword;
	long tempbankcardID;

	cout << "请输入管理密码" << endl;
	cin >> temppassword;

	if (temppassword == adminpassword)
	{
		cout << "请输入要解冻的卡号" << endl;
		cin >> tempbankcardID;
		vector<user>::iterator iter = myuser.begin();
		while (iter != myuser.end())
		{
			if (iter->findusertransfer(tempbankcardID) == 0)
			{
				if (iter->getflag() == 1)
				{
					cout << "您的账户未冻结" << endl;
					return -1;
				}
				else
				{
					iter->resetflag();
					cout << "解冻成功" << endl;
					return 0;
				}
			}
			iter++;
		}
		cout << "卡号输入有误" << endl;
		return -1;

	}
	else
	{
		cout << "密码输入有误" << endl;
		return -1;
	}

}


int main()
{
	admin mybank;
	mybank.readinfile();
	mybank.showmain();
	mybank.writeinfile();

	return 0;
}
#endif

int a;


