#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// from http://stackoverflow.com/a/2159469
struct noop {
    void operator()(...) const {}
};

void populate_translate_hash(std::unordered_map<std::string, std::string>& hash, std::string& stop, std::string& bogus) {
    /*
     * Translation with ambiguity codes
     *
     * A            A           Adenine
     * C            C           Cytosine
     * G            G           Guanine
     * T            T           Thymine
     * U            U           Uracil
     * M          A or C
     * R          A or G
     * W          A or T/U
     * S          C or G
     * Y          C or T/U
     * K          G or T/U
     * V        A or C or G
     * H        A or C or T/U
     * D        A or G or T/U
     * B        C or G or T/U
     * X      G or A or C or T/U
     * N      G or A or C or T/U
     *
     */

    hash.emplace("TCA", "S"); hash.emplace("UCA", "S");
    hash.emplace("TCC", "S"); hash.emplace("UCC", "S");
    hash.emplace("TCG", "S"); hash.emplace("UCG", "S");
    hash.emplace("TCT", "S"); hash.emplace("UCU", "S"); hash.emplace("TCU", "S"); hash.emplace("UCT", "S");
    // ambiguous 3rd base
    hash.emplace("TCM", "S"); hash.emplace("UCM", "S");
    hash.emplace("TCR", "S"); hash.emplace("UCR", "S");
    hash.emplace("TCW", "S"); hash.emplace("UCW", "S");
    hash.emplace("TCS", "S"); hash.emplace("UCS", "S");
    hash.emplace("TCY", "S"); hash.emplace("UCY", "S");
    hash.emplace("TCK", "S"); hash.emplace("UCK", "S");
    hash.emplace("TCV", "S"); hash.emplace("UCV", "S");
    hash.emplace("TCH", "S"); hash.emplace("UCH", "S");
    hash.emplace("TCD", "S"); hash.emplace("UCD", "S");
    hash.emplace("TCB", "S"); hash.emplace("UCB", "S");
    hash.emplace("TCX", "S"); hash.emplace("UCX", "S");
    hash.emplace("TCN", "S"); hash.emplace("UCN", "S");

    hash.emplace("TTC", "F"); hash.emplace("UUC", "F"); hash.emplace("TUC", "F"); hash.emplace("UTC", "F");
    // All permutations of TTT -> UUU (8 in total)
    hash.emplace("TTT", "F"); hash.emplace("UUU", "F");
    hash.emplace("TTU", "F"); hash.emplace("TUT", "F"); hash.emplace("UTT", "F");
    hash.emplace("UUT", "F"); hash.emplace("UTU", "F"); hash.emplace("TUU", "F");

    // ambiguous 3rd base
    hash.emplace("TTY", "F"); hash.emplace("UUY", "F"); hash.emplace("TUY", "F"); hash.emplace("UTY", "F");

    hash.emplace("TTA", "L"); hash.emplace("UUA", "L"); hash.emplace("TUA", "L"); hash.emplace("UTA", "L");
    hash.emplace("TTG", "L"); hash.emplace("UUG", "L"); hash.emplace("TUG", "L"); hash.emplace("UTG", "L");
    // ambiguous 3rd base
    hash.emplace("TTR", "L"); hash.emplace("UUR", "L"); hash.emplace("TUR", "L"); hash.emplace("UTR", "L");

    hash.emplace("TAC", "Y"); hash.emplace("UAC", "Y");
    hash.emplace("TAT", "Y"); hash.emplace("UAU", "Y"); hash.emplace("TAU", "Y"); hash.emplace("UAT", "Y");
    // ambiguous 3rd base
    hash.emplace("TAY", "Y"); hash.emplace("UAY", "Y");

    hash.emplace("TAA", stop); hash.emplace("UAA", stop);
    hash.emplace("TAG", stop); hash.emplace("UAG", stop);
    // ambiguous 3rd base
    hash.emplace("TAR", stop); hash.emplace("UAR", stop);

    hash.emplace("TGC", "C"); hash.emplace("UGC", "C");
    hash.emplace("TGT", "C"); hash.emplace("UGU", "C"); hash.emplace("TGU", "C"); hash.emplace("UGT", "C");
    // ambiguous 3rd base
    hash.emplace("TGY", "C"); hash.emplace("UGY", "C");

    hash.emplace("TGA", stop); hash.emplace("UGA", stop);
    // ambiguous 2rd base
    hash.emplace("TRA", stop); hash.emplace("URA", stop);

    hash.emplace("TGG", "W"); hash.emplace("UGG", "W");

    hash.emplace("CTA", "L"); hash.emplace("CUA", "L");
    hash.emplace("CTC", "L"); hash.emplace("CUC", "L");
    hash.emplace("CTG", "L"); hash.emplace("CUG", "L");
    hash.emplace("CTT", "L"); hash.emplace("CUU", "L"); hash.emplace("CTU", "L"); hash.emplace("CUT", "L");
    // ambiguous 3rd base
    hash.emplace("CTM", "L"); hash.emplace("CUM", "L");
    hash.emplace("CTR", "L"); hash.emplace("CUR", "L");
    hash.emplace("CTW", "L"); hash.emplace("CUW", "L");
    hash.emplace("CTS", "L"); hash.emplace("CUS", "L");
    hash.emplace("CTY", "L"); hash.emplace("CUY", "L");
    hash.emplace("CTK", "L"); hash.emplace("CUK", "L");
    hash.emplace("CTV", "L"); hash.emplace("CUV", "L");
    hash.emplace("CTH", "L"); hash.emplace("CUH", "L");
    hash.emplace("CTD", "L"); hash.emplace("CUD", "L");
    hash.emplace("CTB", "L"); hash.emplace("CUB", "L");
    hash.emplace("CTX", "L"); hash.emplace("CUX", "L");
    hash.emplace("CTN", "L"); hash.emplace("CUN", "L");
    // ambiguous 1st base
    hash.emplace("YTA", "L"); hash.emplace("YUA", "L");
    hash.emplace("YTG", "L"); hash.emplace("YUG", "L");
    // ambiguous 1st and 3rd base
    hash.emplace("YTR", "L"); hash.emplace("YUR", "L");

    hash.emplace("CCA", "P");
    hash.emplace("CCC", "P");
    hash.emplace("CCG", "P");
    hash.emplace("CCT", "P"); hash.emplace("CCU", "P");
    // ambiguous 3rd base
    hash.emplace("CCM", "P");
    hash.emplace("CCR", "P");
    hash.emplace("CCW", "P");
    hash.emplace("CCS", "P");
    hash.emplace("CCY", "P");
    hash.emplace("CCK", "P");
    hash.emplace("CCV", "P");
    hash.emplace("CCH", "P");
    hash.emplace("CCD", "P");
    hash.emplace("CCB", "P");
    hash.emplace("CCX", "P");
    hash.emplace("CCN", "P");

    hash.emplace("CAC", "H");
    hash.emplace("CAT", "H"); hash.emplace("CAU", "H");
    // ambiguous 3rd base
    hash.emplace("CAY", "H");

    hash.emplace("CAA", "Q");
    hash.emplace("CAG", "Q");
    // ambiguous 3rd base
    hash.emplace("CAR", "Q");

    hash.emplace("CGA", "R");
    hash.emplace("CGC", "R");
    hash.emplace("CGG", "R");
    hash.emplace("CGT", "R"); hash.emplace("CGU", "R");
    // ambiguous 3rd base
    hash.emplace("CGM", "R");
    hash.emplace("CGR", "R");
    hash.emplace("CGW", "R");
    hash.emplace("CGS", "R");
    hash.emplace("CGY", "R");
    hash.emplace("CGK", "R");
    hash.emplace("CGV", "R");
    hash.emplace("CGH", "R");
    hash.emplace("CGD", "R");
    hash.emplace("CGB", "R");
    hash.emplace("CGX", "R");
    hash.emplace("CGN", "R");

    hash.emplace("ATA", "I"); hash.emplace("AUA", "I");
    hash.emplace("ATC", "I"); hash.emplace("AUC", "I");
    hash.emplace("ATT", "I"); hash.emplace("AUU", "I"); hash.emplace("ATU", "I"); hash.emplace("AUT", "I");
    // ambiguous 3rd base
    hash.emplace("ATM", "I"); hash.emplace("AUM", "I");
    hash.emplace("ATW", "I"); hash.emplace("AUW", "I");
    hash.emplace("ATY", "I"); hash.emplace("AUY", "I");
    hash.emplace("ATH", "I"); hash.emplace("AUH", "I");

    hash.emplace("ATG", "M"); hash.emplace("AUG", "M");

    hash.emplace("ACA", "T");
    hash.emplace("ACC", "T");
    hash.emplace("ACG", "T");
    hash.emplace("ACT", "T"); hash.emplace("ACU", "T");
    // ambiguous 3rd base
    hash.emplace("ACM", "T");
    hash.emplace("ACR", "T");
    hash.emplace("ACW", "T");
    hash.emplace("ACS", "T");
    hash.emplace("ACY", "T");
    hash.emplace("ACK", "T");
    hash.emplace("ACV", "T");
    hash.emplace("ACH", "T");
    hash.emplace("ACD", "T");
    hash.emplace("ACB", "T");
    hash.emplace("ACX", "T");
    hash.emplace("ACN", "T");

    hash.emplace("AAC", "N");
    hash.emplace("AAT", "N"); hash.emplace("AAU", "N");
    // ambiguous 3rd base
    hash.emplace("AAY", "N");

    hash.emplace("AAA", "K");
    hash.emplace("AAG", "K");
    // ambiguous 3rd base
    hash.emplace("AAR", "K");

    hash.emplace("AGC", "S");
    hash.emplace("AGT", "S"); hash.emplace("AGU", "S");
    // ambiguous 3rd base
    hash.emplace("AGY", "S");

    hash.emplace("AGA", "R");
    hash.emplace("AGG", "R");
    // ambiguous 3rd base
    hash.emplace("AGR", "R");
    // ambiguous 1st base
    hash.emplace("MGA", "R");
    hash.emplace("MGG", "R");
    // ambiguous 1st and 3rd base
    hash.emplace("MGR", "R");

    hash.emplace("GTA", "V"); hash.emplace("GUA", "V");
    hash.emplace("GTC", "V"); hash.emplace("GUC", "V");
    hash.emplace("GTG", "V"); hash.emplace("GUG", "V");
    hash.emplace("GTT", "V"); hash.emplace("GUU", "V"); hash.emplace("GTU", "V"); hash.emplace("GUT", "V");
    // ambiguous 3rd base
    hash.emplace("GTM", "V"); hash.emplace("GUM", "V");
    hash.emplace("GTR", "V"); hash.emplace("GUR", "V");
    hash.emplace("GTW", "V"); hash.emplace("GUW", "V");
    hash.emplace("GTS", "V"); hash.emplace("GUS", "V");
    hash.emplace("GTY", "V"); hash.emplace("GUY", "V");
    hash.emplace("GTK", "V"); hash.emplace("GUK", "V");
    hash.emplace("GTV", "V"); hash.emplace("GUV", "V");
    hash.emplace("GTH", "V"); hash.emplace("GUH", "V");
    hash.emplace("GTD", "V"); hash.emplace("GUD", "V");
    hash.emplace("GTB", "V"); hash.emplace("GUB", "V");
    hash.emplace("GTX", "V"); hash.emplace("GUX", "V");
    hash.emplace("GTN", "V"); hash.emplace("GUN", "V");

    hash.emplace("GCA", "A");
    hash.emplace("GCC", "A");
    hash.emplace("GCG", "A");
    hash.emplace("GCT", "A"); hash.emplace("GCU", "A");
    // ambiguous 3rd base
    hash.emplace("GCM", "A");
    hash.emplace("GCR", "A");
    hash.emplace("GCW", "A");
    hash.emplace("GCS", "A");
    hash.emplace("GCY", "A");
    hash.emplace("GCK", "A");
    hash.emplace("GCV", "A");
    hash.emplace("GCH", "A");
    hash.emplace("GCD", "A");
    hash.emplace("GCB", "A");
    hash.emplace("GCX", "A");
    hash.emplace("GCN", "A");

    hash.emplace("GAC", "D");
    hash.emplace("GAT", "D"); hash.emplace("GAU", "D");
    // ambiguous 3rd base
    hash.emplace("GAY", "D");

    hash.emplace("GAA", "E");
    hash.emplace("GAG", "E");
    // ambiguous 3rd base
    hash.emplace("GAR", "E");

    hash.emplace("GGA", "G");
    hash.emplace("GGC", "G");
    hash.emplace("GGG", "G");
    hash.emplace("GGT", "G"); hash.emplace("GGU", "G");
    // ambiguous 3rd base
    hash.emplace("GGM", "G");
    hash.emplace("GGR", "G");
    hash.emplace("GGW", "G");
    hash.emplace("GGS", "G");
    hash.emplace("GGY", "G");
    hash.emplace("GGK", "G");
    hash.emplace("GGV", "G");
    hash.emplace("GGH", "G");
    hash.emplace("GGD", "G");
    hash.emplace("GGB", "G");
    hash.emplace("GGX", "G");
    hash.emplace("GGN", "G");

    // add all untranslatable codons to the hash as X, includes uracyl
    std::string nucleotides = "ABCDGHKMNRSTUVWXY";

    // TODO This could probably be more elegant but 3 loops get the job done
    for(std::string::const_iterator a = nucleotides.begin(); a < nucleotides.end(); ++a) {
        for(std::string::const_iterator b = nucleotides.begin(); b < nucleotides.end(); ++b) {
            for(std::string::const_iterator c = nucleotides.begin(); c < nucleotides.end(); ++c) {
                char codon[] = {*a, *b, *c, 0};
                hash.emplace(codon, "X");
            }
        }
    }
}

