package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)
var writer = bufio.NewWriter(os.Stdout)

func readLine() string {
	s, _ := reader.ReadString('\n')
	return strings.TrimSpace(s)
}

func readInts() []int {
	fields := strings.Fields(readLine())
	res := make([]int, len(fields))
	for i, f := range fields {
		res[i], _ = strconv.Atoi(f)
	}
	return res
}

var (
	t, n, q int
)

func main() {
	defer writer.Flush()

	t, _ = strconv.Atoi(readLine())
	for ; t > 0; t-- {
		header := readInts()
		n, q = header[0], header[1]
		a := readInts()

		sum0 := make([]int, n+1)
		sum1 := make([]int, n+1)
		diff := make([]int, n+1)

		for i := 0; i < n; i++ {
			sum0[i+1] = sum0[i]
			sum1[i+1] = sum1[i]
			if a[i] == 0 {
				sum0[i+1]++
			} else if a[i] == 1 {
				sum1[i+1]++
			}

			if i > 0 && a[i] != a[i-1] {
				diff[i+1] = diff[i] + 1
			} else {
				diff[i+1] = diff[i]
			}
		}

		for ; q > 0; q-- {
			lr := readInts()
			l, r := lr[0], lr[1]

			z := sum0[r] - sum0[l-1]
			o := sum1[r] - sum1[l-1]

			if z%3 != 0 || o%3 != 0 {
				fmt.Fprintln(writer, -1)
				continue
			}

			ans := z/3 + o/3
			numPairs := r - l
			sw := diff[r] - diff[l]
			if numPairs == sw {
				ans++
			}

			fmt.Fprintln(writer, ans)
		}
	}
}
