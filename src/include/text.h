#ifndef _TEXT_H
#define _TEXT_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
unsigned char text_contains(char**str,char*instance);
void text_set(char**str,char*value){
    *str=(char*)malloc(strlen(value)+1);
    if(*str==NULL){
        fprintf(stderr,"\n%s: alocação falhou",value);
        return;
    }
    strcpy(*str,value);
}
void text_add(char**str,char*value){
    size_t aux_len=strlen(*str)+strlen(value);
    *str=(char*)realloc(*str,aux_len+1);
    if(*str==NULL){
        fprintf(stderr,"\n%s: realloc falhou",value);
        return;
    }
    strcat(*str,value);
}
void text_addChar(char**str,char c){
    size_t aux_len=strlen(*str)+1;
    *str=(char*)realloc(*str,aux_len+1);
    if(*str==NULL){
        fprintf(stderr,"\n%c: realloc falhou",c);
        return;
    }
    char*added=(char*)malloc(2);
    if(added==NULL){
        fprintf(stderr,"\nmalloc(2) falhou");
        return;
    }
    added[0]=c;added[1]='\0';
    strcat(*str,added);
}
void text_prependChar(char**str,char c){
    char*aux=(char*)malloc(strlen(*str)+2);
    if(aux==NULL){
        fprintf(stderr,"\nalocação falhou");
        return;
    }
    aux[0]=c;aux[1]='\0';
    strcat(aux,*str);
    *str=(char*)realloc(*str,strlen(*str)+2);
    if(*str==NULL){
        fprintf(stderr,"\nrealloc falhou");
        return;
    }
    strcpy(*str,aux);
}
void text_prepend(char**str,char*value){
    size_t aux_len=strlen(*str)+strlen(value);
    char*aux=(char*)malloc(aux_len+1);
    if(aux==NULL){
        fprintf(stderr,"\nmalloc falhou");
        return;
    }
    strcpy(aux,value);
    strcat(aux,*str);
    *str=(char*)realloc(*str,aux_len+1);
    if(*str==NULL){
        fprintf(stderr,"\nrealloc falhou");
        return;
    }
    strcpy(*str,aux);
}
unsigned char text_equals(char**str,char*value){
    return strcmp(*str,value)==0;
}
long int text_indexOf(char**str,char*instance){
    char*result=strstr(*str,instance);
    return result-*str;
}
void text_substring(char**str,char**receive,size_t index1,size_t index2){
    text_set(receive,"");
    size_t i;
    for(i=index1;i<index2;i++){
        text_addChar(receive,((unsigned char*)*str)[i]);
    }
}
void text_replace(char**str,char*pattern,char*substitute){
    size_t index1=text_indexOf(str,pattern);
    size_t index2=index1+strlen(pattern);
    char*first,*second;text_substring(str,&first,0,index1);
    text_substring(str,&second,index2,strlen(*str));
    text_set(str,"");text_add(str,first);text_add(str,substitute);text_add(str,second);
}
void text_replaceAll(char**str,char*pattern,char*substitute){
    size_t pattern_len = strlen(pattern);
    size_t substitute_len = strlen(substitute);
    size_t str_len = strlen(*str);

    char*result=(char*)malloc(1);
    if(result==NULL){
        fprintf(stderr,"\nmalloc(1) falhou");
        return;
    }
    result[0]='\0';
    size_t result_len=0;
    char*current=*str;
    char*match;

    while((match=strstr(current,pattern))!=NULL){
        size_t prefix_len=match-current;
        result=(char*)realloc(result,result_len+prefix_len+1);
        if(result==NULL){
            fprintf(stderr,"\nrealloc falhou");
            return;
        }
        strncat(result,current,prefix_len);
        result_len+=prefix_len;
        result=(char*)realloc(result,result_len+substitute_len+1);
        if(result==NULL){
            fprintf(stderr,"\nrealloc falhou");
        }
        strcat(result,substitute);
        result_len+=substitute_len;
        current=match+pattern_len;
    }
    size_t remaining_len=strlen(current);
    result=(char*)realloc(result,result_len+remaining_len+1);
    if(result==NULL){
        fprintf(stderr,"\nrealloc falhou");
        return;
    }
    strcat(result,current);
    text_set(str,result);
}
void text_trim(char**str){
    size_t i;char*aux,*aux2;text_set(&aux,"");text_set(&aux2,"");
    for(i=0;i<strlen(*str)&&((char*)*str)[i]==' ';i++){
    }
    for(;i<strlen(*str);i++){
        text_addChar(&aux,((unsigned char*)*str)[i]);
    }
    for(i=strlen(aux)-1;i>0 && aux[i]==' ';i--){
    }
    for(;i>0;i--){
        text_prependChar(&aux2,aux[i]);
    }
    text_prependChar(&aux2,aux[0]);
    text_set(str,aux2);
}
void text_toUpperCase(char**str){
    char*s=*str;
    while(*s){
        *s=toupper((unsigned char)*s);
        s++;
    }
}
void text_toLowerCase(char**str){
    char*s=*str;
    while(*s){
        *s=tolower((unsigned char)*s);
        s++;
    }
}
unsigned char text_contains(char**str,char*instance){
    return strstr(*str,instance)!=NULL;
}
size_t text_numberOf(char**str,char*pattern){
    char*aux;text_set(&aux,*str);
    size_t count;
    for(count=0;text_contains(&aux,pattern);count++){
        text_replace(&aux,pattern,"");
    }
    return count;
}
char**text_split(char**str,char*pattern){
    size_t len=0;
    char**res=(char**)malloc(sizeof(char*)*1);
    long int index=text_indexOf(str,pattern);
    char*front,*front2,*back;
    text_set(&front,*str);text_set(&front2,"");
    text_set(&back,"");
    while(index>=0){
        text_substring(&front,&back,0,index);
        text_substring(&front,&front2,index+strlen(pattern),strlen(front));
        text_set(&front,front2);
        len++;
        res=(char**)realloc(res,sizeof(char*)*(len+1));
        text_set(&res[len-1],back);
        index=text_indexOf(&front,pattern);
    }
    len++;
    res=(char**)realloc(res,sizeof(char*)*(len+1));
    text_replaceAll(&front,pattern,"");
    text_set(&res[len-1],front);
    return res;
}
#endif
