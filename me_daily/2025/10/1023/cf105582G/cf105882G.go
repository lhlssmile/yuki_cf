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
	header := readInts()
	n, a, b := header[0], header[1], header[2]
	k1, k2 := n/2, n-(n/2)
	v1, v2 := make([]int64, k1), make([]int64, k2)
	for i := 0; i < k1; i++ {
		mt := readInts()
		m, t := mt[0], mt[1]
		res := m*b - a*t
		v1[i] = int64(res)
	}
	for i := 0; i < k2; i++ {
		mt := readInts()
		m, t := mt[0], mt[1]
		res := m*b - a*t
		v2[i] = int64(res) // 同上
	}
	mp := make(map[int64]int)
	for mask := 0; mask < (1 << k1); mask++ {
		var val int64 = 0
		for j := 0; j < k1; j++ {
			if mask&(1<<j) != 0 {
				val += v1[j]
			}
		}
		mp[val]++
	}
	var ans int64 = 0
	for mask := 0; mask < (1 << k2); mask++ {
		var val int64 = 0
		for j := 0; j < k2; j++ {
			if mask&(1<<j) != 0 {
				val += v2[j]
			}
		}
		if cnt, ok := mp[-val]; ok {
			ans += int64(cnt)
		}
	}
	fmt.Fprintln(writer, ans-1)
}
