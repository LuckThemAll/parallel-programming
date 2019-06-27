#include "mpi.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#define BUFSIZE 1

void create_file() {
    ofstream file;
    file.open ("file.txt");
    for (int i = 0; i < BUFSIZE*10; i++)
        file << 'a';
    file.close();
}

int main(int argc, char **argv) {
    create_file();
    int num, sum;
    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_File fh;
    char buf[BUFSIZE];

    MPI_File_open(MPI_COMM_WORLD, "file.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &fh);
    MPI_File_set_view(fh, 0, MPI_CHAR, MPI_CHAR, "native", MPI_INFO_NULL);
    do{
        MPI_File_read(fh, buf, BUFSIZE, MPI_CHAR, &status);
        MPI_Get_count(&status, MPI_CHAR, &num);
        printf("buf=%s\n", buf);
        sum += num;
    } while(num >= BUFSIZE);
    MPI_File_close(&fh);
    //    вывести число считанных символов sum из файла
    cout << sum << endl;
    MPI_Finalize();

    remove("file.txt");
    return EXIT_SUCCESS;
}