package main

type Map struct {
	length int
	values []int
}

func Hash(s string) uint32 {
	var hash uint32 = 2166136261

	for i := 0; i < len(s); i++ {
		hash ^= uint32(s[i])
		hash *= 16777619
	}

	return hash
}

func NewMap() *Map {
	return &Map{}
}
