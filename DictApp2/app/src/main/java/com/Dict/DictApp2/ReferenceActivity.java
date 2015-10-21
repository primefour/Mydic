package com.Dict.DictApp2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.GestureDetector;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;


public class ReferenceActivity extends Activity {
    public static String WEBVIEW_TITLE_1 = "WEBTITLE";
    final static String TAG="ReferenceActivity";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_reference);
        View v = (View) findViewById(R.id.refer_root_view);
        String title = getIntent().getStringExtra(ReferenceActivity.WEBVIEW_TITLE_1);
        setTitle(title);
    }

}
