package com.primefour.robot;

public class HtmlHRef {
	private String mBaseURL;
	private String mContent;
	
	public HtmlHRef(String url,String content){
		mBaseURL = url ;
		mContent = content;
	}
	
	public HtmlHRef(String baseUrl,String path,String content){
		mBaseURL = baseUrl + path;
		mContent = content;
	}
	
	public HtmlHRef(String baseUrl,HTMLTag tag){
		if(baseUrl == null){
			mBaseURL = tag.getAttributeValue("href");
		}else{
			mBaseURL = baseUrl + tag.getAttributeValue("href");
		}
		mContent = tag.getContent();
	}
	
	public HtmlHRef(HTMLTag tag){
		mBaseURL = tag.getAttributeValue("href");
		mContent = tag.getContent();
	}
	
	public String getBaseUrl(){
		return mBaseURL;
	}
	
	public String getContent(){
		return mContent;
	}
}
