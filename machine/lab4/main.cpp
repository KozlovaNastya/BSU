#include <iostream>
using namespace std;
extern "C" int __stdcall FindNum1(int*, int*, const int, int);
extern "C" int __cdecl FindNum2(int*, int*, const int, int);
extern "C" int __stdcall FindNum3(int*, int*, const int, int);
extern "C" int __cdecl FindNum4(int*, int*, const int, int);
extern "C" int __fastcall FindNum5(int*, int*, const int, int);

int main() {
	const int N = 7;
	int a1[N] = { 1,2,5,6,4,3,8 };
	int a2[N] = { 1,5,6,4,3,9,8 };
	int minValue = 100000;
	cout << "There are two arrays:" << endl;
	for (const int& el1 : a1) cout << el1 << ' ';
	cout << endl;
	for (const int& el2 : a2) cout << el2 << ' ';
	cout << endl;
	cout << "__stdcall for _FindNum1@16 : " << FindNum1(a1, a2, N, minValue) << endl;
	cout << "__cdecl for _FindNum2 : " << FindNum2(a1, a2, N, minValue) << endl;
	cout << "__fastcall for FindNum5 : " << FindNum5(a1, a2, N, minValue) << endl;
	cout << "__stdcall for FindNum3 : " << FindNum3(a1, a2, N, minValue) << endl;
	cout << "__cdecl for FindNum4 : " << FindNum4(a1, a2, N, minValue) << endl;
	return 0;
}