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
	header := readInts()
	m, n, k := header[0], header[1], header[2]
	grid := make([][]int, m)
	for i := range grid {
		grid[i] = make([]int, n)
	}
	for i := 0; i < m; i++ {
		gi := readInts()
		for j := 0; j < n; j++ {
			grid[i][j] = gi[j]
		}
	}
	f := make([][]int, n+1)
	for i := range f {
		f[i] = make([]int, k+1)
	}
	f[1][0] = 1
	const MOD int = 1_000_000_007
	newF := make([]int, k+1)
	for _, row := range grid {
		for j := 0; j < n; j++ {
			for s := 0; s < k; s++ {
				newS := (s + row[j]) % k
				newF[s] = (f[j+1][newS] + f[j][newS]) % MOD
			}
			copy(f[j+1], newF) //保存上一行的状态
		}
	}
	fmt.Fprintln(writer, f[n][0])
}
