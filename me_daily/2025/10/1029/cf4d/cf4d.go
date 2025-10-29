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

type Envelope struct {
	w, h, idx int
}

func main() {
	defer writer.Flush()

	// 读取输入
	header := readInts()
	n, w, h := header[0], header[1], header[2]
	var envs []Envelope
	for i := 0; i < n; i++ {
		r := readInts()
		wi, hi := r[0], r[1]
		// 只考虑能放下卡片的信封
		if wi > w && hi > h {
			envs = append(envs, Envelope{wi, hi, i + 1})
		}
	}

	if len(envs) == 0 {
		fmt.Fprintln(writer, 0)
		return
	}

	// 按宽度排序
	sort.Slice(envs, func(i, j int) bool {
		return envs[i].w < envs[j].w
	})

	m := len(envs)
	dp := make([]int, m)
	parent := make([]int, m)

	// 初始化
	for i := 0; i < m; i++ {
		dp[i] = 1
		parent[i] = -1
	}

	// DP求最长递增子序列
	for i := 1; i < m; i++ {
		for j := 0; j < i; j++ {
			// 当前信封的宽高都要严格大于前一个
			if envs[i].w > envs[j].w && envs[i].h > envs[j].h {
				if dp[j]+1 > dp[i] {
					dp[i] = dp[j] + 1
					parent[i] = j
				}
			}
		}
	}

	// 找到最长链的结尾
	maxLen := 0
	endIdx := 0
	for i := 0; i < m; i++ {
		if dp[i] > maxLen {
			maxLen = dp[i]
			endIdx = i
		}
	}

	// 重构路径
	var path []int
	idx := endIdx
	for idx != -1 {
		path = append(path, envs[idx].idx)
		idx = parent[idx]
	}

	// 反转路径
	for i, j := 0, len(path)-1; i < j; i, j = i+1, j-1 {
		path[i], path[j] = path[j], path[i]
	}

	fmt.Fprintln(writer, maxLen)
	for i, v := range path {
		if i > 0 {
			fmt.Fprint(writer, " ")
		}
		fmt.Fprint(writer, v)
	}
	fmt.Fprintln(writer)
}
