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

    put_into_table("TCA", 'S');
    put_into_table("TCC", 'S');
    put_into_table("TCG", 'S');
    put_into_table("TCT", 'S');

    put_into_table("TTC", 'F');
    put_into_table("TTT", 'F');

    put_into_table("TTA", 'L');
    put_into_table("TTG", 'L');

    put_into_table("TAC", 'Y');
    put_into_table("TAT", 'Y');

    put_into_table("TAA", '_');
    put_into_table("TAG", '_');

    put_into_table("TGC", 'C');
    put_into_table("TGT", 'C');

    put_into_table("TGA", '_');

    put_into_table("TGG", 'W');

    put_into_table("CTA", 'L');
    put_into_table("CTC", 'L');
    put_into_table("CTG", 'L');
    put_into_table("CTT", 'L');

    put_into_table("CCA", 'P');
    put_into_table("CCC", 'P');
    put_into_table("CCG", 'P');
    put_into_table("CCT", 'P');

    put_into_table("CAC", 'H');
    put_into_table("CAT", 'H');

    put_into_table("CAA", 'Q');
    put_into_table("CAG", 'Q');

    put_into_table("CGA", 'R');
    put_into_table("CGC", 'R');
    put_into_table("CGG", 'R');
    put_into_table("CGT", 'R');

    put_into_table("ATA", 'I');
    put_into_table("ATC", 'I');
    put_into_table("ATT", 'I');

    put_into_table("ATG", 'M');

    put_into_table("ACA", 'T');
    put_into_table("ACC", 'T');
    put_into_table("ACG", 'T');
    put_into_table("ACT", 'T');

    put_into_table("AAC", 'N');
    put_into_table("AAT", 'N');

    put_into_table("AAA", 'K');
    put_into_table("AAG", 'K');

    put_into_table("AGC", 'S');
    put_into_table("AGT", 'S');

    put_into_table("AGA", 'R');
    put_into_table("AGG", 'R');

    put_into_table("GTA", 'V');
    put_into_table("GTC", 'V');
    put_into_table("GTG", 'V');
    put_into_table("GTT", 'V');

    put_into_table("GCA", 'A');
    put_into_table("GCC", 'A');
    put_into_table("GCG", 'A');
    put_into_table("GCT", 'A');

    put_into_table("GAC", 'D');
    put_into_table("GAT", 'D');

    put_into_table("GAA", 'E');
    put_into_table("GAG", 'E');

    put_into_table("GGA", 'G');
    put_into_table("GGC", 'G');
    put_into_table("GGG", 'G');
    put_into_table("GGT", 'G');

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
