#include <stdio.h>
malloc, free,
printf, write, 
access, open, read, close,
strerror, perror,
fork, wait, waitpid, wait3, wait4, 
exit, 
execve, 
dup, dup2, pipe,

char *readline (const char *prompt);
		"readline will read a line from the terminal and return it, using prompt
	as a prompt.  If prompt is NULL or the empty string, no prompt  is  is‐
	sued.   The  line returned is allocated with malloc(3); the caller must
	free it when finished.  The line returned has  the  final  newline  re‐
	moved, so only the text of the line remains.

	readline  offers  editing  capabilities  while the user is entering the
	line.  By default, the line editing commands are similar  to  those  of
	emacs.  A vi-style line editing interface is also available."

void rl_clear_history (void)
	"Clear the history list by deleting all of the entries, in the same manner as the History library's
	 clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list."


int rl_on_new_line (void)
	"Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. "



void rl_replace_line (const char *text, int clear_undo)
	"Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If
	 clear_undo is non-zero, the undo list associated with the current line is cleared. "

void rl_redisplay (void)
    "Change what's displayed on the screen to reflect the current contents of rl_line_buffer."


void add_history (const char *string)
    "Place string at the end of the history list. The associated data field (if any) is set to NULL.
	 If the maximum number of history entries has been set using stifle_history(), and the new number of history entries would exceed that maximum, the oldest history entry is removed."


#include <signal.h>

	sighandler_t signal(int signum, sighandler_t handler)

 #include <signal.h>

	int sigaction(int signum, const struct sigaction *act,
			struct sigaction *oldact);
#include <signal.h>

	int sigemptyset(sigset_t *set);
"sigemptyset() initializes the signal set given by set to empty, with all signals excluded from the set."
int sigaddset(sigset_t *set, int signum);
"sigaddset() and sigdelset() add and delete respectively signal signum from set."

#include <sys/types.h>
	#include <signal.h>

	int kill(pid_t pid, int sig);
#include <unistd.h>

	char *getcwd(char *buf, size_t size);
#include <unistd.h>
"The  getcwd() function copies an absolute pathname of the current working directory to the array pointed to by
       buf, which is of length size.

       If the length of the absolute pathname of the current working directory, including the terminating null  byte,
       exceeds  size bytes, NULL is returned, and errno is set to ERANGE; an application should check for this error,
       and allocate a larger buffer if necessary.

       As an extension to the POSIX.1-2001 standard, glibc's getcwd() allocates the  buffer  dynamically  using  mal‐
       loc(3)  if  buf is NULL.  In this case, the allocated buffer has the length size unless size is zero, when buf
       is allocated as big as necessary.  The caller should free(3) the returned buffer."

	int chdir(const char *path);
"chdir() changes the current working directory of the calling process to the directory specified in path."

#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>

	int stat(const char *pathname, struct stat *statbuf);
	int fstat(int fd, struct stat *statbuf);
	int lstat(const char *pathname, struct stat *statbuf);
		"These  functions return information about a file, in the buffer pointed to by statbuf.  No permissions are required on the file itself, but—in the case of stat(), fs‐
		tatat(), and lstat()—execute (search) permission is required on all of the directories in pathname that lead to the file.

		stat() and fstatat() retrieve information about the file pointed to by pathname; the differences for fstatat() are described below.

		lstat() is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that it refers to.

		fstat() is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd."
#include <unistd.h>

	int unlink(const char *pathname);
	"unlink()  deletes  a name from the filesystem.  If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was
	using is made available for reuse.

	If the name was the last link to a file but any processes still have the file open, the file will remain in existence until the last file descriptor referring  to  it
	is closed.

	If the name referred to a symbolic link, the link is removed.

	If the name referred to a socket, FIFO, or device, the name for it is removed but processes which have the object open may continue to use it."
#include <sys/types.h>
	#include <dirent.h>

	DIR *opendir(const char *name);
	   "The  opendir()  function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream.  The stream is positioned at the
	first entry in the directory."
#include <dirent.h>

	struct dirent *readdir(DIR *dirp); 
	   "The  readdir()  function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL on
	reaching the end of the directory stream or if an error occurred.

	In the glibc implementation, the dirent structure is defined as follows:

	    struct dirent {
		 ino_t	   d_ino;	/* Inode number */
		 off_t	   d_off;	/* Not an offset; see below */
		 unsigned short d_reclen;    /* Length of this record */
		 unsigned char  d_type;      /* Type of file; not supported
						    by all filesystem types */
		 char	    d_name[256]; /* Null-terminated filename */
	    };"
