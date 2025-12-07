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

type BIT struct {
	tree []int
	n    int
}

func NewBIT(n int) *BIT {
	return &BIT{make([]int, n+1), n}
}

func (b *BIT) add(i, v int) {
	for ; i <= b.n; i += i & -i {
		b.tree[i] += v
	}
}

func (b *BIT) sum(i int) int {
	res := 0
	for ; i > 0; i -= i & -i {
		res += b.tree[i]
	}
	return res
}

func totalScore(hp int, damage, requirement []int) int {
	n := len(damage)

	// prefix damage
	prefix := make([]int, n+1)
	for i := 0; i < n; i++ {
		prefix[i+1] = prefix[i] + damage[i]
	}

	// compress prefix values and limit values
	all := make([]int, 0, 2*n)
	limit := make([]int, n+1)
	for i := 1; i <= n; i++ {
		limit[i] = hp - requirement[i-1] + prefix[i]
		all = append(all, prefix[i-1], limit[i])
	}

	sort.Ints(all)
	all = unique(all)

	// coordinate mapping
	comp := func(x int) int {
		idx := sort.SearchInts(all, x)
		return idx + 1
	}

	bit := NewBIT(len(all))
	res := 0

	// initial prefix[0]
	bit.add(comp(prefix[0]), 1)

	for i := 1; i <= n; i++ {
		// query valid starting positions j
		res += bit.sum(comp(limit[i]))
		// add prefix[i] for future ranges
		bit.add(comp(prefix[i]), 1)
	}

	return res
}

func unique(a []int) []int {
	j := 0
	for i := 1; i < len(a); i++ {
		if a[i] != a[j] {
			j++
			a[j] = a[i]
		}
	}
	return a[:j+1]
}

func main() {
	defer writer.Flush()

	hp, _ := strconv.Atoi(readLine())
	damage := readInts()
	requirement := readInts()

	ans := totalScore(hp, damage, requirement)
	fmt.Fprintln(writer, ans)
}
