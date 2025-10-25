package main

import (
	"bufio"
	"fmt"
	"math"
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

func solve(h, w int, a [][]byte) {
	var total int64 = 0
	for i := 0; i < h; i++ {
		for j := 0; j < w; j++ {
			if a[i][j] == '#' {
				total++
			}
		}
	}
	if total == 0 {
		fmt.Fprintln(writer, 0)
		return
	}
	prefix := make([][]int64, h+1)
	for i := range prefix {
		prefix[i] = make([]int64, w+1)
	}
	for i := 0; i < h; i++ {
		for j := 0; j < w; j++ {
			val := int64(0)
			if a[i][j] == '#' {
				val = 1
			}
			prefix[i+1][j+1] = prefix[i][j+1] + prefix[i+1][j] - prefix[i][j] + val
		}
	}
	rectSum := func(r1, c1, r2, c2 int) int64 {
		return prefix[r2][c2] - prefix[r1-1][c2] - prefix[r2][c1-1] + prefix[r1-1][c1-1]
	}
	divs := []int{}
	for i := 1; i*i <= int(total); i++ {
		if int(total)%i == 0 {
			divs = append(divs, i)
			if i != int(total)/i {
				divs = append(divs, int(total)/i)
			}
		}
	}
	sort.Ints(divs)
	possS := []int{}
	mn := min(h, w)
	for _, d := range divs {
		sq := int(math.Sqrt(float64(d)) + 0.5)
		if sq*sq == d && sq >= 1 && sq <= mn {
			possS = append(possS, sq)
		}
	}
	sort.Sort(sort.Reverse(sort.IntSlice(possS)))
	canTile := func(s int) bool {
		covered := make([][]bool, h)
		for i := range covered {
			covered[i] = make([]bool, w)
		}
		for i := 0; i < h; i++ {
			for j := 0; j < w; j++ {
				if a[i][j] != '#' || covered[i][j] {
					continue
				}
				if i+s > h || j+s > w {
					return false
				}
				r1, c1, r2, c2 := i+1, j+1, i+s, j+s
				if rectSum(r1, c1, r2, c2) != int64(s*s) {
					return false
				}
				ok := true
				for di := 0; di < s && ok; di++ {
					for dj := 0; dj < s && ok; dj++ {
						if covered[i+di][j+dj] {
							ok = false
						}
					}
				}
				if !ok {
					return false
				}
				for di := 0; di < s; di++ {
					for dj := 0; dj < s; dj++ {
						covered[i+di][j+dj] = true
					}
				}
			}
		}
		return true
	}
	for _, s := range possS {
		if canTile(s) {
			fmt.Fprintln(writer, s)
			return
		}
	}
	fmt.Fprintln(writer, 1)
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func main() {
	defer writer.Flush()
	header := readInts()
	h, w := header[0], header[1]
	a := make([][]byte, h)
	for i := 0; i < h; i++ {
		line := readLine()
		a[i] = make([]byte, w)
		copy(a[i], []byte(line)) // 读grid：readLine转byte slice
	}
	solve(h, w, a)
}
