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
		header := readInts()
		r0, x, d, n := header[0], header[1], header[2], header[3]
		divs := readLine()
		curS, ans := r0, 0
		for i := 0; i < n; i++ {
			if divs[i] == '1' {
				ans += 1
				if i < n-1 && strings.Contains(divs[i+1:], "2") {
					curS = max(0, curS-d)
				}
			} else {
				if curS < x {
					ans += 1
					if i < n-1 && strings.Contains(divs[i+1:], "2") {
						curS = max(0, curS-d)
					}
				}
			}
		}
		fmt.Fprintln(writer, ans)
	}
}
