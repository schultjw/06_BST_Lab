06_BST_Lab
==============

Implement a binary search tree in C++

Requirements
------------

1. All methods except the destructor and `size()` should be O(h), where h is the height of the tree
2. `size()` should be O(n)

Reading
=======
"Open Data Structures," Chapter 6, the entire chapter. http://opendatastructures.org/ods-cpp/6_Binary_Trees.html

Questions
=========

#### 1. Which of the above requirements work, and which do not? For each requirement, write a brief response.

1. Works. Worst case scenario, they follow the longest route to the bottom of the tree in O(h) time.
2. Works. size needs to touch every node in the tree, so it is O(n).

#### 2. Do exercises 6.7 and 6.9 on http://opendatastructures.org/ods-cpp/6_3_Discussion_Exercises.html. Keep in mind: You do NOT need to write real working code, you may write pseudo-code. In fact, that is preferred.

6.7
preOrderNumber(node, number){
 if node == null return
 node.number = number
 preOrderNumber(node.left, number+1)
 preOrderNumber(node.right.number+1)
}
inOrderNumber(node, number)[
 if node == null return
 inOrderNumber(node.left, number+1)
 node.number = number
 inOrdernumber(node.right, number+1)
}
postOrderNumber(node, number)
 if node == null return
 postOrderNumber(node.left, number+1)
 postOrderNumber(node.right, number+1)
 node.number = number
}

6.9
6.9.1 post order number associated with the node is the size of the subtree.
6.9.2 pre order number of the min node plus 1 is the depth. 
		`min(u).pre + 1`
6.9.3 ancestors come before descendents in preorder, and vice versa in postorder. so 
	`return (u.pre < w.pre && u.post > w.post)`
#### 3. What is one question that confused you about this exercise, or one piece of advice you would share with students next semester?

It's hard to figure out what to do in some of these functions until you recognize the recursiveness inherent in navigating the tree.