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
	defer writer.Flush() //main() 结束时自动调用
	t, _ := strconv.Atoi(readLine())
	for ; t > 0; t-- {
		n, _ := strconv.Atoi(readLine())

		a := readInts()

		M := make([]int, n+1)
		M[1] = a[0]
		for i := 1; i < n; i++ {
			M[i+1] = max(M[i], a[i])
		}
		var ans int = 0
		for i := 0; i < n; i += 2 {
			if i == 0 {
				u := M[2] - 1
				b := min(a[i], max(0, u))
				ans += a[i] - b
				// 1 4 2 5 3 -> M: 0 1 4 4 5 5
			} else if i == n-1 {
				u := M[n-1] - 1
				b := min(a[i], max(0, u))
				ans += a[i] - b
			} else {
				u := min(M[i], M[i+2]) - 1
				b := min(a[i], max(0, u))
				ans += a[i] - b
			}
		}
		fmt.Fprintln(writer, ans)

	}

}
