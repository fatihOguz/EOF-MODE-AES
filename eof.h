#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
# include <assert.h> 

// matrisler için size bilgileri 
#define KEY_SIZE 4
#define TEXT_SIZE 4
#define STATE_SIZE 4
#define SBOX_SIZE 16
#define MAX_ROUNDS 11
#define SBOX_LOOKUP(lookup_box, num) lookup_box[(num) >> 4][(num) & 0x0F];

uint8_t static initChipper[KEY_SIZE][KEY_SIZE];
// anahtar matrisi
uint8_t static key[KEY_SIZE][KEY_SIZE];
// state matrisi
uint8_t static state[STATE_SIZE][STATE_SIZE];

uint8_t static plainText[STATE_SIZE][STATE_SIZE];

uint8_t static chipper[STATE_SIZE][STATE_SIZE];


uint8_t static allChipper[TEXT_SIZE][STATE_SIZE][STATE_SIZE];
// orginal mesajımı tutan matrisim
uint8_t static orig_msg[STATE_SIZE][STATE_SIZE];
// substitute box matrisi
uint8_t static sbox[SBOX_SIZE][SBOX_SIZE];
// deşifrelemede kullandığım substitute box matrisi
uint8_t static inv_sbox[SBOX_SIZE][SBOX_SIZE];
// roundlara göre anahtar matrisi
uint8_t static sub_keys [MAX_ROUNDS][KEY_SIZE][KEY_SIZE];
int initialize_called;


/**
	command arguman line ile alınan file ları matris yapar
	anahtar üretimini gerçekleştirip aes şifreleme algoritmasının başlangıç durumuna hazırlar
	*/
void initialize(char * key_file, char * state_file, char* sbox_file, char* inv_sbox_file,char* Init_Chipper_file);
/**
	SubBytes
	ShiftRows
	MixColumns
	addRoundKey
	şeklinde 9 round ve final round unda bu işlemden mix columns haricinde bir kere daha 
	gerçekleyip chipper text e ulaşır.
	*/
void encrypt();
/**
	encrypt fonksiyonunun geriye yönelik işlemlerini yapıp orjinal metne ulaşır.
	*/
void decrypt();

uint8_t * getState();
/**
	ekrana state basar
	*/
void printState();
/**
	ekrena subkeys basar
	*/
void printSubKeys();
/**
	programın başarılı bi şekilde bitip bitmediği bilgisini ekranda gösterir.
	*/
void assertStateIsOrigMesg();
/**
	subkeys ve s box matrisleri ile işleme girip bir anahtar üretir
	*/
void generateSubkeys();
/**
	command argumant line dan aldığı file ları uygun bir şekilde matris's çevirir.
*/
void initFromFile(int size, uint8_t matrix[size][size], char * file_name);
/**
Step4
	AddRoundKey:
	matrisimizin anahtar matrisi ile xor lanması işlemi
*/
void addRoundKey(int round);
/**
Shift Rows:
	matrisin satırının index numarasınca sola shift etme işlemi
	bu fonksiyon şifreleme için kullanılır
	deşifrelemede 1 sağ yapılmalı*/	
void shiftRows();
/**
Shift Rows:
	matrisin satırının index numarasınca sağa shift etme işlemi
	bu fonksiyon deşifreleme için kullanılır
	şifrelemede 1 sola yapılmalı*/
void invShiftRows();
/** 
	Shift row işlemi için yardımcı fonksiyondur.
	1 kere sola shift etme işlemini yapar
	*/
void helperShiftRow(int row);
/**
Substitute Bytes:
	Orjinal mesaj matrisin 8 bitlik bilgilerini Sbox a yerleştirilme işlemini yapar
	*/
void subByte(uint8_t sbox_to_use[SBOX_SIZE][SBOX_SIZE]);
/**
Step3
	Mix Matrix:
	matrisin 1.colon ile bir matris ile çarpılıp kendi kolanuna konulması

*/
void mixColumns();
/**
	mix Columns işleminin tersini gerçekleştirir
	deşifrelemede kullanılır
	*/
void invMixColumns();
/**matrisi ekrana basar*/
void printMatrix(int size, uint8_t matrix[size][size]);
// https://en.wikipedia.org/wiki/Finite_field_arithmetic
uint8_t gmult(uint8_t a, uint8_t b);