void populate_complement_hash(std::unordered_map<std::string, std::string>& hash) {
    /*
     * Complementation with ambiguity codes
     *
     * A            A           ->        T           = T
     * C            C           ->        G           = G
     * G            G           ->        C           = C
     * T            T           ->        A           = A
     * U            U           ->        A           = A
     * M          A or C        ->      T or G        = K
     * R          A or G        ->      T or C        = Y
     * W          A or T        ->      T or A        = W
     * S          C or G        ->      G or C        = S
     * Y          C or T        ->      G or A        = R
     * K          G or T        ->      C or A        = M
     * V        A or C or G     ->    T or G or C     = B
     * H        A or C or T     ->    T or G or A     = D
     * D        A or G or T     ->    T or C or A     = H
     * B        C or G or T     ->    G or C or A     = V
     * X      G or A or T or C  ->  C or T or A or G  = X
     * N      G or A or T or C  ->  C or T or A or G  = N
     *
     */

    // Standard ones
    hash.emplace("A", "T");
    hash.emplace("T", "A");
    hash.emplace("C", "G");
    hash.emplace("G", "C");

    // Uracyl becomes A
    hash.emplace("U", "A");

    // And all the ambiguous ones
    hash.emplace("M", "K");
    hash.emplace("R", "Y");
    hash.emplace("W", "W");
    hash.emplace("S", "S");
    hash.emplace("Y", "R");
    hash.emplace("K", "M");
    hash.emplace("V", "B");
    hash.emplace("H", "D");
    hash.emplace("D", "H");
    hash.emplace("B", "V");
    hash.emplace("X", "X");
    hash.emplace("N", "N");
}

