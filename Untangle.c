#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Untangle.h"

uint8_t Untangle(DataFormat Fmt, const uint8_t* pBuffer, WordRecord* const wordList) {

	uint8_t nWords = 0; 	

	if ( Fmt == CLEAR ) { 

		uint16_t offset = (uint16_t) pBuffer[0];
		WordRecord *cword = malloc( sizeof(WordRecord) );

		if ( offset != 0 ) { 
			while ( offset != 0 ) {
			
				// house keeping
				nWords+=1;				
				uint8_t len = pBuffer[ offset ] - 3;			
				cword->word = calloc( len, sizeof(char) );
				
				//fill up the word (char array in wordrecord) 
				for ( int i = 0; i < len; i++ ) {
					cword->word[i] = (char) pBuffer[offset + 3 + i];				
				}
				
				offset = (uint16_t) pBuffer[offset + 1];
			}
		}
			
		return nWords;	
	}

	else {
		return 0;
	}

}

void clearWordRecords(WordRecord* const wordList, uint8_t nWords) {
	free ( wordList ); 
	nWords = 0;
	
}


