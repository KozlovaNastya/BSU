# Semantics of Moving

This program is designed to model characters with various attributes, such as name, condition, race, speed, and artifacts. The program also supports creating specialized characters (Magic Characters) with additional properties like mana and magic artifacts. It demonstrates the use of C++ features such as move semantics, dynamic memory management, polymorphism, and sorting with custom comparison functions.

## Features
- **Character Class**: Represents a character with attributes like name, condition, race, speed, and artifacts.
- **MagicCharacter Class**: Inherits from the `Character` class and adds properties for magic attributes, such as mana and magic artifacts.
- **Move Semantics**: Demonstrates the use of move constructors and move assignment operators for efficient object management.
- **Dynamic Memory Management**: Manages an array of magic artifacts dynamically.
- **Sorting**: Sorts characters alphabetically by name.
- **Polymorphism**: Allows both `Character` and `MagicCharacter` objects to be stored in a single container and accessed polymorphically.

## Classes

### `Character` Class
The `Character` class represents a basic character with the following attributes:
- `ID`: A unique identifier.
- `name`: The character's name.
- `condition`: The condition of the character (normal, paralyzed, or dead).
- `race`: The character's race (human, dwarf, or elf).
- `speed`: The character's speed.
- `artifacts`: The number of artifacts the character possesses.

### `MagicCharacter` Class
The `MagicCharacter` class extends `Character` and adds the following attributes:
- `maxMana`: The maximum mana the character can have.
- `mana`: The current mana of the character.
- `magicArtefacts`: The number of magical artifacts the character possesses.
- `listOfArtefacts`: A dynamically allocated array storing the magic artifacts.

### Key Methods
- `Character` and `MagicCharacter` constructors and destructors.
- Move constructors and assignment operators for efficient management of resources.
- Getter and setter methods for modifying and retrieving character attributes.
- `operator<<`: Outputs a character's attributes to the console.

### Sorting
The program includes a function `AlphaSort` that sorts characters based on their names.

### Magic Artefacts
The program defines an enumeration `Artefacts`, which includes:
- `sword`
- `staff`
- `rune`
- `potion`
- `amulet`

## Program Flow

1. **Character Creation**: The program demonstrates character creation using constructors with parameters, and the use of move constructors and assignment operators.
2. **Setting Attributes**: The program sets and prints new attributes for characters.
3. **Comparison**: Characters are compared based on their IDs using the less-than operator (`operator<`).
4. **Magic Characters**: The program demonstrates creating `MagicCharacter` objects with additional attributes like mana and magic artifacts.
5. **Sorting**: A list of characters (both `Character` and `MagicCharacter`) is sorted alphabetically by name.
6. **Polymorphism**: The program counts the number of `Character` and `MagicCharacter` objects in a mixed list.

## Example Ouput

```
constructor with parameters
ID: 0; Name: Legolas; Condition: normal; Race: elf; Speed: 15; Artifacts: 5;
copy constructor
ID: 1; Name: Legolas; Condition: normal; Race: elf; Speed: 15; Artifacts: 5;
operator =
ID: 2; Name: Legolas; Condition: normal; Race: elf; Speed: 15; Artifacts: 5;
for ch1
getID() : 0
getName() :
getCondition() : dead
getRace() : elf
getSpeed() : 0
getArtifacts() : 0
setName(), setCondition(), setSpeed(), setArtifacts() for ch2
ID: 1; Name: Lucy; Condition: paralyzed; Race: elf; Speed: 0; Artifacts: 1;
compare by ID
ch1 < ch2 : 1
ch3 < ch1 : 0
MAGIC CHARACTERS
constructor with parameters
ID: 3; Name: Elvin; Condition: normal; Race: human; Speed: 20; Artifacts: 5; Max Mana: 50; mana: 37; count of Magic Artefacts: 2
list of magic Artefacts:
amulet
potion
copy constructor
ID: 4; Name: Elvin; Condition: normal; Race: human; Speed: 20; Artifacts: 5; Max Mana: 50; mana: 37; count of Magic Artefacts: 2
list of magic Artefacts:
amulet
potion
operator =
ID: 5; Name: ; Condition: dead; Race: human; Speed: 0; Artifacts: 0; Max Mana: 50; mana: 37; count of Magic Artefacts: 0
list of magic Artefacts:
for ch4:
getID() : 3
getName() :
getCondition() : dead
getRace() : human
getSpeed() : 0
getArtifacts() : 0
getMaxMana() : 50
getMana() : 37
getMagicArtefacts() : 0
List of Magic Artefacts: setName(), setCondition(), setSpeed(), setArtifacts() for ch5
ID: 4; Name: Anna; Condition: dead; Race: human; Speed: 0; Artifacts: 0; Max Mana: 90; mana: 0; count of Magic Artefacts: 0
list of magic Artefacts:
compare by ID
ch4 < ch5 : 1
ch6 < ch5 : 0
array with two types of characters
ID: 8; Name: Elvin; Condition: normal; Race: human; Speed: 20; Artifacts: 5;
ID: 6; Name: Legolas; Condition: normal; Race: elf; Speed: 15; Artifacts: 5;
ID: 7; Name: Lucy; Condition: paralyzed; Race: human; Speed: 10; Artifacts: 3;
Number of Character: 2
Number of MagicCharacter: 1
```

## File Structure
- `main.cpp`: The main program file, where the program flow and logic are implemented.

- `character.cpp`: Contains the implementation of the `Character` and `MagicCharacter` classes, including their methods.

- `character.h`: The header file for `Character` and `MagicCharacter` classes, containing the class declarations and associated helper functions.

## Conclusion
This program demonstrates the use of advanced `C++` features such as move semantics, polymorphism, and dynamic memory management. It is a simple but powerful example of how to manage objects in `C++` and demonstrate object-oriented principles.
