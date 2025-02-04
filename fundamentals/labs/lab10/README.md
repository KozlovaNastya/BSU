# Class List

## Program Description
This program provides a simple implementation of a flower management system using a singly linked list. The program allows for operations such as adding, deleting, searching, and printing flower information.

## Features
1. Add Flowers:
  - Insert flowers at the beginning or end of the list.
2. Delete Flowers:
  - Remove the first, last, or specific flowers from the list.
3. Search Flowers:
  - Search flowers by name and count the number of comparisons during the search.
4. Increase Height:
  - Increase the height of all flowers by a set value using a callback function.
5. Display Information:
  - Display flower details with callback functions and list printing.
6. Deep Copy:
  - Supports copying the list of flowers via both constructor and assignment operator.

## Structure
### Classes
- `ListOfFlowers`: A class that manages a linked list of flowers. Each flower has a name, color, and height.
### Key Methods
- `InsertFirst`: Insert a flower at the beginning of the list.
- `InsertLast`: Insert a flower at the end of the list.
- `DeleteFirst`: Remove the first flower from the list.
- `DeleteLast` : Remove the last flower from the list.
- `DeleteByValue`: Delete a flower by its name.
- `SearchByValueWithCount` : Search for a flower by name and count the number of comparisons made.
- `IncreaseHeight`: Increases the height of all flowers by 10.
- `Top`: Display information about the first flower in the list.
- `ListPrint`: Print the information of all flowers in the list.
- `Erase`: Delete all flowers in the list.
### Flower Structure  
Each flower is represented by a `ListItem` structure that contains:
- `FlowerName`: The name of the flower (string).
- `FlowerColor`: The color of the flower (string).
- `FlowerHigh`: The height of the flower in centimeters (float).
- `Next`: A pointer to the next flower in the list (pointer to `ListItem`).

## Memory Management
The `ListOfFlowers` class uses dynamic memory allocation to create and manage the flower list. It is essential to manage memory properly to avoid leaks, which is done by using the destructor and `Erase` method.

## Example Usage
main.cpp
```C++
int main() {
    ListOfFlowers flowers;
    
    // Insert flowers at the beginning and end
    flowers.InsertFirst("Tulip", "Yellow", 30.3f);
    flowers.InsertLast("Lily", "White", 40.1f);
    flowers.InsertFirst("Rose", "Red", 16.3f);
    
    // Print flower list
    flowers.ListPrint();
    
    // Copy flower list
    ListOfFlowers flowersCopy = flowers;
    flowersCopy.ListPrint();
    
    // Search for a flower
    int comparisons = 0;
    bool found = flowers.SearchByValueWithCount("Tulip", comparisons);
    cout << "Found: " << found << ", Comparisons: " << comparisons << endl;
    
    // Increase height of all flowers
    flowers.ForEach(&ListOfFlowers::IncreaseHeight);
    flowers.ListPrint();
    
    // Delete a flower by value
    flowers.DeleteByValue("Rose");
    flowers.ListPrint();
    
    // Delete first and last flower
    flowers.DeleteFirst();
    flowers.DeleteLast();
    
    // Delete all flowers
    flowers.Erase();
    flowers.ListPrint();
}
```
### Example Output
New list  
list is empty  
Insert First  
Name: Tulip, Color: Yellow, High: 30.3  
Insert Last  
Name: Tulip, Color: Yellow, High: 30.3  
Name: Lily, Color: White, High: 40.1  
Insert First  
Name: Rose, Color: Red, High: 16.3  
Name: Rose, Color: Red, High: 16.3  
Name: Tulip, Color: Yellow, High: 30.3  
Name: Lily, Color: White, High: 40.1  
Insert Last  
Name: Rose, Color: Red, High: 16.3  
Name: Rose, Color: Red, High: 16.3  
Name: Tulip, Color: Yellow, High: 30.3  
Name: Lily, Color: White, High: 40.1  
Name: Camoline, Color: Pink, High: 10.16  
Insert Last  
Name: Rose, Color: Red, High: 16.3  
Name: Tulip, Color: Yellow, High: 30.3  
Name: Lily, Color: White, High: 40.1  
Name: Camoline, Color: Pink, High: 10.16  
Name: Pione, Color: Violet, High: 60.9  
Searching for flower 'Pione'  
Found: 1, Comparisons: 3  
...  
Delete ALL  
list is empty  
