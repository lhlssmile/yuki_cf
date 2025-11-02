package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

func abs(x int64) int64 {
	if x < 0 {
		return -x
	}
	return x
}

func min(a, b int64) int64 {
	if a < b {
		return a
	}
	return b
}

func cost2(x, y int64) int64 {
	return abs(x - y)
}

func cost3(x, y, z int64) int64 {
	a := []int64{x, y, z}
	sort.Slice(a, func(i, j int) bool { return a[i] < a[j] })
	return abs(a[1]-a[0]) + abs(a[2]-a[1])
}

func solve(a []int64) int64 {
	n := len(a)
	const INF int64 = 1e12
	ans := INF

	// 尝试3个可能的断点
	for cut := 0; cut < 3; cut++ {
		if cut >= n {
			continue
		}

		// 重新排列数组
		re := make([]int64, n)
		for i := 0; i < n; i++ {
			re[i] = a[(i+cut)%n]
		}

		// DP求解
		f := make([]int64, n+1)
		for i := range f {
			f[i] = INF
		}
		f[0] = 0

		for i := 2; i <= n; i++ {
			// 长度为2的块
			f[i] = min(f[i], f[i-2]+cost2(re[i-2], re[i-1]))
			// 长度为3的块
			if i >= 3 {
				f[i] = min(f[i], f[i-3]+cost3(re[i-3], re[i-2], re[i-1]))
			}
		}

		ans = min(ans, f[n])
	}

	return ans
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	t, _ := strconv.Atoi(scanner.Text())

	for i := 0; i < t; i++ {
		scanner.Scan()
		n, _ := strconv.Atoi(scanner.Text())

		scanner.Scan()
		line := scanner.Text()
		parts := strings.Fields(line)
		a := make([]int64, n)
		for j := 0; j < n; j++ {
			a[j], _ = strconv.ParseInt(parts[j], 10, 64)
		}

		fmt.Println(solve(a))
	}
}
