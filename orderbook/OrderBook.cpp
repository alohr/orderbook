#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "LobsterOrderBook.h"
#include "SimpleOrderBook.h"

#include "cmdline.h"

static bool debug = false;

struct Context {
    gengetopt_args_info argsinfo;
};

void usage(int status)
{
    cmdline_parser_print_help();
    exit(status);
}

void processFiles(MessageReader& reader, Context& context)
{
    for (unsigned i = 0; i < context.argsinfo.inputs_num; ++i) {
        const char *filename = context.argsinfo.inputs[i];
        reader.read(filename);
    }
}

int main(int argc, char *argv[])
{
    Context context;
    gengetopt_args_info *argsinfo = &context.argsinfo;
    MessageReader *reader = nullptr;
    
    memset(&context.argsinfo, 0, sizeof context.argsinfo);
    if (cmdline_parser( argc, argv, argsinfo) != 0)
        exit(2);

    if (argsinfo->inputs_num == 0)
        usage(2);

    if (argsinfo->lobster_flag) {
        LobsterOrderBook orderbook;
        LobsterReader reader(orderbook);
        processFiles(reader, context);
        orderbook.print();
    } else {
        SimpleOrderBook orderbook;
        SimpleMessageReader reader(orderbook);
        processFiles(reader, context);
        orderbook.print();
    }

    cmdline_parser_free(argsinfo);
    
    return 0;
}
