package hashmap
type Entry struct {
	key string
	value int 
}

type Map struct {
	length int
	values [][]Entry
}

func hash(s string) uint32 {
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

func (m *Map) Insert(key string, value int) {
	h := hash(key)
	index := h%uint32(len(m.values))

	m.values[index] = append(m.values[index], Entry{
		key: key,
		value: value,
	})
	m.length++
}


// Print functions

func (m* Map) Entries() []Entry{
	entries := make([]Entry, 0, m.length)

	for _, bucket := range m.values {
		for _, entry := range bucket {
			entries = append(entries, entry)
		}
	}
	
	return entries
}

func (m *Map) Keys() []string {
	keys := make([]string, 0, m.length)

	for _, bucket := range m.values {
		for _, entry := range bucket {
			keys = append(keys, entry.key)
		}
	}

	return keys
}
