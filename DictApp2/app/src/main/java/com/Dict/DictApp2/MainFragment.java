package com.Dict.DictApp2;

import android.app.Activity;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
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

        // Activities containing this fragment must implement its callbacks.
        if (!(activity instanceof Callbacks)) {
            throw new IllegalStateException("Activity must implement fragment's callbacks.");
        }

        mCallbacks = (Callbacks) activity;
    }


    @Override
    public void onClick(View view) {

        /*
        if(getSearchWord() == null){
            return ;
        }
        String wordMeaning = mCallbacks.onSearchButtonClick(getSearchWord());
        if(wordMeaning == null){
            wordMeaning = NOT_FOUND_WORD;
        }*/
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
        String wordMeaning ="<html>\n" +
                "    <head>\n" +
                "    <title>My Awesome Page</title>\n" +
                "        <script type=\"text/javascript\" charset=\"utf-8\">\n" +
                "            function sayHello() {\n" +
                "                document.getElementById('foo').innerHTML = 'Hi there!';\n" +
                "            }\n" +
                "        </script>\n" +
                "    </head>\n" +
                "    <body>\n" +
                "        <h1 id=\"foo\" onclick=\"sayHello()\">Click me!</h1>\n" +
                "    </body>\n" +
                "</html>\n" ;
        //webView.loadData(wordMeaning, "text/html; charset=UTF-8", null);
        //webView.loadDataWithBaseURL("file:///mnt/sdcard/",wordMeaning, "text/html","charset=UTF-8", null);
        webView.loadDataWithBaseURL("file:///mnt/sdcard/",wordMeaning, "text/html","charset=UTF-8", null);
        //webView.loadData(wordMeaning,WEB_MIME_TYPE,WEB_ENCODE_FORMAT) ;
        //webView.loadUrl("http://news.sina.com.cn/");
    }

    public interface Callbacks {
        /**
         * Callback for when button be clicked.
         */
        public String onSearchButtonClick(String searchWord);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        mRootView = inflater.inflate(R.layout.fragment_main_page,container,false);
        Button searchButton = ((Button) mRootView.findViewById(R.id.SearchButton));
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

        return mRootView;
    }

    public String getSearchWord() {
        if(mRootView != null){
            return ((EditText) mRootView.findViewById(R.id.SearchEditText)).getText().toString();
        }
        return null;
    }

    public void setWordMeaningString(String searchResult){
        WebView webView = ((WebView) mRootView.findViewById(R.id.MeaningWebView));
        webView.getSettings().setDefaultTextEncodingName(WEB_ENCODE_FORMAT);
        //webView.loadData(searchResult,WEB_MIME_TYPE,WEB_ENCODE_FORMAT) ;
        webView.loadUrl("http://news.sina.com.cn/");
    }


}

