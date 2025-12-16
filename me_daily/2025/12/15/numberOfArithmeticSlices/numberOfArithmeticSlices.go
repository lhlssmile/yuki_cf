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
	defer writer.Flush() //main() 结束时自动调用
	n, _ := strconv.Atoi(readLine())
	if n < 3 {
		fmt.Fprintln(writer, 0)
		return
	}
	a := readInts()
	ans, cur := 0, 0
	for i := 2; i < n; i++ {
		if a[i-1]-a[i-2] == a[i]-a[i-1] {
			cur++
		} else {
			cur = 0
		}

		ans += cur
	}
	fmt.Fprintln(writer, ans)
	// fastPrintInts(arr) // 高性能输出
}
