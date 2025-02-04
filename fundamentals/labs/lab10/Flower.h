#ifndef FLOWER_H
#define FLOWER_H
#include <iostream>
using namespace std;
class ListOfFlowers {
protected:
	struct ListItem {
		string FlowerName = "undefined";
		string FlowerColor = "undefined";
		float FlowerHigh = 0;
		ListItem* Next = nullptr;
	};
	ListItem* First;
public:
	ListOfFlowers();
	ListOfFlowers(const string&, const string&, const float&);
	ListOfFlowers(const ListOfFlowers&);
	ListItem* getFirst();
	void InsertFirst(const string&, const string&, const float&);
	void InsertLast(const string&, const string&, const float&);
	bool DeleteFirst();
	bool DeleteLast();
	void Top() const;
	void ListPrint() const; 
	void ForEach(void (ListOfFlowers::* callback)(const ListItem&) const) const;
    void ForEach(void(ListOfFlowers::* callback)(ListItem&));
	const ListOfFlowers& operator = (const ListOfFlowers&); 
	virtual~ListOfFlowers(); 
	void Erase(); 
	bool DeleteByValue(const string& flowerName);
	bool SearchByValueWithCount(const string& flowerName, int& comparisonsCount) const;
	void PrintFlowerInfo(const ListItem&) const;
	void IncreaseHeight(ListItem&);
protected:
	void Clone(const ListOfFlowers&);
};
#endif
