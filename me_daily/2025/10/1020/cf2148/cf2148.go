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

var (
	t, n int
	a    []int64
)

func readInts() []int {
	fields := strings.Fields(readLine())
	res := make([]int, len(fields))
	for i, f := range fields {
		res[i], _ = strconv.Atoi(f)
	}
	return res
}
func solve(a []int64) int64 {
	var sumEven int64 = 0
	oddVals := []int64{}
	for _, x := range a {
		if x%2 == 0 {
			sumEven += x
		} else {
			oddVals = append(oddVals, x)
		}
	}
	k := len(oddVals)
	if k == 0 {
		return 0
	}
	var sumOdd int64
	slices.Sort(oddVals)
	for _, x := range oddVals {
		sumOdd += x
	}
	total := sumEven + sumOdd
	numSac := k / 2 // Go的int除法对正数就是向下取整 (floor)
	var sumSac int64
	for i := 0; i < numSac; i++ {
		sumSac += oddVals[i]
	}
	return total - sumSac
}
func main() {
	defer writer.Flush() //main() 结束时自动调用
	t, _ := strconv.Atoi(readLine())
	for ; t > 0; t-- {
		n, _ := strconv.Atoi(readLine())
		a = make([]int64, n)
		readInt := readInts()
		for i := 0; i < n; i++ {
			a[i] = int64(readInt[i])
		}
		fmt.Fprintln(writer, solve(a))
	}

}
