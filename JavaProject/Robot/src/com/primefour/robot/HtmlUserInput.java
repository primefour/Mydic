package com.primefour.robot;

public class HtmlUserInput {
	private String mBaseUrl;
	private String mHtmlMethed;
	private String mTitle;
	private String mId;
	private String mUserInput;
	
	public HtmlUserInput(String Url,String methed,String title,String id){
		mBaseUrl = Url;
		mHtmlMethed = methed;
		mTitle = title;
		mId = id;
	}
	
	public void setUserInput(String value){
		mUserInput = value;
	}
	//according to methed to generate Url
	public String getCommitUrl(){
		return null;
	}
}
