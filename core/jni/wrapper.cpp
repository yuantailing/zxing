#include <cstdint>
#include <jni.h>

#include "qrdecoder/qr.hpp"

using namespace std;


static inline size_t _b2i(string const& s) {
    size_t x = 0;
    for (char c : s) {
        x = (x * 2) + c - '0';
    }
    return x;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_google_zxing_qrcode_decoder_Decoder_nativeCorrect( JNIEnv* env, jobject job, jint version, jint ecl, jbyteArray array )
{
    int8_t *ptr = env->GetByteArrayElements(array, NULL);
    size_t length = env->GetArrayLength(array);
    vector<int> codewords(length);
    for (size_t i = 0; i < length; i++)
        codewords[i] = ((int)ptr[i] + 256) % 256;
    env->ReleaseByteArrayElements(array, ptr, 0);

    string code;
    try {
        code = qr_codewords_to_code((size_t)version, (size_t)ecl, codewords, { 3, true, 4 });
    } catch (...) { }

    vector<int8_t> code_bytes;
    for (size_t i = 0; i + 8 <= code.length(); i += 8)
        code_bytes.push_back((int8_t)(uint8_t)_b2i(code.substr(i, 8)));
    jbyteArray ret = env->NewByteArray(code_bytes.size());
    env->SetByteArrayRegion(ret, 0, code_bytes.size(), code_bytes.data());
    return ret;
}
