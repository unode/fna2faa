# About

Translates nucleotides (DNA & RNA) in FASTA format to aminoacid sequences and can handle translation of ambiguous codons using IUPAC ambiguity codes.

# Usage

Defaults to translating the first frame in forward direction, doesn't stop on STOP codons, uses `*` as STOP symbol and `X` for untranslatable codons.

Can translate sequences from a file or STDIN/PIPE (by passing `-` as filename) and outputs to STDOUT.

## Options

* `-q` or `--quiet`: silence warning messages
* `-a` or `--all_frames`: output translation for all 6 possible frames
* `-f` or `--frame i`: specify which frame to output (0 to 5). Frames 0 to 2 are forward strand, 3 to 5 are reverse strand.
* `-s` or `--first_stop`: stop translation when first stop codon is found
* `-t` or `--stop_codon`: character to use as stop symbol. Defaults to `*`
* `-n` or `--no_bogus`: skips untranslatable codons instead of printing `X`

# Testing

A small test case is available. Use:

    make test

to run it.

# Authors

 * [Luis Pedro Coelho](http://luispedro.org)
 * [Renato Alves](https://github.com/Unode)

License: GPLv3+

Test status: [![wercker status](https://app.wercker.com/status/b3891e4439e12cc5bca8864fa4f09f63/s/master "wercker status")](https://app.wercker.com/project/byKey/b3891e4439e12cc5bca8864fa4f09f63)
