package com.Dict.DictApp2;

import android.app.Activity;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.support.v4.app.Fragment;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AnimationUtils;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.webkit.WebChromeClient;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;


/**
 * Created by crazyhorse on 15-4-4.
 */
public class MainFragment extends Fragment implements View.OnClickListener {
    public static final int DISK_SCAN_CHECKER = 0;
    private View mRootView = null;
    private WebView mWebView ;
    private EditText mEditText;
    private Button mButton;
    private ClipboardManager mClipboard;
    private Callbacks mCallbacks = null;
    private final String WEB_ENCODE_FORMAT = "utf-8";
    private final String WEB_MIME_TYPE = "text/html";
    private final String NOT_FOUND_WORD = "Hello World!";
    private final String TAG = "MainFragment";
    private String mClipWord = null;
    private boolean mClipChange = false;
    ClipboardManager.OnPrimaryClipChangedListener mClipListener = new ClipboardManager.OnPrimaryClipChangedListener(){
        @Override
        public void onPrimaryClipChanged() {
            // TODO Auto-generated method stub
            //Toast.makeText(getActivity(), "TEXT IS COPIED!!! :", Toast.LENGTH_SHORT).show();
            mClipChange = true;
        }
    };

    @Override
    public void onAttach(Activity activity) {
        Log.e(TAG, "onAttach #########################");
        super.onAttach(activity);
        mCallbacks = (Callbacks) activity;
        mClipboard = (ClipboardManager)getActivity().getSystemService(getActivity().CLIPBOARD_SERVICE);
        //Add listener to listen clipboard changes
        mClipboard.addPrimaryClipChangedListener( mClipListener);
    }

    @Override
    public void onDetach(){
        Log.e(TAG,"onAttach #########################");
        mClipboard.removePrimaryClipChangedListener(mClipListener);
        super.onDestroy();
    }

    @Override
    public void onStart() {
        super.onStart();
        Log.e(TAG,"onStart #############################");
    }
    @Override
    public void onPause() {
        super.onPause();
        /*
        ((InputMethodManager)getActivity().getSystemService(getActivity().INPUT_METHOD_SERVICE)).hideSoftInputFromWindow(
                getActivity().getCurrentFocus().getWindowToken(), InputMethodManager.HIDE_NOT_ALWAYS);
                */
        Log.e(TAG,"###########onPause");
    }
    @Override
    public void onResume() {
        if(mEditText != null && mClipboard != null && DictUtils.getService() != null) {
            onClick(null);
        }
        super.onResume();
        Log.e(TAG,"###############onResume ");
    }


        /**
         * Called when the Fragment is no longer started.  This is generally
         * tied to {@link Activity#onStop() Activity.onStop} of the containing
         * Activity's lifecycle.
         */
    @Override
    public void onStop() {
        Log.e(TAG,"###########onStop");
        super.onStop();
    }

    private boolean isWordFormat(String tt){
        if(tt.length() > 50){
            return false;
        }
        return true;
    }

    private void queryWord(){
        String word = getSearchWord();
        if (word == null || word.length() == 0) {
            ClipData clip = mClipboard.getPrimaryClip();
            ClipData.Item item = clip.getItemAt(0);
            word = item.getText().toString();
            Log.e(TAG, "mClipboard word is  " + word);
            if (word == null || word.length() == 0 || !isWordFormat(word)) {
                return;
            }
            mEditText.setText(word);
        }

        String wordMeaning = mCallbacks.onSearchButtonClick(word.toLowerCase());
        //show word Meaning
        mWebView.loadData(wordMeaning, "text/html; charset=UTF-8", null);
        mWebView.reload();
    }




