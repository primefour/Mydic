package com.Dict.DictApp2;

/**
 * Created by crazyhorse on 15-4-5.
 */
public class DictSearchEngine {
    Callbacks mAsyncDeliverCB = null;
    //public
    public boolean addDictionary(String path){
        return false;
    }
    public boolean removeDictionary(String path){
        return false;
    }
    public String queryWord(String searchWord){
        return null;
    }

    public String asyncQueryWord(String searchWord){

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
