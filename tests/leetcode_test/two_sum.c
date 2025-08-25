// Problem Name: Two Sum
// Description: Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// You can return the answer in any order.

/*
Python Solution (from LeetCode discussions):
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        hashmap = {}
        for i in range(len(nums)):
            complement = target - nums[i]
            if complement in hashmap:
                return [hashmap[complement], i]
            hashmap[nums[i]] = i
*/

#include <stdio.h>
#include <stdlib.h>
#include "hash_map.h"

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashMap* map = create_hash_map(16);
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int index;
        if (hash_map_get(map, complement, &index)) {
            result[0] = index;
            result[1] = i;
            hash_map_free(&map);
            return result;
        }
        hash_map_put(map, nums[i], i);
    }

    hash_map_free(&map);
    free(result);
    *returnSize = 0;
    return NULL; // No solution found
}

int main() {
    // Test Case 1
    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    int returnSize1;
    int* result1 = twoSum(nums1, 4, target1, &returnSize1);
    printf("Test Case 1: [%d, %d]\n", result1[0], result1[1]); // Expected: [0, 1]
    free(result1);

    // Test Case 2
    int nums2[] = {3, 2, 4};
    int target2 = 6;
    int returnSize2;
    int* result2 = twoSum(nums2, 3, target2, &returnSize2);
    printf("Test Case 2: [%d, %d]\n", result2[0], result2[1]); // Expected: [1, 2]
    free(result2);

    // Test Case 3
    int nums3[] = {3, 3};
    int target3 = 6;
    int returnSize3;
    int* result3 = twoSum(nums3, 2, target3, &returnSize3);
    printf("Test Case 3: [%d, %d]\n", result3[0], result3[1]); // Expected: [0, 1]
    free(result3);

    return 0;
}