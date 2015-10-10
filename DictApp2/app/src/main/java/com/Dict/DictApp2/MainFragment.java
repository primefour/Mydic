package com.Dict.DictApp2;

import android.app.Activity;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AnimationUtils;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;


/**
 * Created by crazyhorse on 15-4-4.
 */
public class MainFragment extends Fragment implements View.OnClickListener {
    public static final int DISK_SCAN_CHECKER = 0;
    private View mRootView = null;
    private Callbacks mCallbacks = null;
    private final String WEB_ENCODE_FORMAT = "utf-8";
    private final String WEB_MIME_TYPE = "text/html";
    private final String NOT_FOUND_WORD = "Hello World!";
    private final String TAG = "MainFragment";
    private Activity mMainActivity;

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        mMainActivity = activity;
        mCallbacks = (Callbacks) activity;
    }


    @Override
    public void onClick(View view) {

        if(getSearchWord() == null){
            return ;
        }
        String wordMeaning = mCallbacks.onSearchButtonClick(getSearchWord());
        //show word Meaning
        WebView webView = ((WebView) mRootView.findViewById(R.id.MeaningWebView));
        webView.getSettings().setDefaultTextEncodingName(WEB_ENCODE_FORMAT);
        webView.getSettings().setJavaScriptEnabled(true);
        webView.getSettings().setDomStorageEnabled(true);
        webView.getSettings().setAllowFileAccess(true);
        final Activity activity = mMainActivity;
        webView.setWebChromeClient(new WebChromeClient() {
            public void onProgressChanged(WebView view, int progress) {
                // Activities and WebViews measure progress with different scales.
                // The progress meter will automatically disappear when we reach 100%
                activity.setProgress(progress * 1000);
            }
        });
        webView.setWebViewClient(new WebViewClient() {
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url) {
                Log.e(TAG,"######url = " + url);
                return super.shouldOverrideUrlLoading(view,url);
                //return true;
            }

            public void onReceivedError(WebView view, int errorCode, String description, String failingUrl) {
                Toast.makeText(activity, "Oh no! " + description, Toast.LENGTH_SHORT).show();
            }

            public boolean shouldBlockMediaRequest(String url) {
                Log.e(TAG,"######url = " + url);
                return false ;
            }

            });
        webView.loadData(wordMeaning, "text/html; charset=UTF-8", null);
        //webView.loadDataWithBaseURL("file:///mnt/sdcard/",wordMeaning, "text/html","charset=UTF-8", null);
        //webView.loadDataWithBaseURL("file:///mnt/sdcard/",wordMeaning, "text/html","charset=UTF-8", null);
        //webView.loadData(wordMeaning,WEB_MIME_TYPE,WEB_ENCODE_FORMAT) ;
        //webView.loadUrl("file:///android_asset/index.html");
    }

    public interface Callbacks {
        /**
         * Callback for when button be clicked.
         */
        public String onSearchButtonClick(String searchWord);
    }

    View mProgressContainer;
    View mMainContainer;
    boolean mListShown = false;

    void makeListShown() {
        if (!mListShown) {
            mListShown = true;
            mProgressContainer.startAnimation(AnimationUtils.loadAnimation(getActivity(), android.R.anim.fade_out));
            mProgressContainer.setVisibility(View.GONE);
            mMainContainer.startAnimation(AnimationUtils.loadAnimation(getActivity(), android.R.anim.fade_in));
            mMainContainer.setVisibility(View.VISIBLE);
        }
    }

    Handler Myhandler = new Handler(){

        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case DISK_SCAN_CHECKER:
                    Log.e(TAG,"############DISK_SCAN_CHECKER##########");
                    if(DictUtils.getService() != null){
                        Log.e(TAG, "############setActivateOnItemClick");
                        try {
                            Log.e(TAG,"DictUtils.getService().checkDiskScanComplete() " + DictUtils.getService().checkDiskScanComplete());
                            if(DictUtils.getService().checkDiskScanComplete()){
                                makeListShown();
                            }else{
                                Message msg1 = Myhandler.obtainMessage(DISK_SCAN_CHECKER) ;
                                Myhandler.sendMessageDelayed(msg1, 1000);
                            }
                        } catch (RemoteException e) {
                            e.printStackTrace();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    };


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        mRootView = inflater.inflate(R.layout.fragment_main_page,container,false);
        Button searchButton = ((Button) mRootView.findViewById(R.id.SearchButton));
        mProgressContainer = mRootView .findViewById(R.id.mainProgressContainer);
        mMainContainer = mRootView.findViewById(R.id.mainLinearLayout);

        searchButton.setOnClickListener(this);
        //show word Meaning
        WebView mWebView = ((WebView) mRootView.findViewById(R.id.MeaningWebView));
        mWebView.setWebViewClient(new WebViewClient(){
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url) {
                Log.e(TAG,"######url = " + url);
                return super.shouldOverrideUrlLoading(view,url);
                //return true;
            }

        });

        Message msg1 = Myhandler.obtainMessage(DISK_SCAN_CHECKER) ;
        Myhandler.sendMessageDelayed(msg1,1000);

        return mRootView;
    }

    public String getSearchWord() {
        if(mRootView != null){
            return ((EditText) mRootView.findViewById(R.id.SearchEditText)).getText().toString();
        }
        return null;
    }
}

