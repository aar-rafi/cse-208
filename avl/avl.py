class AVLNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1


class AVLTree:
    def __init__(self):
        self.root = None

    def height(self, node):
        if node is None:
            return 0
        return node.height

    def balance_factor(self, node):
        if node is None:
            return 0
        return self.height(node.left) - self.height(node.right)

    def update_height(self, node):
        if node is None:
            return 0
        node.height = max(self.height(node.left), self.height(node.right)) + 1

    def rotate_left(self, z):
        y = z.right
        T2 = y.left

        y.left = z
        z.right = T2

        self.update_height(z)
        self.update_height(y)

        return y

    def rotate_right(self, y):
        x = y.left
        T2 = x.right

        x.right = y
        y.left = T2

        self.update_height(y)
        self.update_height(x)

        return x

    def rebalance(self, node):
        if node is None:
            return node

        self.update_height(node)

        balance = self.balance_factor(node)

        # Left-Left case
        if balance > 1 and self.balance_factor(node.left) >= 0:
            return self.rotate_right(node)

        # Right-Right case
        if balance < -1 and self.balance_factor(node.right) <= 0:
            return self.rotate_left(node)

        # Left-Right case
        if balance > 1 and self.balance_factor(node.left) < 0:
            node.left = self.rotate_left(node.left)
            return self.rotate_right(node)

        # Right-Left case
        if balance < -1 and self.balance_factor(node.right) > 0:
            node.right = self.rotate_right(node.right)
            return self.rotate_left(node)

        return node

    def insert(self, key):
        self.root = self._insert(self.root, key)

    def _insert(self, node, key):
        if node is None:
            return AVLNode(key)

        if key < node.key:
            node.left = self._insert(node.left, key)
        elif key > node.key:
            node.right = self._insert(node.right, key)
        else:
            return node  # Duplicate keys not allowed

        return self.rebalance(node)

    def find(self, key):
        return self._find(self.root, key)

    def _find(self, node, key):
        if node is None:
            return False
        if node.key == key:
            return True
        elif key < node.key:
            return self._find(node.left, key)
        else:
            return self._find(node.right, key)

    def delete(self, key):
        self.root = self._delete(self.root, key)

    def _delete(self, node, key):
        if node is None:
            return node

        if key < node.key:
            node.left = self._delete(node.left, key)
        elif key > node.key:
            node.right = self._delete(node.right, key)
        else:
            # Node with only one child or no child
            if node.left is None:
                temp = node.right
                node = None
                return temp
            elif node.right is None:
                temp = node.left
                node = None
                return temp

            # Node with two children: Get the inorder successor (smallest in the right subtree)
            temp = self._get_min_value_node(node.right)
            node.key = temp.key
            node.right = self._delete(node.right, temp.key)

        return self.rebalance(node)

    def _get_min_value_node(self, node):
        while node.left is not None:
            node = node.left
        return node

    def traversal(self):
        result = []
        self._in_order_traversal(self.root, result)
        return result

    def _in_order_traversal(self, node, result):
        if node:
            self._in_order_traversal(node.left, result)
            result.append(str(node.key))
            self._in_order_traversal(node.right, result)


def perform_operations(input_file):
    avl_tree = AVLTree()
    output_avl = open("out_avlpy.txt", "w")
    report_avl = open("report_avlpy.txt", "w")

    with open(input_file, "r") as f:
        for line in f:
            operation, value = line.strip().split(" ")

            start_time = time.time()

            if operation == "I":
                avl_tree.insert(int(value))
                output_avl.write("(" + avl_tree.root.__str__() + ")\n")
            elif operation == "D":
                avl_tree.delete(int(value))
                output_avl.write("(" + avl_tree.root.__str__() + ")\n")
            elif operation == "F":
                if avl_tree.find(int(value)):
                    output_avl.write("found\n")
                else:
                    output_avl.write("not found\n")
            elif operation == "T":
                traversal_result = avl_tree.traversal()
                output_avl.write(" ".join(traversal_result) + "\n")

            end_time = time.time()
            elapsed_time = (end_time - start_time) * 1000
            report_avl.write(f"{operation} {elapsed_time:.8f}\n")

    output_avl.close()
    report_avl.close()


if __name__ == "__main__":
    import time

    perform_operations("in.txt")
