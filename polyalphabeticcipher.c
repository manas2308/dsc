#include<stdio.h>
#include<string.h>
#include<ctype.h>
void encrypt(char text[],char key[]);
void decrypt(char text[],char key[]);
void generatekey(char text[],char key[],char newkey[]);
int main(){
	char text[100];
	char key[100];
	char newkey[100];
	printf("enter the text: ");
	gets(text);
	printf("enter the key: ");
	gets(key);
	generatekey(text,key,newkey);
	encrypt(text,newkey);
	printf("%s is encrypted\n",text);
	decrypt(text,newkey);
	printf("%s is decrypted\n",text);
	return 0;
}
void generatekey(char text[],char key[],char newkey[]){
	int textlen=strlen(text);
	int keylen=strlen(key);
	int i,j;
	for(i=0,j=0;i<textlen;i++,j++){
		if(j==keylen)j=0;
		newkey[i]=toupper(key[j]);
	}
	newkey[i]='\0';
}
void encrypt(char text[],char key[]){
	int textlen=strlen(text);
	for(int i=0;i<textlen;i++){
		if(isalpha(text[i])){
			char offset=isupper(text[i])?'A':'a';
			text[i]=(toupper(text[i])+key[i]-2*'A')%26+offset;
		}
	}
}
void decrypt(char text[], char key[]) {
    int textlen = strlen(text);
    for (int i = 0; i < textlen; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (toupper(text[i]) - key[i] + 26) % 26 + offset;
        }
    }
}