SRC := $(wildcard ./Login/*.cpp ./Login/dogcom/*.cpp)
BINPATH := bin
TARGET := jlu-drcom
CXX := c++
CXXFLAGS := -O2 -march=native

$(BINPATH)/$(TARGET): $(SRC)
	mkdir -p $(BINPATH)
	$(CXX) $(CXXFLAGS) -o $(BINPATH)/$(TARGET) $(SRC)

build: $(BINPATH)/$(TARGET)

run: $(BINPATH)/$(TARGET)
	$(BINPATH)/$(TARGET)
