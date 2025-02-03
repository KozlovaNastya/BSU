#include "Flower.h"
void ListOfFlowers::PrintFlowerInfo(const ListOfFlowers::ListItem& item) const{
	cout << "Name: " << item.FlowerName << ", "
		<< "Color: " << item.FlowerColor << ", "
		<< "Height: " << item.FlowerHigh << " cm" << endl;
}
void ListOfFlowers::IncreaseHeight(ListItem& item) {
	item.FlowerHigh += 10;
}
ListOfFlowers::ListOfFlowers() : First(nullptr) {}
ListOfFlowers::ListOfFlowers(const string& value1, const string& value2, const float& value3) {
	First = new ListItem;
	First->FlowerName = value1;
	First->FlowerColor = value2;
	First->FlowerHigh = value3;
	First->Next = nullptr;
}
ListOfFlowers::ListOfFlowers(const ListOfFlowers& value) {
	if (value.First == nullptr) {
		First = nullptr;
	}
	else {
		Clone(value);
	}
}
ListOfFlowers::ListItem* ListOfFlowers::getFirst() {
	return First;
}
void ListOfFlowers::InsertFirst(const string& value1, const string& value2, const float& value3) {
	ListItem* newListItem = new ListItem;
	newListItem->FlowerName = value1;
	newListItem->FlowerColor = value2;
	newListItem->FlowerHigh = value3;
	newListItem->Next = First;
	First = newListItem;
}
void ListOfFlowers::InsertLast(const string& value1, const string& value2, const float& value3) {
	ListItem* newListItem = new ListItem;
	newListItem->FlowerName = value1;
	newListItem->FlowerColor = value2;
	newListItem->FlowerHigh = value3;
	newListItem->Next = nullptr;
	if (First == nullptr) {
		First = newListItem;
	}
	else {
		ListItem* current = First;
		while (current->Next != nullptr) {
			current = current->Next;
		}
		current->Next = newListItem;
	}
}
bool ListOfFlowers::DeleteFirst() {
	if (First == nullptr)
		return false;
	ListItem* newListItem = First;
	First = First->Next;
	delete newListItem;
	return true;
}
bool ListOfFlowers::DeleteLast() {
	if (First == nullptr)
		return false;
	if (First->Next == nullptr) {
		delete First;
		First = nullptr;
		return true;
	}
	ListItem* current = First;
	while (current->Next->Next != nullptr) {
		current = current->Next;
	}
	delete current->Next;
	current->Next = nullptr;
	return true;
}
bool ListOfFlowers::DeleteByValue(const string& flowerName) {
	if (First == nullptr)
		return false;
	if (First->FlowerName == flowerName) {
		ListItem* temp = First;
		First = First->Next;
		delete temp;
		return true;
	}
	ListItem* current = First;
	while (current->Next != nullptr) {
		if (current->Next->FlowerName == flowerName) {
			ListItem* temp = current->Next;
			current->Next = current->Next->Next;
			delete temp;
			return true;
		}
		current = current->Next;
	}

	return false; 
}
bool ListOfFlowers::SearchByValueWithCount(const string& flowerName, int& comparisonsCount) const {
	comparisonsCount = 0;
	ListItem* current = First;
	while (current != nullptr) {
		comparisonsCount++;
		if (current->FlowerName == flowerName) {
			return true;
		}
		current = current->Next;
	}
	return false;
}
const ListOfFlowers& ListOfFlowers::operator = (const ListOfFlowers& other) {
	if (this == &other) {
		return *this;
	}
	Erase();
	Clone(other);
	return *this;
}
void ListOfFlowers::Clone(const ListOfFlowers& other) {
	ListItem* otherCurrent = other.First;
	ListItem* newCurrent = nullptr;
	while (otherCurrent != nullptr) {
		ListItem* newItem = new ListItem;
		newItem->FlowerName = otherCurrent->FlowerName;
		newItem->FlowerColor = otherCurrent->FlowerColor;
		newItem->FlowerHigh = otherCurrent->FlowerHigh;
		newItem->Next = nullptr;

		if (First == nullptr) {
			First = newItem;
		}
		else {
			if (newCurrent != nullptr) {
				newCurrent->Next = newItem;
			}
		}
		newCurrent = newItem;
		otherCurrent = otherCurrent->Next;
	}
}
void ListOfFlowers::ForEach(void (ListOfFlowers::* callback)(const ListItem&) const) const {
	ListItem* current = First;
	while (current) {
		(this->*callback)(*current);  // Используем указатель на метод с квалификатором const
		current = current->Next;
	}
}
void ListOfFlowers::ForEach(void (ListOfFlowers::* callback)(ListItem&)) {
	ListItem* current = First;
	while (current != nullptr) {
		(this->*callback)(*current);  // Правильный вызов указателя на метод
		current = current->Next;
	}
}
void ListOfFlowers::Top()const {
	if (First == nullptr)
		cout << "list is empty" << endl;
	else cout << "Name: " << First->FlowerName << ", Color: " << First->FlowerColor <<
		", High: " << First->FlowerHigh << endl;
}
void ListOfFlowers::ListPrint()const
{
	ListItem* newListItem = First;
	if (newListItem == nullptr)
		cout << "list is empty" << endl;
	else
	{
		while (newListItem != nullptr)
		{
			cout << "Name: " << newListItem->FlowerName << ", Color: " << newListItem->FlowerColor << 
				", High: " << newListItem->FlowerHigh << endl;
			newListItem = newListItem->Next;
		}
	};
}
void ListOfFlowers::Erase() {
	ListItem* current = First;
	while (current != nullptr) {
		ListItem* next = current->Next;
		delete current;
		current = next;
	}
	First = nullptr;
}
ListOfFlowers::~ListOfFlowers() {
	ListItem* current = First;
	while (current != nullptr) {
		ListItem* next = current->Next; 
		delete current;
		current = next;
	}
}