import numpy as np

from cppcounter_C import HashTable


class Counter(HashTable):
    def __init__(self, keys: np.ndarray, capacity: int = 0, capacity_factor: float = 1.75):
        assert isinstance(keys, np.ndarray), "Keys must be of type numpy.ndarray"
        assert capacity_factor > 1.0, "Capacity factor must be greater than 1.0"

        # Dynamically determine hashtable capacity if not provided
        if capacity == 0:
            capacity = int(keys.size * capacity_factor) 
        assert capacity > keys.size, "Capacity must be greater than size of keyset"

        super().__init__(keys, capacity)

    def count(self, keys, threads: int = 0):
        assert isinstance(keys, np.ndarray), "Keys must be of type numpy.ndarray"
        super().count(keys, threads)

    def __getitem__(self, keys, threads: int = 0):
        assert isinstance(keys, np.ndarray), "Keys must be of type numpy.ndarray"
        return super().get(keys)

