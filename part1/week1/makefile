sourcefiles = $(wildcard *.cpp)
outputs = $(basename $(sourcefiles))

# compile individual source files
%: %.cpp
	g++ $^ -o $@

.PHONY: clean all
# compile all files
all: $(outputs)

clean: 
	rm -rf $(outputs)