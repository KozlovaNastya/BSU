# Anagram Detection Program

## Objective
To identify and display pairs of words that are reverse anagrams (palindromic pairs) from input text, handling case insensitivity and eliminating duplicates.

## Program Functionality
Reads text input line by line, finds pairs of words where one word is the exact reverse of another, and outputs these unique pairs in alphabetical order.

## Algorithm Implementation

### Core Logic
```java
String reversed = new StringBuilder(words[i]).reverse().toString();
for (int j = i + 1; j < n; j++) {
    if (reversed.equalsIgnoreCase(words[j])) {
        String pair;
        if (words[i].compareToIgnoreCase(words[j]) < 0) {
            pair = words[i] + " - " + words[j];
        } else {
            pair = words[j] + " - " + words[i];
        }
        uniquePairs.add(pair.toLowerCase());
    }
}
```

### Key Components
- Input Processing: Reads lines continuously until EOF
- Word Extraction: Splits text using regex `[^\\p{L}]+` to get only letter sequences
- Pair Detection: Compares each word's reverse with other words
- Duplicate Prevention: Uses `HashSet` to store unique pairs
- Normalization: Converts to lowercase for case-insensitive comparison
