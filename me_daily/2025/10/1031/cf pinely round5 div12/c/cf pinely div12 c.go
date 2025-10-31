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

func sum[E ~int | ~float64](s []E) E {
	var total E
	for _, v := range s {
		total += v
	}
	return total
}

func main() {
	defer writer.Flush() //main() 结束时自动调用
	t, _ := strconv.Atoi(readLine())

	for ; t > 0; t-- {
		header := readInts()
		n, x := header[0], header[1]
		prices := readInts()
		sumP := sum(prices)
		levels := sumP / x // 防溢，用int64算levels
		sort.Slice(prices, func(i, j int) bool {
			return prices[i] > prices[j]
		})
		var curS int = 0
		smallItems := make([]int, len(prices[levels:]))
		copy(smallItems, prices[levels:])
		largeItems := make([]int, levels)
		copy(largeItems, prices[:levels])
		var res []int
		largeIdx := 0
		bonusPoints := int(sum(prices[:levels]))
		for level := 1; level <= levels; level++ {
			target := level * x
			for curS < target-largeItems[largeIdx] && len(smallItems) > 0 {
				item := smallItems[len(smallItems)-1]
				smallItems = smallItems[:len(smallItems)-1]
				res = append(res, item)
				curS += item
			}
			res = append(res, largeItems[largeIdx])
			curS += largeItems[largeIdx]
			largeIdx++
		}
		res = append(res, smallItems...)
		fmt.Fprintln(writer, bonusPoints)

		// 输出res，空格分隔
		if len(res) > 0 {
			out := make([]string, len(res))
			for i, v := range res {
				out[i] = strconv.Itoa(v)
			}
			fmt.Fprintln(writer, strings.Join(out, " "))
		} else {
			fmt.Fprintln(writer)
		}
	}
}
