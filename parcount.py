from mpi4py import MPI
import sys
import re
from collections import Counter
import time

def analyze_text(chunk):
    char_count = Counter()
    word_count = Counter()
    word_pattern = re.compile(r'[a-zA-Z0-9]{1,62}')

    for line in chunk:
        for char in line:
            if 32 <= ord(char) <= 126:
                char_count[char] += 1
        words = word_pattern.findall(line)
        for word in words:
            word_count[word.lower()] += 1

    return char_count, word_count

def main():
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    size = comm.Get_size()

    if len(sys.argv) != 2:
        print("Check")
        sys.exit(1)

    input_file = sys.argv[1]
    with open(input_file, 'r') as f:
        lines = f.readlines()
    chunk_size = len(lines) // size
    chunk = lines[rank * chunk_size:(rank + 1) * chunk_size] if rank < size - 1 else lines[rank * chunk_size:]

    start_time = time.time()
    local_char_count, local_word_count = analyze_text(chunk)
    total_char_count = comm.reduce(local_char_count, op=MPI.SUM, root=0)
    total_word_count = comm.reduce(local_word_count, op=MPI.SUM, root=0)

    if rank == 0:
        top_chars = total_char_count.most_common(10)
        print("========= Top 10 Characters =========")
        print("Ch\tFreq")
        print("-------------------------------------")
        for char, count in top_chars:
            print(f"{char}\t{count}")

        top_words = total_word_count.most_common(10)
        word_id_map = {}
        current_id = 1

        for line in lines:
            for word in re.findall(r'[a-zA-Z0-9]{1,62}', line.lower()):
                if word not in word_id_map:
                    word_id_map[word] = current_id
                    current_id += 1

        print("\n=========== Top 10 Words ============")
        print("Word\t\tID\tFreq")
        print("-------------------------------------")
        for word, count in top_words:
            print(f"{word:<15}\t{word_id_map.get(word, 'N/A')}\t{count}")

        print(f"\nExecution time: {time.time() - start_time:.6f} seconds")

if __name__ == "__main__":
    main()

