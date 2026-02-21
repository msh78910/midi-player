#include <stdio.h>
#include <string.h>
#include "MIDI_header.h"
#include <soundio/endian.h>
#include <soundio/soundio.h>

int beep (float freq , int len);

// Run: gcc main.c beep.o libsoundio.so.2 -lm
int isCorrupted_MIDIFile(FILE* file);
int playMIDI(FILE* file);

int main(int argc, char **argv) {
    int len = beep (500.0f, 1000);
    char address[100];
    if (argc > 1) {
        strcpy(address, argv[1]);
    } else {
        puts("Enter the MIDI file's address:");
        /* *address = */ fgets(address ,99 , stdin);
    }
    FILE* file = fopen (address, "rb");
    if (file == NULL)  {
        printf("%s %s\n", "couldn't read the file from: ", address);
        return 1; // the appropriate number for failing to read a file
    }
    
    // test the MIDI file integrity
    int integrityStatusCode = 0;
    if ((integrityStatusCode = isCorrupted_MIDIFile(file)) ) {
        printf ("%s%d\n", "file is curropted with the status code ", integrityStatusCode);
        return 1;
    }

    if ( playMIDI(file) ) {
        printf ("%s\n", "Error while playing the file ");
        return 1;
    }

    fclose(file);

    puts ("Read the MIDI file successfully");

    return 0;
}

// returns 0 if integrated and healthy and ERROR_CODE if it's not
int isCorrupted_MIDIFile(FILE* file) {

    return 0; // is integrated/healthy
}

int playMIDI(FILE* file) {


    return 0;
}