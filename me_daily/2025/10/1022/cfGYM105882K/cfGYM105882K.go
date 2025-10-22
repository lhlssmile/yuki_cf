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

type Pair struct {
	f, s int
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func main() {
	defer writer.Flush()
	n, _ := strconv.Atoi(readLine())

	p := []Pair{}

	if n&1 == 1 {
		p = append(p, Pair{f: 0, s: 0})
		x, y := 0, 0
		for i := 0; i < n/2-1; i++ {
			y += 25
			p = append(p, Pair{f: x, s: y})
			x += 25
			p = append(p, Pair{f: x, s: y})
		}
		x = max(x, 25)
		p = append(p, Pair{f: x, s: 0})
		p = append(p, Pair{f: x / 25 * 9, s: x / 25 * (-12)})
	} else {
		p = append(p, Pair{f: 0, s: 0})
		x, y := 0, 0
		for i := 0; i < n/2-1; i++ {
			y += 25
			p = append(p, Pair{f: x, s: y})
			x += 25
			p = append(p, Pair{f: x, s: y})
		}
		p = append(p, Pair{f: x, s: 0})
	}

	dx, dy := 5, 12
	for _, pair := range p {
		x, y := pair.f, pair.s
		X, Y := x*dx+y*dy, (-dy)*x+y*dx
		fmt.Fprintf(writer, "%d %d\n", X, Y)
	}
}
