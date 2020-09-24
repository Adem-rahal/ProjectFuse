
 
#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

char dir_list[ 256 ][ 256 ];
int curr_dir_idx = -1;

char files_list[ 256 ][ 256 ];
int curr_file_idx = -1;

char files_content[ 256 ][ 256 ];
int curr_file_content_idx = -1;

int get_file_index( const char *path )
{
	path++; // On enlève le / 
	
	for ( int curr_idx = 0; curr_idx <= curr_file_idx; curr_idx++ )
		if ( strcmp( path, files_list[ curr_idx ] ) == 0 )
			return curr_idx;
	
	return -1;
}

void write_to_file( const char *path, const char *new_content )
{
	int file_idx = get_file_index( path );
	
	if ( file_idx == -1 ) // No such file
		return;
		
	strcpy( files_content[ file_idx ], new_content ); 
}

static int do_getattr( const char *path, struct stat *st)
{
	printf( "[getattr] Called\n" );
	printf( "\tAttributes of %s requested\n", path );
	
	
	st->st_uid = getuid(); 
	st->st_gid = getgid(); 
	st->st_atime = time( NULL ); 
	st->st_mtime = time( NULL ); 
	
	if ( strcmp( path, "/" ) == 0 )
	{
		st->st_mode = S_IFDIR | 0755;
		st->st_nlink = 2; 
	}
	else
	{
		st->st_mode = S_IFREG | 0644;
		st->st_nlink = 1;
		st->st_size = 1024;
	}
	
	return 0;
}

static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi )
{
	printf( "--> Getting The List of Files of %s\n", path );
	
	filler( buffer, ".", NULL, 0,0); // Current Directory
	filler( buffer, "..", NULL, 0,0 ); // Parent Directory
	
	if ( strcmp( path, "/" ) == 0 ) // If the user is trying to show the files/directories of the root directory show the following
	{
		filler( buffer, "hello", NULL, 0, 0 );
		filler( buffer, "shutdown", NULL, 0 ,0);
		filler( buffer, "suspend", NULL, 0 ,0);
		filler ( buffer, "update", NULL, 0 ,0);
		filler ( buffer, "test", NULL, 0 ,0);
	}
	
	return 0;
}

static int do_read( const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fi )
{
	printf( "--> Trying to read %s, %u, %u\n", path, offset, size );
	
	char helloText[] = "Hello\n";
	
	
	char *selectedText = NULL;
	
	
	
	if ( strcmp( path, "/hello" ) == 0 )
		selectedText = helloText;
	
	else if (strcmp( path, "/update" ) == 0)
		system("sudo apt update");
		
	else
		return -1;
	
	
	
	memcpy( buffer, selectedText + offset, size );
		
	return strlen( selectedText ) - offset;
}

static int do_write( const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *info )
{
	if ( strcmp( path, "/shutdown" ) == 0 )
		system("shutdown -P now");
	else if ( strcmp( path, "/suspend" ) == 0 )
		system("systemctl suspend");

	write_to_file( path, buffer );
	
	return size;
}

static struct fuse_operations operations = {
    .getattr	= do_getattr,
    .readdir	= do_readdir,
    .read		= do_read,
	.write		= do_write,
};

int main( int argc, char *argv[] )
{
	return fuse_main( argc, argv, &operations, NULL );
	
}
