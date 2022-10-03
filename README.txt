1. Run 'dmood_hw2.c' file.
   gcc -o dmood_hw2 dmood_hw2.c

2. Run 'dmood_hw2' executable file.
   ./dmood_hw2
3. Run executable file with given options:
    -S: List all files with size, permissions and last access time.
        ./dmood_hw2 -S ./
    -s: List all files with file size less than or equal to the value specified.
	./dmood_hw2 -s <max_size> <path>
    -f: List all files with specified conditions in documentation
	./dmood_hw2 -f <string_pattern> <depth>

