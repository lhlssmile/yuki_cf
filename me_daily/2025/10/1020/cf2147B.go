package main

import (
	"fmt"
)

func solve(n int) []int {
	res := make([]int, 2*n)

	// Fill first n positions with n, n-1, ..., 1
	for i := 0; i < n; i++ {
		res[i] = n - i
	}

	// Fill remaining positions
	for x := n; x >= 1; x-- {
		for j := n; j < 2*n; j += x {
			if res[j] == 0 {
				res[j] = x
				break
			}
		}
	}

	return res
}

func main() {
	var t int
	fmt.Scan(&t)

	for t > 0 {
		var n int
		fmt.Scan(&n)

		res := solve(n)

		for i := 0; i < 2*n; i++ {
			if i > 0 {
				fmt.Print(" ")
			}
			fmt.Print(res[i])
		}
		fmt.Println()

		t--
	}
}
