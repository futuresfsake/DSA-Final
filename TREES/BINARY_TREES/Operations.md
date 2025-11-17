🌳 Binary Tree — Basic Operations
Operation	Description
initTree()	Initialize the binary tree (e.g., set root = NULL).
createNode(data)	Create a new node containing a value, with left and right = NULL.
insert(root, data)	Insert a new node into the tree (depends on type — BST, heap, etc.).
isEmpty(root)	Check if the tree is empty.
getRoot()	Return the root node.
🌿 Access & Relationships
Operation	Description
getLeft(node)	Return the left child of a node.
getRight(node)	Return the right child of a node.
getParent(node) (optional)	Return the parent (if parent pointer or recursion is maintained).
isLeaf(node)	Check if a node has no children.
🌼 Traversal Operations
Operation	Description
preorder(root)	Visit root → left → right.
inorder(root)	Visit left → root → right (for BST, gives sorted order).
postorder(root)	Visit left → right → root.
levelOrder(root)	Visit nodes level by level (uses a queue).
🌲 Computation / Structural Operations
Operation	Description
countNodes(root)	Return the total number of nodes in the tree.
countLeaves(root)	Return the number of leaf nodes.
height(root)	Compute the height (max depth) of the tree.
depth(node)	Compute the distance of a node from the root.
isBalanced(root)	Check if the height difference between left and right subtrees ≤ 1.
mirror(root)	Swap left and right subtrees recursively.
🍃 Search and Deletion (for Binary Search Trees)
Operation	Description
search(root, key)	Find a node containing the given key.
deleteNode(root, key)	Remove a node while maintaining BST properties.
findMin(root)	Return the node with the smallest value.
findMax(root)	Return the node with the largest value.