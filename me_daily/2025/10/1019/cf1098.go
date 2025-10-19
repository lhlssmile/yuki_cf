package main

import (
	"bufio"
	"fmt"
	"math"
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

func readInt64s() []int64 {
	fields := strings.Fields(readLine())
	res := make([]int64, len(fields))
	for i, f := range fields {
		res[i], _ = strconv.ParseInt(f, 10, 64)
	}
	return res
}

func min(a, b int64) int64 {
	if a < b {
		return a
	}
	return b
}

var (
	bad    bool
	parent []int
	ans    int64
	graph  [][]int
	s      []int64
)

func dfs(u, p int) {
	if s[u] == -1 {
		if len(graph[u]) == 0 {
			s[u] = s[p]
		} else {
			mn := int64(math.MaxInt64)
			for _, v := range graph[u] {
				mn = min(mn, s[v])
			}
			if mn < s[p] {
				bad = true
				return
			}
			s[u] = mn
		}
	}
	ans += s[u] - s[p]
	for _, v := range graph[u] {
		dfs(v, u)
	}
}

func main() {
	defer writer.Flush()

	n, _ := strconv.Atoi(readLine())

	// 预分配slice，类似resize
	parent = make([]int, n+1)
	graph = make([][]int, n+1)
	for i := range graph {
		graph[i] = make([]int, 0)
	}
	s = make([]int64, n+1)

	// 读parent[2]到parent[n]
	parentVals := readInts()
	for i := 0; i < n-1; i++ {
		parent[i+2] = parentVals[i]
		graph[parentVals[i]] = append(graph[parentVals[i]], i+2)
	}

	// 读s[1]到s[n]
	sVals := readInt64s()
	for i := 0; i < n; i++ {
		s[i+1] = sVals[i]
	}

	s[0] = 0 // 虚拟根节点
	dfs(1, 0)

	if bad {
		fmt.Fprintln(writer, -1)
	} else {
		fmt.Fprintln(writer, ans)
	}
}
