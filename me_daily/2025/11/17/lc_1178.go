package main

import (
	"bufio"
	"fmt"
	"math/bits"
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

func toMask(s string) int {
	m := 0
	for _, c := range s {
		m |= 1 << (c - 'a')
	}
	return m
}

func main() {
	defer writer.Flush()

	head := readInts()
	wl, pl := head[0], head[1]

	// 读入 wl 个单词（同一行）
	wordFields := strings.Fields(readLine())
	words := wordFields[:wl]

	// 读入 pl 行 puzzles
	puzzleFields := strings.Fields(readLine())
	puzzles := puzzleFields[:pl]

	// 频率表：mask -> count
	freq := make(map[int]int)

	for _, w := range words {
		m := toMask(w)
		// 字母数超过7的不可能被 puzzle 覆盖
		if bits := bits.OnesCount(uint(m)); bits <= 7 {
			freq[m]++
		}
	}

	ans := make([]int, pl)

	for i, p := range puzzles {
		pMask := toMask(p)
		firstBit := 1 << (p[0] - 'a')
		rest := pMask ^ firstBit

		cnt := 0
		for sub := rest; ; sub = (sub - 1) & rest {
			cnt += freq[sub|firstBit]
			if sub == 0 {
				break
			}
		}

		ans[i] = cnt
	}

	for i, v := range ans {
		if i > 0 {
			fmt.Fprint(writer, " ")
		}
		fmt.Fprint(writer, v)
	}
	fmt.Fprintln(writer)
}
