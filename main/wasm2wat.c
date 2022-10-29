#include "../src/ast.h"
#include "../src/read_bin.h"
#include "../src/write_wat.h"

int web49_file_main(const char *inarg, const char *outarg) {
    FILE *infile = fopen(inarg, "rb");
    if (infile == NULL) {
        fprintf(stderr, "cannot open file: %s\n", inarg);
        return 1;
    }
    web49_module_t mod = web49_readbin_module(infile);
    fclose(infile);
    if (outarg == NULL) {
        web49_wat_print_module(stdout, mod);
    } else {
        FILE *outfile = fopen(outarg, "wb");
        web49_wat_print_module(outfile, mod);
        fclose(outfile);
    }
    return 0;
}

int main(int argc, const char **argv) {
    const char *inarg = NULL;
    const char *outarg = NULL;
    for (size_t i = 1; i < argc; i += 1) {
        if (!strcmp(argv[i], "-o")) {
            i += 1;
            outarg = argv[i];
        } else if (inarg == NULL) {
            inarg = argv[i];
        } else {
            fprintf(stderr, "extra cli arg: %s\n", argv[i]);
            return 1;
        }
    }
    return web49_file_main(inarg, outarg);
}
