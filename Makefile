.PHONY: static clean

fna2faa: fna2faa.cpp
	g++ -std=c++11 -O3 -o fna2faa fna2faa.cpp
	strip fna2faa

static: fna2faa-static
fna2faa-static: fna2faa.cpp
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
	rm -f fna2faa fna2faa-static
	rm -f result.stdout result.stderr

benchmark: fna2faa fna2faa-static
	@echo ">> Running benchmark by piping 8M sequences for a total of 336T nucleotides <<"
	@echo ">>>> Standard build <<<<"
	@awk '{a[NR]=$$0}END{for (i=0; i<1000000; i++){for(k in a){print a[k]}}}' tests/test.fa | /usr/bin/time -v ./fna2faa --quiet - 1>/dev/null
	@echo ">>>> Static build <<<<"
	@awk '{a[NR]=$$0}END{for (i=0; i<1000000; i++){for(k in a){print a[k]}}}' tests/test.fa | /usr/bin/time -v ./fna2faa-static --quiet - 1>/dev/null
	@echo "DONE"
