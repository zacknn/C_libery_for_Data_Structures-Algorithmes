// Problem Name: Merge Two Sorted Lists
// Description: You are given the heads of two sorted linked lists list1 and list2.
// Merge the two lists into one sorted list. The list should be made by splicing together the nodes of the first two lists.
// Return the head of the merged linked list.

/*
Python Solution (from LeetCode discussions):
class Solution:
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode()
        current = dummy
        while list1 and list2:
            if list1.val < list2.val:
                current.next = list1
                list1 = list1.next
            else:
                current.next = list2
                list2 = list2.next
            current = current.next
        current.next = list1 if list1 else list2
        return dummy.next
*/

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

Node* mergeTwoLists(Node* list1, Node* list2) {
    Node* dummy = create_node(0);
    Node* current = dummy;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            current->next = list1;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }

    current->next = (list1 != NULL) ? list1 : list2;

    Node* merged = dummy->next;
    free(dummy);
    return merged;
}

int main() {
    // Test Case 1
    Node* list1 = NULL;
    append_node_At_End(&list1, 1);
    append_node_At_End(&list1, 2);
    append_node_At_End(&list1, 4);

    Node* list2 = NULL;
    append_node_At_End(&list2, 1);
    append_node_At_End(&list2, 3);
    append_node_At_End(&list2, 4);

    Node* merged1 = mergeTwoLists(list1, list2);
    printf("Test Case 1: ");
    print_linked_list(merged1); // Expected: [1 1 2 3 4 4]
    free_linked_list(&merged1);

    // Test Case 2
    Node* list3 = NULL;
    Node* list4 = NULL;
    Node* merged2 = mergeTwoLists(list3, list4);
    printf("Test Case 2: ");
    print_linked_list(merged2); // Expected: List is empty
    free_linked_list(&merged2);

    // Test Case 3
    Node* list5 = NULL;
    append_node_At_End(&list5, 0);

    Node* list6 = NULL;
    Node* merged3 = mergeTwoLists(list5, list6);
    printf("Test Case 3: ");
    print_linked_list(merged3); // Expected: [0]
    free_linked_list(&merged3);

    return 0;
}