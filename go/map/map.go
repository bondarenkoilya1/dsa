package hashmap

import "fmt"

type Entry struct {
	key string
	value int
}

type Map struct {
	length int
	values [][]Entry
}

func Hash(s string) uint32 {
	var hash uint32 = 2166136261

	for i := 0; i < len(s); i++ {
		hash ^= uint32(s[i])
		hash *= 16777619
	}

	return hash
}

func NewMap(size int) *Map {
	return &Map{
		length: 0,
		values: make([][]Entry, size),
	}
}

func (m* Map) Entries() {
	for _, bucket := range m.values {
		for _, entry := range bucket {
			fmt.Printf("{ %s: %d }\n", entry.key, entry.value)
		}
	}
}