bool get_sequence(std::istream& input, std::string& header, std::string& seq) {
    if (!std::getline(input, header)) return false;
    if (!std::getline(input, seq)) return false;
    std::string next;
    while (input.peek() != '>') {
        if (!std::getline(input, next)) return true;
        seq += next;
    }
    return true;
}

void set_frame_and_direction(int frame, int &active_frame, int &direction) {
    direction = frame / 3;  // 0 = 0-2 ; 1 = 3-5
    active_frame = frame % 3;
}

void show_usage(char **argv) {
    fprintf(stderr, "Usage: %s [options] <filename or - for STDIN>\n", argv[0]);
    fprintf(stderr, "  About:\n");
    fprintf(stderr, "    Translates nucleotides (DNA & RNA) to aminoacid sequences\n");
    fprintf(stderr, "    This software can translate sequences that use IUPAC ambiguity codes\n");
    fprintf(stderr, "    Defaults to translating the first frame in -> direction, doesn't stop on\n");
    fprintf(stderr, "    stop codons, uses * as STOP symbol and X for untranslatable codons.\n");
    fprintf(stderr, "\n  Options:\n");
    fprintf(stderr, "    -h --help           - Show this message\n");
    fprintf(stderr, "    -v --version        - Print version and exit\n");
    fprintf(stderr, "    -q --quiet          - Silence warning messages\n");
    fprintf(stderr, "    -a --all_frames     - Output translation for all frames\n");
    fprintf(stderr, "    -f --frame i        - Specify which frame to output (0, 1, 2, 3, 4, 5)\n");
    fprintf(stderr, "                          Frames 0-2 are -> strand, 3-5 are <-.\n");
    fprintf(stderr, "    -s --first_stop     - Stop translation when first stop codon is found\n");
    fprintf(stderr, "    -t --stop_codon     - Character to use as stop symbol, * by default\n");
    fprintf(stderr, "    -n --no_bogus       - Skips untranslatable codons instead of printing X\n");
}

