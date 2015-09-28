package com.Dict.DictApp2;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

/**
 * Created by crazyhorse on 15-4-5.
 */
public class DictSearchEngine {
    private final static String CALLBACK_SEARCH_RESULT = "searchResult";

    public static native String dictEngQueryWord(String word);
    public static native boolean dictEngAddDictionary(String name);
    public static native boolean dictEngRemoveDictionary(String name);
    public static native void dictEngScanPath(String path);
    public static native void dictEngInit();
    public static native void dictEngDeinit();

    static {
        System.loadLibrary("searchEngine");
    }

}
