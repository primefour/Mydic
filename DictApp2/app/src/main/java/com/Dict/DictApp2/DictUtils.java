package com.Dict.DictApp2;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.util.Log;

import java.util.HashMap;

/**
 * Created by crazyhorse on 15-10-3.
 */
public class DictUtils {
    private static final String TAG = "DictUtils";
    private static HashMap<Context,ServiceBinder> mBinderMap = new HashMap<Context,ServiceBinder>() ;
    private static IDictQueryService sService = null;

    public static IDictQueryService getService(){
        return sService ;
    }


    private static class ServiceBinder implements ServiceConnection {
        ServiceConnection mCallback;

        ServiceBinder(ServiceConnection callback){
            mCallback = callback ;
        }
        public void onServiceConnected(ComponentName className, android.os.IBinder binder){
            Log.e(TAG, "onServiceConnected");
            sService = IDictQueryService.Stub.asInterface(binder);
            if(mCallback != null){
                mCallback.onServiceConnected(className,binder);
            }
        }

        public void onServiceDisconnected(ComponentName className){
            Log.e(TAG,"onServiceDisconnected");
            if(mCallback != null){
                mCallback.onServiceDisconnected(className);
            }
            sService = null;
        }
    }


    public static  void bindToService(Context context){
        ServiceBinder  sb = new ServiceBinder(null);
        Intent ii = new Intent(context,DictQueryService.class);
        context.startService(new Intent(context, DictQueryService.class));
        if(context.bindService(ii,sb,0)){
            mBinderMap.put(context,sb);
        }
    }

    public static void unBindFromService(Context context){
        context.unbindService(mBinderMap.get(context));
        mBinderMap.remove(context);
        if(mBinderMap.isEmpty()){
            sService = null;
        }
    }

}
