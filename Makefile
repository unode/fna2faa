.PHONY: static clean

fna2faa: fna2faa.cpp
	@echo "Creating a normal build"
	g++ -std=c++11 -O3 -o fna2faa fna2faa.cpp
	strip fna2faa

static: fna2faa-static

fna2faa-static: fna2faa.cpp
	@echo "Creating a static build"
	g++ -std=c++11 -O3 -static -o fna2faa-static fna2faa.cpp
	strip fna2faa-static

run: fna2faa
	cat tests/test.fa | ./fna2faa -

test: fna2faa
	@echo -n "Translating default from file ... "
	@./fna2faa tests/test.fa > result.stdout 2> result.stderr
	@diff -u tests/expected-verbose.stderr result.stderr
	@diff -u tests/expected-verbose.stdout result.stdout
	@echo "DONE"
	@echo -n "Translating quietly from STDIN (--quiet) ... "
	@cat tests/test.fa | ./fna2faa --quiet - > result.stdout 2> result.stderr
	@diff -u tests/expected.stderr result.stderr
	@diff -u tests/expected.stdout result.stdout
	@echo "DONE"
	@echo -n "Translating up to first STOP codon (--first_stop) ... "
	@./fna2faa --first_stop tests/test.fa > result.stdout 2> result.stderr
	@diff -u tests/expected-first_stop.stderr result.stderr
	@diff -u tests/expected-first_stop.stdout result.stdout
	@echo "DONE"
	@echo -n "Translating frame 1 from forward strand (--frame 1) ... "
	@./fna2faa --frame 1 tests/test.fa > result.stdout 2> result.stderr
	@diff -u tests/expected-frame-1.stderr result.stderr
	@diff -u tests/expected-frame-1.stdout result.stdout
	@echo "DONE"
	@echo -n "Translating frame 0 from reverse strand (--frame 3) ... "
	@./fna2faa --frame 3 tests/test.fa > result.stdout 2> result.stderr
	@diff -u tests/expected-frame-3.stderr result.stderr
	@diff -u tests/expected-frame-3.stdout result.stdout
	@echo "DONE"
	@echo -n "Translating frame 0 from reverse strand up to first STOP (--frame 3 --first_stop) ... "
	@./fna2faa --frame 3 --first_stop tests/test.fa > result.stdout 2> result.stderr
	@diff -u tests/expected-frame-3-first_stop.stderr result.stderr
	@diff -u tests/expected-frame-3-first_stop.stdout result.stdout
	@echo "DONE"
	@echo -n "Translating all 6 frames (--all_frames) ... "
	@./fna2faa --all_frames tests/test.fa > result.stdout 2> result.stderr
	@diff -u tests/expected-all-frames.stderr result.stderr
	@diff -u tests/expected-all-frames.stdout result.stdout
	@echo "DONE"
	@echo -n "Testing version (--version) ... "
	@./fna2faa --version > result.stdout 2> result.stderr
	@diff -u tests/expected-version.stderr result.stderr
	@diff -u tests/expected-version.stdout result.stdout
	@echo "DONE"
	@echo "No problems found"
clean:
	rm -f fna2faa fna2faa-static fna2faa-*
	rm -f result.stdout result.stderr

benchmark:
	@echo "Benchmarking normal build"
	@./benchmark.sh HEAD~1
	@echo "Benchmarking static build"
	@./benchmark.sh --static HEAD~1
