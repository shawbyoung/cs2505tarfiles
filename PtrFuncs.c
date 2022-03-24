#include "PtrFuncs.h"
#include <inttypes.h>     // for formatting stdint types 
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//// On my honor: // // - I have not discussed the C language code in my program with // anyone other than my instructor or the teaching assistants // assigned to this course. // // - I have not used C language code obtained from another student, // or any other unauthorized source, either modified or unmodified. // // - If any C language code or documentation used in my program // was obtained from an authorized source, such as a text book or // course notes, that has been clearly noted with a proper citation // in the comments of my program. // // - I have not designed this program in such a way as to defeat or // interfere with the normal operation of the Curator System. // // <Shaw Young>

///  Declare any static helper functions you write here!!  ///



/**  Uses pointer-based logic to access a specified portion of a region of
 *   memory and prints the corresponding bytes to a supplied file stream.
 *   The bytes are separated by one or more spaces, and the last byte is
 *   followed by a newline character, just as in the example function.
 * 
 *   Pre: Out is open on a file
 *        baseAddr points to the first byte of the memory region
 *        Offset is the index of the first relevant byte of the memory region
 *        nBytes is the number of bytes to be printed
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.  You may not
 *      use array bracket notation for any reason whatsoever.
 */
void showBytesAtOffset(FILE* Out, const uint8_t* const baseAddr, uint16_t Offset, uint8_t nBytes) {
	for ( uint8_t pos = 0; pos < nBytes; pos++) {
		fprintf(Out, "%02X ", *(baseAddr + Offset + pos) );
	}

	fprintf(Out, "\n");
   // Implement this function!!
}

/**  Uses pointer-based logic to display a specified portion of a region
 *   of memory, using pointer typecasts to control the number of bytes 
 *   that are displayed, and the way those bytes are interpreted.
 * 
 *   Pre:   Out is open on a file
 *          baseAddr points to the first byte of the memory region
 *          Offset is the location, relative to baseAddr, of the first
 *             relevant byte of the memory region
 *          Sgn indicates whether the bytes are to be interpreted as
 *             representing a signed or unsigned integer
 *          nByte is 1, 2, 4 or 8
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.  You may not
 *      use array bracket notation for any reason whatsoever.
 */
void showValueAtOffset(FILE* Out, const uint8_t* const baseAddr, uint32_t Offset, 
                                  Sign Sgn, uint8_t nBytes) {
	if ( Sgn == UNSIGNED ) {
		if ( nBytes == 1 ) {
			fprintf(Out, "%u\n", *( (uint8_t*) (baseAddr + Offset)) );
		}
		if ( nBytes == 2 ) {
			fprintf(Out, "%u\n", *( (uint16_t*) (baseAddr + Offset)) );
		}
		if ( nBytes == 4 ) {

			fprintf(Out, "%u\n", *( (uint32_t*) (baseAddr + Offset)) );
		}
		if ( nBytes == 8 ) {
			fprintf(Out, "%lu\n", *( (uint64_t*) (baseAddr + Offset)) );
		}
	}
	if ( Sgn == SIGNED) {
		if ( nBytes == 1 ) {
			fprintf(Out, "%d\n", *( (int8_t*) (baseAddr + Offset)) );
		}
		if ( nBytes == 2 ) {
			fprintf(Out, "%d\n", *( (int16_t*) (baseAddr + Offset)) );
		}
		if ( nBytes == 4 ) {
			fprintf(Out, "%d\n", *( (int32_t*) (baseAddr + Offset)) );
		}
		if ( nBytes == 8 ) {
			fprintf(Out, "%ld\n", *( (int64_t*) (baseAddr + Offset)) );
		}
	}
   // Implement this function!!
}

