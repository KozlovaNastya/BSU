#include <iostream>
#include "Flower.h"
int main() {
	cout << "New list" << endl;
	ListOfFlowers flowers;
	flowers.ListPrint();
	cout << "Insert First" << endl;
	flowers.InsertFirst("Tulip", "Yellow", 30.3f);
	flowers.ListPrint();
	cout << "Insert Last" << endl;
	flowers.InsertLast("Lily", "White", 40.1f);
	flowers.ListPrint();
	cout << "Insert First" << endl;
	flowers.InsertFirst("Rose", "Red", 16.3f);
	flowers.ListPrint();
	cout << "Insert Last" << endl;
	flowers.InsertLast("Camoline", "Pink", 10.16f);
	flowers.ListPrint();
	cout << "Insert Last" << endl;
	flowers.InsertLast("Pione", "Violet", 60.9f);
	flowers.ListPrint();

	cout << "Copy with constructor" << endl;
	ListOfFlowers flowersCopy1(flowers);
	flowersCopy1.ListPrint();
	cout << "Copy with =" << endl;
	ListOfFlowers flowersCopy2 = flowers;
	flowersCopy2.ListPrint();

	int comparisonsCount1 = 0;
	cout << "Searching for flower 'Pione'" << endl;
	bool found1 = flowers.SearchByValueWithCount("Pione", comparisonsCount1);
	cout << comparisonsCount1 << endl;

	int comparisonsCount2 = 0;
	cout << "Searching for flower 'Tulip'" << endl;
	bool found2 = flowers.SearchByValueWithCount("Tulip", comparisonsCount2);
	cout << "Kol comparisons " << comparisonsCount2 << endl;

	int comparisonsCount3 = 0;
	cout << "Searching for flower 'Pose'" << endl;
	bool found3 = flowers.SearchByValueWithCount("Rose", comparisonsCount3);
	cout << "Kol comparisons " << comparisonsCount3 << endl;

	int comparisonsCount4 = 0;
	cout << "Searching for flower 'Mayi'" << endl;
	bool found4 = flowers.SearchByValueWithCount("Mayi", comparisonsCount4);
	cout << "Kol comparisons " << comparisonsCount4 << endl;

	cout << "Callback for increase FlowerHigh + 10" << endl;
	flowers.ForEach(&ListOfFlowers::IncreaseHeight);
	flowers.ListPrint();

	cout << "Delete flower 'Rose'" << endl;
	flowers.DeleteByValue("Rose");
	flowers.ListPrint();


	cout << "DeleteFisrt" << endl;
	flowers.DeleteFirst();
	flowers.ListPrint();

	cout << "DeleteLast" << endl;
	flowers.DeleteLast();
	flowers.ListPrint();

	cout << "Delete ALL" << endl;
	flowers.Erase();
	flowers.ListPrint();

	//cout << "Callback for view" << endl;
	//flowers.ForEach(&ListOfFlowers::PrintFlowerInfo);
	return 0;
}
