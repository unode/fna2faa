#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

// from http://stackoverflow.com/a/2159469
struct noop {
    void operator()(...) const {}
};

void populate_hash(std::unordered_map<std::string, std::string>& hash, std::string& stop) {
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
     * W          A or T
     * S          C or G
     * Y          C or T
     * K          G or T
     * V        A or C or G
     * H        A or C or T
     * D        A or G or T
     * B        C or G or T
     * X      G or A or T or C
     * N      G or A or T or C
     *
     */

    hash.emplace("TCA", "S");
    hash.emplace("TCC", "S");
    hash.emplace("TCG", "S");
    hash.emplace("TCT", "S");
    // ambiguous 3rd base
    hash.emplace("TCM", "S");
    hash.emplace("TCR", "S");
    hash.emplace("TCW", "S");
    hash.emplace("TCS", "S");
    hash.emplace("TCY", "S");
    hash.emplace("TCK", "S");
    hash.emplace("TCV", "S");
    hash.emplace("TCH", "S");
    hash.emplace("TCD", "S");
    hash.emplace("TCB", "S");
    hash.emplace("TCX", "S");
    hash.emplace("TCN", "S");

    hash.emplace("TTC", "F");
    hash.emplace("TTT", "F");
    // ambiguous 3rd base
    hash.emplace("TTY", "F");

    hash.emplace("TTA", "L");
    hash.emplace("TTG", "L");
    // ambiguous 3rd base
    hash.emplace("TTR", "L");

    hash.emplace("TAC", "Y");
    hash.emplace("TAT", "Y");
    // ambiguous 3rd base
    hash.emplace("TAY", "Y");

    hash.emplace("TAA", stop);
    hash.emplace("TAG", stop);
    // ambiguous 3rd base
    hash.emplace("TAR", stop);

    hash.emplace("TGC", "C");
    hash.emplace("TGT", "C");
    // ambiguous 3rd base
    hash.emplace("TGY", "C");

    hash.emplace("TGA", stop);
    // ambiguous 2rd base
    hash.emplace("TRA", stop);

    hash.emplace("TGG", "W");

    hash.emplace("CTA", "L");
    hash.emplace("CTC", "L");
    hash.emplace("CTG", "L");
    hash.emplace("CTT", "L");
    // ambiguous 3rd base
    hash.emplace("CTM", "L");
    hash.emplace("CTR", "L");
    hash.emplace("CTW", "L");
    hash.emplace("CTS", "L");
    hash.emplace("CTY", "L");
    hash.emplace("CTK", "L");
    hash.emplace("CTV", "L");
    hash.emplace("CTH", "L");
    hash.emplace("CTD", "L");
    hash.emplace("CTB", "L");
    hash.emplace("CTX", "L");
    hash.emplace("CTN", "L");
    // ambiguous 1st base
    hash.emplace("YTA", "L");
    hash.emplace("YTG", "L");
    // ambiguous 1st and 3rd base
    hash.emplace("YTR", "L");

    hash.emplace("CCA", "P");
    hash.emplace("CCC", "P");
    hash.emplace("CCG", "P");
    hash.emplace("CCT", "P");
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
    hash.emplace("CAT", "H");
    // ambiguous 3rd base
    hash.emplace("CAY", "H");

    hash.emplace("CAA", "Q");
    hash.emplace("CAG", "Q");
    // ambiguous 3rd base
    hash.emplace("CAR", "Q");

    hash.emplace("CGA", "R");
    hash.emplace("CGC", "R");
    hash.emplace("CGG", "R");
    hash.emplace("CGT", "R");
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

    hash.emplace("ATA", "I");
    hash.emplace("ATC", "I");
    hash.emplace("ATT", "I");
    // ambiguous 3rd base
    hash.emplace("ATM", "I");
    hash.emplace("ATW", "I");
    hash.emplace("ATY", "I");
    hash.emplace("ATH", "I");

    hash.emplace("ATG", "M");

    hash.emplace("ACA", "T");
    hash.emplace("ACC", "T");
    hash.emplace("ACG", "T");
    hash.emplace("ACT", "T");
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
    hash.emplace("AAT", "N");
    // ambiguous 3rd base
    hash.emplace("AAY", "N");

    hash.emplace("AAA", "K");
    hash.emplace("AAG", "K");
    // ambiguous 3rd base
    hash.emplace("AAR", "K");

    hash.emplace("AGC", "S");
    hash.emplace("AGT", "S");
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

    hash.emplace("GTA", "V");
    hash.emplace("GTC", "V");
    hash.emplace("GTG", "V");
    hash.emplace("GTT", "V");
    // ambiguous 3rd base
    hash.emplace("GTM", "V");
    hash.emplace("GTR", "V");
    hash.emplace("GTW", "V");
    hash.emplace("GTS", "V");
    hash.emplace("GTY", "V");
    hash.emplace("GTK", "V");
    hash.emplace("GTV", "V");
    hash.emplace("GTH", "V");
    hash.emplace("GTD", "V");
    hash.emplace("GTB", "V");
    hash.emplace("GTX", "V");
    hash.emplace("GTN", "V");

    hash.emplace("GCA", "A");
    hash.emplace("GCC", "A");
    hash.emplace("GCG", "A");
    hash.emplace("GCT", "A");
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
    hash.emplace("GAT", "D");
    // ambiguous 3rd base
    hash.emplace("GAY", "D");

    hash.emplace("GAA", "E");
    hash.emplace("GAG", "E");
    // ambiguous 3rd base
    hash.emplace("GAR", "E");

    hash.emplace("GGA", "G");
    hash.emplace("GGC", "G");
    hash.emplace("GGG", "G");
    hash.emplace("GGT", "G");
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

int main(int argc, char *argv[]) {
    std::string h, seq, translated;
    std::unordered_map<std::string, std::string> hash;
    std::string stop = "";
    std::string filename = "";
    std::shared_ptr<std::istream> file;

    int codon = 3;

    if (argc < 2 || argc > 3) {
        std::cout << "Usage: " << argv[0] << " [--include-stop-codons] <filename>\n";
        std::cout << "      Sequences are read from a file (or stdin if filename is '-') and written to stdout\n";
        return 1;
    }

    if (argc >= 2) {
        std::string stopcodon ("--with-stop-codons");

        if (stopcodon.compare(argv[1]) == 0) {
            stop = "*";
            std::cerr << "INFO: Including stop codons\n";
            filename = argv[2];
        } else {
            filename = argv[1];
        }
    }

    if (filename == "-") {
        // Reading from stdin
        file.reset(&std::cin, noop());
    } else {
        file.reset(new std::ifstream(filename.c_str()));
    }

    populate_hash(hash, stop);

    while (get_sequence(*file, h, seq)) {
        std::cout << h << '\n';

        int seq_len = seq.length();
        int rem_i = seq_len % codon;
        seq = seq.substr(0, seq_len - rem_i);

        if (rem_i > 0)
            std::cerr << "WARN: Sequence with length not multiple of 3. Last " << rem_i << " bases ignored on '" << h << "'\n";

        for(std::string::const_iterator it = seq.begin(); it < seq.end(); ++it, ++it, ++it) {
            char codon[] = {*it, *(it+1), *(it+2), 0};
            std::cout << hash[codon];
        }

        std::cout << '\n';
    }
}
