.PHONY: static clean

fna2faa: convert.cpp
	g++ -O2 -o fna2faa convert.cpp

static: fna2faa-static
fna2faa-static: convert.cpp
	g++ -O2 -static -o fna2faa-static convert.cpp
	strip fna2faa-static

clean:
	rm -f fna2faa
	rm -f fna2faa-static
