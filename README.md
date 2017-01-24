# Convert nucleotide FASTA to amino acid FASTA

Pretty fast conversion of nucleotide to amino acids  
The refactored version has roughly half the performance of the first version but can handle ambiguous codons

In the new version it's also possible to optionally output stop codons as `*`. By default these are omitted from the output.  
To do this pass `--with-stop-codons` on the command line.

A small test case is now also available. Use:

    make test

to run it.

Authors:
 * [Luis Pedro Coelho](http://luispedro.org)
 * [Renato Alves](https://github.com/Unode)

License: GPLv3+
