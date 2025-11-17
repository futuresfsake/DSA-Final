🌿 Parent Pointer Implementation — Operations

initTree() – Initialize the tree with parent values.

getRoot() – Find the node whose parent is -1.

getParent(node) – Return the parent of a given node.

getChildren(node) – List all nodes whose parent equals the given node.

getSiblings(node) – List all nodes that share the same parent.

isRoot(node) – Check if a node is the root.

preorder(node) – Visit the node, then recursively visit its children.

postorder(node) – Visit all children first, then the node.

depth(node) – Count how many steps it takes to reach the root (distance from root).

height(node) – (Optional) Compute the height of the subtree rooted at the node.

🌳 List of Children Implementation — Operations

initTree() – Initialize an array of child lists for each node.

getRoot() – Identify the node that isn’t listed as a child of any node.

getChildren(node) – Return all children in the node’s list.

getParent(node) – Find which node’s child list contains the given node.

addChild(parent, child) – Insert a new child into a parent’s list.

deleteChild(parent, child) – Remove a child from the parent’s list.

preorder(node) – Visit node, then recursively traverse its child lists.

postorder(node) – Visit all children first, then the node.

printTree() – Display each node and its children.