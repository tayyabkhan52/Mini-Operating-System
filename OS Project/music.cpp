#include <ao/ao.h>
#include <mpg123.h>
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char **argv) {
    int process_choice = 15, terminate_signal = 1, yet_to_read = 1;
    char terminate = 'n';

    while (terminate != 'y') {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
            return 1;
        }

        ao_initialize();

        int driver = ao_default_driver_id();

        mpg123_init();
        mpg123_handle *mh = mpg123_new(NULL, NULL);
        mpg123_open(mh, argv[1]);
        mpg123_format_none(mh);
        mpg123_format(mh, 44100, MPG123_STEREO, MPG123_ENC_SIGNED_16);

        int channels, encoding;
        long rate;
        mpg123_getformat(mh, &rate, &channels, &encoding);

        ao_sample_format format;
        format.bits = 16;
        format.channels = channels;
        format.rate = rate;
        format.byte_format = AO_FMT_LITTLE;
        format.matrix = 0;

        ao_device *device = ao_open_live(driver, &format, NULL);
        char *buffer = new char[4096];
        size_t done;

        while (mpg123_read(mh, (unsigned char *) buffer, 4096, &done) == MPG123_OK) {
            ao_play(device, buffer, done);
        }

        delete[] buffer;
        ao_close(device);
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        ao_shutdown();
        cout << "Want to terminate the program? Press y if yes, or any other key to continue." << endl;
        cin >> terminate;
    }

    std::ofstream outfile("IPC.txt");
    char a = ',';
    // Write two integer values to the file
    outfile << yet_to_read << a << terminate_signal << a << process_choice << std::endl;
    // Close the file
    outfile.close();
    return 0;
}

