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
type Result struct {
	left, right int
}

func check(vi, n int, a []int, k int) Result {
	s := make([]int, n+1)
	res := Result{0, 0}
	
	for i := 1; i <= n; i++ {
		val := -1
		if a[i] >= vi {
			val = 1
		}
		s[i] = s[i-1] + val
	}
	
	pos := 0
	for i := k; i <= n; i++ {
		if s[i-k] < s[pos] {
			pos = i - k
		}
		if s[i]-s[pos] >= 0 {
			res.left = pos + 1
			res.right = i
			return res
		}
	}
	return res
}

func solve(a []int, n, k int) {
	lo, hi, ans := 1, n, 0
	finalRes := Result{0, 0}
	
	for lo <= hi {
		vi := lo + (hi-lo)/2
		lr := check(vi, n, a, k)
		if lr.left > 0 {
			ans = vi
			finalRes = lr
			lo = vi + 1
		} else {
			hi = vi - 1
		}
	}
	fmt.Printf("%d %d %d\n", ans, finalRes.left, finalRes.right)
}
func main() {
	defer writer.Flush() //main() 结束时自动调用
	t, _ := strconv.Atoi(readLine())
	for ; t > 0; t-- {
		header := readInts()
		n, k := header[0], header[1]
		ar := readInts()
		a := make([]int, n+1)
		for i := 1; i <= n; i++ {
			a[i] = ar[i-1]
		}
		solve(a, n, k)
	}
}
