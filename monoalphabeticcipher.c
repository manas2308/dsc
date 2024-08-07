#include<stdio.h>
#include<ctype.h>
#include<string.h>
void encrypt(char text[],const char key[],char encrypted_text[]);
void decrypt(char text[],const char key[],char decrypted_text[]);
int main(){
	char text[100];
	char encrypted_text[100];
	char decrypted_text[100];
	const char *key="QWERTYUIOPASDFGHJKLZXCVBNM";
	printf("enter the text: ");
	fgets(text,sizeof(text),stdin);
	encrypt(text,key,encrypted_text);
	printf("encrypted text:%s\n",encrypted_text);
	decrypt(encrypted_text,key,decrypted_text);
	printf("decrypted text:%s\n",decrypted_text);
	return 0;
}
void encrypt(char text[],const char key[],char encrypted_text[]){
	for(int i=0;text[i]!='\0';i++){
		if(isalpha(text[i])){
			char offset=isupper(text[i])?'A':'a';
			encrypted_text[i]=key[toupper(text[i])-'A'];
			if(islower(text[i])){
				encrypted_text[i]=tolower(encrypted_text[i]);
			}
		}else{
			encrypted_text[i]=text[i];
		}
	}
	encrypted_text[strlen(text)]='\0';
}
void decrypt(char text[],const char key[],char decrypted_text[]){
	char reversekey[26];
	for(int i=0;i<26;i++){
		reversekey[key[i]-'A']='A'+i;
	}
	for(int i=0;text[i]!=0;i++){
		if(isalpha(text[i])){
			char offset=isupper(text[i])?'A':'a';
			decrypted_text[i]=reversekey[toupper(text[i])-'A'];
			if(islower(text[i])){
				decrypted_text[i]=tolower(decrypted_text[i]);
			}
		}else{
			decrypted_text[i]=text[i];
		}
	}
	decrypted_text[strlen(text)]='\0';
}