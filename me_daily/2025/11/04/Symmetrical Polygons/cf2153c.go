package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
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
	t, _ := strconv.Atoi(readLine())

	for ; t > 0; t-- {
		_, _ = strconv.Atoi(readLine()) // 喵~ 两个_，忽略值和错误！  // 喵~ 忽略n，读了但不存！
		a := readInts()
		cnt := make(map[int]int)
		for _, x := range a {
			cnt[x]++
		}
		var base int64 = 0
		odd, even := []int{}, []int{}

		for x, c := range cnt {
			base += int64(x) * int64(c/2)
			if c&1 == 1 {
				odd = append(odd, x)
			} else if c >= 2 {
				even = append(even, x)
			}
		}
		if base == 0 {
			fmt.Fprintln(writer, 0)
			continue
		}
		var ans int64 = 0
		for _, x := range odd {
			if 2*base > int64(x) {
				ans = max(ans, base<<1+int64(x))
			}
		}
		slices.Sort(odd)
		for i := 1; i < len(odd); i++ {
			if int64(odd[i-1])+2*base > int64(odd[i]) {
				ans = max(ans, int64(odd[i-1])+2*base+int64(odd[i]))
			}
		}
		for _, x := range even {
			if base-int64(x) > 0 {
				ans = max(ans, 2*base)
			}
		}
		fmt.Fprintln(writer, ans)
	}
	// fastPrintInts(arr) // 高性能输出  <- 这个arr没定义，建议删掉或修复哦
}
