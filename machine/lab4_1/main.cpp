#include <iostream>
extern "C" int __fastcall Find1(const unsigned int* ar, int size);
int main() {
	srand(time(0));
	unsigned int ar[10];
	for (int i = 0; i < 10; i++) ar[i] = rand() % 10;
	std::cout << "massiv:" << std::endl;
	for (const int& elem : ar) std::cout << elem << ' ';
	std::cout << std::endl;
	std::cout << Find1(ar, 10);
	return 0;
}