#include <sys/types.h>
#include <dirent.h>

	int closedir(DIR *dirp);
"The  closedir() function closes the directory stream associated with dirp.  A successful call to closedir() also closes the underlying file descriptor associated with
	dirp.  The directory stream descriptor dirp is not available after this call."
#include <unistd.h>

	int isatty(int fd); 
	   "The isatty() function tests whether fd is an open file descriptor referring to a terminal."
#include <unistd.h>

char *ttyname(int fd);
"The function ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error (for example,
	if fd is not connected to a terminal).  The return value may point to static data, possibly overwritten by the next call.  The function ttyname_r() stores this  path‐
	name in the buffer buf of length buflen."
#include <unistd.h>

int ttyslot(void);
"The legacy function ttyslot() returns the index of the current user's entry in some file."

#include <sys/ioctl.h>

	int ioctl(int fd, unsigned long request, ...);
"The  ioctl()  system  call  manipulates  the  underlying device parameters of special files.  In particular, many operating characteristics of character special files
	(e.g., terminals) may be controlled with ioctl() requests.  The argument fd must be an open file descriptor.

	The second argument is a device-dependent request code.  The third argument is an untyped pointer to memory.  It's traditionally char *argp (from the days before void
	* was valid C), and will be so named for this discussion.

	An ioctl() request has encoded in it whether the argument is an in parameter or out parameter, and the size of the argument argp in bytes.  Macros and defines used in
	specifying an ioctl() request are located in the file <sys/ioctl.h>."

#include <stdlib.h>

	char *getenv(const char *name);
"The getenv() function searches the environment list to find the environment variable name, and returns a pointer to the corresponding value string."
#include <termios.h>
	#include <unistd.h>

	int tcgetattr(int fd, struct termios *termios_p);

	int tcsetattr(int fd, int optional_actions,
			const struct termios *termios_p);
	"tcgetattr() gets the parameters associated with the object referred by fd and stores them in the termios structure referenced by termios_p.  This function may be  in‐
	voked from a background process; however, the terminal attributes may be subsequently changed by a foreground process.

	tcsetattr()  sets  the parameters associated with the terminal (unless support is required from the underlying hardware that is not available) from the termios struc‐
	ture referred to by termios_p.  optional_actions specifies when the changes take effect:"

#include <curses.h>
#include <term.h>
int tgetent(char *bp, const char *name);
int tgetflag(char *id);
int tgetnum(char *id);
char *tgetstr(char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));
"These routines are included as a conversion aid for programs that use the termcap library. Their parameters are the same and the routines are emulated using the terminfo database. Thus, they can only be used to query the capabilities of entries for which a terminfo entry has been compiled.

The tgetent routine loads the entry for name. It returns 1 on success, 0 if there is no such entry, and -1 if the terminfo database could not be found. The emulation ignores the buffer pointer bp.

The tgetflag routine gets the boolean entry for id, or zero if it is not available.

The tgetnum routine gets the numeric entry for id, or -1 if it is not available.

The tgetstr routine returns the string entry for id, or zero if it is not available. Use tputs to output the returned string. The return value will also be copied to the buffer pointed to by area, and the area value will be updated to point past the null ending this value.

Only the first two characters of the id parameter of tgetflag, tgetnum and tgetstr are compared in lookups.

The tgoto routine instantiates the parameters into the given capability. The output from this routine is to be passed to tputs.

The tputs routine is described on the curs_terminfo(3X) manual page. It can retrieve capabilities by either termcap or terminfo name.

The variables PC, UP and BC are set by tgetent to the terminfo entry's data for pad_char, cursor_up and backspace_if_not_bs, respectively. UP is not used by ncurses. PC is used in the tdelay_output function. BC is used in the tgoto emulation. The variable ospeed is set by ncurses in a system-specific coding to reflect the terminal speed.
Return Value

Except where explicitly noted, routines that return an integer return ERR upon failure and OK (SVr4 only specifies "an integer value other than ERR") upon successful completion.

Routines that return pointers return NULL on error."