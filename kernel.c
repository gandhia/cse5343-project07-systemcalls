/* kernel.c
   A kernel that inputs system calls and interrupts.
   Avani Gandhi
*/

void printString(char* word);
void readString(char* word);
void readSector(char* buffer, int sector);
int mod(int a, int b);
void handleInterrupt21 (int ax, int bx, int cx, int dx);
char line[80];
char buffer[512];

int main () {
	printString("Hello World.\r\n\0");
	printString("Enter a line:  \0");
	readString(line);
	printString("\r\n\0");
	printString(line);
	printString("\r\n\0");
	readSector(buffer, 30);
	printString(buffer);
	printString("\r\n\0");
	makeInterrupt21();
	interrupt(0x21,0,0,0,0);
//	interrupt (0x21,1,line,0,0);
//	interrupt (0x21,0,line,0,0);

	while (1) {
//	  todo
	}
	return 0;
}

void printString(char* word) {
	int x=0;
	char c = word[x];
	while (c != 0) {
		interrupt(0x10, 0xe * 256 + c, 0, 0, 0);
		x=x+1;
		c = word[x];
	}
}

void readString(char* word) {
	int x=0;
	char c = interrupt(0x16, 0, 0, 0, 0);
	while (c != 0xd) {
		word[x] = c;
		interrupt(0x10, 0xe * 256 + c, 0, 0, 0);
		x=x+1;
		c = interrupt(0x16, 0, 0, 0, 0);
		while (c == 0x8) {
			if (x > 0) {
				x = x-1;
			}
			c = interrupt(0x16, 0, 0, 0 ,0);			
		}
	}
	word[x] = 0xa;
	word[x+1] = 0x0;
}

void readSector(char* buffer, int sector) {
	int CH = sector/36;
	int CL = mod (sector, 18);
	int DH = mod (sector/18, 2);
	interrupt(0x13, 2 * 256 + 1, buffer, CH * 256 + CL + 1, DH * 256 + 0);
}

void handleInterrupt21 (int ax, int bx, int cx, int dx) {
	printString("Hello World...again.");
/*	if (ax == 0) {
		printString (bx);
	}
	else if (ax == 1) {
		readString (bx);
	}
	else if (ax == 2) {
		readSector (bx, cx);
	}
	else {
		printString ("You entered an improper value. System fail.");
	}
*/}

int mod (int a, int b) {
	while (a >= b) {
		a = a-b;
	}
	return a;
}