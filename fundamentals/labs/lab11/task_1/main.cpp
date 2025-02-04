#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int main() {
	setlocale(LC_ALL, ".1251");
	vector<int> numbers;
	int n = 5, a, sum = 0, count = 0, N, count1 = 0, count2 = 0, minValue, maxValue, razn;
	cout << "Enter the elements of the array (end the input with the number 0):" << endl;
	while (cin >> a && a != 0) {
		numbers.push_back(a);
	}
	cout << "Enter the number to compare with: ";
	cin >> N;
	maxValue = numbers[0];
	minValue = numbers[0];
	for (int num : numbers) {
		sum += num;
		count++;
		if (num == N)
			count1++;
		if (num > N)
			count2++;
		if (num > maxValue)
			maxValue = num;
		if (num < minValue)
			minValue = num;
	}
	int srznach = sum / count;
	razn = maxValue - minValue;
	if (find(numbers.begin(), numbers.end(), 0) != numbers.end()) {
		for (int i = 0; i < count; i++) {
			if (numbers[i] == 0)
				numbers[i] = srznach;
		}
	}
	cout << "Sum of the numbers: " << sum << endl << "Number of elements: " << count << endl;
	cout << "Count of numbers equal to " << N << " = " << count1 << endl;
	cout << "Count of numbers greater than " << N << " = " << count2 << endl;
	cout << "Replace all elements with the arithmetic mean:" << endl;
	for (int num : numbers)
		cout << num << ' ';
	int k = 1;
	for (int i = 0; i < numbers.size(); i++) {
		int sum = 0;
		for (int j = max(0, i - k); j <= min((int)numbers.size() - 1, i + k); j++) {
			sum += numbers[j];
		}
		numbers[i] += sum;
	}
	cout << endl << "Add to each element in the vector the sum of all numbers from neighboring intervals (parameter k=1):" << endl;
	for (int num : numbers)
		cout << num << ' ';
	for (int i = 0; i < count; i++) {
		if (abs(numbers[i])%2 == 0)
			numbers[i] = razn;
	}
	cout << endl << "Replace all numbers where the number is even:" << endl;
	for (int num : numbers)
		cout << num << ' ';
	for (int i = 0; i < numbers.size(); i++) {
		for (int j = i+1; j < numbers.size();) {
			if (numbers[i] == numbers[j])
				numbers.erase(numbers.begin() + j);
			else j++;
		}
	}
	cout << endl << "Remove all duplicates from the sequence in increasing order, except the first one:" << endl;
	for (int num : numbers)
		cout << num << ' ';
	return 0;
}
