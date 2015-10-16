package com.Dict.DictApp2;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.GestureDetector;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;


public class ReferenceActivity extends Activity {

    final static String TAG="ReferenceActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_reference);
        View v = (View) findViewById(R.id.refer_root_view);

    }

    GestureDetector.SimpleOnGestureListener sol = new GestureDetector.SimpleOnGestureListener(){
        @Override
        public final boolean onFling(final MotionEvent e1, final MotionEvent e2,
                                     final float speedX, final float speedY) {
            Log.e(TAG, "##############################onfling");
            return false;
        }
    };



}
