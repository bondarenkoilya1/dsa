package main

import (
	"fmt"
	hashmap "map/map"
)

func main() {
	m := hashmap.NewMap(5)


m.Insert("a", 10)

m.Insert("k", 20)

m.Insert("u", 30)
	entries := m.Entries()	
	keys := m.Keys()
	fmt.Println(entries,keys)
}
