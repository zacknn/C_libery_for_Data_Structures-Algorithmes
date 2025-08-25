// Problem Name: Valid Parentheses
// Description: Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
// An input string is valid if:
// 1. Open brackets must be closed by the same type of brackets.
// 2. Open brackets must be closed in the correct order.
// 3. Every close bracket has a corresponding open bracket of the same type.

/*
Python Solution (from LeetCode discussions):
class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        mapping = {')': '(', '}': '{', ']': '['}
        for char in s:
            if char in mapping:
                top_element = stack.pop() if stack else '#'
                if mapping[char] != top_element:
                    return False
            else:
                stack.append(char)
        return not stack
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

int isValid(char * s) {
    Stack* stack = create_stack(strlen(s));
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            push(stack, s[i]);
        } else {
            if (stack_is_empty(stack)) {
                free_stack(stack);
                return 0;
            }
            int top = pop(stack);
            if ((s[i] == ')' && top != '(') ||
                (s[i] == '}' && top != '{') ||
                (s[i] == ']' && top != '[')) {
                free_stack(stack);
                return 0;
            }
        }
    }
    int empty = stack_is_empty(stack);
    free_stack(stack);
    return empty;
}

int main() {
    // Test Case 1
    char* s1 = "()";
    printf("Test Case 1: %d\n", isValid(s1)); // Expected: 1

    // Test Case 2
    char* s2 = "()[]{}";
    printf("Test Case 2: %d\n", isValid(s2)); // Expected: 1

    // Test Case 3
    char* s3 = "(]";
    printf("Test Case 3: %d\n", isValid(s3)); // Expected: 0

    // Test Case 4
    char* s4 = "([)]";
    printf("Test Case 4: %d\n", isValid(s4)); // Expected: 0

    // Test Case 5
    char* s5 = "{[]}";
    printf("Test Case 5: %d\n", isValid(s5)); // Expected: 1

    return 0;
}