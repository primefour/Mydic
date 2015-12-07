package com.Dict.DictApp2;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;


public class DictLaunchActivity extends Activity {

    private ImageView mSkipImgView = null;
    private ImageView mADImgView = null;
    private Handler mHandler = new Handler();


    private void runSplashProcess() {
        Intent it = new Intent(DictLaunchActivity.this,DictMainActivity.class);
        startActivity(it);
        finish();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_launcher);
        mSkipImgView = (ImageView) findViewById(R.id.skip_splash);
        mADImgView = (ImageView)findViewById(R.id.ad_img);
        mSkipImgView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                runSplashProcess();
            }
        });
    }

    @Override
    protected  void onResume(){
        super.onResume();
        mHandler.postDelayed(new Runnable() {
            @Override
            public void run() {
                runSplashProcess();
            }
        },500);
    }
}
