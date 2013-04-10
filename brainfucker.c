#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_SIZE 30000

void die( const char * );
void die_errno( const char * );

int main(int argc, char **argv) {
    if( argc < 2 ) {
        die( "no program file given" );
    }
    
    unsigned char tape[ TAPE_SIZE ];
    memset( tape, 0, TAPE_SIZE );
    unsigned char *pointer = tape;
    
    // open program file
    FILE *program = fopen( argv[ 1 ], "r" );
    if( program == NULL ) {
        die_errno( "couldn't open program" );
    }
    
    int ret;
    int bracket_depth;
    unsigned char command;
    while( (ret = fgetc( program )) != EOF ) {
        command = (unsigned char) ret;
        
        switch( command ) {
            case '>':
                if( pointer - tape < TAPE_SIZE - 1 ) {
                    pointer++;
                }
                else {
                    die( "attempting memory access after end of tape" );
                }
                break;
            
            case '<':
                if( pointer - tape > 0 ) {
                    pointer--;
                }
                else {
                    die( "attempting memory access before beginning of tape" );
                }
                break;
                
            case '+':
                (*pointer)++;
                break;
                
            case '-':
                (*pointer)--;
                break;
                
            case '.':
                if( putchar( *pointer ) == EOF ) {
                    die( "putchar failed" );
                }
                break;
                
            case ',':
                if( (ret = getchar()) == EOF ) {
                    if( ferror( stdin ) != 0 ) {
                        die( "getchar failed" );
                    }
                }
                else {
                    *pointer = (unsigned char) ret;
                }
                break;
                
            case '[':
                if( *pointer == 0 ) {
                    bracket_depth = 1;
                    while( bracket_depth > 0 ) {
                        if( (ret = fgetc( program )) == EOF ) {
                            if( ferror( program ) != 0 ) {
                                die( "fgetc on program file failed" );
                            }
                            else {
                                die( "no matching ] found" );
                            }
                        }
                        
                        if( ret == '[' ) {
                            bracket_depth++;
                        }
                        else if( ret == ']' ) {
                            bracket_depth--;
                        }
                    }
                }
                break;
            
            case ']':
                if( *pointer != 0 ) {
                    bracket_depth = 1;
                    while( bracket_depth > 0 ) {
                        if( fseek( program, -2, SEEK_CUR) == -1 ) {
                            die_errno( "fseek on program file failed" );
                        }
                        
                        if( (ret = fgetc( program )) == EOF ) {
                            if( ferror( program ) != 0 ) {
                                die( "fgetc on program file failed" );
                            }
                            else {
                                die( "no matching [ found" );
                            }
                        }
                        
                        if( ret == ']' ) {
                            bracket_depth++;
                        }
                        else if( ret == '[' ) {
                            bracket_depth--;
                        }
                    }
                }
                break;
        }
    }
    
    if( ferror( program ) != 0 ) {
        die( "fgetc on program file failed" );
    }
    
    if( fclose( program ) == EOF ) {
        die_errno( "fclose on program file failed" );
    }
    
    return 0;
}

void die( const char * message ) {
    fprintf( stderr, "ERROR: %s\n", message );
    exit( EXIT_FAILURE );
}

void die_errno( const char * message ) {
    perror( message );
    exit( EXIT_FAILURE );
}
