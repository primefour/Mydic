package com.Dict.DictApp2;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

/**
 * Created by crazyhorse on 15-4-5.
 */
public class DictSearchEngine {
    private static Callbacks mAsyncDeliverCB = null;
    private static final int MESSAGE_MEANING_ARRIVING = 0;
    private static final int MESSAGE_META_ARRIVING = 1;

    private static Handler mUIThreadHandler  = new Handler(){
        @Override
        public void handleMessage(Message msg){
            switch(msg.what){
                case MESSAGE_MEANING_ARRIVING:
                    if(mAsyncDeliverCB != null){
                        String word = msg.getData().getString(CALLBACK_SEARCH_RESULT);
                        mAsyncDeliverCB.onWordMeaningArriving(word);
                    }
                    break;
                case MESSAGE_META_ARRIVING:
                    if(mAsyncDeliverCB != null){
                        String word = msg.getData().getString(CALLBACK_SEARCH_RESULT);
                        mAsyncDeliverCB.onWordMetaArriving(null);
                    }

                default:
                    break;
            }
        }

    };

    private final static String CALLBACK_SEARCH_RESULT = "searchResult";



    public static native String engQueryWord(String searchWord);
    public static native void engAsyncQueryWord(String searchWord);
    public static native boolean engAddDictionary(String path);
    public static native boolean engRemoveDictionary(String path);
    public static native void initEng();
    public static native void destroyEng();

    public static void nativeCallback(TextMetaData searchResult){
        //will run at work thread
        Bundle bundle = new Bundle();
       // bundle.putString(CALLBACK_SEARCH_RESULT,searchResult);
       // Message msg = mUIThreadHandler.obtainMessage(MESSAGE_MEANING_ARRIVING);
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
        public void onWordMetaArriving(TextMetaData mt);
    }

    public void setCallback(Callbacks cb) {

        mAsyncDeliverCB = cb;
    }

    static {
        System.loadLibrary("searchEngine");
    }

}
