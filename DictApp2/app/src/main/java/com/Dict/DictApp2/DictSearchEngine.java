package com.Dict.DictApp2;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

/**
 * Created by crazyhorse on 15-4-5.
 */
public class DictSearchEngine {
    private Callbacks mAsyncDeliverCB = null;
    private static Handler mUIThreadHandler;
    private final static String CALLBACK_SEARCH_RESULT = "searchResult";



    public static native String engQueryWord(String searchWord);
    public static native void engAsyncQueryWord(String searchWord);
    public static native boolean engAddDictionary(String path);
    public static native boolean engRemoveDictionary(String path);

    public static void nativeCallback(String searchResult){
        //will run at work thread
        Bundle bundle = new Bundle();
        bundle.putString(CALLBACK_SEARCH_RESULT,searchResult);
        Message msg = Message.obtain();
        msg.setData(bundle);
        msg.setTarget(mUIThreadHandler);
        msg.sendToTarget();
    }

    public boolean addDictionary(String path){
        return false;
    }
    public boolean removeDictionary(String path){
        return false;
    }
    public String queryWord(String searchWord){
        return null;
    }

    public void asyncQueryWord(String searchWord){
        return ;
    }

    public interface Callbacks {
        /**
         * Callback for delivering the word meaning to user
         */
        public void onWordMeaningArriving(String searchResult);
    }

    public void setCallback(Callbacks cb) {

        mAsyncDeliverCB = cb;
    }


}
