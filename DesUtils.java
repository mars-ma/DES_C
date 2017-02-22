package dev.mars.utils;

import android.content.Context;

import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;

/**
 * Created by ma.xuanwei on 2017/2/20.
 */

public class DesUtils {
    static {
        System.loadLibrary("native-lib");
    }

    public String decrypt(String encryptedStr){
        if(encryptedStr==null||encryptedStr.length()==0)
            return "";
        return desDecrypt(encryptedStr);
    }

    public String encrypt(String source){
        if(source==null||source.length()==0)
            return "";
        try {
            return desEncrypt(URLDecoder.decode(source,"UTF-8"));
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return null;
    }

    public native String desDecrypt(String data);

    public native String desEncrypt(String data);
}
