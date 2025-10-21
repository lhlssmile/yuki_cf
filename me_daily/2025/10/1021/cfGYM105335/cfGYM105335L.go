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

func main() {
	defer writer.Flush()
	nStr := readLine()
	n, _ := strconv.Atoi(nStr)
	a := readInts()

	if n == 1 {
		fmt.Fprintln(writer, 1)
		return
	}
	if n == 2 {
		// 简单：交换或偏移，[1,2]→[2,1]
		fmt.Fprintln(writer, 3-a[0], 3-a[1])
		return
	}

	// 前两个计算（模拟k1,k2偏移）
	tmp := []int{a[0] - 1, a[1] - 1}
	if tmp[1] > tmp[0] { // 修正：原if tmp[1] > tmp[0]
		tmp[1]--
	}
	tmp[1] += n * (n - 1) / 2
	tmp[0] += tmp[1] / (n - 1)
	tmp[1] %= (n - 1) // 加这步！否则tmp[1]超
	tmp[0] %= n
	ans := []int{tmp[0] + 1, tmp[1] + 1} // 从空slice起步，len=2
	if ans[1] >= ans[0] {
		ans[1]++
	}

	// 标记（vis1: p后缀值出现；vis2: q可用=1）
	vis1 := make([]int, n+1)  // 默认0=未出现
	vis2 := make([]int, n+1)  // 默认0=不可用
	for i := 1; i <= n; i++ { // 修正：1~n set1
		vis2[i] = 1
	}
	for i := 2; i < n; i++ {
		vis1[a[i]] = 1
	}
	for _, x := range ans[:2] { // 只前两个，修正range
		if x <= n { // 防x>n
			vis2[x] = 0
		}
	}

	// 映射（双指针配对剩余）
	mapping := make([]int, n+1)
	p1, p2 := 1, 1
	for i := 0; i < n-2; i++ {
		for p1 <= n && vis1[p1] == 0 { // 加p1<=n 防越界
			p1++
		}
		for p2 <= n && vis2[p2] == 0 {
			p2++
		}
		if p1 > n || p2 > n { // 安全break，虽不该发生
			break
		}
		mapping[p1] = p2
		p1++
		p2++
	}

	// 后缀append
	for i := 2; i < n; i++ {
		ans = append(ans, mapping[a[i]])
	}

	// 输出一行空格
	for i, x := range ans {
		if i > 0 {
			fmt.Fprint(writer, " ")
		}
		fmt.Fprint(writer, strconv.Itoa(x))
	}
	fmt.Fprintln(writer)
}
