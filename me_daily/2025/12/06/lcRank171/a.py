import math

class Solution:
    def isPrime(self, n: int) -> bool:
        if n <= 1:
            return False
        if n == 2 or n == 3:
            return True
        if n % 2 == 0 or n % 3 == 0:
            return False
        i = 5
        while i * i <= n:
            if n % i == 0 or n % (i + 2) == 0:
                return False
            i += 6
        return True
    
    def isFullPrime(self, num: int) -> bool:
        s = str(num)
        n = len(s)
        
        # 生成前缀
        prefixes = []
        for i in range(1, n + 1):
            prefix = int(s[:i])
            prefixes.append(prefix)
        
        # 生成后缀
        suffixes = []
        for i in range(1, n + 1):
            suffix = int(s[-i:])
            suffixes.append(suffix)
        
        # 检查所有
        all_primes = True
        for p in prefixes + suffixes:
            if not self.isPrime(p):
                all_primes = False
                break
        
        return all_primes