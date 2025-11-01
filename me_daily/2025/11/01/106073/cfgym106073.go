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

// 输出整数切片，空格分隔
func printInts(arr []int) {
	if len(arr) == 0 {
		fmt.Fprintln(writer)
		return
	}
	for i, v := range arr {
		if i > 0 {
			fmt.Fprint(writer, " ")
		}
		fmt.Fprint(writer, v)
	}
	fmt.Fprintln(writer)
}

// 高性能版本，使用strings.Builder
func fastPrintInts(arr []int) {
	if len(arr) == 0 {
		fmt.Fprintln(writer)
		return
	}
	var sb strings.Builder
	for i, v := range arr {
		if i > 0 {
			sb.WriteByte(' ')
		}
		sb.WriteString(strconv.Itoa(v))
	}
	fmt.Fprintln(writer, sb.String())
}

// 泛型版本，支持任意类型
func printSlice[T any](arr []T) {
	if len(arr) == 0 {
		fmt.Fprintln(writer)
		return
	}
	for i, v := range arr {
		if i > 0 {
			fmt.Fprint(writer, " ")
		}
		fmt.Fprint(writer, v)
	}
	fmt.Fprintln(writer)
}

func main() {
	defer writer.Flush() // main() 结束时自动调用

	// 读取输入
	nums := readInts()
	n, q := nums[0], nums[1]
	x := readInts()

	const MOD = 1000000007
	const REV2 = (MOD + 1) / 2 // 2的模逆元

	cur := 0
	ans := make([]int, n+1)

	// 从右往左处理
	for i := q - 1; i >= 0; i-- {
		v := x[i]
		ans[v] = (ans[v] + cur*REV2) % MOD
		cur = (cur + v) * REV2 % MOD
	}
	ans[1] = (ans[1] + cur) % MOD

	// 输出结果（跳过索引0）
	for i := 1; i <= n; i++ {
		fmt.Fprintln(writer, ans[i])
	}
}