    @Override
    public void onClick(View view) {
        queryWord();
        /*
        String word = getSearchWord();
        if (word == null || word.length() == 0) {
            ClipData clip = mClipboard.getPrimaryClip();
            ClipData.Item item = clip.getItemAt(0);
            word = item.getText().toString();
            Log.e(TAG, "mClipboard word is  " + word);
            if (word == null || word.length() == 0 || !isWordFormat(word)) {
                return;
            }
            mEditText.setText(word);
        }

        String wordMeaning = mCallbacks.onSearchButtonClick(word.toLowerCase());
        //show word Meaning
        mWebView.loadData(wordMeaning, "text/html; charset=UTF-8", null);
        mWebView.reload();
        //webView.loadDataWithBaseURL("file:///mnt/sdcard/",wordMeaning, "text/html","charset=UTF-8", null);
        //webView.loadDataWithBaseURL("file:///mnt/sdcard/",wordMeaning, "text/html","charset=UTF-8", null);
        //webView.loadData(wordMeaning,WEB_MIME_TYPE,WEB_ENCODE_FORMAT) ;
        //webView.loadUrl("file:///android_asset/index.html");
        */
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
            mEditText.setEnabled(true);
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
                                queryWord();
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

    TextWatcher mTextWatcher  = new TextWatcher() {
        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {
// TODO Auto-generated method stub
        }
        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) {
// TODO Auto-generated method stub
        }
        @Override
        public void afterTextChanged(Editable s) {
            if(mEditText.getText().toString()!=null&&!mEditText.getText().toString().equals("")){
                mButton.setVisibility(View.VISIBLE);
            }else{
                mButton.setVisibility(View.INVISIBLE);
            }
        }
    };



    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        mRootView = inflater.inflate(R.layout.fragment_main_page,container,false);
        //Button searchButton = ((Button) mRootView.findViewById(R.id.SearchButton));
        mProgressContainer = mRootView .findViewById(R.id.mainProgressContainer);
        mMainContainer = mRootView.findViewById(R.id.mainLinearLayout);
        mEditText =(EditText)mRootView.findViewById(R.id.SearchEditText);

        mEditText.setOnEditorActionListener(new EditText.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                Log.i(TAG, "onEditorAction ----------- actionId:" + actionId);
                if (actionId == EditorInfo.IME_ACTION_SEARCH) {
                    InputMethodManager imm = (InputMethodManager)v.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(v.getWindowToken(), 0);
                    queryWord();
                }
                return false;
            }

        });
        mEditText.addTextChangedListener(mTextWatcher);
        mEditText.setEnabled(false);
        mButton = (Button) mRootView.findViewById(R.id.clear_button);

        mButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mEditText.setText("");
                Log.e(TAG,"mClipChangel ====" + mClipChange);
                if(mClipChange){
                    mClipChange = false;
                    queryWord();
                }
            }
        });

        //searchButton.setOnClickListener(this);
        //show word Meaning
        mWebView = ((WebView) mRootView.findViewById(R.id.MeaningWebView));
        mWebView.getSettings().setDefaultTextEncodingName(WEB_ENCODE_FORMAT);
        mWebView.getSettings().setJavaScriptEnabled(true);
        mWebView.getSettings().setDomStorageEnabled(true);
        mWebView.getSettings().setAllowFileAccess(true);
        mWebView.setWebViewClient(new WebViewClient() {
            @Override
            public boolean shouldOverrideUrlLoading(WebView view, String url) {
                Log.e(TAG, "######url = " + url);
                try {
                    URI tmp = new URI(url);
                    String scheme = tmp.getScheme();
                    if(scheme.equalsIgnoreCase("bword")){
                        ClipData clip;
                        String text = tmp.getHost();
                        Log.e(TAG,"##############txt = " + text);
                        clip= ClipData.newPlainText("text", text);
                        mClipboard.setPrimaryClip(clip);
                        mEditText.setText("");
                        mClipChange = true;
                        queryWord();
                        return true;
                    }
                } catch (URISyntaxException e) {
                    e.printStackTrace();
                }
                return super.shouldOverrideUrlLoading(view,url);
                //return true;
            }

            public void onReceivedError(WebView view, int errorCode, String description, String failingUrl) {
                Toast.makeText(getActivity(), "Oh no! " + description, Toast.LENGTH_SHORT).show();
            }

            public boolean shouldBlockMediaRequest(String url) {
                Log.e(TAG,"######url = " + url);
                return false ;
            }

        });

        Message msg1 = Myhandler.obtainMessage(DISK_SCAN_CHECKER) ;
        Myhandler.sendMessageDelayed(msg1,1000);

        return mRootView;
    }

    public String getSearchWord() {
        if(mRootView != null){
            return mEditText.getText().toString();
        }
        return null;
    }
}

