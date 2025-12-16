package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func mulmod(a, b, mod uint64) uint64 {
	res := uint64(0)
	a = a % mod
	for b > 0 {
		if b&1 == 1 {
			if res >= mod-a {
				res = res - (mod - a)
			} else {
				res += a
			}
		}
		if a >= mod-a {
			a = a - (mod - a)
		} else {
			a += a
		}
		b >>= 1

	}
	return res
}

func powmod(a, d, mod uint64) uint64 {
	res := uint64(1)

	for d > 0 {
		if d&1 == 1 {
			res = mulmod(res, a, mod)
		}
		a = mulmod(a, a, mod)
		d >>= 1
	}
	return res
}

func isPrimeMR(n uint64) bool {
	if n < 2 {
		return false
	}
	small := []uint64{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}
	for _, p := range small {
		if n == p {
			return true
		}
		if n%p == 0 {
			return false
		}
	}
	d := n - 1
	s := 0
	for d&1 == 0 {
		d >>= 1
		s++
	}
	bases := []uint64{2, 325, 9375, 28178, 450775, 9780504, 1795265022}
	for _, a := range bases {
		if a >= n { // a % n == 0 if a >= n, but adjust
			a = a % n
			if a == 0 {
				continue
			}
		}
		x := powmod(a, d, n)
		if x == 1 || x == n-1 {
			continue // 通过这轮
		}
		composite := true
		for r := 1; r < s; r++ { // r从1到s-1
			x = mulmod(x, x, n)
			if x == n-1 {
				composite = false
				break
			}
		}
		if composite {
			return false // 复合数！
		}
	}
	return true // 素数！
}

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
	in := readInts()
	a, b, mod := in[0], in[1], in[2]
	fmt.Fprintln(writer, mulmod(uint64(a), uint64(b), uint64(mod)))
	// fastPrintInts(arr) // 高性能输出
}
