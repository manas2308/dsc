#include<stdio.h>
#include<ctype.h>
void encrypt(char text[],int shift,char encrypted_text[]);
void decrypt(char text[],int shift,char decrypted_text[]);
int main(){
	int shift;
	char text[100];
	char encrypted_text[100];
	char decrypted_text[100];
	printf("enter the text: ");
	fgets(text,sizeof(text),stdin);
	printf("enter the shift: ");
	scanf("%d",&shift);
	encrypt(text,shift,encrypted_text);
	printf("encrypted text:%s\n",encrypted_text);
	decrypt(text,shift,decrypted_text);
	printf("decrypted text:%s\n",decrypted_text);
	return 0;
}
void encrypt(char text[],int shift,char encrypted_text[]){
	for(int i=0;text[i]!='\0';i++){
		if(isalpha(text[i])){
			char offset=isupper(text[i])?'A':'a';
			encrypted_text[i]=(text[i]+offset+shift)%26+offset;
		}else{
			encrypted_text[i]=text[i];
		}
	}
	encrypted_text[strlen(text)]='\0';
}
void decrypt(char text[],int shift,char decrypted_text[]){
	for(int i=0;text[i]!='\0';i++){
		if(isalpha(text[i])){
			char offset=isupper(text[i])?'A':'a';
			decrypted_text[i]=(text[i]-offset-shift+26)%26+offset;
		}else{
			decrypted_text[i]=text[i];
		}
	}
	decrypted_text[strlen(text)]='\0';
}