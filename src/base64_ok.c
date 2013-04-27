/*
原始链接
thunder://QUFmdHA6Ly9kczpkc0B4bGkuMnR1LmNjOjMxNTk0LzIwMTPHubuoL1vRuMDXz8LU2Hd3dy4ydHUuY2Ndx7m7qDAxLnJtdmJaWg==
base64解码: QUFmdHA6Ly9kczpkc0B4bGkuMnR1LmNjOjMxNTk0LzIwMTPHubuoL1vRuMDXz8LU2Hd3dy4ydHUuY2Ndx7m7qDAxLnJtdmJaWg==
解码之后
AAftp://ds:ds@xli.2tu.cc:31594/2013??w.2tu.cc]?.rmvbZZ
最终
ftp://ds:ds@xli.2tu.cc:31594/2013枪花/[迅雷下载www.2tu.cc]枪花01.rmvb
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="; 
char* base64_encode(const char* data, int data_len); 
char *base64_decode(const char* data, int data_len); 
static char find_pos(char ch); 

#define OUTLEN 255

int covert(char *desc, char *src, char *input, size_t ilen, char *output, size_t olen)
{
	char **pin = &input;
	char **pout = &output;
	iconv_t cd = iconv_open(desc, src);
	if (cd == (iconv_t)-1)
	{
		return -1;
	}
	
	memset(output, 0, olen);
	if (iconv(cd, pin, &ilen, pout, &olen)) 
	{
		iconv_close(cd);
		return -1;
	}
	iconv_close(cd);
	return 0;
}

int main(int argc, char* argv[]) 
{ 
    char *realurl = NULL;
    char *ptr = NULL;
    char *enc="QUFmdHA6Ly9kczpkc0B4bGkuMnR1LmNjOjMxNTk0LzIwMTPHubuoL1vRuMDXz8LU2Hd3dy4ydHUuY2Ndx7m7qDAxLnJtdmJaWg==";
    int len = strlen(enc); 
    char *dec = base64_decode(enc, len); 

    printf("\nSource : %s\n", enc);
	len = strlen(dec);
	char *output = (char *)malloc(OUTLEN);
	covert("UTF-8", "GBK", dec, len, output, OUTLEN);

    printf("\nDecoded : %s\noutput:%s\n", dec,output); 
	len = strlen(output);
	realurl = malloc(len);
	ptr = output;
	ptr = ptr+2;	//skip "aa"
	printf("ptr:%s\n",ptr);
	strncpy(realurl,ptr,len-4);
	realurl[len-4] = '\0';
	printf("realurl:%s\n",realurl);	
    free(output); 
	free(realurl);
    free(dec); 
    return 0; 
} 

char *base64_encode(const char* data, int data_len) 
{ 
    //int data_len = strlen(data); 
    int prepare = 0; 
    int ret_len; 
    int temp = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    char changed[4]; 
    int i = 0; 
    ret_len = data_len / 3; 
    temp = data_len % 3; 
    if (temp > 0) 
    { 
        ret_len += 1; 
    } 
    ret_len = ret_len*4 + 1; 
    ret = (char *)malloc(ret_len); 
      
    if ( ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < data_len) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(changed, '\0', 4); 
        while (temp < 3) 
        { 
            if (tmp >= data_len) 
            { 
                break; 
            } 
            prepare = ((prepare << 8) | (data[tmp] & 0xFF)); 
            tmp++; 
            temp++; 
        } 
        prepare = (prepare<<((3-temp)*8)); 
        for (i = 0; i < 4 ;i++ ) 
        { 
            if (temp < i) 
            { 
                changed[i] = 0x40; 
            } 
            else 
            { 
                changed[i] = (prepare>>((3-i)*6)) & 0x3F; 
            } 
            *f = base[changed[i]]; 
            f++; 
        } 
    } 
    *f = '\0'; 
      
    return ret; 
      
} 

static char find_pos(char ch)   
{ 
    char *ptr = (char*)strrchr(base, ch);//the last position (the only) in base[] 
    return (ptr - base); 
} 

char *base64_decode(const char *data, int data_len) 
{ 
    int ret_len = (data_len / 4) * 3; 
    int equal_count = 0; 
    char *ret = NULL; 
    char *f = NULL; 
    int tmp = 0; 
    int temp = 0; 
    char need[3]; 
    int prepare = 0; 
    int i = 0; 
    if (*(data + data_len - 1) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 2) == '=') 
    { 
        equal_count += 1; 
    } 
    if (*(data + data_len - 3) == '=') 
    {//seems impossible 
        equal_count += 1; 
    } 
    switch (equal_count) 
    { 
    case 0: 
        ret_len += 4;	//3 + 1 [1 for NULL] 
        break; 
    case 1: 
        ret_len += 4;	//Ceil((6*3)/8)+1 
        break; 
    case 2: 
        ret_len += 3;	//Ceil((6*2)/8)+1 
        break; 
    case 3: 
        ret_len += 2;	//Ceil((6*1)/8)+1 
        break; 
    } 
    ret = (char *)malloc(ret_len); 
    if (ret == NULL) 
    { 
        printf("No enough memory.\n"); 
        exit(0); 
    } 
    memset(ret, 0, ret_len); 
    f = ret; 
    while (tmp < (data_len - equal_count)) 
    { 
        temp = 0; 
        prepare = 0; 
        memset(need, 0, 4); 
        while (temp < 4) 
        { 
            if (tmp >= (data_len - equal_count)) 
            { 
                break; 
            } 
            prepare = (prepare << 6) | (find_pos(data[tmp])); 
            temp++; 
            tmp++; 
        } 
        prepare = prepare << ((4-temp) * 6); 
        for (i=0; i<3 ;i++ ) 
        { 
            if (i == temp) 
            { 
                break; 
            } 
            *f = (char)((prepare>>((2-i)*8)) & 0xFF); 
            f++; 
        } 
    } 
    *f = '\0'; 
    return ret; 
}
