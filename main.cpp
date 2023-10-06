#if 1
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <list>
#include <stdio.h>

using namespace std;

//����һ���û���
class user
{
public:
	user();//��ʼ���û���Ϣ
	void showuser(void);//��ʾ�û���Ϣ
	void createuser(void);//�����û�
	int findusertransfer(long&);//�����û�����ת��,��ȷ����0��ʧ�ܷ���-1������
	int finduser(long&, string&);//�����û���ƥ���������ڵ�¼,��ȷ����0��ʧ�ܷ���-1
	void deposit(void);//���
	void dispense(void);//ȡ��
	int transferfrom(string&);//ת��
	void transferto(int&, string&);//ת��
	int changepassword(void);//�޸�����
	void writeuser(void);//д���ļ���
	void readuser(void);//���ļ��ж�ȡ
	string gettime(void);//��ȡ��ǰʱ��
	string getname(void);//��ȡ��ǰ�˻�����
	int getflag(void);//��ȡ�����־
	void setflag(void);//����
	void resetflag(void);//�ⶳ
	long getbankcardID(void);//��ȡ��ǰ�˻���ת��ʱ�Ƚ�
	string changeint(int&);//������ת����string��
	static long bankcardID0;//�������г�ʼ����Ϊ��̬��Ա����
private:
	string name;//����
	long bankcardID;//���п��� 
	string userpassword;//�û�����
	string ID;//���ID
	int income;//����
	int expend;//֧��
	int remaining;//���
	string opdate;//��������
	string note;//������ע
	list<string> usercheck;//�û��˵�
	int userchecknum;//�û��˵���Ŀ
	int flag;//�����־
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

//�����û������� ���� ID
void user::createuser(void)
{
	cout << "����������" << endl;
	cin >> name;
	cout << "����������" << endl;
	cin >> userpassword;
	cout << "���������ID" << endl;
	cin >> ID;
	bankcardID = bankcardID0++;
}


//��ʾ�˻���Ϣ����ϸ
void user::showuser(void)
{
	cout << "������" << name << endl;
	cout << "���п��ţ�" << bankcardID << endl;
	cout << "���ID��" << ID << endl;
	cout << "��" << remaining << endl;

	//��ʾ���û����˻���ϸ
	list<string>::iterator iter = usercheck.begin();
	while (iter != usercheck.end())
	{
		cout << *iter << endl;
		iter++;
	}
}


//�ж����п�ID�ж��Ƿ��ǵ�ǰ�û�
int user::findusertransfer(long& bi)
{
	if (bankcardID == bi)
		return 0;
	return -1;
}


//�жϸ������Ƿ��ǵ�ǰ�û�������
int user::finduser(long& bi, string& pw)
{
	if (bankcardID == bi && userpassword == pw)
	{
		return 0;
	}
	return -1;
}


void user::deposit(void)//���
{
	cout << "����������" << endl;
	cin >> income;
	remaining += income;
	cout << "��ǰ��" << remaining << endl;

	//����һ��������¼
	string newcheck;
	string string1 = "+";
	string string2 = changeint(income);  //������ת�����ַ���
	string string3 = "---���:";
	string string4 = changeint(remaining);
	string string5 = gettime();
	string string6 = "---ATM���---";
	newcheck = string1 + string2 + string3 + string4 + string6 + string5;
	usercheck.push_back(newcheck);
	userchecknum++;
}

void user::dispense(void)//ȡ��
{
	cout << "������ȡ����" << endl;
	cin >> expend;
	if (remaining < expend)
	{
		cout << "��ǰ����" << endl;
		return;
	}
	remaining -= expend;
	cout << "��ǰ��" << remaining << endl;

	string newcheck;
	string string1 = "-";
	string string2 = changeint(expend);
	string string3 = "---���:";
	string string4 = changeint(remaining);
	string string5 = gettime();
	string string6 = "---ATMȡ��---";
	newcheck = string1 + string2 + string3 + string4 + string6 + string5;
	usercheck.push_back(newcheck);
	userchecknum++;
}


//tempname �Է������� ת��ȥ
int user::transferfrom(string& tempname)//ת��
{
	cout << "������ת�˽��" << endl;
	cin >> income;
	if (remaining < income)
	{
		cout << "�˻�����" << endl;
		return -1;
	}
	else
	{
		remaining -= income;

		string newcheck;
		string string1 = "-";
		string string2 = changeint(income);
		string string3 = "---���:";
		string string4 = changeint(remaining);
		string string5 = gettime();
		string string6 = "---ת�˸�";
		string string7 = "---";

		newcheck = string1 + string2 + string3 + string4 + string6 + tempname + string7 + string5;
		usercheck.push_back(newcheck);
		userchecknum++;
		return income;
	}
}


//ת���� 
void user::transferto(int& in, string& tempname)
{
	income = in;
	remaining += income;

	string newcheck;
	string string1 = "+";
	string string2 = changeint(income);
	string string3 = "---���:";
	string string4 = changeint(remaining);
	string string5 = gettime();
	string string6 = "---����";
	string string7 = "��ת��---";
	newcheck = string1 + string2 + string3 + string4 + string6 + tempname + string7 + string5;
	usercheck.push_back(newcheck);
	userchecknum++;
}


//�޸��û����� 
int user::changepassword(void)//�޸�����
{
	string temppassword1;
	string temppassword2;
	string temppassword3;
	cout << "�����뵱ǰ����" << endl;
	cin >> temppassword1;
	if (temppassword1 == userpassword)
	{
		cout << "�������µ�����" << endl;
		cin >> temppassword2;
		cout << "���ٴ������µ�����" << endl;
		cin >> temppassword3;
		if (temppassword2 == temppassword3)
		{
			userpassword = temppassword2;
			return 0;
		}
		else
		{
			cout << "�����벻һ�£�����������" << endl;
		}
	}
	cout << "�������" << endl;
	return -1;
}


//�����û���Ϣ���˻���ϸ ���ļ��� cout �ض����ļ�
void user::writeuser(void)
{
	cout << userchecknum << endl;
	cout << name << endl;//����
	cout << bankcardID << endl;//���п��� 
	cout << userpassword << endl;//�û�����
	cout << ID << endl;//���ID
	cout << remaining << endl;//���

	list<string>::iterator iter = usercheck.begin();
	while (iter != usercheck.end())
	{
		cout << *iter << endl;
		iter++;
	}
}

//cin�ض����ļ�
void user::readuser(void)
{
	string tempcheck;

	cin >> userchecknum;
	cin >> name;//����
	cin >> bankcardID;//���п��� 
	cin >> userpassword;//�û�����
	cin >> ID;//���ID
	cin >> remaining;//���

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

void user::setflag(void)//����
{
	flag = 0;
}

void user::resetflag(void)//�ⶳ
{
	flag = 1;
}



//����һ�������� bank��
class admin
{
public:
	admin();//��ʼ����������Ϊ��123456��
	void showmain(void);//��������¼���˳�����
	void establish(void);//����
	int cancel(void);//����,��ȷ����0��ʧ�ܷ���-1
	int login(void);//��¼
	void loginchoose(user&);//�û���¼�ɹ���ѡ���ܽ���
	int admintransfer(user&);//ת��
	int writeinfile(void);//���û���Ϣд���ļ�
	int readinfile(void);//���ļ������û���Ϣ
	int resetuserflag(void);//�ⶳ
private:
	string adminpassword;//��������
	vector<user> myuser;//�û�����
	static int usernum;//�û�����
};
int admin::usernum = 0;

admin::admin()
{
	adminpassword = "123456";
}


//����ҵ��
void admin::establish()
{
	string temppassword;
	cout << "�������������" << endl;
	cin >> temppassword;

	if (temppassword == adminpassword)
	{
		user newuser;
		newuser.createuser(); //�����û���Ϣ �û��� ���� ID
		cout << "�����ɹ�" << endl;
		usernum++;
		cout << "�������Ƿ���Ҫ���:1���� 2����" << endl;

		int ah;
		cin >> ah;
		if (1 == ah)
		{
			newuser.deposit(); //���ô�����ɴ��Ĺ���
		}

		myuser.push_back(newuser);
		newuser.showuser();
	}
	else
	{
		cout << "������������" << endl;
	}
}


// �����Ĺ���
int admin::cancel(void)
{
	string temppassword;
	long tempbankcardID;
	int i = 0;
	cout << "�������������" << endl;
	cin >> temppassword;

	if (temppassword == adminpassword)
	{
		cout << "������Ҫע���Ŀ���" << endl;
		cin >> tempbankcardID;
		vector<user>::iterator iter = myuser.begin();
		while (iter != myuser.end())
		{
			if (iter->findusertransfer(tempbankcardID) == 0)
			{
				//����ID�ҵ��û�
				myuser.erase(myuser.begin() + i);
				cout << "�˻�ɾ���ɹ�" << endl;
				usernum--;
				return 0;
			}
			iter++;
			i++;
		}
		cout << "������������" << endl;
		return -1;
	}
	else
	{
		cout << "������������" << endl;
		return -1;
	}
}


//��¼�Ĺ���
int admin::login()
{

	long tempbankcardID;
	string tempuserpassword;
	cout << "�����뿨��" << endl;
	cin >> tempbankcardID;

	vector<user>::iterator iter1 = myuser.begin();
	while (iter1 != myuser.end())
	{
		if (iter1->findusertransfer(tempbankcardID) == 0)
		{
			//�����е��û����ݿ����ҵ��˸ÿ���
			if (iter1->getflag() == 1)  //�жϸ��˻��Ƿ񱻶���
			{
				//���û�ж��ᣬ�����û���������
				for (int i = 3; i > 0; i--)
				{
					cout << "����������,������" << i << "�γ���" << endl;
					cin >> tempuserpassword;
					vector<user>::iterator iter2 = myuser.begin();
					while (iter2 != myuser.end())
					{
						if (iter2->finduser(tempbankcardID, tempuserpassword) == 0)
						{
							//��ʾ�û����˻�������ƥ��,�Ե�ǰ�û�����¼
							loginchoose(*iter2);
							return 0;
						}
						iter2++;
					}
					cout << "������������" << endl;
				}
				iter1->setflag();
				cout << "�˻��Ѷ���" << endl;
				return -1;
			}
			else
			{
				cout << "�����˻��Ѷ���" << endl;
				return -1;
			}
		}
		iter1++;
	}

	cout << "������������" << endl;
	return -1;
}

void admin::showmain()
{
	int ah;
label1:	cout << "��ѡ���ܣ�1������ 2����¼ 3������ 4���ⶳ 5���˳�" << endl;
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
label2:	cout << "��ѡ���ܣ�1����� 2��ȡ�� 3��ת�� 4����ѯ 5���޸����� 6���˳�" << endl;
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
	cout << "������Է��˻�����" << endl;
	cin >> tempbankID;
	if (tempbankID == curbankID)
	{
		cout << "�޷�ת�˸��Լ�" << endl;
		return -1;
	}

		vector<user>::iterator iter = myuser.begin();
	while (iter != myuser.end())
	{
		if (iter->findusertransfer(tempbankID) == 0)
		{ //�ҵ���ת�˶Է����û���Ϣ

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
	cout << "������������" << endl;
	return -1;
}

int admin::writeinfile(void)//���û���Ϣд���ļ�
{
	//	cout<<"hello"<<endl;

	streambuf* backup;
	ofstream fout;
	fout.open("./bank.txt");
	backup = cout.rdbuf();
	cout.rdbuf(fout.rdbuf());//�ض���

	cout << usernum << endl;
	cout << user::bankcardID0 << endl;

	cout.rdbuf(backup);//�ض������
	fout.close();

	fout.open("./bank.txt", ios::app);
	backup = cout.rdbuf();
	cout.rdbuf(fout.rdbuf());//�ض���

	vector<user>::iterator iter = myuser.begin();
	while (iter != myuser.end())
	{
		iter->writeuser();
		iter++;
	}

	cout.rdbuf(backup);//�ض������
	fout.close();
	cout << "write called" << endl;
	return 0;
}

int admin::readinfile(void)//���ļ������û���Ϣ
{
	int i = 0;
	streambuf* backup;
	ofstream fin;
	fin.open("./bank.txt", ios::in);
	backup = cin.rdbuf();
	cin.rdbuf(fin.rdbuf());//�ض���

	cin >> usernum;
	cin >> user::bankcardID0;


	for (i = 0; i < usernum; i++)
	{
		user tempuser;
		tempuser.readuser();
		myuser.push_back(tempuser);
	}

	cin.rdbuf(backup);//�ض������
	fin.close();

	cout << "read called" << endl;
	return 0;
}


//�ⶳ�û���Ϣ
int admin::resetuserflag()
{
	string temppassword;
	long tempbankcardID;

	cout << "�������������" << endl;
	cin >> temppassword;

	if (temppassword == adminpassword)
	{
		cout << "������Ҫ�ⶳ�Ŀ���" << endl;
		cin >> tempbankcardID;
		vector<user>::iterator iter = myuser.begin();
		while (iter != myuser.end())
		{
			if (iter->findusertransfer(tempbankcardID) == 0)
			{
				if (iter->getflag() == 1)
				{
					cout << "�����˻�δ����" << endl;
					return -1;
				}
				else
				{
					iter->resetflag();
					cout << "�ⶳ�ɹ�" << endl;
					return 0;
				}
			}
			iter++;
		}
		cout << "������������" << endl;
		return -1;

	}
	else
	{
		cout << "������������" << endl;
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


