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
		n, _ := header[0], header[1]
		fsb := readInts()
		inc := 0
		for i := 1; i < len(fsb); i++ {
			if fsb[i] > fsb[i-1] {
				inc++
			} else {
				inc = 0
			}
		}
		if inc == len(fsb)-1 {
			fmt.Fprintln(writer, n-fsb[len(fsb)-1]+1)
			continue
		}
		fmt.Fprintln(writer, 1)

	}
}
