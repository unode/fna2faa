#!/usr/bin/env bash

command -v awk >/dev/null 2>&1 || {
echo "'awk' not found. Aborting benchmark." >&2
exit 1; }

command -v getopt >/dev/null 2>&1 || {
echo "'getopt' not found. Aborting benchmark." >&2
exit 1; }

command -v git >/dev/null 2>&1 || {
echo "'git' not found. Aborting benchmark." >&2
exit 1; }

command -v hyperfine >/dev/null 2>&1 || {
echo "'hyperfine' not found. Aborting benchmark." >&2
exit 1; }

CMD="fna2faa"

# Parse args using getopt (instead of getopts) to allow arguments before options
ARGS=$(getopt -o s: -l static: -n "$0" -- "$@")
# reorganize arguments as returned by getopt
eval set -- "$ARGS"

while true; do
    case "$1" in
        # Shift before to throw away option
        # Shift after if option has a required positional argument
        -s|--static)
            shift
            CMD="fna2faa-static"
            shift
            ;;
        --)
            shift
            break
            ;;
    esac
done

if [ "$#" -ne 1 ]; then
    echo "Please specify the commit with which to benchmark against"
    exit 1
fi

if [[ -n $(git status --porcelain) ]]; then
    echo "!! Warning this script will benchmark the most recent commit against the provided commit. Please commit your changes !!"
    exit 1;
fi

COMMIT_PREV="$(git rev-parse --short "$1")"
COMMIT_CURR="$(git rev-parse --short HEAD)"

git worktree remove -f "fna2faa-$COMMIT_PREV-folder"
rm -rf fna2faa "fna2faa-$COMMIT_PREV" "fna2faa-$COMMIT_CURR"

( git worktree add fna2faa-prev-folder "$1" && cd fna2faa-prev-folder && make $CMD && mv fna2faa ../fna2faa-previous && cd .. && git worktree remove -f fna2faa-prev-folder )
make $CMD && mv $CMD fna2faa-current

echo ">> Benchmarking (8 long sequences - 343M nucleotides) <<"
hyperfine \
  -n "Current commit $COMMIT_CURR" \
  "awk '{if ($$0 !~ /^>/) {for (i=0; i<1000000; i++) print} else {print}}' tests/test.fa | ./fna2faa-current --quiet - 1>/dev/null" \
  -n "Previous commit $COMMIT_PREV" \
  "awk '{if ($$0 !~ /^>/) {for (i=0; i<1000000; i++) print} else {print}}' tests/test.fa | ./fna2faa-previous --quiet - 1>/dev/null"

echo ">> Benchmarking (8M short sequences - 343M nucleotides) <<"
hyperfine \
  -n "Current commit $COMMIT_CURR" \
	"awk '{a[NR]=$$0}END{for (i=0; i<1000000; i++){for(k in a){print a[k]}}}' tests/test.fa | ./fna2faa-current --quiet - 1>/dev/null" \
  -n "Previous commit $COMMIT_PREV" \
	"awk '{a[NR]=$$0}END{for (i=0; i<1000000; i++){for(k in a){print a[k]}}}' tests/test.fa | ./fna2faa-previous --quiet - 1>/dev/null"
