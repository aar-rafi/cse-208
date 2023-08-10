def compare_files(file1_path, file2_path):
    with open(file1_path, "r") as file1, open(file2_path, "r") as file2:
        lines1 = file1.readlines()
        lines2 = file2.readlines()

        if len(lines1) != len(lines2):
            return False

        for line1, line2 in zip(lines1, lines2):
            if line1.strip() != line2.strip():
                return False

    return True


if __name__ == "__main__":
    file1_path = "out_avl.txt"
    file2_path = "./testio/io3/out_avl.txt"

    are_same = compare_files(file1_path, file2_path)

    if are_same:
        print("The two files are identical.")
    else:
        print("The two files are different.")
