/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <android/log.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *
 */

//jstring thirdFlag();
bool a9='a';
bool a1='b';
bool a3='c';
bool a6='d';
bool b2='e';
bool b7='f';
bool g8='g';
JNIEXPORT jstring JNICALL
Java_pt_oposec_ctfzadas_MainActivity_stringFromJNI(JNIEnv *env,
                                                   jobject thiz) {
#if defined(__arm__)
#if defined(__ARM_ARCH_7A__)
#if defined(__ARM_NEON__)
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a/NEON (hard-float)"
#else
#define ABI "armeabi-v7a/NEON"
#endif
#else
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a (hard-float)"
#else
#define ABI "armeabi-v7a"
#endif
#endif
#else
#define ABI "armeabi"
#endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif

    return (*env)->NewStringUTF(env, "IGNORE THIS " ABI ".");
}


JNIEnv *envzadas;
jstring tres_out;
void jump_not_here (void) {
    tres_out = (*envzadas)->NewStringUTF(envzadas, "This_is_not_the_flag");
}

void jump_here (void) {
    tres_out = (*envzadas)->NewStringUTF(envzadas, "{oposec}I_love_to_jump");
    //tres_out = (*envzadas)->NewStringUTF(envzadas, "This_is_the_flag");
}

jstring JNICALL
Java_pt_oposec_ctfzadas_CTFObject_thirdFlag(JNIEnv *env, jobject thiz, jbyteArray payload) {
    void (*i)() ;
    i= jump_not_here;
    envzadas=env;
    char buffer[5];//XYZW\0
    jboolean isCopy;
    jbyte* aux_payload = (*env)->GetByteArrayElements(env, payload, &isCopy);
    strcpy(buffer, aux_payload);
    i();
    return  tres_out;
}

JNIEXPORT jstring JNICALL
Java_pt_oposec_ctfzadas_CTFObject_secondFlag(JNIEnv *env, jobject thiz, jstring key) {
    const char *aux_key = (*env)->GetStringUTFChars(env, key, 0);

    char str[] = "H^C\\DVRNJXFnT\\ClE[VhCX]";


    int len_str = strlen(str);
    int len_aux = strlen(aux_key);
    int y=0,i=0;

    char *output= malloc(sizeof(char) * (len_str + 1));

    while (true){

        char temp = str[i] ^ aux_key[y];

        if (temp >= 0x20 && temp <= 0x7e){
            output[i] = temp;
        }
        else{
            output[i] = 0x41;
        }

        i++;
        y++;

        if (y>=len_aux){
            y=0;
        }
        if (i>=len_str){
            break;
        }
    }

    output[len_str]=0x0;


    return (*env)->NewStringUTF(env, output);

}

JNIEXPORT jstring JNICALL
Java_pt_oposec_ctfzadas_CTFObject_firstFlag(JNIEnv *env, jobject thiz) {
    const char *aux_key = "abcd";
    char str[]="ABCDEFGHIABCDEFGHII";
    int y=0,i=0;
    int len_aux = strlen(aux_key);
    int len_str = strlen(str);
    char *output= malloc(sizeof(char) * (len_str + 1));
    str[0]+=str[1];
    str[1]+=str[2];
    str[2]+=str[3];
    str[4]+=str[5];
    str[6]+=str[7];
    str[7]+=str[8];
    str[8]+=str[9];
    str[9]+=str[10];



    while (true){

        char temp = str[i] ^ aux_key[y];

            output[i] = temp;

        i++;
        y++;

        if (y>=len_aux){
            y=0;
        }
        if (i>=len_str){
            break;
        }
    }
    output[len_str]=0x0;
    output[0]-=0x67;
    char cc = 0x3c;
    output[1]-=0x78;
    output[2]-=0x74;
    output[3]+='O';
    output[4]-=0x77;
    output[5]+='A';
    output[6]-=0x89;
    char dd = 0xAA;
    dd=0xBB;
    dd=dd>>3;
    output[7]-=0x78;
    output[8]-=0x97;
    output[9]-=0x79;
    output[10]+='H';
    output[11]+='L';
    output[12]+=':';
    char aa= 0x28;
    output[13]+=(aa<<1);
    output[14]+=0x3c;
    output[15]+=(aa<<1);
    output[16]+=0x36;
    output[17]+=0x3a;
    output[18]+=0x50;
    output[19]=0x0;

    return (*env)->NewStringUTF(env, output);
}