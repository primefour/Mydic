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
		
		if(tag.getAttributeValue("title") != null){
			mContent += tag.getAttributeValue("title");
			System.out.println("title = " + tag.getAttributeValue("title"));
			System.out.println("mContent = " + mContent );
		}
	}
	
	public HtmlHRef(HTMLTag tag){
		mBaseURL = tag.getAttributeValue("href");
		mContent = tag.getContent();
		if(tag.getAttributeValue("title") != null){
			mContent += tag.getAttributeValue("title");
			System.out.println("title = " + tag.getAttributeValue("title"));
			System.out.println("mContent = " + mContent );
		}
	}
	
	public String getBaseUrl(){
		return mBaseURL;
	}
	
	public String getContent(){
		return mContent;
	}
	
	public void updateContent(String a){
		StringBuilder sb = new StringBuilder();
		if(mContent != null){
			sb.append(mContent); 
		}
		if(a != null){
			sb.append(a); 
		}
		if(sb.length() != 0){
			mContent = sb.toString();
		}
//		System.out.println("updateContent " + mContent);
	}
	
	public String toString(){
		return mBaseURL + "==>" + mContent;
	}
}
