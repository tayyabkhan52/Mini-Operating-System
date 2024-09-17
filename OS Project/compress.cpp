#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <zlib.h>
#include <fstream>
#define CHUNK 16384

int main(int argc, char *argv[]) {
    char input_file[256];
    int process_choice = 12, terminate_signal = 1, yet_to_read = 1;
    char terminate = 'n';
    while (terminate != 'y') {
        printf("Enter the name of the input file: ");
        scanf("%255s", input_file);

        char *output_file = new char[strlen(input_file) + 4];

        strcpy(output_file, input_file);
        strcat(output_file, ".gz");

        int input_fd = open(input_file, O_RDONLY);
        if (input_fd < 0) {
            perror("open");
            exit(1);
        }

        int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (output_fd < 0) {
            perror("open");
            exit(1);
        }

        int ret;
        z_stream strm;
        unsigned char in[CHUNK];
        unsigned char out[CHUNK];

        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        ret = deflateInit2(&strm, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY);
        if (ret != Z_OK) {
            fprintf(stderr, "deflateInit2 failed with error code %d\n", ret);
            exit(1);
        }

        do {
            strm.avail_in = read(input_fd, in, CHUNK);
            if (strm.avail_in == -1) {
                perror("read");
                exit(1);
            }
            strm.next_in = in;

            do {
                strm.avail_out = CHUNK;
                strm.next_out = out;
                ret = deflate(&strm, Z_FINISH);
                if (ret == Z_STREAM_ERROR) {
                    fprintf(stderr, "deflate failed with error code %d\n", ret);
                    exit(1);
                }
                int have = CHUNK - strm.avail_out;
                if (write(output_fd, out, have) != have) {
                    perror("write");
                    exit(1);
                }
            } while (strm.avail_out == 0);

        } while (ret != Z_STREAM_END);

        ret = deflateEnd(&strm);
        if (ret != Z_OK) {
            fprintf(stderr, "deflateEnd failed with error code %d\n", ret);
            exit(1);
        }

        close(input_fd);
        close(output_fd);

        printf("File compressed successfully to %s\n", output_file);

        delete[] output_file;
        std::cout << "Want to terminate the program? Press y if yes, or any other key to continue." << std::endl;
        std::cin >> terminate;
    }

    std::ofstream outfile("IPC.txt");
    char a = ',';
    // Write two integer values to the file
    outfile << yet_to_read << a << terminate_signal << a << process_choice << std::endl;
    // Close the file
    outfile.close();

    return 0;
}

