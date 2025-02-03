### Problem Description
In this task, you need to perform several operations on an array of integers. For each array of n elements, the following operations are required:

1. Count the number of sign changes in the array, where zero is considered a positive number.
2. Calculate the product of elements between the first and second zero elements in the array.
3. Compress the array by removing all elements equal to a given number P, and fill the freed-up positions at the end of the array with zeros.

### Description of Operations
#### 1. Counting the Number of Sign Changes
A sign change occurs when the sign of two adjacent elements differs (for example, a positive value changes to negative or vice versa). Zero is considered a positive number when counting sign changes.

#### 2. Calculating the Product of Elements Between the First and Second Zero
You need to find the first and second zeros in the array. If there are elements between them, their product is calculated. If there are no elements between the zeros (for example, the zeros are adjacent), the result will be 1.

#### 3. Compressing the Array
You need to remove all elements that are equal to P. After removing these elements, the remaining elements should be shifted to the left, and the empty positions at the end of the array should be filled with zeros.

### Algorithm
#### Step 1: Count the Number of Sign Changes
- Traverse the array and check each adjacent pair of elements to see if their signs differ (positive/negative). If the sign changes, increment the counter.
#### Step 2: Calculate the Product Between the First and Second Zero
- Find the indices of the first and second zeros in the array.
- Calculate the product of all elements between these zeros. If there are no elements between them, return 1.
#### Step 3: Compress the Array
- Traverse the array and remove all elements equal to P.
- Shift the remaining elements to the left, and fill the empty positions at the end with zeros.
