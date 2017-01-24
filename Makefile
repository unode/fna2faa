.PHONY: static clean

fna2faa: convert.cpp
	g++ -std=c++11 -O2 -o fna2faa convert.cpp

static: fna2faa-static
fna2faa-static: convert.cpp
	g++ -std=c++11 -O2 -static -o fna2faa-static convert.cpp
	strip fna2faa-static

run: fna2faa
	cat tests/test.fa | ./fna2faa

test: fna2faa
	@cat tests/test.fa | ./fna2faa > result.stdout 2> result.stderr
	@diff tests/expected.stdout result.stdout
	@diff tests/expected.stderr result.stderr
clean:
	rm -f fna2faa fna2faa-static
	rm -f result.stdout result.stderr
