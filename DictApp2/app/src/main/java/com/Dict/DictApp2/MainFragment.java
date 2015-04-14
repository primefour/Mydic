package com.Dict.DictApp2;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;


/**
 * Created by crazyhorse on 15-4-4.
 */
public class MainFragment extends Fragment implements View.OnClickListener {
    private View mRootView = null;
    private Callbacks mCallbacks = null;
    private final String WEB_ENCODE_FORMAT = "utf-8";
    private final String WEB_MIME_TYPE = "text/html";
    private final String NOT_FOUND_WORD = "Hello World!";

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);

        // Activities containing this fragment must implement its callbacks.
        if (!(activity instanceof Callbacks)) {
            throw new IllegalStateException("Activity must implement fragment's callbacks.");
        }

        mCallbacks = (Callbacks) activity;
    }


    @Override
    public void onClick(View view) {

        if(getSearchWord() == null){
            return ;
        }
        String wordMeaning = mCallbacks.onSearchButtonClick(getSearchWord());
        if(wordMeaning == null){
            wordMeaning = NOT_FOUND_WORD;
        }
        //show word Meaning
        WebView webView = ((WebView) mRootView.findViewById(R.id.MeaningWebView));
        webView.getSettings().setDefaultTextEncodingName(WEB_ENCODE_FORMAT);
        webView.loadData(wordMeaning, "text/html; charset=UTF-8", null);
        //webView.loadData(wordMeaning,WEB_MIME_TYPE,WEB_ENCODE_FORMAT) ;
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
        webView.loadData(searchResult,WEB_MIME_TYPE,WEB_ENCODE_FORMAT) ;
    }


}

