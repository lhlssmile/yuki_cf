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

func readInt64s() []int64 {
	fields := strings.Fields(readLine())
	res := make([]int64, len(fields))
	for i, f := range fields {
		res[i], _ = strconv.ParseInt(f, 10, 64)
	}
	return res
}

func max(a, b float64) float64 {
	if a > b {
		return a
	}
	return b
}

func min(a, b float64) float64 {
	if a < b {
		return a
	}
	return b
}

func main() {
	defer writer.Flush()
	n, _ := strconv.Atoi(readLine())
	x := readInt64s()
	v := readInt64s()

	possible := func(t float64) bool {
		lmx := -1e18
		rmx := 1e18
		for i := 0; i < n; i++ {
			left := float64(x[i]) - float64(v[i])*t
			right := float64(x[i]) + float64(v[i])*t
			lmx = max(lmx, left)
			rmx = min(rmx, right)
		}
		return lmx <= rmx
	}
	lo, hi := 0.0, 2e9
	for i := 0; i < 100; i++ {
		mid := (lo + hi) / 2
		if possible(mid) {
			hi = mid
		} else {
			lo = mid
		}
	}
	fmt.Fprintf(writer, "%.12f\n", lo)
}
