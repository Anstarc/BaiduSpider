#include "Spider.h"
#include <windows.h>
#include <iostream>

using namespace std;

int main(void)
{
	string s = "现场确认%20site%3Awww.xxswjw.gov.cn";
	Spider* sp = new Spider(s);
	cout<<sp->GetResult();
	MessageBox(NULL,TEXT("HELLO WORLD!"),TEXT("MSG"),MB_OK);
	system("pause");
	return 0;
}