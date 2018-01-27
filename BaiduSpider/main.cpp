#include "Spider.h"
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <thread>

using namespace std;

void ShowMSG(string s)
{
	MessageBox(NULL,s.c_str(),TEXT("新结果"),MB_OK);
}

int SearchItem(vector<string>& vs)
{
	int count = 0;
	string s = "现场确认%20site%3Awww.xxswjw.gov.cn";
	Spider* sp = new Spider(s);

	string res = UtfToGbk(sp->GetResult().c_str());
	int a = res.rfind("content_left");

	res = res.substr(a);
	res = res.substr(0,res.find("相关搜索"));

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

	cout<<"间隔时间(秒)："<<endl;
	cin>>interval;
	interval *= 1000;

	while (true)
	{
		cout<<endl;
		counter++;
		cout<<"第"<<counter<<"次  ";

		SYSTEMTIME st = { 0 };
		GetLocalTime(&st);
		cout<<st.wHour<<"时"<<st.wMinute<<"分"<<st.wSecond<<"秒";
		
		int n=SearchItem(vs);
		if (n)
			cout<<" -- "<<n<<"条新结果";
		cout<<endl;

		Sleep(interval);
	}
	system("pause");
	return 0;
}