package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func reverse(s string) string {
	runes := []rune(s)
	for i, j := 0, len(runes)-1; i < j; i, j = i+1, j-1 {
		runes[i], runes[j] = runes[j], runes[i]
	}
	return string(runes)
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	t, _ := strconv.Atoi(scanner.Text())

	for i := 0; i < t; i++ {
		scanner.Scan()
		n, _ := strconv.ParseInt(scanner.Text(), 10, 64)
		binary := fmt.Sprintf("%b", n)
		ans := "NO"

		for length := 1; length < 64; length++ {
			if len(binary) <= length {
				// Pad with leading zeros
				padded := strings.Repeat("0", length-len(binary)) + binary

				// Check if palindrome
				isPalindrome := padded == reverse(padded)

				valid := isPalindrome

				// If odd length, middle bit must be 0
				if length%2 == 1 {
					middleChar := padded[length/2]
					valid = valid && middleChar == '0'
				}

				if valid {
					ans = "YES"
					break
				}
			}
		}

		fmt.Println(ans)
	}
}
