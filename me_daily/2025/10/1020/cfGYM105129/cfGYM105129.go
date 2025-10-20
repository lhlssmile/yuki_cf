package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strconv"
	"strings"
)

var reader = bufio.NewReader(os.Stdin)
var writer = bufio.NewWriter(os.Stdout)

func readLine() string {
	s, _ := reader.ReadString('\n')
	return strings.TrimSpace(s)
}

var (
	toCheck []int64
)
var pre = []int{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}

func init() {
	toCheck = []int64{1}
	for _, x := range pre {
		k := len(toCheck)
		for i := 0; i < k; i++ {
			newVal := toCheck[i] * int64(x)
			toCheck = append(toCheck, newVal)
		}
	}
	slices.Sort(toCheck)
}

func readInts() []int {
	fields := strings.Fields(readLine())
	res := make([]int, len(fields))
	for i, f := range fields {
		res[i], _ = strconv.Atoi(f)
	}
	return res
}

func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func main() {
	defer writer.Flush()
	t, _ := strconv.Atoi(readLine())
	for ; t > 0; t-- {
		n, _ := strconv.Atoi(readLine())
		vis := make([]int, 51)
		nums := readInts()
		a := make([]int, n)
		for i := 0; i < n; i++ {
			a[i] = nums[i]
			vis[a[i]] = 1
		}

		for _, v := range toCheck {
			ok := true
			for i := 2; i <= 50; i++ {
				if vis[i] == 1 && gcd(int64(i), v) == 1 {
					ok = false
					break
				}
			}
			if ok {
				fmt.Fprintln(writer, v)
				break
			}
		}
	}
}
