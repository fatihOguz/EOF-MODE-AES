/******************************************************************************************

        aes programının encrypt ve decrypt fonksiyonlarında bir önceki şifreyi cipher adlı
        bir matrise atadım.

        IV cipher dosya olarak dışarıdan alındı(initial chipper)



       main fonksiyonda 3 tane aes işlemi 
       Ci = Encrypt(Pi ^ Ci-1)
       CO = IV,
       cbc mode formülünce şifrelendi
       bu 3 aes işlemi için plainText1,2,3 command arguman line ile alındı

       Pi = Decrypt(Ci) ^ Ci-1
       C0=IV
       cbc mode formülünce de şifreler geri çözüldü
       Her aşamada plain textler matris şekilde bastırıldı.



       Note XOR lama işlemleri main de yapıldı.

*********************************************************************************************/




/**********************************************************************************************/
#include "eof.h"
#include "eofmake.c"
int main(int argc, char *argv[])
{
    if(argc < 5) {
        printf("ERROR: expecting 7 paths \"key_file, 3 plaintext_file, sbox_file, inv_sbox_file,Init_Chipper_file\"\n");
        exit(-1);
    }

    char* key_file = NULL, *state_file = NULL, *sbox_file = NULL, *inv_sbox_file = NULL  ,*Init_Chipper_file = NULL;
    key_file = argv[1];
    sbox_file = argv[2];
    inv_sbox_file = argv[3];
    Init_Chipper_file = argv[4];
     state_file = argv[5];
     int count = 5;
    initialize(key_file, state_file, sbox_file, inv_sbox_file,Init_Chipper_file);



/**************************************************************************************************************/
    
    for(int a=0;a<3;a++){



        state_file=argv[count+a];
        initFromFile(STATE_SIZE, plainText, state_file);
        printf("\n\n*********************************\n");
        printf("%d.Plain Text ",a+1);
        printMatrix(STATE_SIZE,plainText);
        printf("*********************************\n");
        for(int i=0;i<STATE_SIZE;i++){
           for(int j=0;j<STATE_SIZE;j++){
               state[i][j]=initChipper[i][j];
            }
        }
        encrypt();

        for(int i=0;i<STATE_SIZE;i++){
            for(int j=0;j<STATE_SIZE;j++){
                allChipper[a][i][j]=state[i][j] ^ plainText[i][j];
            }
        }
        printf("\n\n*********************************\n");
         printf("%d.Chipper Text",a+1 );
        printMatrix(STATE_SIZE,allChipper[a]);
        printf("*********************************\n");

    }

   
/************************************************************************************************************************************/
printf("decrypt   Decrypt   Decrypt  Decrypt  Decrypt  Decrypt   Decrypt   Decrypt   Decrypt    Decrypt     Decrypt      Decrypt     Decrypt\n");

 for(int a=0;a<3;a++){



        
        for(int i=0;i<STATE_SIZE;i++){
           for(int j=0;j<STATE_SIZE;j++){
               state[i][j]=initChipper[i][j];
            }
        }
        encrypt();

        for(int i=0;i<STATE_SIZE;i++){
            for(int j=0;j<STATE_SIZE;j++){
                plainText[i][j]=state[i][j] ^ allChipper[a][i][j];
            }
        }
        printf("\n\n*********************************\n");
         printf("%d.Plain Text",a+1 );
        printMatrix(STATE_SIZE,plainText);
printf("*********************************\n");

    }


    


   
    return 0;
}


/**********************************************************************************************/