int main(int argc, char **argv) {
    std::string h, allseq, seq, translated;
    std::unordered_map<std::string, std::string> translate_hash;
    std::unordered_map<std::string, std::string> complement_hash;
    std::string stop = "*";
    std::string bogus = "X";
    std::string filename = "";
    std::shared_ptr<std::istream> file;

    int do_all_frames = 0;  // one frame only by default
    int active_frame, frame = 0;  // default 1st frame
    int direction = 0;  // default forward
    // Used during iteration
    int start_frame, end_frame = 0;
    int codon = 3;
    int halt_on_stop = 0;
    int verbose = 1;
    int show_help = 0;

    struct option long_options[] = {
        {"help",         no_argument,       NULL, 'h'},
        {"version",      no_argument,       NULL, 'v'},
        {"quiet",        no_argument,       NULL, 'q'},
        {"first_stop",   no_argument,       NULL, 's'},
        {"no_bogus",     no_argument,       NULL, 'b'},
        {"all_frames",   no_argument,       NULL, 'a'},
        {"frame",        required_argument, NULL, 'f'},
        {"stop",         required_argument, NULL, 't'},
        {NULL,           0,                 NULL, 0}
    };

    int c;
    opterr = 0;

    while ( ( c = getopt_long(argc, argv, ":hvqsaf:t:", long_options, NULL) ) != -1) {

        switch (c) {
            case 'f':
                frame = atoi(optarg);
                break;

            case 'h':
                show_help = 1;
                break;

            case 'v':
                fprintf(stderr, "fna2faa: v0.1.1\n");
                exit(0);
                break;

            case 's':
                halt_on_stop = 1;
                break;

            case 't':
                stop = optarg;
                break;

            case 'a':
                do_all_frames = 1;
                break;

            case 'q':
                verbose = 0;
                break;

            case 'b':
                bogus = "";
                break;

            case ':':   /* missing option argument */
                show_usage(argv);
                fprintf(stderr, "\nERROR: option `-%c' requires an argument\n", optopt);
                exit(1);

            case '?':
                show_usage(argv);
                fprintf(stderr, "\nERROR: unknown option '-%c'\n", optopt);
                exit(1);

            default:
                show_usage(argv);
                exit(1);
                break;
        }
    }

    if (show_help) {
        show_usage(argv);
        exit(0);
    };

    /* Print any remaining command line arguments (not options). */
    if (argc - optind != 1) {
        show_usage(argv);
        fprintf(stderr, "\nERROR: Require one filename (or - to read from STDIN)\n");
        exit(1);
    }

    filename = argv[optind];

    if (frame < 0 || frame > 5) {
        show_usage(argv);
        fprintf(stderr, "\nERROR: Start frame (%i) is not in range 0 to 5\n", frame);
        fprintf(stderr, "\nNOTE: 0-2 is forward strand, 3-5 is reverse strand\n");
        exit(1);
    }

    if (do_all_frames) {
        start_frame = 0;
        end_frame = 5;  // inclusive
    } else {
        start_frame = frame;
        end_frame = frame;
    }

    if (filename == "-") {
        // Reading from stdin
        file.reset(&std::cin, noop());
    } else {
        std::ifstream input_file(filename.c_str());
        if (! input_file.good()) {
            fprintf(stderr, "ERROR: Cannot read %s\n", filename.c_str());
        }
        input_file.close();
        file.reset(new std::ifstream(filename.c_str()));
    }

    if (verbose) {
        if (do_all_frames) {
            fprintf(stderr, "Output will include all frames\n");
        } else {
            set_frame_and_direction(frame, active_frame, direction);
            if (direction)
                fprintf(stderr, "Will translate frame %i on strand <-\n", active_frame);
            else
                fprintf(stderr, "Will translate frame %i on strand ->\n", active_frame);
        }
        if (halt_on_stop)
            fprintf(stderr, "Will stop on first stop codon of each sequence\n");

        fprintf(stderr, "Using %s as stop symbol\n", stop.c_str());

        if (filename == "-") {
            fprintf(stderr, "Reading from STDIN\n");
        } else {
            fprintf(stderr, "Reading from %s\n", filename.c_str());
        }
    }

    populate_translate_hash(translate_hash, stop, bogus);
    populate_complement_hash(complement_hash);

    while (get_sequence(*file, h, allseq)) {
        for (int frame = start_frame; frame <= end_frame; ++frame) {
            // Recalculate frame and direction based on current frame
            set_frame_and_direction(frame, active_frame, direction);

            // Reverse complement current sequence
            if (direction) {
                std::string revseq = "";
                for(std::string::const_iterator it = allseq.begin(); it < allseq.end(); ++it) {
                    char base[] = {*it, 0};
                    revseq += complement_hash[base];
                }
                std::reverse(revseq.begin(), revseq.end());
                allseq = revseq;
            }

            // truncate sequence to have multiples of 3
            int seq_len = allseq.length();
            int rem_i = (seq_len - active_frame) % codon;
            seq = allseq.substr(active_frame, seq_len - rem_i);

            if (rem_i > 0)
                if (verbose)
                    fprintf(stderr, "WARN: Sequence with length not multiple of 3. Last %i bases ignored on '%s'\n", rem_i, h.c_str());

            if (do_all_frames)
                std::cout << h << ':' << active_frame << ':' << direction << '\n';
            else
                std::cout << h << '\n';

            if (halt_on_stop) {
                // Need to check every aminoacid translated
                for(std::string::const_iterator it = seq.begin(); it < seq.end(); ++it, ++it, ++it) {
                    char codon[] = {*it, *(it+1), *(it+2), 0};
                    std::string aa = translate_hash[codon];
                    std::cout << aa;

                    if (aa == stop)
                        break;
                }
            } else {
                for(std::string::const_iterator it = seq.begin(); it < seq.end(); ++it, ++it, ++it) {
                    char codon[] = {*it, *(it+1), *(it+2), 0};
                    std::cout << translate_hash[codon];
                }
            }

            std::cout << '\n';
        }
    }
}
