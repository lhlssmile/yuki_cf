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

// 输出整数切片，空格分隔（用你的printInts）
func printInts(arr []int) {
	if len(arr) == 0 {
		fmt.Fprintln(writer)
		return
	}
	for i, v := range arr {
		if i > 0 {
			fmt.Fprint(writer, " ")
		}
		fmt.Fprint(writer, v)
	}
	fmt.Fprintln(writer)
}

type UnionFind struct {
	n            int
	parent, rank []int
}

func NewUnionFind(n int) *UnionFind {
	parent := make([]int, n)
	rank := make([]int, n)
	for i := range parent {
		parent[i] = i  // 修正：初始化parent[i]=i
	}
	return &UnionFind{
		n:      n,
		parent: parent,
		rank:   rank,
	}
}

func (uf *UnionFind) find(x int) int {
	if uf.parent[x] != x {
		uf.parent[x] = uf.find(uf.parent[x])
	}
	return uf.parent[x]
}

func (uf *UnionFind) union(x, y int) {
	px, py := uf.find(x), uf.find(y)
	if px != py {
		if uf.rank[px] > uf.rank[py] {
			uf.parent[py] = px
		} else if uf.rank[px] < uf.rank[py] {
			uf.parent[px] = py
		} else {
			uf.parent[py] = px
			uf.rank[px]++
		}
	}
}

func main() {
	defer writer.Flush()
	header := readInts()
	n, m, FP := header[0], header[1], header[2]
	meetings := make([][3]int, m)
	for i := 0; i < m; i++ {
		l := readInts()
		x, y, t := l[0], l[1], l[2]
		meetings[i] = [3]int{x, y, t}  // 修正：直接赋值整个数组
	}

	uf := NewUnionFind(n)
	uf.union(0, FP)
	knownRoots := make(map[int]struct{})  // 修正：用map作为set存根
	root0 := uf.find(0)
	knownRoots[root0] = struct{}{}  // 只加一个根（0和FP已union）

	// 排序：按time
	sort.Slice(meetings, func(i, j int) bool {
		return meetings[i][2] < meetings[j][2]
	})

	i := 0
	for i < m {
		curTime := meetings[i][2]
		var group [][2]int  // 修正：用[][2]int存pairs，便于建adj
		for i < m && meetings[i][2] == curTime {
			mi := meetings[i]
			x, y := mi[0], mi[1]
			group = append(group, [2]int{x, y})
			i++
		}
		if len(group) == 0 {  // 修正：len检查
			continue
		}

		// 建adj：map[int][]int
		adj := make(map[int][]int)
		involved := make(map[int]struct{})  // 修正：拼写
		for _, pair := range group {
			x, y := pair[0], pair[1]
			adj[x] = append(adj[x], y)
			adj[y] = append(adj[y], x)
			involved[x] = struct{}{}
			involved[y] = struct{}{}
		}

		// BFS：从知道的起点
		visited := make(map[int]struct{})
		queue := []int{}  // 简单queue，用slice + front index模拟（够用）
		front := 0
		for person := range involved {  // 只从involved查
			if _, ok := knownRoots[uf.find(person)]; ok && _, ok2 := visited[person]; !ok2 {
				queue = append(queue, person)
				visited[person] = struct{}{}
			}
		}

		// BFS遍历
		for front < len(queue) {
			u := queue[front]
			front++
			for _, v := range adj[u] {
				if _, ok := visited[v]; !ok {
					visited[v] = struct{}{}
					queue = append(queue, v)
					uf.union(u, v)  // 关键：边上union
				}
			}
		}

		// 更新knownRoots：所有visited的根
		for p := range visited {
			knownRoots[uf.find(p)] = struct{}{}
		}
	}

	// 收集结果：所有find(j) in knownRoots
	result := []int{}
	for j := 0; j < n; j++ {
		if _, ok := knownRoots[uf.find(j)]; ok {
			result = append(result, j)
		}
	}
	sort.Ints(result)  // 排序输出
	printInts(result)
}