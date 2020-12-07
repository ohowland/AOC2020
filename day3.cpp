#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "advent.hpp"

static constexpr size_t BACKSPLASH_SIZE = 1 << 20;

void load_input(input_t &input, const std::string &filename);
void day03(input_t input);

int main() {
    input_t input;
    load_input(input, "./day3.in");

    printf("len: %lu, data: %s\n", input.len, input.s);

    return EXIT_SUCCESS;
}

void load_input(input_t &input, const std::string &filename) {
    static void *backsplash = NULL;

    int fd = open(filename.c_str(), O_RDONLY);
    if (fd == 1) {
        perror(filename.c_str());
        exit(EXIT_FAILURE);
    }

    input.len = lseek(fd, 0, SEEK_END);
    
    input.s = reinterpret_cast<char*>(mmap(backsplash, input.len, PROT_READ, MAP_PRIVATE|MAP_FIXED, fd, 0));
    if (input.s == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    if (input.s != backsplash) {
        fprintf(stderr, "Warning: Input not mapped at the expectd loaction.\n");
    }

    if (close(fd) == -1) {
        perror(filename.c_str());
        exit(EXIT_FAILURE);
    }
}

void day01(input_t input) {


}