#include <stdio.h>
#include "MIDI_header.h"
#include <soundio/endian.h>
#include <soundio/soundio.h>

int beep (float freq , int len);

// Run: gcc main.c beep.o libsoundio.so.2 -lm
int isCorrupted_MIDIFile(FILE* file);
int playMIDI(FILE* file);

int main2();

int main() {
    int len = beep (1000.0f, 3000);
    return 0;
}

int main2() {
    int len = beep (1000.0f, 1000);
    return 0;

    char * address = "argv";
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