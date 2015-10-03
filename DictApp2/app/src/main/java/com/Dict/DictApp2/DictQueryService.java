package com.Dict.DictApp2;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.Environment;
import android.os.IBinder;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.appwidget.AppWidgetManager;
import android.content.ComponentName;
import android.content.ContentResolver;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.BroadcastReceiver;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.database.Cursor;
import android.database.sqlite.SQLiteException;
import android.graphics.Bitmap;
import android.media.audiofx.AudioEffect;
import android.media.AudioManager;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;

import java.io.File;
import java.io.FileOutputStream;
import java.lang.ref.WeakReference;
import java.util.ArrayList;
import java.util.List;


public class DictQueryService extends Service {
    private DictSearchEngine mEngine  = new DictSearchEngine();
    private final IBinder mBinder = new ServiceStub(this);
    private boolean mIsFirstStart = true;
    private final String FIRST_START = "first_start";
    /*
    FIRST_START  ==> BOOLEAN
     dictionary status of last ==> list (store dictionary name)

     */
    private SharedPreferences mPreferences;

    private ArrayList<String> mAllDictionaryList;


    private int mServiceStartId ;
    private final String TAG= "DictQueryService ";

    private String DICT_ROOT_DIR = "/sdcard/";
    private final String DICT_DIR = "MiGuoDict";



    private void init(){
        mEngine.dictEngInit();
    }

    private void deInit(){
        mEngine.dictEngDeinit();
    }


    //interface
    public String queryWord(String word){
        String meaning = null;
        if(word != null){
            meaning = mEngine.dictEngQueryWord(word);
        }
        if(meaning == null){
            return "No This Word !";
        }else{
            return meaning;
        }
    }

    //interface
    public boolean addDictionary(String name){
        mAllDictionaryList = mEngine.dictEngGetDictList();
        boolean isExist = false ;
        for(String tmp :mAllDictionaryList){
            if(tmp.equals(name)){
                isExist = true;
            }
        }

        if(isExist){
            mEngine.dictEngAddDictionary(name);
        }
        return true;
    }

    //interface
    public boolean removeDictionary(String name){
        mAllDictionaryList = mEngine.dictEngGetDictList();
        boolean isExist = false ;
        for(String tmp :mAllDictionaryList){
            if(tmp.equals(name)){
                isExist = true;
            }
        }
        if(isExist){
           mEngine.dictEngRemoveDictionary(name);
        }
        return true;
    }

    //interface
    public void scanPath(String path){
        //check is there path is validatable
        if(mIsFirstStart){
            mEngine.dictEngScanPath(DICT_ROOT_DIR);
        }else{
            if(path != null){
                mEngine.dictEngScanPath(path);
            }else{
                mEngine.dictEngScanPath(DICT_ROOT_DIR);
            }
        }
    }

    //interface
    public List<String> getDictList(){

        return mEngine.dictEngGetDictList();
    }



    @Override
    public void onCreate() {
        Log.e(TAG,"##########onCreate");
        super.onCreate();
        mPreferences = getSharedPreferences("Dictionary",MODE_PRIVATE);
        mIsFirstStart  = mPreferences.getBoolean(FIRST_START,true);
        File sdCard = Environment.getExternalStorageDirectory();
        DICT_ROOT_DIR = sdCard.getAbsolutePath();
        File directory = new File (DICT_ROOT_DIR + DICT_DIR);
        directory.mkdirs();
    }

    @Override
    public void onDestroy() {
        // Check that we're not being destroyed while something is still playing.
        super.onDestroy();
    }


    class MyBinder extends Binder{
        public DictQueryService getService(){
            return DictQueryService.this;
        }
    }


    @Override
    public IBinder onBind(Intent intent) {
        Log.e(TAG,"##########onBind");
        return mBinder;
    }

    @Override
    public void onRebind(Intent intent) {
        Log.e(TAG,"##########onRebind");
        super.onRebind(intent);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.e(TAG,"##########onStartCommand");
        mServiceStartId = startId;
        if (intent != null) {
            String action = intent.getAction();
            String cmd = intent.getStringExtra("command");
        }
        return START_STICKY;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        Log.e(TAG,"##########onUnbind");
        // No active playlist, OK to stop the service right now
        stopSelf(mServiceStartId);
        return true;
    }

    static class ServiceStub extends IDictQueryService.Stub {
        private WeakReference<DictQueryService> mService;
        ServiceStub(DictQueryService inst) {
            mService = new WeakReference<DictQueryService>(inst );
        }

        @Override
        public String queryWord(String word) throws RemoteException {
            return mService.get().queryWord(word);
        }

        @Override
        public boolean addDictionary(String name) throws RemoteException {
            return mService.get().addDictionary(name);
        }

        @Override
        public boolean removeDictionary(String name) throws RemoteException {
            return mService.get().removeDictionary(name);
        }

        @Override
        public void scanPath(String path) throws RemoteException {
            mService.get().scanPath(path);
        }

        @Override
        public List<String> getDictList() throws RemoteException {
            return mService.get().getDictList();
        }
    }
}
