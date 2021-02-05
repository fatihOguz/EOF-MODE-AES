# EOF-MODE-AES


EOF
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
Note XOR lama işlemleri main d
