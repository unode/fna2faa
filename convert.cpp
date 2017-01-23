#include <iostream>
#include <vector>
#include <string>

struct nuc2aa_converter {
    nuc2aa_converter();

    void convert(const std::string& s, std::ostream& out) {
        const int size = s.size();
        char* out_buffer = new char[size/3+1];
        char* pout = out_buffer;

        for (int si = 0; si+2 < size; si += 3) {
            int code = (code_for[s[si]] << 6) | (code_for[s[si+1]] << 3) | code_for[s[si+2]];
            char v = table[code];
            if (v != '_') *pout++ = v;
            else if (v == '\0') {
                delete [] out_buffer;
                throw "Bad codon";
            }
        }
        *pout = '\0';
        out << out_buffer;
        delete [] out_buffer;
    }
    private:
    void put_into_table(const char* codon, char c) {
        int code = (code_for[codon[0]] << 6) | (code_for[codon[1]] << 3) | code_for[codon[2]];
        table[code] = c;
    }
    std::vector<int> code_for;
    std::vector<char> table;
};
nuc2aa_converter::nuc2aa_converter()
    :code_for(256)
    ,table(512) {
    for (int i = 0; i != 256; ++i) {
        code_for[i] = 0x7;
    }
    code_for[int('a')] = 0;
    code_for[int('A')] = 0;
    code_for[int('c')] = 1;
    code_for[int('C')] = 1;
    code_for[int('g')] = 2;
    code_for[int('G')] = 2;
    code_for[int('t')] = 3;
    code_for[int('T')] = 3;

    for(const char* bad =
                "BDHKMNRSWVXY"
                "bdhkmnrswvxy";
                *bad; ++bad) code_for[*bad] = 4;

    for (int i = 0; i != 512; ++i) {
        table[i] = '\0';
    }
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

    put_into_table("TCA", 'S');
    put_into_table("TCC", 'S');
    put_into_table("TCG", 'S');
    put_into_table("TCT", 'S');
    // ambiguous 3rd base
    put_into_table("TCM", 'S');
    put_into_table("TCR", 'S');
    put_into_table("TCW", 'S');
    put_into_table("TCS", 'S');
    put_into_table("TCY", 'S');
    put_into_table("TCK", 'S');
    put_into_table("TCV", 'S');
    put_into_table("TCH", 'S');
    put_into_table("TCD", 'S');
    put_into_table("TCB", 'S');
    put_into_table("TCX", 'S');
    put_into_table("TCN", 'S');

    put_into_table("TTC", 'F');
    put_into_table("TTT", 'F');
    // ambiguous 3rd base
    put_into_table("TTY", 'F');

    put_into_table("TTA", 'L');
    put_into_table("TTG", 'L');
    // ambiguous 3rd base
    put_into_table("TTR", 'L');

    put_into_table("TAC", 'Y');
    put_into_table("TAT", 'Y');
    // ambiguous 3rd base
    put_into_table("TAY", 'Y');

    put_into_table("TAA", '_');
    put_into_table("TAG", '_');
    // ambiguous 3rd base
    put_into_table("TAR", '_');

    put_into_table("TGC", 'C');
    put_into_table("TGT", 'C');
    // ambiguous 3rd base
    put_into_table("TGY", 'C');

    put_into_table("TGA", '_');
    // ambiguous 2rd base
    put_into_table("TRA", '_');

    put_into_table("TGG", 'W');

    put_into_table("CTA", 'L');
    put_into_table("CTC", 'L');
    put_into_table("CTG", 'L');
    put_into_table("CTT", 'L');
    // ambiguous 3rd base
    put_into_table("CTM", 'L');
    put_into_table("CTR", 'L');
    put_into_table("CTW", 'L');
    put_into_table("CTS", 'L');
    put_into_table("CTY", 'L');
    put_into_table("CTK", 'L');
    put_into_table("CTV", 'L');
    put_into_table("CTH", 'L');
    put_into_table("CTD", 'L');
    put_into_table("CTB", 'L');
    put_into_table("CTX", 'L');
    put_into_table("CTN", 'L');
    // ambiguous 1st base
    put_into_table("YTA", 'L');
    put_into_table("YTG", 'L');
    // ambiguous 1st and 3rd base
    put_into_table("YTR", 'L');

    put_into_table("CCA", 'P');
    put_into_table("CCC", 'P');
    put_into_table("CCG", 'P');
    put_into_table("CCT", 'P');
    // ambiguous 3rd base
    put_into_table("CCM", 'P');
    put_into_table("CCR", 'P');
    put_into_table("CCW", 'P');
    put_into_table("CCS", 'P');
    put_into_table("CCY", 'P');
    put_into_table("CCK", 'P');
    put_into_table("CCV", 'P');
    put_into_table("CCH", 'P');
    put_into_table("CCD", 'P');
    put_into_table("CCB", 'P');
    put_into_table("CCX", 'P');
    put_into_table("CCN", 'P');

    put_into_table("CAC", 'H');
    put_into_table("CAT", 'H');
    // ambiguous 3rd base
    put_into_table("CAY", 'H');

    put_into_table("CAA", 'Q');
    put_into_table("CAG", 'Q');
    // ambiguous 3rd base
    put_into_table("CAR", 'Q');

    put_into_table("CGA", 'R');
    put_into_table("CGC", 'R');
    put_into_table("CGG", 'R');
    put_into_table("CGT", 'R');
    // ambiguous 3rd base
    put_into_table("CGM", 'R');
    put_into_table("CGR", 'R');
    put_into_table("CGW", 'R');
    put_into_table("CGS", 'R');
    put_into_table("CGY", 'R');
    put_into_table("CGK", 'R');
    put_into_table("CGV", 'R');
    put_into_table("CGH", 'R');
    put_into_table("CGD", 'R');
    put_into_table("CGB", 'R');
    put_into_table("CGX", 'R');
    put_into_table("CGN", 'R');

    put_into_table("ATA", 'I');
    put_into_table("ATC", 'I');
    put_into_table("ATT", 'I');
    // ambiguous 3rd base
    put_into_table("ATM", 'I');
    put_into_table("ATW", 'I');
    put_into_table("ATY", 'I');
    put_into_table("ATH", 'I');

    put_into_table("ATG", 'M');

    put_into_table("ACA", 'T');
    put_into_table("ACC", 'T');
    put_into_table("ACG", 'T');
    put_into_table("ACT", 'T');
    // ambiguous 3rd base
    put_into_table("ACM", 'T');
    put_into_table("ACR", 'T');
    put_into_table("ACW", 'T');
    put_into_table("ACS", 'T');
    put_into_table("ACY", 'T');
    put_into_table("ACK", 'T');
    put_into_table("ACV", 'T');
    put_into_table("ACH", 'T');
    put_into_table("ACD", 'T');
    put_into_table("ACB", 'T');
    put_into_table("ACX", 'T');
    put_into_table("ACN", 'T');

    put_into_table("AAC", 'N');
    put_into_table("AAT", 'N');
    // ambiguous 3rd base
    put_into_table("AAY", 'N');

    put_into_table("AAA", 'K');
    put_into_table("AAG", 'K');
    // ambiguous 3rd base
    put_into_table("AAR", 'K');

    put_into_table("AGC", 'S');
    put_into_table("AGT", 'S');
    // ambiguous 3rd base
    put_into_table("AGY", 'S');

    put_into_table("AGA", 'R');
    put_into_table("AGG", 'R');
    // ambiguous 3rd base
    put_into_table("AGR", 'R');
    // ambiguous 1st base
    put_into_table("MGA", 'R');
    put_into_table("MGG", 'R');
    // ambiguous 1st and 3rd base
    put_into_table("MGR", 'R');

    put_into_table("GTA", 'V');
    put_into_table("GTC", 'V');
    put_into_table("GTG", 'V');
    put_into_table("GTT", 'V');
    // ambiguous 3rd base
    put_into_table("GTM", 'V');
    put_into_table("GTR", 'V');
    put_into_table("GTW", 'V');
    put_into_table("GTS", 'V');
    put_into_table("GTY", 'V');
    put_into_table("GTK", 'V');
    put_into_table("GTV", 'V');
    put_into_table("GTH", 'V');
    put_into_table("GTD", 'V');
    put_into_table("GTB", 'V');
    put_into_table("GTX", 'V');
    put_into_table("GTN", 'V');

    put_into_table("GCA", 'A');
    put_into_table("GCC", 'A');
    put_into_table("GCG", 'A');
    put_into_table("GCT", 'A');
    // ambiguous 3rd base
    put_into_table("GCM", 'A');
    put_into_table("GCR", 'A');
    put_into_table("GCW", 'A');
    put_into_table("GCS", 'A');
    put_into_table("GCY", 'A');
    put_into_table("GCK", 'A');
    put_into_table("GCV", 'A');
    put_into_table("GCH", 'A');
    put_into_table("GCD", 'A');
    put_into_table("GCB", 'A');
    put_into_table("GCX", 'A');
    put_into_table("GCN", 'A');

    put_into_table("GAC", 'D');
    put_into_table("GAT", 'D');
    // ambiguous 3rd base
    put_into_table("GAY", 'D');

    put_into_table("GAA", 'E');
    put_into_table("GAG", 'E');
    // ambiguous 3rd base
    put_into_table("GAR", 'E');

    put_into_table("GGA", 'G');
    put_into_table("GGC", 'G');
    put_into_table("GGG", 'G');
    put_into_table("GGT", 'G');
    // ambiguous 3rd base
    put_into_table("GGM", 'G');
    put_into_table("GGR", 'G');
    put_into_table("GGW", 'G');
    put_into_table("GGS", 'G');
    put_into_table("GGY", 'G');
    put_into_table("GGK", 'G');
    put_into_table("GGV", 'G');
    put_into_table("GGH", 'G');
    put_into_table("GGD", 'G');
    put_into_table("GGB", 'G');
    put_into_table("GGX", 'G');
    put_into_table("GGN", 'G');

    for (int pi = 0; pi != 3; ++pi) {
        for (int c = 0; c != (1 << 6); ++c) {
            int code;
            if (pi == 0) {
                code = (4 << 6) | c;
            } else if (pi == 1) {
                code = ((c & (0x7<<3)) << 3) | 4 | (c & 0x7);
            } else if (pi == 2) {
                code = (c << 3) | 4;
            }
            table[code] = 'X';
        }
    }
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

int main() {
    std::string h, seq;
    nuc2aa_converter converter;
    while (get_sequence(std::cin, h, seq)) {
        std::cout << h << '\n';
        converter.convert(seq, std::cout);
        std::cout << '\n';
    }
}
