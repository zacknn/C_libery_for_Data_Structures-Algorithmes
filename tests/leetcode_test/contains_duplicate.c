// Problem Name: Contains Duplicate
// Description: Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

/*
Python Solution (from LeetCode discussions):
class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        seen = set()
        for num in nums:
            if num in seen:
                return True
            seen.add(num)
        return False
*/

#include <stdio.h>
#include <stdlib.h>
#include "hash_set.h"

int containsDuplicate(int* nums, int numsSize) {
    HashSet* set = create_hash_set(16);
    for (int i = 0; i < numsSize; i++) {
        if (hash_set_contains(set, nums[i])) {
            hash_set_free(&set);
            return 1;
        }
        hash_set_add(set, nums[i]);
    }
    hash_set_free(&set);
    return 0;
}

int main() {
    // Test Case 1
    int nums1[] = {1, 2, 3, 1};
    printf("Test Case 1: %d\n", containsDuplicate(nums1, 4)); // Expected: 1

    // Test Case 2
    int nums2[] = {1, 2, 3, 4};
    printf("Test Case 2: %d\n", containsDuplicate(nums2, 4)); // Expected: 0

    // Test Case 3
    int nums3[] = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    printf("Test Case 3: %d\n", containsDuplicate(nums3, 10)); // Expected: 1

    return 0;
}