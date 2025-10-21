package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
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

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func solve(a []int, k, op int) int {
	cnt := make(map[int]int)
	diff := make(map[int]int)

	for _, x := range a {
		cnt[x]++
		diff[x-k]++
		diff[x+k+1]--
	}

	keys := make([]int, 0, len(diff))
	for x := range diff {
		keys = append(keys, x)
	}
	sort.Ints(keys)

	ans, sumD := 0, 0
	for _, x := range keys {
		sumD += diff[x]
		ans = max(ans, min(sumD, cnt[x]+op))
	}
	return ans
}

func main() {
	defer writer.Flush()

	// ✅ 一行读取 n k op
	header := readInts()
	_, k, op := header[0], header[1], header[2]

	// ✅ 再读一行数组 a
	a := readInts()

	fmt.Fprintln(writer, solve(a, k, op))
}
