package com.primefour.robot;

import java.util.ArrayList;
import java.util.Iterator;

public class HtmlFormRequest {
	private String mBaseUri;
	private String mReqMethod;
	private String mName;
	private String mId ;
	private ArrayList<HtmlSelectOption> mSelectOptionList;
	private ArrayList<HtmlUserInput> mUserInputList;
	
	public HtmlFormRequest(String uri,String method,String name,String id){
		mName = name;
		mId = id;
		mReqMethod = method;
		if(mReqMethod == null){
			mReqMethod = "get" ;
		}
		mBaseUri = uri;
		mSelectOptionList = new ArrayList<HtmlSelectOption>();
		mUserInputList = new ArrayList<HtmlUserInput>();
	}
	
	
	public void insertSelectInput(HtmlSelectOption so){
		mSelectOptionList.add(so);
	}
	
	public void insertUserInput(HtmlUserInput si){
		mUserInputList.add(si);
	}
	
	public String getBaseUri(){
		return mBaseUri;
	}
	
	public HtmlSelectOption getSelectByName(String name){
			Iterator<HtmlSelectOption> hi = mSelectOptionList.iterator();
			while(hi.hasNext()){
				HtmlSelectOption hso = hi.next();
				if(hso.getName().equalsIgnoreCase(name)){
					return hso;
				}
			}
			return null;
	}
	
	public HtmlUserInput getInputByName(String name){
			Iterator<HtmlUserInput> hu = mUserInputList.iterator();
			while(hu.hasNext()){
				HtmlUserInput hui = hu.next();
				if(hui.getInputName().equalsIgnoreCase(name)){
					return hui;
				}
			}
			return null;
	}
	
	public String getHtmlReqStr(){
		StringBuilder sb = new StringBuilder();
		if("get".equals(mReqMethod.toLowerCase())){
			sb.append(mBaseUri);
			sb.append("?");
			Iterator<HtmlSelectOption> hi = mSelectOptionList.iterator();
			while(hi.hasNext()){
				HtmlSelectOption hso = hi.next();
				sb.append(hso.getCommitString());
				sb.append('&');
			}
			
			Iterator<HtmlUserInput> hu = mUserInputList.iterator();
			while(hu.hasNext()){
				HtmlUserInput hui = hu.next();
				sb.append(hui.getCommitString());
				sb.append('&');
			}
			sb.setCharAt(sb.length(), '\0');
			return sb.toString();
		}else{
			sb.append("?");
			Iterator<HtmlSelectOption> hi = mSelectOptionList.iterator();
			while(hi.hasNext()){
				HtmlSelectOption hso = hi.next();
				sb.append(hso.getCommitString());
				sb.append('&');
			}
			
			Iterator<HtmlUserInput> hu = mUserInputList.iterator();
			while(hu.hasNext()){
				HtmlUserInput hui = hu.next();
				sb.append(hui.getCommitString());
				sb.append('&');
			}
			sb.setCharAt(sb.length(), '\0');
			return sb.toString();
		}
	}
}
