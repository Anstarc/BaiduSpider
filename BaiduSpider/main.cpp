#include "Spider.h"
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <thread>

using namespace std;

void ShowMSG(string s)
{
	MessageBox(NULL,s.c_str(),TEXT("�½��"),MB_OK);
}

int SearchItem(vector<string>& vs)
{
	int count = 0;
	string s = "�ֳ�ȷ��%20site%3Awww.xxswjw.gov.cn";
	Spider* sp = new Spider(s);

	string res = UtfToGbk(sp->GetResult().c_str());
	int a = res.rfind("content_left");

	res = res.substr(a);
	res = res.substr(0,res.find("�������"));

	while (res.find("title")!=-1)
	{
		res = res.substr(res.find("title")+8);
		string ss = res.substr(0,res.find("\""));
		if (find(vs.begin(),vs.end(),ss)==vs.end())
		{
			thread* t =new thread(ShowMSG, ss);
			t->detach();
			vs.push_back(ss);
			count++;
		}
	}
	return count;
}

int main(void)
{
	vector<string> vs;
	int interval;
	int counter = 0;
	vector<thread> vt;

	cout<<"���ʱ��(��)��"<<endl;
	cin>>interval;
	interval *= 1000;

	while (true)
	{
		cout<<endl;
		counter++;
		cout<<"��"<<counter<<"��  ";

		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		cout<<st.wHour<<"ʱ"<<st.wMinute<<"��"<<st.wSecond<<"��";
		
		int n=SearchItem(vs);
		if (n)
			cout<<" -- "<<n<<"���½��";
		cout<<endl;

		Sleep(interval);
	}
	system("pause");
	return 0;
}