package com.Dict.DictApp2;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.Environment;
import android.os.Handler;
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
import android.os.Message;
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
    private final int DICT_SCAN_COMPLETE = 0;



    private void init(){
        mEngine.dictEngInit();
    }

    private void deInit(){
        mEngine.dictEngDeinit();
    }


    private Handler mServiceHandler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            switch(msg.what){
                case DICT_SCAN_COMPLETE:
                    boolean first = mPreferences.getBoolean(FIRST_START,true);
                    SharedPreferences.Editor ed = mPreferences.edit();
                    ed.putBoolean(FIRST_START,false);
                    ArrayList<String> list =  mEngine.dictEngGetDictList();
                    if(first) {
                        for (String tmp : list) {
                            ed.putBoolean(tmp,true);
                        }
                    }else{
                        boolean flag = false;
                        for (String tmp : list) {
                            flag = mPreferences.getBoolean(tmp,true);
                            ed.putBoolean(tmp,flag);
                        }
                    }
                    ed.commit();
                    ed.apply();
                    break;
                default:
                    break;
            }
        }
    };

    public boolean getDictStatus(String name) {
        Log.e(TAG,name + " = " + mPreferences.getBoolean(name,false));
        return mPreferences.getBoolean(name,false);
    }

    public void setDictStatus(String name,boolean flag) {

        Log.e(TAG,"setDictStatus" + name + " = " +flag);
        SharedPreferences.Editor ed = mPreferences.edit();
        ed.putBoolean(name,flag);
        ed.commit();
        ed.apply();
    }

    private void  scanDisk(String path){
        scanPath(path);
        Message msg = mServiceHandler.obtainMessage(DICT_SCAN_COMPLETE);
        mServiceHandler.dispatchMessage(msg);
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
        Log.e(TAG, "##########onCreate");
        super.onCreate();
        mPreferences = getSharedPreferences("Dictionary",MODE_PRIVATE);
        mIsFirstStart  = mPreferences.getBoolean(FIRST_START,true);
        Log.e(TAG,"##########onCreate ==>" + mIsFirstStart);
        File sdCard = Environment.getExternalStorageDirectory();
        DICT_ROOT_DIR = sdCard.getAbsolutePath();
        File directory = new File (DICT_ROOT_DIR + "/" + DICT_DIR);
        Log.e(TAG,"##########onCreate ==>" + DICT_ROOT_DIR + "/" + DICT_DIR);
        directory.mkdirs();
        init();

        Thread scanner = new Thread(new Runnable() {
            @Override
            public void run() {
                scanDisk(null);
            }
        });
        scanner.start();
    }

    @Override
    public void onDestroy() {
        deInit();
        // Check that we're not being destroyed while something is still playing.
        super.onDestroy();
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
        Log.e(TAG,"##########onStartCommand startId = " + startId);
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
        //stopSelf(mServiceStartId);
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
            mService.get().scanDisk(path);
        }

        @Override
        public List<String> getDictList() throws RemoteException {
            return mService.get().getDictList();
        }
        @Override
        public boolean getDictStatus(String name){
            return mService.get().getDictStatus(name);
        }
        @Override
        public void setDictStatus(String name,boolean flag){
            mService.get().setDictStatus(name,flag);
        }
    }
}
