import sys

# Initialize variables of each type
my_int: int = 0
my_str: str = ""
my_float: float = 0.00
my_bool: bool = False
my_list: list = []
my_tuple: tuple = ()
my_dict: dict = {}

# Print the size of each type
print(f"Size of int : {sys.getsizeof(my_int)} octets")
print(f"Size of str : {sys.getsizeof(my_str)} octets")
print(f"Size of float : {sys.getsizeof(my_float)} octets")
print(f"Size of bool : {sys.getsizeof(my_bool)} octets")
print(f"Size of list : {sys.getsizeof(my_list)} octets")
print(f"Size of tuple : {sys.getsizeof(my_tuple)} octets")
print(f"Size of dict : {sys.getsizeof(my_dict)} octets")
