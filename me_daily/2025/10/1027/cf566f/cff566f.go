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

const MAX int = 1000001

func main() {
	defer writer.Flush() //main() 结束时自动调用
	n, _ := strconv.Atoi(readLine())
	exist := make([]bool, MAX)

	a := readInts()
	for i := 0; i < n; i++ {
		exist[a[i]] = true
	}

	f := make([]int, MAX)
	var ans int = 0

	for x := 1; x < MAX; x++ {
		if !exist[x] {
			continue
		}
		f[x] = max(f[x], 1)
		for y := x * 2; y < MAX; y += x {
			if exist[y] {
				f[y] = max(f[y], f[x]+1)
			}
		}
		ans = max(ans, f[x])
	}
	fmt.Fprintln(writer, ans)

}
