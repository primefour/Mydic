package com.primefour.robot;

import java.net.URLEncoder;

public class HtmlUserInput {
	//input name for identify input controller
	private String mName;
	//different function for different controller
	private String mId;
	//User input value
	private String mUserInput;
	//description
	private String mTitle;
	/*
<form action="http://www.example.com/login.php">
	 <p>Username:
		 <input type="text" name="username" size="15"
			 maxlength="30" />
	 </p>
</form>
*/
	public HtmlUserInput(String title,String name,String id){
		mTitle = title;
		mName = name;
		mId = id;
	}
	
	public String getInputId(){
		return mId;
	}
	
	public String getInputName(){
		return mName;
	}
	
	public String getTitle(){
		return mTitle;
	}
	
	public void setUserInput(String value){
		mUserInput = value;
	}
	//generate commit string
	public String getCommitString(){
			StringBuilder sb = new StringBuilder();
			sb.append(mName);
			sb.append("=");
			sb.append(mUserInput);
			return URLEncoder.encode(sb.toString());
	}
}
