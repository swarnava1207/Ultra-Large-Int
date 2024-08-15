# Modify this file to implement the count_pairs_file function
# using ultra-large integers in C/C++.
from ctypes import *
def read_file(filename: str) -> tuple[list[int], int]:
    with open(filename) as file:
        # First line is the target
        target = int(file.readline())
        # Second line is the number of integers
        n = int(file.readline())
        # Read the n integers and return them as a list
        return ([int(file.readline()) for _ in range(n)], target)


def count_pairs(data: list[int], target: int) -> int:
    """Count the number of pairs of
    list indices i < j such that
    data[i] - data[j] = target.
    Time complexity: Naive O(n^2).
    """
    result = 0
    n = len(data)
    for i in range(n - 1):
        for j in range(i + 1, n):
            if data[i] - data[j] == target:
                result += 1
    return result


def test_count_pairs():
    # Simple correctness tests
    assert count_pairs([1, 2, 3, 4, 5], 1) == 0
    assert count_pairs([5, 4, 3, 2, 1], 1) == 4
    assert count_pairs([1, 2, 3, 4, 5], -3) == 2
    # Test with huge integers
    assert count_pairs([10**20 + 2, 10**20 + 1, 10**20], 1) == 2
    print("count_pairs.py: All tests passed")


def count_pairs_file(filename: str) -> int:
    data, target = read_file(filename)
    C_library = CDLL(r"\home\swarn\DSA\count_pairs.so")

    count_pairs_c = C_library.main
    count_pairs_c.argtypes = [c_int,c_void_p]
    count_pairs_c.restype = [c_wchar_p]

    return count_pairs_c(len(data) + 2," ".join(data) +" " + str(target))
count_pairs_file("inputs.txt")