/**  Uses pointer-based logic to search a specified portion of a region
 *   of memory for occurrences of a specified one-byte value.  When a
 *   matching byte is found, the offset of that occurrence (relative to
 *   the base address) is written, in hexadecimal.
 * 
 *   Pre:   Out is open on a file
 *          baseAddr points to the first byte of the memory region
 *          Length is number of bytes in the memory region
 *          Byte is the value to be found
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.  You may not
 *      use array bracket notation for any reason whatsoever.
 */
void findOccurrencesOfByte(FILE* Out, const uint8_t* const baseAddr, uint32_t Length, uint8_t Byte) {

   // Implement this function!!
	uint32_t pos = 0;
	while ( pos < Length ) {
		if ( *(baseAddr + pos) == Byte ) {
			fprintf(Out, "%02X ", pos );
		}
		pos++;
	}

	fprintf(Out, "\n");
}

/**  Uses pointer-based logic to copy a specified portion of a region of
 *   memory to replace the bytes in another portion of that memory region.
 * 
 *   Pre:   baseAddr points to the first byte of the memory region to be examined
 *          Source and Destination are offsets of the first bytes of two sections
 *             of the memory region that each contain Length bytes
 *          The regions at offset Source and Destination do not overlap
 *   Post:  Length bytes, beginning at offset Source, have been copied to Length consecutive
 *             consecutive locations, beginning at offset Destination
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.
 */
void copyBlock(const uint8_t* const baseAddr, uint32_t Source, uint32_t Destination, uint32_t Length) {
	for ( int32_t pos = 0; pos < Length; pos++ ) {
		int8_t *psrc = (Source + baseAddr + pos);
		int8_t *pdest = Destination + baseAddr + pos;
		*pdest = *psrc;
	}

   // Implement this function!!
}


/**  Uses pointer-based logic to search a specified portion of a region of
 *   memory for occurrences of a specified sequence of bytes.
 * 
 *   Pre:   Out is open on a file
 *          baseAddr points to the first byte of the memory region
 *          Length is number of bytes in the memory region
 *          Sequence points to a copy of the sequence to be found
 *          sLength is the number of bytes in the sequence
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.  You may not
 *      use array bracket notation for any reason whatsoever.
 */
void findOccurrencesOfSequence(FILE* Out, const uint8_t* const baseAddr, 
                               uint32_t Length, const uint8_t* const Sequence, uint32_t sLength) {
	uint32_t pos = 0;

	while ( pos < Length ) {

		if ( *(baseAddr + pos) == *(Sequence) ) {

			int8_t cSeq = 0;
			for ( int32_t i = 0; i < sLength; i++ ) {

				if ( *(baseAddr + pos + i) != *(Sequence + i) ) {
					cSeq = 1;
				}
			}

			if ( cSeq == 0 ) {
				fprintf(Out, "%02X ", pos);
			}
		}
		pos++;
	}

	fprintf(Out, "\n");
}


/**  Uses pointer-based logic to modify the contents of a specified portion
 *   of a region of memory, by bitwise blending with bytes of another
 *   portion of that memory region.
 * 
 *   Pre:   Out is open on a file
 *          baseAddr points to the first byte of the memory region
 *          First and Second point to the first bytes of two sections
 *             of the memory region that each contain Length bytes
 *          The regions pointed to by First and Second do not overlap
 *   Post:  Length bytes, beginning at *Second, have been blended with Length
 *             bytes, beginning at *First; the blending is accomplished as
 *             follows: the k-th byte of *Second is modified by XORing its
 *             hi nybble with the low nybble of the k-th byte from *First,
 *             and its low nybble with the hi nybble of the k-th byte from
 *             *First.
 *   Restrictions:
 *      You must use only pointer syntax in accessing the data.
 */
void blendBytes(const uint8_t* const First, uint8_t* const Second, uint32_t Length) {
	for ( int32_t pos = 0; pos < Length; pos++ ) {
		int8_t *psrc = ( ~( *(First) ) ) ^ *(Second);
		int8_t *pdest = Second + pos;
		*pdest = *psrc;
	}
   // Implement this function!!
}

