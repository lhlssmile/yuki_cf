package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

var in = bufio.NewReader(os.Stdin)
var out = bufio.NewWriter(os.Stdout)

func nextInt() int {
	var x int
	fmt.Fscan(in, &x)
	return x
}

func nextInt64() int64 {
	var x int64
	fmt.Fscan(in, &x)
	return x
}

func main() {
	defer out.Flush()

	t := nextInt()
	for ; t > 0; t-- {
		n, m, q := nextInt(), nextInt(), nextInt()

		a := make([]int64, n)
		for i := range a {
			a[i] = nextInt64()
		}
		sort.Slice(a, func(i, j int) bool { return a[i] > a[j] })

		b := make([]int64, m)
		for i := range b {
			b[i] = nextInt64()
		}
		sort.Slice(b, func(i, j int) bool { return b[i] > b[j] })

		prefixA := make([]int64, n+1)
		for i := 0; i < n; i++ {
			prefixA[i+1] = prefixA[i] + a[i]
		}

		prefixB := make([]int64, m+1)
		for i := 0; i < m; i++ {
			prefixB[i+1] = prefixB[i] + b[i]
		}

		for ; q > 0; q-- {
			x, y, z := nextInt(), nextInt(), nextInt()

			if z == 0 {
				fmt.Fprintln(out, 0)
				continue
			}

			L := max(0, z-y)
			R := min(z, x)
			if L > R {
				fmt.Fprintln(out, 0)
				continue
			}

			best := int64(0)
			for k := L; k <= R; k++ {
				sum := prefixA[k] + prefixB[z-k]
				if sum > best {
					best = sum
				}
			}
			fmt.Fprintln(out, best)
		}
	}
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
