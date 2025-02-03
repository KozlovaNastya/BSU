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
	// конструктор
	ListOfFlowers(const string&, const string&, const float&);
	// конструктор копировани€
	ListOfFlowers(const ListOfFlowers&);
	//получение первого элемента
	ListItem* getFirst();
	// добавление нового элемента в начало списка
	void InsertFirst(const string&, const string&, const float&);
	//добавление нового элемента в конец списка
	void InsertLast(const string&, const string&, const float&);
	// удаление первого элемента
	bool DeleteFirst();
	// удаление последнего элемента
	bool DeleteLast();
	// посмотреть первый элемент списка
	void Top() const;
	// печать элементов списка
	void ListPrint() const; 
	// выполнить действи€ над всеми элементами списка, не измен€€ его
	void ForEach(void (ListOfFlowers::* callback)(const ListItem&) const) const;
	// выполнить действи€ над всеми элементами списка, измен€€ его
    void ForEach(void(ListOfFlowers::* callback)(ListItem&));
	// оператор присваивани€
	const ListOfFlowers& operator = (const ListOfFlowers&); 
	// деструктор
	virtual~ListOfFlowers(); 
	// удаление элементов списка
	void Erase(); 
	//удаление элемента по значению
	bool DeleteByValue(const string& flowerName);
	//поиск элемента по значению с подсчетом
	bool SearchByValueWithCount(const string& flowerName, int& comparisonsCount) const;
	void PrintFlowerInfo(const ListItem&) const;
	void IncreaseHeight(ListItem&);
protected:
	void Clone(const ListOfFlowers&); // клонирование
};
#endif