from collections import defaultdict
from typing import List
import sys
from collections import Counter
input = lambda: sys.stdin.readline().strip()
II = lambda: int(input())
LII = lambda: list(map(int, input().split()))
SI = lambda: input()
LSI = lambda: input().split()


vowels = ['a','e','i','o','u']


#  先处理
def count_vowels(word):
    return sum(1 for c in word if c in vowels)

def main():
    s = SI()
    words = s.split()
    if not words:return ""
    else:
        first_word = words[0]
        first_cnt = count_vowels(first_word)

        processed_word = [first_word]

        for w in words[1:]:
            if count_vowels(w) == first_cnt:
                processed_word.append(w[::-1])
            else:processed_word.append(w)
        
    res = ' '.join(processed_word)
    print(res)
