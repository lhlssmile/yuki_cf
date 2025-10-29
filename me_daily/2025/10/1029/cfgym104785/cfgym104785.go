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
	header := readInts()
	_, m := header[0], header[1]
	idx1 := []int{}
	idx2 := []int{}
	for i := 1; i < m+1; i++ {
		r := readInts()
		ai, bi := r[0], r[1]
		if ai > bi {
			idx1 = append(idx1, i)
		} else {
			idx2 = append(idx2, i)
		}
	}
	fmt.Println(writer, "YES")
	if len(idx1) > len(idx2) {
		fmt.Fprintln(writer, len(idx1))
		for i := 0; i < len(idx1); i++ {
			if i > 0 {
				fmt.Println(" ")
			}
			fmt.Println(idx1[i])
		}
	} else {
		fmt.Println(writer, len(idx2))
		for i := 0; i < len(idx2); i++ {
			if i > 0 {
				fmt.Println(" ")
			}
			fmt.Println(idx2[i])
		}
	}
}
